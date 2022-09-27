#include <stdio.h>
#include <string.h>
#include "sensor.h"
#include "hal_i2c.h"
#include "pmbus.h"

/** Q50SN120A1 VOUT scale is exponent -12 base 2 **/
#define Q50SN120A1_VOUT_SCALE 0.000244140625

/** Q50SN120A1 IOUT/Temperature scale is exponent -2 base 2 **/
#define Q50SN120A1_IOUT_SCALE 0.25
#define Q50SN120A1_TEMPERATURE_SCALE 0.25

	int q50sn120a1_read_pout(uint8_t sensor_num, float *pout_value)
{
	if (pout_value == NULL) {
		printf("[%s] input pout value pointer is NULL\n", __func__);
		return -1;
	}

	uint8_t retry = 5;
	float vout = 0, iout = 0;
	int ret = 0;
	I2C_MSG msg = { 0 };

	msg.bus = sensor_config[sensor_config_index_map[sensor_num]].port;
	msg.target_addr = sensor_config[sensor_config_index_map[sensor_num]].target_addr;
	msg.tx_len = 1;
	msg.rx_len = 2;
	msg.data[0] = PMBUS_READ_VOUT;

	ret = i2c_master_read(&msg, retry);
	if (ret != 0) {
		printf("[%s] i2c read vout fail, ret: %d\n", __func__, ret);
		return -1;
	}
	vout = ((msg.data[1] << 8) | msg.data[0]) * Q50SN120A1_VOUT_SCALE;

	memset(&msg, 0, sizeof(msg));
	msg.bus = sensor_config[sensor_config_index_map[sensor_num]].port;
	msg.target_addr = sensor_config[sensor_config_index_map[sensor_num]].target_addr;
	msg.tx_len = 1;
	msg.rx_len = 2;
	msg.data[0] = PMBUS_READ_IOUT;

	ret = i2c_master_read(&msg, retry);
	if (ret != 0) {
		printf("[%s] i2c read iout fail, ret: %d\n", __func__, ret);
		return -1;
	}
	iout = ((msg.data[1] << 8) | msg.data[0]) * Q50SN120A1_IOUT_SCALE;

	*pout_value = vout * iout;
	return 0;
}

uint8_t q50sn120a1_read(uint8_t sensor_num, int *reading)
{
	if (reading == NULL) {
		printf("[%s] input parameter reading is NULL\n", __func__);
		return SENSOR_UNSPECIFIED_ERROR;
	}

	if (sensor_num > SENSOR_NUM_MAX) {
		printf("[%s] sensor 0x%x input parameter is invalid\n", __func__, sensor_num);
		return SENSOR_UNSPECIFIED_ERROR;
	}

	uint8_t retry = 5;
	uint8_t offset = sensor_config[sensor_config_index_map[sensor_num]].offset;
	float val = 0;
	int ret = 0;
	I2C_MSG msg = { 0 };

	msg.bus = sensor_config[sensor_config_index_map[sensor_num]].port;
	msg.target_addr = sensor_config[sensor_config_index_map[sensor_num]].target_addr;
	msg.tx_len = 1;
	msg.rx_len = 2;
	msg.data[0] = offset;

	if (offset != PMBUS_READ_POUT) {
		ret = i2c_master_read(&msg, retry);
		if (ret != 0) {
			printf("[%s] i2c read fail  ret: %d\n", __func__, ret);
			return SENSOR_FAIL_TO_ACCESS;
		}
		val = (msg.data[1] << 8) | msg.data[0];
	}

	sensor_val *sval = (sensor_val *)reading;
	switch (offset) {
	case PMBUS_READ_VOUT:
		val = val * Q50SN120A1_VOUT_SCALE;
		break;
	case PMBUS_READ_IOUT:
		val = val * Q50SN120A1_IOUT_SCALE;
		break;
	case PMBUS_READ_TEMPERATURE_1:
		val = val * Q50SN120A1_TEMPERATURE_SCALE;
		break;
	case PMBUS_READ_POUT:
		ret = q50sn120a1_read_pout(sensor_num, &val);
		if (ret != 0) {
			return SENSOR_FAIL_TO_ACCESS;
		}
		break;
	default:
		printf("[%s] not support offset: 0x%x\n", __func__, offset);
		return SENSOR_FAIL_TO_ACCESS;
		break;
	}

	sval->integer = (int)val & 0xFFFF;
	sval->fraction = (val - sval->integer) * 1000;
	return SENSOR_READ_SUCCESS;
}

uint8_t q50sn120a1_init(uint8_t sensor_num)
{
	if (sensor_num > SENSOR_NUM_MAX) {
		printf("[%s] input sensor number is invalid\n", __func__);
		return SENSOR_INIT_UNSPECIFIED_ERROR;
	}

	sensor_config[sensor_config_index_map[sensor_num]].read = q50sn120a1_read;
	return SENSOR_INIT_SUCCESS;
}
