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

#include "plat_ipmi.h"

#include <stdio.h>
#include <stdlib.h>
#include <logging/log.h>
#include "ipmi.h"
#include "pmbus.h"
#include "sensor.h"
#include "libutil.h"
#include "lattice.h"
#include "hal_i2c.h"
#include "pex89000.h"
#include "plat_ipmb.h"
#include "plat_lattice.h"
#include "power_status.h"
#include "plat_sensor_table.h"

LOG_MODULE_REGISTER(plat_ipmi);

void OEM_1S_GET_FW_VERSION(ipmi_msg *msg)
{
	/* *********************
	** Request data
	** Byte 0: component id

	** Response data
	** Byte 0: version length
	** Byte 1~ firmware version
	***********************/
	CHECK_NULL_ARG(msg);

	if (msg->data_len != 1) {
		msg->completion_code = CC_INVALID_LENGTH;
		return;
	}

	uint8_t component = msg->data[0];

	if (component >= CB_COMPNT_MAX) {
		msg->completion_code = CC_PARAM_OUT_OF_RANGE;
		return;
	}

	switch (component) {
	case CB_COMPNT_BIC:
		msg->data[0] = BIC_VERSION_COUNT;
		msg->data[1] = BIC_FW_YEAR_MSB;
		msg->data[2] = BIC_FW_YEAR_LSB;
		msg->data[3] = BIC_FW_WEEK;
		msg->data[4] = BIC_FW_VER;
		msg->data[5] = BIC_FW_platform_0;
		msg->data[6] = BIC_FW_platform_1;
		msg->data[7] = BIC_FW_platform_2;
		msg->data_len = BIC_VERSION_COUNT + 1;
		msg->completion_code = CC_SUCCESS;
		break;
	case CB_COMPNT_PEX0:
	case CB_COMPNT_PEX1: {
		/* Get PEX firmware version via i2c */
		if (is_mb_dc_on() == false) {
			msg->completion_code = CC_NOT_SUPP_IN_CURR_STATE;
			return;
		}

		int reading = 0;
		uint8_t pex_sensor_num = ((component == CB_COMPNT_PEX0) ? SENSOR_NUM_TEMP_PEX_0 :
										SENSOR_NUM_TEMP_PEX_1);
		sensor_cfg *cfg = &sensor_config[sensor_config_index_map[pex_sensor_num]];
		pex89000_unit *p = (pex89000_unit *)cfg->priv_data;

		if (cfg->pre_sensor_read_hook) {
			if (cfg->pre_sensor_read_hook(cfg->num, cfg->pre_sensor_read_args) ==
			    false) {
				LOG_ERR("Pex%d pre-read fail", component - CB_COMPNT_PEX0);
				msg->completion_code = CC_UNSPECIFIED_ERROR;
				return;
			}
		}

		if (pex_access_engine(cfg->port, cfg->target_addr, p->idx, pex_access_flash_ver,
				      &reading) != 0) {
			msg->completion_code = CC_UNSPECIFIED_ERROR;
			if (cfg->post_sensor_read_hook) {
				if (cfg->post_sensor_read_hook(cfg->num, cfg->post_sensor_read_args,
							       NULL) == false) {
					LOG_ERR("Pex%d post-read fail", component - CB_COMPNT_PEX0);
				}
				return;
			}
		}

		if (cfg->post_sensor_read_hook) {
			if (cfg->post_sensor_read_hook(cfg->num, cfg->post_sensor_read_args,
						       NULL) == false) {
				LOG_ERR("Pex%d post-read fail", component - CB_COMPNT_PEX0);
			}
		}

		memcpy(&msg->data[1], &reading, sizeof(reading));
		msg->data[0] = sizeof(reading);
		msg->data_len = sizeof(reading) + 1;
		msg->completion_code = CC_SUCCESS;
		break;
	}
	case CB_COMPNT_CPLD: {
		/* Get CPLD firmware version via i2c */
		lattice_dev_cfg *cpld_cfg = pal_lattice_get_dev_config();
		if (cpld_cfg == NULL) {
			msg->completion_code = CC_UNSPECIFIED_ERROR;
			break;
		}

		int ret = 0;
		ret = lattice_read_usercode(*cpld_cfg, &msg->data[1]);
		if (ret != 0) {
			msg->completion_code = CC_UNSPECIFIED_ERROR;
			break;
		}

		msg->data[0] = LATTICE_RES_GET_USERCODE_LEN;
		msg->data_len = LATTICE_RES_GET_USERCODE_LEN + 1;
		msg->completion_code = CC_SUCCESS;
		break;
	}
	case CB_COMPNT_XDPE15284: {
		/* BIC needs to send MFR firmware command to XDPE15284 first,
		and than the firmware version can be obtained in MFR firmware command data register. */

		/* Get VR firmware version via i2c */
		I2C_MSG i2c_msg = { 0 };
		uint8_t retry = 3;

		/* Send the command to get firmware version */
		i2c_msg.bus = I2C_BUS1;
		i2c_msg.target_addr = XDPE15284D_ADDR;
		i2c_msg.tx_len = 2;
		i2c_msg.data[0] = VR_MFR_FW_COMMAND;
		i2c_msg.data[1] = VR_GET_FIRMWARE_VERSION_CMD;

		if (i2c_master_write(&i2c_msg, retry)) {
			msg->completion_code = CC_UNSPECIFIED_ERROR;
			return;
		}

		/* Read the firmware version in MFR firmware command data register */
		i2c_msg.tx_len = 1;
		i2c_msg.rx_len = VR_FW_VERSION_LEN;
		i2c_msg.data[0] = VR_MFR_FW_COMMAND_DATA;

		if (i2c_master_read(&i2c_msg, retry)) {
			msg->completion_code = CC_UNSPECIFIED_ERROR;
			return;
		}

		msg->data[0] = VR_MFR_FW_COMMAND_DATA_LEN;
		msg->data[1] = i2c_msg.data[4];
		msg->data[2] = i2c_msg.data[3];
		msg->data[3] = i2c_msg.data[2];
		msg->data[4] = i2c_msg.data[1];
		msg->data_len = VR_MFR_FW_COMMAND_DATA_LEN + 1;
		msg->completion_code = CC_SUCCESS;
		break;
	}
	default:
		LOG_ERR("Component not supported: 0x%x", component);
		msg->completion_code = CC_UNSPECIFIED_ERROR;
		break;
	}
	return;
}
