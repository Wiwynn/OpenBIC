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
#include <stdlib.h>
#include <logging/log.h>

#include "libutil.h"
#include "ipmb.h"
#include "ipmi.h"
#include "plat_ipmi.h"
#include "plat_sys.h"
#include "plat_class.h"
#include "plat_isr.h"
#include "hal_i3c.h"
#include "power_status.h"
#include "plat_i3c.h"
#include "plat_dimm.h"

enum THREAD_STATUS {
	THREAD_SUCCESS = 0,
	// If k_work_schedule_for_queue() is running, return 1
	THREAD_RUNNING = 1,
};

enum SLOT_STATUS {
	SLOT_NOT_PRESENT = 0x00,
	SLOT_PRESENT = 0x80, // Bit 7 is set to 1
};

LOG_MODULE_REGISTER(plat_ipmi);

bool pal_request_msg_to_BIC_from_HOST(uint8_t netfn, uint8_t cmd)
{
	if (netfn == NETFN_STORAGE_REQ) {
		if (cmd == CMD_STORAGE_ADD_SEL) {
			return false;
		}
	}

	if (netfn == NETFN_APP_REQ) {
		if (cmd == CMD_APP_SET_SYS_INFO_PARAMS) {
			return false;
		}
	}
	// In YV4, all IPMI commands are all sent to BIC
	return true;
}

void APP_GET_BMC_GLOBAL_ENABLES(ipmi_msg *msg)
{
	CHECK_NULL_ARG(msg);

	msg->data[0] = ENABLE;
	msg->data_len = 1;

	msg->completion_code = CC_SUCCESS;
	return;
}

void APP_SET_ACPI_POWER(ipmi_msg *msg)
{
	CHECK_NULL_ARG(msg);

	msg->completion_code = CC_SUCCESS;
	return;
}

void APP_CLEAR_MESSAGE_FLAGS(ipmi_msg *msg)
{
	CHECK_NULL_ARG(msg);

	msg->completion_code = CC_SUCCESS;
	return;
}

// Reset BMC
void APP_COLD_RESET(ipmi_msg *msg)
{
	CHECK_NULL_ARG(msg);

	if (msg->data_len != 0) {
		msg->completion_code = CC_INVALID_LENGTH;
		return;
	}

	switch (pal_submit_bmc_cold_reset()) {
	case -EBUSY:
		msg->completion_code = CC_NODE_BUSY;
		break;
	case -EINVAL:
		msg->completion_code = CC_INVALID_PARAM;
		break;
	case -ENODEV:
		msg->completion_code = CC_SENSOR_NOT_PRESENT;
		break;
	case THREAD_RUNNING:
	case THREAD_SUCCESS:
		msg->completion_code = CC_SUCCESS;
		break;
	default:
		msg->completion_code = CC_UNSPECIFIED_ERROR;
		break;
	}

	msg->data_len = 0;
	return;
}

void OEM_GET_CHASSIS_POSITION(ipmi_msg *msg)
{
	CHECK_NULL_ARG(msg);

	if (msg->data_len != 0) {
		msg->completion_code = CC_INVALID_LENGTH;
		return;
	}

	msg->completion_code = CC_SUCCESS;
	msg->data_len = 1;

	uint8_t slot_id = get_slot_id();

	uint8_t blade_config = BLADE_CONFIG_UNKNOWN;
	if (get_blade_config(&blade_config) == false) {
		LOG_ERR("Failed to get the blade configuration");
		msg->completion_code = CC_UNSPECIFIED_ERROR;
		return;
	}

	/*   msg->data[0] format:
	 *
	 *   Slot Present (Bit 7):
	 *       0: Slot not present
	 *       1: Slot present
	 *
	 *   Reserved (Bits [6:4])
	 *
	 *   Slot ID (Bits [3:0]):
	 *       0001: Slot 1
	 *       0010: Slot 2
	 *       ...
	 *       1000: Slot 8
	 */

	msg->data[0] = SLOT_PRESENT + blade_config + slot_id;
	return;
}

void APP_GET_SELFTEST_RESULTS(ipmi_msg *msg)
{
	CHECK_NULL_ARG(msg);

	if (msg->data_len != 0) {
		msg->completion_code = CC_INVALID_LENGTH;
		return;
	}

	// Bios needs get self test and get system info before getting set system info
	// Using hardcode directly response
	msg->data[0] = 0x55;
	msg->data[1] = 0x00;
	msg->data_len = 2;
	msg->completion_code = CC_SUCCESS;

	return;
}

void OEM_1S_DEBUG_GET_HW_SIGNAL(ipmi_msg *msg)
{
	CHECK_NULL_ARG(msg);

	memcpy(&msg->data[0], &hw_event_register[0], sizeof(hw_event_register));

	//clear cache register after bmc read.
	memset(hw_event_register, 0, sizeof(hw_event_register));

	msg->data_len = sizeof(hw_event_register);
	msg->completion_code = CC_SUCCESS;
	return;
}

