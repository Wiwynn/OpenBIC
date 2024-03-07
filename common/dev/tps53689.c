/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <string.h>
#include <logging/log.h>
#include "libutil.h"
#include "sensor.h"
#include "hal_i2c.h"
#include "pmbus.h"
#include "util_pmbus.h"
#include "tps53689.h"

#define VR_TI_REG_CRC 0xF4

LOG_MODULE_REGISTER(tps53689);

// This feature is for parsing hex file
void tps536xx_parse_image(struct mp2856_config *dev_cfg)
{
	FILE *fp;
	char line[80];
	char *token;
	int config_data_idx = 0;
	struct tps_config *config = NULL;

	if (info == NULL || path == NULL) {
		return NULL;
	}

	fp = fopen(path, "r");
	if (!fp) {
		printf("Failed to open VR image\n");
		return NULL;
	}

	config = (struct tps_config *)calloc(1, sizeof(struct tps_config));
	if (config == NULL) {
		printf("ERROR: no space for creating config!\n");
		fclose(fp);
		return NULL;
	}

	/*
	 * Hex image format:
	 * Line 1  ":020000040000FA"
	 * Line 2  ":200000005449536C5000010076A1AE969610FFFFBFFFFFF516F69A039A0300000006CD0465"
	 * ```
	 * Line 10 ":200100000000000000000000000000000000000000000000000000000000000000000000DF"
	 * Line 11 ":00000001FF"
	 * 
	 * The information about updating is in line 1 to line 10, from the 5th byte to the 32th byte
	 * 
	 */
	while (fgets(line + 1, sizeof(line) - 1, fp) !=
	       NULL) { // Ths first character ":" is not useful, so use "+1" to skip it
		// The first and last line are not useful
		if (strlen(line) != TPS536XX_UPDATE_INFO_LENS) {
			continue;
		}

		for (int index = 0; index < TPS536XX_UPDATE_INFO_BYTES; index++) {
			char c[2];
			c[0] = line[index * 2 + TPS536XX_UPDATE_INFO_START_BYTE];
			c[1] = line[index * 2 + (TPS536XX_UPDATE_INFO_START_BYTE + 1)];

			if (config_data_idx <= 5) { //Device ID
				config->devid[config_data_idx] = strtol(c, NULL, 16);
				config->data[config_data_idx++] = 0xFF;
			} else if (config_data_idx == 8) { // address
				config->addr = strtol(c, NULL, 16);
				config->data[config_data_idx++] = 0xFF;
			} else if (config_data_idx == 9 && config_data_idx == 10) { // CRC
				config->crc[config_data_idx - 9] = strtol(c, NULL, 16);
				config->data[config_data_idx++] = 0xFF;
			} else {
				config->data[config_data_idx++] = strtol(c, NULL, 16);
			}
		}
	}

	fclose(fp);
}

bool tps536xx_get_crc(uint8_t bus, uint8_t addr, uint32_t *crc)
{
	CHECK_NULL_ARG_WITH_RETURN(crc, false);

	I2C_MSG i2c_msg = { 0 };

	uint8_t retry = 5;
	i2c_msg.bus = bus;
	i2c_msg.target_addr = addr;
	i2c_msg.tx_len = 1;
	i2c_msg.rx_len = 2;
	i2c_msg.data[0] = VR_TI_REG_CRC;

	if (i2c_master_read(&i2c_msg, retry)) {
		LOG_DBG("read register 0x%02X failed", i2c_msg.data[0]);
		return false;
	}

	*crc = (i2c_msg.data[3] << 24) | (i2c_msg.data[2] << 16) | (i2c_msg.data[1] << 8) |
	       i2c_msg.data[0];

	return true;
}

