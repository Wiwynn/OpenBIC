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

#define VR_TI_REG_CRC 0xF4

LOG_MODULE_REGISTER(tps53689);

int tps53689_get_crc(uint8_t bus, uint8_t addr, uint32_t *crc)
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
