#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libutil.h"
#include "sensor.h"
#include "hal_i2c.h"

#define I2C_DATA_SIZE 5

struct VOLTAGE_FULL_SCALE_RANGE_INFO {
	long unsigned int v_range_selection;
	float vfsout;
};

struct VOLTAGE_FULL_SCALE_RANGE_INFO FOLDBACK_MODE_TABLE[4] = {
	{ 0x0, 5.547 },  { 0x1, 8.32 },  { 0x2, 16.64 },  { 0x3, 33.28 }
};

typedef union {
	volatile uint8_t value;
	struct {
		volatile uint8_t _16_bit : 1;
		volatile uint8_t gpio_mode : 1;
		volatile uint8_t vsource_vdd : 1;
		volatile uint8_t foldback_mode : 2;
		volatile uint8_t ilim_adjust : 3;
	} fields;
} ilim_adjust_t;

ilim_adjust_t ilim_adjust;

uint8_t ltc4282_read(uint8_t sensor_num, int *reading)
{
	if ((reading == NULL) || (sensor_num > SENSOR_NUM_MAX) ||
	    (sensor_config[sensor_config_index_map[sensor_num]].init_args == NULL)) {
		return SENSOR_UNSPECIFIED_ERROR;
	}

	ltc4282_init_arg *init_arg =
		(ltc4282_init_arg *)sensor_config[sensor_config_index_map[sensor_num]].init_args;
	if (init_arg->is_init == false) {
		printf("[%s], device isn't initialized\n", __func__);
		return SENSOR_UNSPECIFIED_ERROR;
	}

	if (!init_arg->r_sense) {
		printf("%s, Rsense hasn't given\n", __func__);
		return SENSOR_UNSPECIFIED_ERROR;
	}

	float Rsense = init_arg->r_sense / 1000;
	float Vfsout;
	for(uint8_t cnt = 0; cnt <= ARRAY_SIZE(FOLDBACK_MODE_TABLE); cnt++)
	{
		if (ilim_adjust.fields.foldback_mode == FOLDBACK_MODE_TABLE[cnt].v_range_selection)
		{
			Vfsout = FOLDBACK_MODE_TABLE[cnt].vfsout;
			break;
		}
		if (cnt == ARRAY_SIZE(FOLDBACK_MODE_TABLE))
		{
			printf("[%s] Unknown voltage range, the foldback mode 0x%x\n", __func__, ilim_adjust.fields.foldback_mode);
			return SENSOR_UNSPECIFIED_ERROR;
		}
	}

	I2C_MSG msg = { 0 };
	char *data = (uint8_t *)malloc(I2C_DATA_SIZE * sizeof(uint8_t));
	uint8_t bus = sensor_config[sensor_config_index_map[sensor_num]].port;
	uint8_t target_addr = sensor_config[sensor_config_index_map[sensor_num]].target_addr;
	uint8_t offset = sensor_config[sensor_config_index_map[sensor_num]].offset;
	uint8_t tx_len = 0, rx_len = 0;
	uint8_t retry = 5, ret = SENSOR_UNSPECIFIED_ERROR;
	double val = 0;

	tx_len = 1;
	rx_len = 2;
	data[0] = offset;
	msg = construct_i2c_message(bus, target_addr, tx_len, data, rx_len);
	if (i2c_master_read(&msg, retry) != 0)
	{
		ret = SENSOR_FAIL_TO_ACCESS;
		goto cleanup;
	}

	// Refer to LTC4282 datasheet page 23.
	switch (offset) {
	case LTC4282_VSENSE_OFFSET:
		val = (((msg.data[0] << 8) | msg.data[1]) * 0.04 / 65535 / Rsense);
		break;
	case LTC4282_POWER_OFFSET:
		val = (((msg.data[0] << 8) | msg.data[1]) * Vfsout * 0.04 * 65536 / 65535 / 65535 / Rsense);
		break;
	case LTC4282_VSOURCE_OFFSET:
		val = (((msg.data[0] << 8) | msg.data[1]) * Vfsout / 65535);
		break;
	default:
		printf("[%s] Unsupported the offset 0x%x for sensor number 0x%x\n", __func__, offset, sensor_num);
		ret = SENSOR_NOT_FOUND;
		goto cleanup;
	}

	sensor_val *sval = (sensor_val *)reading;
	memset(sval, 0, sizeof(*sval));

	sval->integer = (int)val & 0xFFFF;
	sval->fraction = (val - sval->integer) * 1000;

	ret = SENSOR_READ_SUCCESS;

cleanup:
	SAFE_FREE(data);
	return ret;
}

uint8_t ltc4282_init(uint8_t sensor_num)
{
	if (sensor_num > SENSOR_NUM_MAX) {
		return SENSOR_INIT_UNSPECIFIED_ERROR;
	}

	I2C_MSG msg;
	char *data = (uint8_t *)malloc(I2C_DATA_SIZE * sizeof(uint8_t));
	uint8_t bus = sensor_config[sensor_config_index_map[sensor_num]].port;
	uint8_t target_addr = sensor_config[sensor_config_index_map[sensor_num]].target_addr;
	uint8_t tx_len = 0, rx_len = 0;
	uint8_t retry = 5;

	ltc4282_init_arg *init_args =
		(ltc4282_init_arg *)sensor_config[sensor_config_index_map[sensor_num]].init_args;
	if (init_args->is_init)
	{
		goto init_param;
	}

	// Set ILIM_ADJUST register value
	tx_len = 2;
	rx_len = 0;
	data[0] = LTC4282_ILIM_ADJUST_OFFSET;
	data[1] = init_args->ilim_adjust;
	msg = construct_i2c_message(bus, target_addr, tx_len, data, rx_len);
	if (i2c_master_write(&msg, retry) != 0) {
		printf("Failed to set LTC4282 register(0x%x)\n", data[0]);
		goto cleanup;
	}

init_param:
	// Read ILIM_ADJUST register value
	tx_len = 1;
	rx_len = 1;
	data[0] = LTC4282_ILIM_ADJUST_OFFSET;
	msg = construct_i2c_message(bus, target_addr, tx_len, data, rx_len);
	if (i2c_master_write(&msg, retry) != 0) {
		printf("Failed to read LTC4282 register(0x%x)\n", data[0]);
		goto cleanup;
	}
	ilim_adjust.value = msg.data[0];

	init_args->is_init = true;

cleanup:
	SAFE_FREE(data);

	sensor_config[sensor_config_index_map[sensor_num]].read = ltc4282_read;
	return SENSOR_INIT_SUCCESS;
}