bool tps53689_fwupdate(uint8_t bus, uint8_t addr, uint8_t *img_buff, uint32_t img_size)
{
	CHECK_NULL_ARG_WITH_RETURN(img_buff, false);

	uint8_t ret = false;

	// Parse image
	struct tps_config *config = { 0 };
	if (tps536xx_parse_image(config) == false) {
		LOG_ERR("Failed to parse image!");
		goto exit;
	}

	// TODO

	for (int index = 0; index < 6; index++) {
		if (config->devid[index] != tps536c5_dev_id[index]) {
			LOG_ERR("Failed to update firmware, device ID is not matched!");
			goto exit;
		}
	}
	// TODO
	if (config->addr != ADDR) {
		LOG_ERR("Failed to update firmware, address is not matched!");
		goto exit;
	}
	// TODO
	if (config->crc[0] == CRC[0] && config->crc[1] == CRC[1]) {
		LOG_ERR("Failed to update firmware, CRC is matched!");
		goto exit;
	}

	uint8_t retry = 5;
	I2C_MSG msg;

	msg.bus = ;
	msg.target_addr = config->addr;
	msg.tx_len = 1;
	msg.rx_len = 0;

	// set USER_NVM_INDEX 00h
	msg.data[0] = TI_REG_USER_NVM_INDEX;
	msg.data[1] = 0x00;
	i2c_master_write(&msg, retry);

	// program the image
	msg.data[0] = TI_REG_USER_NVM_EXECUTE;
	int offset = 0;
	for (int index = 0; index < 9; index++) {
		memcpy(&msg.data[1], &config->data[offset], TPS536XX_UPDATE_INFO_BYTES);
		i2c_master_write(&msg, retry);
		offset += TPS536XX_UPDATE_INFO_BYTES;
	}
}

uint8_t tps53689_read(sensor_cfg *cfg, int *reading)
{
	CHECK_NULL_ARG_WITH_RETURN(cfg, SENSOR_UNSPECIFIED_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(reading, SENSOR_UNSPECIFIED_ERROR);

	if (cfg->num > SENSOR_NUM_MAX) {
		LOG_ERR("sensor num: 0x%x is invalid", cfg->num);
		return SENSOR_UNSPECIFIED_ERROR;
	}

	uint8_t retry = 5;
	sensor_val *sval = (sensor_val *)reading;
	I2C_MSG msg;
	memset(sval, 0, sizeof(sensor_val));

	msg.bus = cfg->port;
	msg.target_addr = cfg->target_addr;
	msg.tx_len = 1;
	msg.rx_len = 2;
	msg.data[0] = cfg->offset;

	if (i2c_master_read(&msg, retry))
		return SENSOR_FAIL_TO_ACCESS;

	uint8_t offset = cfg->offset;
	if (offset == PMBUS_READ_VOUT) {
		/* ULINEAR16, get exponent from VOUT_MODE */
		float exponent;
		if (!get_exponent_from_vout_mode(cfg, &exponent))
			return SENSOR_FAIL_TO_ACCESS;

		float actual_value = ((msg.data[1] << 8) | msg.data[0]) * exponent;
		sval->integer = actual_value;
		sval->fraction = (actual_value - sval->integer) * 1000;
	} else if (offset == PMBUS_READ_IOUT || offset == PMBUS_READ_IIN ||
		   offset == PMBUS_READ_TEMPERATURE_1 || offset == PMBUS_READ_POUT) {
		/* SLINEAR11 */
		uint16_t read_value = (msg.data[1] << 8) | msg.data[0];
		float actual_value = slinear11_to_float(read_value);
		sval->integer = actual_value;
		sval->fraction = (actual_value - sval->integer) * 1000;
	} else {
		return SENSOR_FAIL_TO_ACCESS;
	}

	return SENSOR_READ_SUCCESS;
}

uint8_t tps53689_init(sensor_cfg *cfg)
{
	CHECK_NULL_ARG_WITH_RETURN(cfg, SENSOR_INIT_UNSPECIFIED_ERROR);

	if (cfg->num > SENSOR_NUM_MAX) {
		return SENSOR_INIT_UNSPECIFIED_ERROR;
	}

	cfg->read = tps53689_read;
	return SENSOR_INIT_SUCCESS;
}
