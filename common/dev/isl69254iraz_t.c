#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "sensor.h"
#include "hal_i2c.h"
#include "pmbus.h"

uint8_t isl69254iraz_t_read(uint8_t sensor_num, int *reading)
{
	if (reading == NULL) {
		printf("[%s] input parameter reading is NULL\n", __func__);
		return SENSOR_UNSPECIFIED_ERROR;
	}
	memset(reading, 0, sizeof(int));

	if (sensor_num > SENSOR_NUM_MAX) {
		printf("[%s] sensor 0x%x input parameter is invaild\n", __func__, sensor_num);
		return SENSOR_UNSPECIFIED_ERROR;
	}

	uint8_t retry = 5;
	int val = 0, ret = 0;
	I2C_MSG msg;
	memset(&msg, 0, sizeof(I2C_MSG));

	msg.bus = sensor_config[sensor_config_index_map[sensor_num]].port;
	msg.target_addr = sensor_config[sensor_config_index_map[sensor_num]].target_addr;
	msg.tx_len = 1;
	msg.rx_len = 2;
	msg.data[0] = sensor_config[sensor_config_index_map[sensor_num]].offset;

	ret = i2c_master_read(&msg, retry);
	if (ret != 0) {
		printf("[%s] i2c read fail  ret: %d\n", __func__, ret);
		return SENSOR_FAIL_TO_ACCESS;
	}

	uint8_t offset = sensor_config[sensor_config_index_map[sensor_num]].offset;
	val = (msg.data[1] << 8) | msg.data[0];
	sensor_val *sval = (sensor_val *)reading;
	if (offset == PMBUS_READ_VOUT) {
		/* 1 mV/LSB, unsigned integer */
		sval->integer = val / 1000;
		sval->fraction = val % 1000;
	} else if (offset == PMBUS_READ_IOUT) {
		/* 0.1 A/LSB, 2's complement */
		sval->integer = (int16_t)val / 10;
		sval->fraction = (int16_t)(val - (sval->integer * 10)) * 100;
	} else if (offset == PMBUS_READ_TEMPERATURE_1) {
		/* 1 Degree C/LSB, 2's complement */
		sval->integer = val;
	} else if (offset == PMBUS_READ_POUT) {
		/* 1 Watt/LSB, 2's complement */
		sval->integer = val;
	} else {
		printf("[%s] not support offset 0x%x\n", __func__, offset);
		return SENSOR_FAIL_TO_ACCESS;
	}

	return SENSOR_READ_SUCCESS;
}

uint8_t isl69254iraz_t_init(uint8_t sensor_num)
{
	if (sensor_num > SENSOR_NUM_MAX) {
		printf("[%s] input sensor number is invaild\n", __func__);
		return SENSOR_INIT_UNSPECIFIED_ERROR;
	}

	sensor_config[sensor_config_index_map[sensor_num]].read = isl69254iraz_t_read;
	return SENSOR_INIT_SUCCESS;
}