/*
Byte 0 - DIMM location
  00h - A
  01h - B
  02h - C
  03h - D
  04h - E
  05h - F
  06h - G
  07h - H
  08h - I
  09h - J
  0Ah - K
  0Bh - L
Byte 1: Device type
  00h - SPD
  01h - SPD NVM
  02h - PMIC
Byte 2: Read/write data length
Byte 3:4: 2byte offset
Byte 5:~ write data
*/
void OEM_1S_WRITE_READ_DIMM(ipmi_msg *msg)
{
	CHECK_NULL_ARG(msg);

	// At least include DIMM location, device type, write/read len, offset
	if (msg->data_len < 4) {
		msg->completion_code = CC_INVALID_LENGTH;
		return;
	}

	int ret = 0;
	uint8_t dimm_id = msg->data[0];
	uint8_t device_type = msg->data[1];

	// If host is DC on but not post complete, BIC can't read DIMM information via I3C
	if (get_DC_status() == true && get_post_status() == false) {
		msg->completion_code = CC_NOT_SUPP_IN_CURR_STATE;
		return;
	}

	I3C_MSG i3c_msg = { 0 };
	i3c_msg.bus = I3C_BUS3;
	i3c_msg.tx_len = msg->data_len - 3;
	i3c_msg.rx_len = msg->data[2];

	// Check offset byte count: SPD_NVM has 2 bytes offset
	if (device_type == DIMM_SPD_NVM) {
		if (i3c_msg.tx_len < 2) {
			msg->completion_code = CC_INVALID_DATA_FIELD;
			return;
		}
	} else {
		// One byte offset
		if (i3c_msg.tx_len < 1) {
			msg->completion_code = CC_INVALID_DATA_FIELD;
			return;
		}
	}

	memcpy(&i3c_msg.data[0], &msg->data[3], i3c_msg.tx_len);
	msg->data_len = i3c_msg.rx_len;

	if (k_mutex_lock(&i3c_dimm_mutex, K_MSEC(I3C_DIMM_MUTEX_TIMEOUT_MS))) {
		LOG_ERR("Failed to lock I3C dimm mux");
		msg->completion_code = CC_NODE_BUSY;
		return;
	}

	uint8_t i3c_ctrl_mux_data = (dimm_id / (DIMM_ID_MAX / 2)) ? I3C_MUX_BIC_TO_DIMMG_TO_L :
								    I3C_MUX_BIC_TO_DIMMA_TO_F;
	ret = switch_i3c_dimm_mux(i3c_ctrl_mux_data);
	if (ret < 0) {
		msg->completion_code = CC_UNSPECIFIED_ERROR;
		goto exit;
	}

	// I3C_CCC_RSTDAA: Reset dynamic address assignment
	// I3C_CCC_SETAASA: Set all addresses to static address
	ret = all_brocast_ccc(&i3c_msg);
	if (ret != 0) {
		LOG_ERR("Failed to brocast CCC, ret%d bus%d", ret, i3c_msg.bus);
		msg->completion_code = CC_UNSPECIFIED_ERROR;
		goto exit;
	}

	switch (device_type) {
	case DIMM_SPD:
	case DIMM_SPD_NVM:
		i3c_msg.target_addr = spd_i3c_addr_list[dimm_id % (DIMM_ID_MAX / 2)];

		if (device_type == DIMM_SPD_NVM) {
			ret = i3c_spd_reg_read(&i3c_msg, true);
		} else {
			ret = i3c_spd_reg_read(&i3c_msg, false);
		}

		if (ret != 0) {
			LOG_ERR("Failed to read SPD addr0x%x offset0x%x, ret%d",
				i3c_msg.target_addr, i3c_msg.data[0], ret);
			msg->completion_code = CC_UNSPECIFIED_ERROR;
		} else {
			memcpy(&msg->data[0], &i3c_msg.data, i3c_msg.rx_len);
			msg->data_len = i3c_msg.rx_len;
			msg->completion_code = CC_SUCCESS;
		}
		break;

	case DIMM_PMIC:
		i3c_msg.target_addr = pmic_i3c_addr_list[dimm_id % (DIMM_ID_MAX / 2)];

		ret = i3c_transfer(&i3c_msg);
		if (ret != 0) {
			LOG_ERR("Failed to read PMIC addr0x%x offset0x%x, ret%d bus%d",
				i3c_msg.target_addr, i3c_msg.data[0], ret, i3c_msg.bus);
			msg->completion_code = CC_UNSPECIFIED_ERROR;
		} else {
			memcpy(&msg->data[0], &i3c_msg.data, i3c_msg.rx_len);
			msg->data_len = i3c_msg.rx_len;
			msg->completion_code = CC_SUCCESS;
		}
		break;

	default:
		msg->completion_code = CC_INVALID_DATA_FIELD;
		break;
	}
exit:
	// Switch I3C MUX to CPU after read finish
	switch_i3c_dimm_mux(I3C_MUX_CPU_TO_DIMM);

	if (k_mutex_unlock(&i3c_dimm_mutex)) {
		LOG_ERR("Failed to lock I3C dimm MUX");
	}
}
