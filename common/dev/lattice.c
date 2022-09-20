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

#include "lattice.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <logging/log.h>
#include "libutil.h"
#include "hal_i2c.h"
#include "plat_ipmb.h"

LOG_MODULE_REGISTER(lattice);

__weak lattice_dev_cfg *pal_lattice_get_dev_config()
{
	return NULL;
}

int lattice_write_register(lattice_dev_cfg dev_cfg, uint8_t *write_data, uint8_t write_len)
{
	CHECK_NULL_ARG_WITH_RETURN(write_data, -1);

	I2C_MSG i2c_msg = { 0 };
	int ret = 0;
	uint8_t retry = 3;

	i2c_msg.bus = dev_cfg.i2c_bus;
	i2c_msg.target_addr = dev_cfg.address;
	i2c_msg.tx_len = write_len;
	memcpy(&i2c_msg.data[0], &write_data[0], write_len);

	ret = i2c_master_write(&i2c_msg, retry);
	if (ret != 0) {
		LOG_ERR("I2c read fail, ret: %d", ret);
		return -1;
	}

	return 0;
}

int lattice_read_register(lattice_dev_cfg dev_cfg, uint8_t *write_data, uint8_t write_len,
			  uint8_t *read_data, uint8_t read_len)
{
	CHECK_NULL_ARG_WITH_RETURN(write_data, -1);
	CHECK_NULL_ARG_WITH_RETURN(read_data, -1);

	I2C_MSG i2c_msg = { 0 };
	int ret = 0;
	uint8_t retry = 3;

	i2c_msg.bus = dev_cfg.i2c_bus;
	i2c_msg.target_addr = dev_cfg.address;
	i2c_msg.tx_len = write_len;
	i2c_msg.rx_len = read_len;
	memcpy(&i2c_msg.data[0], &write_data[0], write_len);

	ret = i2c_master_read(&i2c_msg, retry);
	if (ret != 0) {
		LOG_ERR("I2c read fail, ret: %d", ret);
		return -1;
	}

	memcpy(&read_data[0], &i2c_msg.data[0], read_len);
	return 0;
}

int lattice_read_usercode(lattice_dev_cfg dev_cfg, uint8_t *usercode)
{
	CHECK_NULL_ARG_WITH_RETURN(usercode, -1);

	uint32_t usercode_cmd = LATTICE_REG_GET_USERCODE;
	uint8_t data_len = sizeof(uint32_t);
	uint8_t lattice_cmd[data_len];
	memcpy(&lattice_cmd[0], &usercode_cmd, data_len);

	return lattice_read_register(dev_cfg, lattice_cmd, data_len, usercode,
				     LATTICE_RES_GET_USERCODE_LEN);
}
