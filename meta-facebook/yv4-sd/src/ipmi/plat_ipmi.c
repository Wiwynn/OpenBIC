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
#include "util_sys.h"
#include "ipmb.h"
#include "ipmi.h"
#include "pldm_oem.h"
#include "plat_ipmi.h"
#include "plat_sys.h"
#include "plat_class.h"
#include "plat_mctp.h"

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
	if (netfn == NETFN_APP_REQ) {
		if ((cmd == CMD_APP_SET_ACPI_POWER) || (cmd == CMD_APP_GET_DEVICE_GUID) ||
		    (cmd == CMD_APP_GET_BMC_GLOBAL_ENABLES) ||
		    (cmd == CMD_APP_CLEAR_MESSAGE_FLAGS) || (cmd == CMD_APP_GET_CAHNNEL_INFO) ||
		    (cmd == CMD_APP_GET_DEVICE_ID) || (cmd == CMD_APP_GET_SELFTEST_RESULTS) ||
		    (cmd == CMD_APP_COLD_RESET)) {
			return true;
		}
	} else if (netfn == NETFN_DCMI_REQ) {
		if (cmd == CMD_DCMI_GET_PICMG_PROPERTIES) {
			return true;
		}
	} else if (netfn == NETFN_OEM_REQ) {
		if (cmd == CMD_OEM_GET_CHASSIS_POSITION) {
			return true;
		}
	}

	else {
		return false;
	}

	return false;
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

	msg->completion_code = CC_SUCCESS;
	msg->data_len = 1;

	uint8_t slot_id = get_slot_id();

	uint8_t blade_config = BLADE_CONFIG_UNKNOWN;
	if (get_blade_config(&blade_config) == false) {
		LOG_ERR("Failed to get the blade configuration");
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

void OEM_1S_SLED_CYCLE(ipmi_msg *msg)
{
	CHECK_NULL_ARG(msg);

	msg->data_len = 0;
	msg->completion_code = CC_SUCCESS;
	
	pldm_msg pldm_msg = { 0 };
	uint8_t bmc_bus = I2C_BUS_BMC;
	uint8_t bmc_interface = pal_get_bmc_interface();
	
	// Send the PLDM OEM cmd to BMC to execute sled cycle
	if (bmc_interface == BMC_INTERFACE_I3C) {
		bmc_bus = I3C_BUS_BMC;
		pldm_msg.ext_params.type = MCTP_MEDIUM_TYPE_TARGET_I3C;
		pldm_msg.ext_params.i3c_ext_params.addr = I3C_STATIC_ADDR_BMC;
		pldm_msg.ext_params.ep = MCTP_EID_BMC;
	} else {
		bmc_bus = I2C_BUS_BMC;
		pldm_msg.ext_params.type = MCTP_MEDIUM_TYPE_SMBUS;
		pldm_msg.ext_params.smbus_ext_params.addr = I2C_ADDR_BMC;
		pldm_msg.ext_params.ep = MCTP_EID_BMC;
	}
	pldm_msg.hdr.pldm_type = PLDM_TYPE_OEM;
	pldm_msg.hdr.cmd = PLDM_OEM_WRITE_FILE_IO;
	pldm_msg.hdr.rq = 1;
	struct pldm_oem_write_file_io_req *ptr = (struct pldm_oem_write_file_io_req *)malloc(
		sizeof(struct pldm_oem_write_file_io_req) + (POWER_CONTROL_LEN * sizeof(uint8_t)));
	if (ptr == NULL) {
		LOG_ERR("Memory allocation failed.");
		msg->completion_code = CC_UNSPECIFIED_ERROR;
		return;
	}

	ptr->cmd_code = POWER_CONTROL;
	ptr->data_length = POWER_CONTROL_LEN;
	ptr->messages[0] = 0x00;

	pldm_msg.buf = (uint8_t *)ptr;
	pldm_msg.len = sizeof(struct pldm_oem_write_file_io_req) + POWER_CONTROL_LEN;

	uint8_t resp_len = sizeof(struct pldm_oem_write_file_io_resp);
	uint8_t rbuf[resp_len];
	if (!mctp_pldm_read(find_mctp_by_bus(bmc_bus), &pldm_msg, rbuf, resp_len)) {
		LOG_ERR("mctp_pldm_read fail");
		msg->completion_code = CC_UNSPECIFIED_ERROR;
		SAFE_FREE(ptr);
		return;
	}

	struct pldm_oem_write_file_io_resp *resp = (struct pldm_oem_write_file_io_resp *)rbuf;
	if (resp->completion_code != PLDM_SUCCESS) {
		LOG_ERR("Check reponse completion code fail %x", resp->completion_code);
		msg->completion_code = CC_UNSPECIFIED_ERROR;
	}

	SAFE_FREE(ptr);

	return;
}
