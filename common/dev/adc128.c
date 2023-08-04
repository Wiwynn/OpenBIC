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

#include "hal_i2c.h"
#include "pmbus.h"
#include "sensor.h"
#include <logging/log.h>
#include <stdio.h>
#include <string.h>
#include "adc128.h"

LOG_MODULE_REGISTER(dev_adc128);

uint8_t adc128_read(sensor_cfg *cfg, int *reading)
{
	CHECK_NULL_ARG_WITH_RETURN(cfg, SENSOR_UNSPECIFIED_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(reading, SENSOR_UNSPECIFIED_ERROR);

	int ret = 0;
	uint8_t retry = 5;
	uint8_t channel = cfg->offset;
	uint16_t value = 0;
	float parameter = 0;
	I2C_MSG msg = { 0 };

	/* Initiate a single conversion */
	msg.bus = cfg->port;
	msg.target_addr = cfg->target_addr;
	msg.tx_len = 2;
	msg.data[0] = ADC128_ONE_SHOT_REG;
	msg.data[1] = ADC128_INITIATE_SINGLE_CONVERSION_VAL;

	ret = i2c_master_write(&msg, retry);
	if (ret != 0) {
		LOG_ERR("Initiate a single conversion fail ret: %d, sensor num: 0x%x", ret,
			cfg->num);
		return false;
	}

	k_msleep(ADC128_DATA_READY_DELAY_MS);

	/* Check busy status */
	memset(&msg, 0, sizeof(I2C_MSG));
	msg.bus = cfg->port;
	msg.target_addr = cfg->target_addr;
	msg.tx_len = 1;
	msg.rx_len = 1;
	msg.data[0] = ADC128_BUSY_STATUS_REG;

	ret = i2c_master_read(&msg, retry);
	if (ret != 0) {
		LOG_ERR("Read busy status fail ret: %d, sensor num: 0x%x", ret, cfg->num);
		return SENSOR_FAIL_TO_ACCESS;
	}

	if ((msg.data[0] & ADC128_DATA_READY_VAL) != 0) {
		LOG_ERR("Data not ready, return value: 0x%x, sensor num: 0x%x", msg.data[0],
			cfg->num);
		return SENSOR_UNSPECIFIED_ERROR;
	}

	/* Read channel report value */
	memset(&msg, 0, sizeof(I2C_MSG));
	msg.bus = cfg->port;
	msg.target_addr = cfg->target_addr;
	msg.tx_len = 1;
	msg.rx_len = 2;
	msg.data[0] = channel;

	ret = i2c_master_read(&msg, retry);
	if (ret != 0) {
		LOG_ERR("Read channel report fail ret: %d, sensor num: 0x%x", ret, cfg->num);
		return SENSOR_FAIL_TO_ACCESS;
	}

	if (cfg->arg1 == 0) {
		LOG_ERR("Sensor config setting error, arg1 is 0");
		return SENSOR_PARAMETER_NOT_VALID;
	}

	parameter = 0.625 * cfg->arg0 / cfg->arg1;
	value = ((msg.data[0] << 8) | msg.data[1]) >> 4;

	sensor_val *sval = (sensor_val *)reading;
	sval->integer = (value * parameter / 1000);
	sval->fraction = ((value * parameter) - (sval->integer * 1000));
	return SENSOR_READ_SUCCESS;
}

uint8_t adc128_init(sensor_cfg *cfg)
{
	CHECK_NULL_ARG_WITH_RETURN(cfg, SENSOR_INIT_UNSPECIFIED_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(cfg->init_args, SENSOR_INIT_UNSPECIFIED_ERROR);

	adc128_init_arg *init_args = (adc128_init_arg *)cfg->init_args;
	if (init_args->is_init) {
		LOG_DBG("adm1278 already initialized.");
		goto skip_init;
	}

	uint8_t retry = 5;
	I2C_MSG msg = { 0 };
	msg.bus = cfg->port;
	msg.target_addr = cfg->target_addr;
	msg.tx_len = 2;
	msg.data[0] = ADC128_CHANNEL_DISABLE_REG;
	msg.data[1] = init_args->channel_disable_setting;

	if (i2c_master_write(&msg, retry)) {
		LOG_ERR("ADC128 initial failed while writing channel disable setting, sensor num: 0x%x",
			cfg->num);
		return SENSOR_INIT_UNSPECIFIED_ERROR;
	}

	memset(&msg, 0, sizeof(msg));
	msg.bus = cfg->port;
	msg.target_addr = cfg->target_addr;
	msg.tx_len = 2;
	msg.data[0] = ADC128_ADVANCED_CONFIG_REG;
	msg.data[1] = init_args->advanced_cfg.value;

	if (i2c_master_write(&msg, retry)) {
		LOG_ERR("ADC128 initial failed while writing advanced cfg, sensor num: 0x%x",
			cfg->num);
		return SENSOR_INIT_UNSPECIFIED_ERROR;
	}

	init_args->is_init = true;

skip_init:
	cfg->read = adc128_read;
	return SENSOR_INIT_SUCCESS;
}
