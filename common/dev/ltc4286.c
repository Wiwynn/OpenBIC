#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sensor.h"
#include "hal_i2c.h"
#include "libutil.h"
#include "pmbus.h"

#define LTC4286_MFR_ADIN1 0xFE38
#define VRANGE_SELECT_25_6_V 0
#define VRANGE_SELECT_102_4_V 1
#define I2C_DATA_SIZE 5

uint8_t vrange_select = 0xFF;

uint8_t ltc4286_read(uint8_t sensor_num, int *reading)
{
	if ((reading == NULL) ||
	    (sensor_config[sensor_config_index_map[sensor_num]].init_args == NULL)) {
		return SENSOR_UNSPECIFIED_ERROR;
	}

	ltc4286_init_arg *init_arg =
		(ltc4286_init_arg *)sensor_config[sensor_config_index_map[sensor_num]].init_args;
	if (init_arg->is_init == false) {
		printf("[%s], device isn't initialized\n", __func__);
		return SENSOR_UNSPECIFIED_ERROR;
	}

	float rsense = init_arg->r_sense / 1000;

	uint8_t retry = 5;
	double val;
	I2C_MSG msg;

	sensor_cfg *cfg = &sensor_config[sensor_config_index_map[sensor_num]];

	msg.bus = cfg->port;
	msg.target_addr = cfg->target_addr;
	msg.tx_len = 1;
	msg.rx_len = 2;
	msg.data[0] = cfg->offset;
	if (i2c_master_read(&msg, retry)) {
		return SENSOR_FAIL_TO_ACCESS;
	}

	switch (cfg->offset) {
	case PMBUS_READ_VIN:
	case PMBUS_READ_VOUT:
		if (vrange_select == VRANGE_SELECT_25_6_V) {
			val = ((msg.data[1] << 8) | msg.data[0]) / 1280;
		} else if (vrange_select == VRANGE_SELECT_102_4_V) {
			val = ((msg.data[1] << 8) | msg.data[0]) / 320;
		} else {
			return SENSOR_UNSPECIFIED_ERROR;
		}
		break;
	case PMBUS_READ_IOUT:
		val = ((msg.data[1] << 8) | msg.data[0]) / (1024000 * rsense);
		break;
	case PMBUS_READ_TEMPERATURE_1:
		val = ((msg.data[1] << 8) | msg.data[0]) - 273;
		break;
	case PMBUS_READ_PIN:
		if (vrange_select == VRANGE_SELECT_25_6_V) {
			val = ((msg.data[1] << 8) | msg.data[0]) / (40000 * rsense);
		} else if (vrange_select == VRANGE_SELECT_102_4_V) {
			val = ((msg.data[1] << 8) | msg.data[0]) / (10000 * rsense);
		} else {
			return SENSOR_UNSPECIFIED_ERROR;
		}
		break;
	default:
		return SENSOR_NOT_FOUND;
	}

	sensor_val *sval = (sensor_val *)reading;
	memset(sval, 0, sizeof(*sval));

	sval->integer = (int32_t)val;
	sval->fraction = (int32_t)(val * 1000) % 1000;

	return SENSOR_READ_SUCCESS;
}

uint8_t ltc4286_init(uint8_t sensor_num)
{
	if (!sensor_config[sensor_config_index_map[sensor_num]].init_args) {
		printf("<error> LTC4286 init args are not provided!\n");
		return SENSOR_INIT_UNSPECIFIED_ERROR;
	}

	ltc4286_init_arg *init_args =
		(ltc4286_init_arg *)sensor_config[sensor_config_index_map[sensor_num]].init_args;
	if (init_args->is_init)
		goto skip_init;

	I2C_MSG msg;
	char *data = (uint8_t *)malloc(I2C_DATA_SIZE * sizeof(uint8_t));
	uint8_t bus = sensor_config[sensor_config_index_map[sensor_num]].port;
	uint8_t target_addr = sensor_config[sensor_config_index_map[sensor_num]].target_addr;
	uint8_t tx_len = 0, rx_len = 0;
	uint8_t retry = 5;

	// Calcute the GPIO voltage (V = MFR_ADIN1/12800)
	tx_len = 2;
	rx_len = 2;
	data[0] = LTC4286_MFR_ADIN1 & 0xFF;
	data[1] = LTC4286_MFR_ADIN1 >> 8 & 0xFF;
	msg = construct_i2c_message(bus, target_addr, tx_len, data, rx_len);
	if (i2c_master_write(&msg, retry) != 0) {
		printf("Failed to get LTC4286 register(0x%x%x)\n", data[1], data[0]);
		goto cleanup;
	}

	/* According the LTC4286 datasheet,
	 * The VRANGE SELECT is 1 if the GPIO voltage is 102.4V.
	 * And the VRANGE SELECT is 0 if the GPIO voltage is 25.6V.
	 */
	float v_gpio = ((msg.data[1] << 8) | msg.data[0]) / 12800;
	if (v_gpio == 102.4) {
		vrange_select = VRANGE_SELECT_102_4_V;
	} else if (v_gpio == 25.6) {
		vrange_select = VRANGE_SELECT_25_6_V;
	} else {
		printf("Unknown LTC4286 GPIO voltage, voltage: %fV", v_gpio);
		goto cleanup;
	}

	init_args->is_init = true;

cleanup:
	SAFE_FREE(data);

skip_init:
	sensor_config[sensor_config_index_map[sensor_num]].read = ltc4286_read;
	return SENSOR_INIT_SUCCESS;
}
