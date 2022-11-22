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
#include <drivers/jtag.h>
#include <logging/log.h>

#include "ipmi.h"
#include "libutil.h"
#include "util_spi.h"
#include "pex89000.h"
#include "plat_gpio.h"
#include "plat_sensor_table.h"

LOG_MODULE_REGISTER(plat_ipmi);

void OEM_1S_GET_FPGA_USER_CODE(ipmi_msg *msg)
{
	CHECK_NULL_ARG(msg);

	printf("[%s] get fpga user code\n", __func__);

	if (msg->data_len != 0) {
		msg->completion_code = CC_INVALID_LENGTH;
		return;
	}

	uint8_t buffer[4] = { 0 };
	uint8_t ir_value = FPGA_USER_CODE;
	uint8_t dr_value = 0x00;
	const struct device *device;
	bool status = true;

	device = device_get_binding("JTAG0");
	if (!device) {
		LOG_ERR("JTAG0 device bound failed");
		return;
	}

	/** mux default high for header; low for bic **/
	gpio_set(JTAG_MUX_SEL, GPIO_LOW);

	/** call zephyr set to reset for using **/
	if (jtag_tap_set(device, TAP_RESET)) {
		status = false;
	}
	printf("[%s] jtag_tap_set: %d\n", __func__, status);

	k_msleep(10);

	/** call zephyr to set instruction register **/
	if (jtag_ir_scan(device, 8, &ir_value, buffer, TAP_IDLE)) {
		status = false;
	}
	printf("[%s] jtag_ir_scan: %d\n", __func__, status);

	/** call zephyr to get data register **/
	if (jtag_dr_scan(device, 32, &dr_value, buffer, TAP_IDLE)) {
		status = false;
	}
	printf("[%s] jtag_dr_scan: %d\n", __func__, status);

	if (status) {
		memcpy(msg->data, buffer, sizeof(buffer));
		msg->data_len = 4;
		msg->completion_code = CC_SUCCESS;
	} else {
		msg->completion_code = CC_UNSPECIFIED_ERROR;
	}

	/** set mux default **/
	gpio_set(JTAG_MUX_SEL, GPIO_HIGH);
	return;
}

void OEM_1S_GET_FW_VERSION(ipmi_msg *msg)
{
	CHECK_NULL_ARG(msg);

	if (msg->data_len != 1) {
		msg->completion_code = CC_INVALID_LENGTH;
		return;
	}

	printf("[%s] get fw version\n", __func__);

	ipmi_msg bridge_msg = { 0 };
	uint8_t component = msg->data[0];
	
	if (component >= CB_COMPNT_MAX) {
		msg->completion_code = CC_PARAM_OUT_OF_RANGE;
		return;
	}
	/* 
	* Return data format: 
	* data[0] = component id
	* data[1] = data length
	* data[2] - data[data length + 1] = firmware version
	*/
	switch (component) {
	/** component 2 **/
	case CB_COMPNT_BIC:
		msg->data[0] = CB_COMPNT_BIC;
		msg->data[1] = BIC_FW_DATA_LENGTH;
		msg->data[2] = BIC_FW_YEAR_MSB;
		msg->data[3] = BIC_FW_YEAR_LSB;
		msg->data[4] = BIC_FW_WEEK;
		msg->data[5] = BIC_FW_VER;
		msg->data[6] = BIC_FW_platform_0;
		msg->data[7] = BIC_FW_platform_1;
		msg->data[8] = BIC_FW_platform_2;
		msg->data_len = 9;
		msg->completion_code = CC_SUCCESS;
		break;

	/** component 3/4 **/
	case CB_COMPNT_PCIE_SWITCH0:
	case CB_COMPNT_PCIE_SWITCH1: {
		/** pcie switch works only when host power on **/
		if (is_mb_dc_on() == false) {
			msg->completion_code = CC_UNSPECIFIED_ERROR;
			return;
		}
		uint8_t pex_sensor_num_table[MAX_PEX_NUMBER] = { SENSOR_NUM_TEMP_PEX_0,
								 SENSOR_NUM_TEMP_PEX_1 };
		int reading;

		uint8_t pex_sensor_num = pex_sensor_num_table[component - CB_COMPNT_PCIE_SWITCH0];
		printf("[%s] get pex_sensor_num: 0x%02x\n", __func__, pex_sensor_num);
		sensor_cfg *cfg = &sensor_config[sensor_config_index_map[pex_sensor_num]];
		pex89000_unit *p = (pex89000_unit *)cfg->priv_data;

//		if (cfg->pre_sensor_read_hook) {
//			if (!cfg->pre_sensor_read_hook(cfg->num, cfg->pre_sensor_read_args)) {
//				msg->completion_code = CC_UNSPECIFIED_ERROR;
//				LOG_ERR("pcie_sw%u pre-read failed", component - CB_COMPNT_PCIE_SWITCH0);
//				return;
//			}
//		}

		if (pex_access_engine(cfg->port, cfg->target_addr, p->idx, pex_access_sbr_ver,
				      &reading)) {
			msg->completion_code = CC_UNSPECIFIED_ERROR;
			LOG_ERR("pcie_sw%u access failed", component - CB_COMPNT_PCIE_SWITCH0);
			return;
		}

//		if (cfg->post_sensor_read_hook) {
//			if (!cfg->post_sensor_read_hook(cfg->num, cfg->post_sensor_read_args, NULL)) {
//				LOG_ERR("pcie_sw%u post-read failed", component - CB_COMPNT_PCIE_SWITCH0);
//			}
//		}

		msg->data[0] = component;
		msg->data[1] = sizeof(reading);
		memcpy(&msg->data[2], &reading, sizeof(reading));
		msg->data_len = sizeof(reading) + 2;
		msg->completion_code = bridge_msg.completion_code;
		break;
	}


	case CB_COMPNT_CPLD:
		printf("[%s] get cb cpld fw version\n", __func__);
		bridge_msg.data_len = 0;
		OEM_1S_GET_FPGA_USER_CODE(&bridge_msg);
		msg->data[0] = component;
		msg->data[1] = bridge_msg.data_len;
		memcpy(&msg->data[2], &bridge_msg.data[0], bridge_msg.data_len);
		msg->data_len = bridge_msg.data_len + 2;
		msg->completion_code = bridge_msg.completion_code;
		break;


	default:
		msg->completion_code = CC_UNSPECIFIED_ERROR;
		break;
	}

	return;
}
