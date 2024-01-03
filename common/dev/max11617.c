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
#include "sensor.h"
#include "hal_i2c.h"
#include "pmbus.h"

#include <logging/log.h>

LOG_MODULE_REGISTER(max11617);

#define MAX1363_CHANNEL_SEL_MASK 0x1E
#define MAX1363_CHANNEL_SEL(a) ((a) << 1)
#define MAX1363_CONFIG_SCAN_SINGLE_1 0x60
#define MAX1363_CONFIG_SE 0x01
#define MAX1363_SCAN_MASK 0x60
#define MAX1363_SE_DE_MASK 0x01

#define MAX11617_VREF 2.048 // unit: volt(V)

static uint8_t setupbyte, configbyte, mode;

static int max11617_set_scan_mode(sensor_cfg *cfg, uint8_t setupbyte, uint8_t configbyte,
				  uint8_t mode)
{
	CHECK_NULL_ARG_WITH_RETURN(cfg, SENSOR_UNSPECIFIED_ERROR);

	configbyte &= ~(MAX1363_CHANNEL_SEL_MASK | MAX1363_SCAN_MASK | MAX1363_SE_DE_MASK);
	configbyte |= mode;

	uint8_t retry = 5;
	int ret = 0;
	I2C_MSG msg;
	memset(&msg, 0, sizeof(I2C_MSG));

	msg.bus = cfg->port;
	msg.target_addr = cfg->target_addr;
	msg.tx_len = 2;
	msg.data[0] = setupbyte;
	msg.data[1] = configbyte;

	ret = i2c_master_write(&msg, retry);
	if (ret != 0) {
		LOG_ERR("i2c write fail, sensor number 0x%x  ret: %d", cfg->num, ret);
		return SENSOR_FAIL_TO_ACCESS;
	}
	return ret;
}

uint8_t max11617_read(sensor_cfg *cfg, int *reading)
{
	CHECK_NULL_ARG_WITH_RETURN(cfg, SENSOR_UNSPECIFIED_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(reading, SENSOR_UNSPECIFIED_ERROR);

	int ret = 0;
	float val = 0;
	sensor_val *sval = (sensor_val *)reading;

	if (cfg->num > SENSOR_NUM_MAX) {
		LOG_ERR("sensor num: 0x%x is invalid", cfg->num);
		return SENSOR_UNSPECIFIED_ERROR;
	}

	mode = (cfg->offset << 1) | MAX1363_CONFIG_SCAN_SINGLE_1 | MAX1363_CONFIG_SE;
	if (max11617_set_scan_mode(cfg, setupbyte, configbyte, mode) != 0) {
		LOG_ERR("max11617_init failed for sensor number 0x%x  ret: %d", cfg->num, ret);
		return SENSOR_FAIL_TO_ACCESS;
	}

	uint8_t retry = 5;
	I2C_MSG msg;
	memset(&msg, 0, sizeof(I2C_MSG));

	msg.bus = cfg->port;
	msg.target_addr = cfg->target_addr;
	msg.rx_len = 2;

	ret = i2c_master_read(&msg, retry);
	if (ret != 0) {
		LOG_ERR("i2c read fail  sensor number 0x%x  ret: %d", cfg->num, ret);
		return SENSOR_FAIL_TO_ACCESS;
	}

	/* Get reading, 1 lsb = vref/4096 */
	max11617_init_arg *init_arg = (max11617_init_arg *)cfg->init_args;
	val = (msg.data[1] | msg.data[0] << 8) & ((1 << 12) - 1);
	val *= (MAX11617_VREF / 4096);
	val *= init_arg->scalefactor;
	sval->integer = val;
	sval->fraction = (val - sval->integer) * 1000;

	return SENSOR_READ_SUCCESS;
}

uint8_t max11617_init(sensor_cfg *cfg)
{
	CHECK_NULL_ARG_WITH_RETURN(cfg, SENSOR_INIT_UNSPECIFIED_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(cfg->init_args, SENSOR_INIT_UNSPECIFIED_ERROR);

	if (cfg->num > SENSOR_NUM_MAX) {
		return SENSOR_INIT_UNSPECIFIED_ERROR;
	}

	setupbyte = 0xD2; // follow Table of Reference Voltage on max11617 datasheet
	configbyte = 0x0;
	mode = 0x17; // s0to11
	if (max11617_set_scan_mode(cfg, setupbyte, configbyte, mode) != 0) {
		LOG_ERR("max11617_init failed for sensor number 0x%x", cfg->num);
		return SENSOR_FAIL_TO_ACCESS;
	}

	cfg->read = max11617_read;
	return SENSOR_INIT_SUCCESS;
}
