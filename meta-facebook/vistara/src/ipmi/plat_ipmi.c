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
#include "ipmi.h"
#include "oem_1s_handler.h"
#include "hal_gpio.h"
#include "plat_ipmi.h"
#include "plat_ipmb.h"
#include "plat_class.h"
#include "libutil.h"
#include "plat_fru.h"
#include "util_spi.h"
#include "plat_spi.h"
#include "plat_sensor_table.h"
#include "plat_dev.h"
#include "plat_mctp.h"
#include "sensor.h"
#include "pmbus.h"
#include "pm8702.h"

LOG_MODULE_REGISTER(plat_ipmi);

void OEM_1S_GET_CARD_TYPE(ipmi_msg *msg)
{
	CHECK_NULL_ARG(msg)

	if (msg->data_len != 1) {
		msg->completion_code = CC_INVALID_LENGTH;
		return;
	}

	CARD_STATUS _1ou_status = get_1ou_status();
	CARD_STATUS _2ou_status = get_2ou_status();
	switch (msg->data[0]) {
	case GET_1OU_CARD_TYPE:
		msg->data_len = 2;
		msg->completion_code = CC_SUCCESS;
		msg->data[0] = GET_1OU_CARD_TYPE;
		if (_1ou_status.present) {
			msg->data[1] = _1ou_status.card_type;
		} else {
			msg->data[1] = TYPE_1OU_ABSENT;
		}
		break;
	case GET_2OU_CARD_TYPE:
		msg->data_len = 2;
		msg->completion_code = CC_SUCCESS;
		msg->data[0] = GET_2OU_CARD_TYPE;
		if (_2ou_status.present) {
			msg->data[1] = _2ou_status.card_type;
		} else {
			msg->data[1] = TYPE_2OU_ABSENT;
		}
		break;
	default:
		msg->data_len = 0;
		msg->completion_code = CC_INVALID_DATA_FIELD;
		break;
	}

	return;
}

int pal_record_bios_fw_version(uint8_t *buf, uint8_t size)
{
	CHECK_NULL_ARG_WITH_RETURN(buf, -1);

	int ret = -1;
	EEPROM_ENTRY set_bios_ver = { 0 };
	EEPROM_ENTRY get_bios_ver = { 0 };

	const uint8_t block_index = buf[3];
	if (block_index >= BIOS_FW_VERSION_BLOCK_NUM) {
		LOG_ERR("BIOS version block index is out of range");
		return -1;
	}

	ret = get_bios_version(&get_bios_ver, block_index);
	if (ret == -1) {
		LOG_ERR("Get BIOS version failed");
		return -1;
	}

	set_bios_ver.data_len = size - 3; // skip netfn, cmd and command code
	memcpy(&set_bios_ver.data[0], &buf[3], set_bios_ver.data_len);

	// Check the written BIOS version is the same with the stored
	ret = memcmp(&get_bios_ver.data[0], &set_bios_ver.data[0],
		     BIOS_FW_VERSION_BLOCK_MAX_SIZE * sizeof(uint8_t));
	if (ret == 0) {
		LOG_DBG("The Written BIOS version is the same as the stored BIOS version in EEPROM");
	} else {
		LOG_DBG("BIOS version set successfully");

		ret = set_bios_version(&set_bios_ver, block_index);
		if (ret == -1) {
			LOG_ERR("Set BIOS version failed");
			return -1;
		}
	}

	return 0;
}

void OEM_1S_GET_BIOS_VERSION(ipmi_msg *msg)
{
	CHECK_NULL_ARG(msg);

	if (msg->data_len != 0) {
		msg->completion_code = CC_INVALID_LENGTH;
		return;
	}

	msg->data_len = 0;

	for (uint8_t block_index = 0; block_index < BIOS_FW_VERSION_BLOCK_NUM; block_index++) {
		EEPROM_ENTRY get_bios_ver = { 0 };
		int ret = get_bios_version(&get_bios_ver, block_index);
		if (ret == -1) {
			LOG_ERR("Get BIOS version failed");
			msg->completion_code = CC_UNSPECIFIED_ERROR;
			return;
		}

		memcpy(msg->data + msg->data_len, get_bios_ver.data, get_bios_ver.data_len);
		msg->data_len += get_bios_ver.data_len;
	}

	msg->completion_code = CC_SUCCESS;
	return;
}

#ifdef CONFIG_I2C_IPMB_SLAVE
void OEM_1S_MSG_OUT(ipmi_msg *msg)
{
	CHECK_NULL_ARG(msg);
#if MAX_IPMB_IDX
	uint8_t target_IF;
	ipmb_error status;
	ipmi_msg *bridge_msg = NULL;

	// If command is valid the default cc is CC_INVALID_CMD, set cc to CC_SUCCESS before we execute the command.
	// If the default cc is CC_INVALID_IANA, call ipmb_send_response for this invalid command.
	if (msg->completion_code != CC_INVALID_IANA) {
		msg->completion_code = CC_SUCCESS;
	}

	// Should input target, netfn, cmd
	if (msg->data_len <= 2) {
		msg->completion_code = CC_INVALID_LENGTH;
	}

	CARD_STATUS _1ou_status = get_1ou_status();
	target_IF = msg->data[0];

	switch (target_IF) {
	case PEER_BMC_IPMB:
		switch (msg->InF_source) {
		case SLOT1_BIC:
			target_IF = msg->data[0] = SLOT3_BIC;
			break;
		case SLOT3_BIC:
			target_IF = msg->data[0] = SLOT1_BIC;
			break;
		default:
			msg->completion_code = CC_INVALID_DATA_FIELD;
			break;
		}

		if (msg->data[1] == NETFN_STORAGE_REQ) {
			msg->data[1] = msg->data[1] << 2;
		}
		break;
	case EXP2_IPMB:
		if (_1ou_status.card_type == TYPE_1OU_EXP_WITH_E1S) {
			target_IF = EXP1_IPMB;
		}
		break;
	case EXP4_IPMB:
		target_IF = EXP3_IPMB;
		break;
	default:
		break;
	}

	// Bridge to invalid or disabled interface
	if ((IPMB_inf_index_map[target_IF] == RESERVED) ||
	    (IPMB_config_table[IPMB_inf_index_map[target_IF]].interface == RESERVED_IF) ||
	    (IPMB_config_table[IPMB_inf_index_map[target_IF]].enable_status == DISABLE)) {
		LOG_ERR("OEM_MSG_OUT: Invalid bridge interface: %x", target_IF);
		msg->completion_code = CC_NOT_SUPP_IN_CURR_STATE;
	}

	// only send to target while msg is valid
	if (msg->completion_code == CC_SUCCESS) {
		bridge_msg = (ipmi_msg *)malloc(sizeof(ipmi_msg));
		if (bridge_msg == NULL) {
			msg->completion_code = CC_OUT_OF_SPACE;
			return;
		} else {
			memset(bridge_msg, 0, sizeof(ipmi_msg));

			LOG_DBG("bridge targetIf %x, len %d, netfn %x, cmd %x", target_IF,
				msg->data_len, msg->data[1] >> 2, msg->data[2]);

			if ((_1ou_status.card_type == TYPE_1OU_EXP_WITH_E1S) &&
			    ((msg->data[0] == EXP2_IPMB) || (msg->data[0] == EXP4_IPMB))) {
				bridge_msg->seq_source = msg->seq_source;
				bridge_msg->InF_target = msg->data[0];
				bridge_msg->InF_source = msg->InF_source;
				bridge_msg->netfn = NETFN_OEM_1S_REQ;
				bridge_msg->cmd = CMD_OEM_1S_MSG_OUT;
				bridge_msg->data[0] = IANA_ID & 0xFF;
				bridge_msg->data[1] = (IANA_ID >> 8) & 0xFF;
				bridge_msg->data[2] = (IANA_ID >> 16) & 0xFF;

				if (msg->data_len != 0) {
					memcpy(&bridge_msg->data[3], &msg->data[0],
					       msg->data_len * sizeof(msg->data[0]));
				}

				bridge_msg->data_len = msg->data_len + 3;
			} else {
				bridge_msg->data_len = msg->data_len - 3;
				bridge_msg->seq_source = msg->seq_source;
				bridge_msg->InF_target = msg->data[0];
				bridge_msg->InF_source = msg->InF_source;
				bridge_msg->netfn = msg->data[1] >> 2;
				bridge_msg->cmd = msg->data[2];

				if (bridge_msg->data_len != 0) {
					memcpy(&bridge_msg->data[0], &msg->data[3],
					       bridge_msg->data_len * sizeof(msg->data[0]));
				}
			}

			status = ipmb_send_request(bridge_msg, IPMB_inf_index_map[target_IF]);

			if (status != IPMB_ERROR_SUCCESS) {
				LOG_ERR("OEM_MSG_OUT send IPMB req fail status: %x", status);
				msg->completion_code = CC_BRIDGE_MSG_ERR;
			}
			SAFE_FREE(bridge_msg);
		}
	}

	// Return to source while data is invalid or sending req to Tx task fail
	if (msg->completion_code != CC_SUCCESS) {
		msg->data_len = 0;
		status = ipmb_send_response(msg, IPMB_inf_index_map[msg->InF_source]);
		if (status != IPMB_ERROR_SUCCESS) {
			LOG_ERR("OEM_MSG_OUT send IPMB resp fail status: %x", status);
		}
	}
#else
	msg->completion_code = CC_UNSPECIFIED_ERROR;
#endif
	return;
}
#endif

void OEM_1S_COPY_FLASH_IMAGE(ipmi_msg *msg)
{
	CHECK_NULL_ARG(msg);

	if (msg->data_len != 13) {
		msg->completion_code = CC_INVALID_LENGTH;
		return;
	}

	uint8_t copy_type = msg->data[0];
	uint32_t src_offset =
		msg->data[1] | (msg->data[2] << 8) | (msg->data[3] << 16) | (msg->data[4] << 24);
	uint32_t dest_offset =
		msg->data[5] | (msg->data[6] << 8) | (msg->data[7] << 16) | (msg->data[8] << 24);
	uint32_t length =
		msg->data[9] | (msg->data[10] << 8) | (msg->data[11] << 16) | (msg->data[12] << 24);

	if (((src_offset % SECTOR_SZ_4K) != 0) || ((dest_offset % SECTOR_SZ_4K) != 0) ||
	    ((length % SECTOR_SZ_4K) != 0)) {
		msg->completion_code = CC_INVALID_DATA_FIELD;
		return;
	}

	if (start_flash_copy(copy_type, src_offset, dest_offset, length)) {
		msg->completion_code = CC_UNSPECIFIED_ERROR;
		return;
	}

	msg->data_len = 0;
	msg->completion_code = CC_SUCCESS;
	return;
}

void GET_COPY_FLASH_STATUS(ipmi_msg *msg)
{
	CHECK_NULL_ARG(msg);

	FLASH_COPY_INFO current_info = { 0 };

	get_flash_copy_info(&current_info);

	msg->data[0] = current_info.status;
	msg->data[1] = current_info.completion_code;
	if ((current_info.total_length == 0)) {
		msg->data[2] = 0;
	} else {
		msg->data[2] = 100 * current_info.current_len / current_info.total_length;
	}
	msg->data_len = 3;
	msg->completion_code = CC_SUCCESS;
	return;
}

void OEM_1S_GET_HSC_STATUS(ipmi_msg *msg)
{
	CHECK_NULL_ARG(msg);

	if (msg->data_len != 0) {
		msg->completion_code = CC_INVALID_LENGTH;
		return;
	}

	uint8_t hsc_type = get_hsc_module();
	I2C_MSG i2c_msg;
	uint8_t retry = 5;

	i2c_msg.bus = I2C_BUS5;
	i2c_msg.tx_len = 1;
	i2c_msg.rx_len = 1;

	switch (hsc_type) {
	case HSC_MODULE_ADM1278:
		i2c_msg.target_addr = ADM1278_ADDR;
		i2c_msg.data[0] = PMBUS_STATUS_BYTE;
		break;
	case HSC_MODULE_LTC4282:
		i2c_msg.target_addr = LTC4282_ADDR;
		i2c_msg.data[0] = LTC4282_STATUS_OFFSET_BYTE1;
		break;
	case HSC_MODULE_MP5990:
		i2c_msg.target_addr = MP5990_ADDR;
		i2c_msg.data[0] = PMBUS_STATUS_BYTE;
		break;
	default:
		LOG_WRN("Unknown hsc module %d", hsc_type);
		msg->completion_code = CC_UNSPECIFIED_ERROR;
		return;
	}

	if (i2c_master_read(&i2c_msg, retry)) {
		LOG_WRN("Failed to read hsc status.");
		msg->completion_code = CC_TIMEOUT;
		return;
	}

	switch (hsc_type) {
	case HSC_MODULE_ADM1278:
	case HSC_MODULE_MP5990:
		msg->data[1] = i2c_msg.data[0] & 0x1C;
		break;
	case HSC_MODULE_LTC4282:
		msg->data[1] = ((i2c_msg.data[0] & BIT(0)) ? BIT(5) : 0) |
			       ((i2c_msg.data[0] & BIT(1)) ? BIT(3) : 0) |
			       ((i2c_msg.data[0] & BIT(2)) ? BIT(4) : 0);
		break;
	default:
		LOG_WRN("Unknown hsc module %d", hsc_type);
		msg->completion_code = CC_UNSPECIFIED_ERROR;
		return;
	}

	msg->data_len = 2;
	msg->data[0] = hsc_type;
	msg->completion_code = CC_SUCCESS;
	return;
}

uint8_t fw_update_pm8702(uint8_t cxl_id, uint8_t pcie_card_id, uint8_t next_active_slot,
			 uint32_t offset, uint16_t msg_len, uint8_t *msg_buf, bool sector_end)
{
	CHECK_NULL_ARG_WITH_RETURN(msg_buf, FWUPDATE_UPDATE_FAIL);

	if (offset > PM8702_UPDATE_MAX_OFFSET) {
		LOG_ERR("Offset: 0x%x is over PM8702 image size maximum", offset);
		return FWUPDATE_ERROR_OFFSET;
	}

	if (msg_len > PM8702_TRANSFER_FW_DATA_LEN) {
		LOG_ERR("Transfer data len over maximum, msg_len: 0x%x", msg_len);
		return FWUPDATE_OVER_LENGTH;
	}

	int req_len = 0;
	uint8_t resp_len = 0;
	pm8702_hbo_status_resp hbo_status = { 0 };

	k_msleep(PM8702_TRANSFER_DELAY_MS);
	if (pal_get_pm8702_hbo_status(pcie_card_id, (uint8_t *)&hbo_status, &resp_len) != true) {
		LOG_ERR("Fail to get HBO status");
		return FWUPDATE_UPDATE_FAIL;
	}

	if (hbo_status.bo_run != PM8702_NO_HBO_RUN_VAL) {
		LOG_ERR("PM8702 HBO bo_run");
		return FWUPDATE_UPDATE_FAIL;
	}

	if (hbo_status.return_code != PM8702_RETURN_SUCCESS) {
		LOG_ERR("PM8702 HBO return code: 0x%x, vendor status: 0x%x", hbo_status.return_code,
			hbo_status.vendor_status);
		return FWUPDATE_UPDATE_FAIL;
	}

	cci_transfer_fw_req update_fw_req = { 0 };
	req_len = PM8702_TRANSFER_FW_HEADER_LEN + msg_len;

	if (offset == PM8702_INITIATE_FW_OFFSET) {
		update_fw_req.action = INITIATE_FW_TRANSFER;
	} else if (sector_end == true) {
		update_fw_req.action = END_TRANSFER;
	} else {
		update_fw_req.action = CONTINUE_FW_TRANSFER;
	}

	update_fw_req.slot = next_active_slot;
	update_fw_req.offset = offset / PM8702_TRANSFER_FW_DATA_LEN;
	memcpy(update_fw_req.data, msg_buf, sizeof(uint8_t) * msg_len);

	k_msleep(PM8702_TRANSFER_DELAY_MS);

	if (pal_pm8702_transfer_fw(pcie_card_id, (uint8_t *)&update_fw_req, req_len) != true) {
		LOG_ERR("Fail to transfer PM8702 firmware");
		return FWUPDATE_UPDATE_FAIL;
	}

	return FWUPDATE_SUCCESS;
}

void OEM_1S_FW_UPDATE(ipmi_msg *msg)
{
	CHECK_NULL_ARG(msg);
	if (msg->data_len < 8) {
		msg->completion_code = CC_INVALID_LENGTH;
		return;
	}

	uint8_t target = msg->data[0];
	uint8_t status = -1;
	uint32_t offset =
		((msg->data[4] << 24) | (msg->data[3] << 16) | (msg->data[2] << 8) | msg->data[1]);
	uint16_t length = ((msg->data[6] << 8) | msg->data[5]);

	if ((length == 0) || (length != msg->data_len - 7)) {
		msg->completion_code = CC_INVALID_LENGTH;
		return;
	}

	if (target == BIOS_UPDATE || (target == (BIOS_UPDATE | IS_SECTOR_END_MASK))) {
		// BIOS size maximum 64M bytes
		if (offset > BIOS_UPDATE_MAX_OFFSET) {
			msg->completion_code = CC_PARAM_OUT_OF_RANGE;
			return;
		}
		int pos = pal_get_bios_flash_position();
		if (pos == -1) {
			msg->completion_code = CC_INVALID_PARAM;
			return;
		}

		// Switch GPIO(BIOS SPI Selection Pin) to BIC
		bool ret = pal_switch_bios_spi_mux(GPIO_HIGH);
		if (!ret) {
			msg->completion_code = CC_UNSPECIFIED_ERROR;
			return;
		}

		status = fw_update(offset, length, &msg->data[7], (target & IS_SECTOR_END_MASK),
				   pos);

		// Switch GPIO(BIOS SPI Selection Pin) to PCH
		ret = pal_switch_bios_spi_mux(GPIO_LOW);
		if (!ret) {
			msg->completion_code = CC_UNSPECIFIED_ERROR;
			return;
		}

	} else if ((target == BIC_UPDATE) || (target == (BIC_UPDATE | IS_SECTOR_END_MASK))) {
		// Expect BIC firmware size not bigger than 320k
		if (offset > BIC_UPDATE_MAX_OFFSET) {
			msg->completion_code = CC_PARAM_OUT_OF_RANGE;
			return;
		}
		status = fw_update(offset, length, &msg->data[7], (target & IS_SECTOR_END_MASK),
				   DEVSPI_FMC_CS0);

	} else if (target == CXL_UPDATE || (target == (CXL_UPDATE | IS_SECTOR_END_MASK))) {
		LOG_INF("%s target0x%x offset0x%x len0x%x", __func__, target, offset, length);

		uint8_t cxl_id = 0;

		if (pm8702_table[cxl_id].is_init != true) {
			bool ret = pal_init_pm8702_info(cxl_id);
			if (ret == false) {
				LOG_ERR("Initial cxl id: 0x%x info fail", cxl_id);
				msg->completion_code = CC_UNSPECIFIED_ERROR;
				return;
			}
		}

		uint8_t next_active_slot =
			pm8702_table[cxl_id].dev_info.fw_slot_info.fields.NEXT_ACTIVE_FW_SLOT;
		if (next_active_slot == PM8702_DEFAULT_NEXT_ACTIVE_SLOT) {
			uint8_t index = 0;
			uint8_t support_fw_slot = pm8702_table[cxl_id].dev_info.fw_slot_supported;

			for (index = 1; index <= support_fw_slot; ++index) {
				if (index != pm8702_table[cxl_id]
						     .dev_info.fw_slot_info.fields.ACTIVE_FW_SLOT) {
					next_active_slot = index;
				}
			}

			if (next_active_slot == PM8702_DEFAULT_NEXT_ACTIVE_SLOT) {
				LOG_ERR("Fail to find next active slot");
				msg->completion_code = CC_UNSPECIFIED_ERROR;
				return;
			}

			pm8702_table[cxl_id].dev_info.fw_slot_info.fields.NEXT_ACTIVE_FW_SLOT =
				next_active_slot;
		}

		status = fw_update_pm8702(cxl_id, 0, next_active_slot, offset, length,
					  &msg->data[7], (target & IS_SECTOR_END_MASK));

	} else if (target == PRoT_FLASH_UPDATE ||
		   (target == (PRoT_FLASH_UPDATE | IS_SECTOR_END_MASK))) {
		if (offset > BIOS_UPDATE_MAX_OFFSET) {
			msg->completion_code = CC_PARAM_OUT_OF_RANGE;
			return;
		}

		int pos = pal_get_prot_flash_position();
		if (pos == -1) {
			msg->completion_code = CC_INVALID_PARAM;
			return;
		}

		status = fw_update(offset, length, &msg->data[7], (target & IS_SECTOR_END_MASK),
				   pos);

	} else {
		msg->completion_code = CC_INVALID_DATA_FIELD;
		return;
	}

	msg->data_len = 0;

	switch (status) {
	case FWUPDATE_SUCCESS:
		msg->completion_code = CC_SUCCESS;
		break;
	case FWUPDATE_OUT_OF_HEAP:
		msg->completion_code = CC_LENGTH_EXCEEDED;
		break;
	case FWUPDATE_OVER_LENGTH:
		msg->completion_code = CC_OUT_OF_SPACE;
		break;
	case FWUPDATE_REPEATED_UPDATED:
		msg->completion_code = CC_INVALID_DATA_FIELD;
		break;
	case FWUPDATE_UPDATE_FAIL:
		msg->completion_code = CC_TIMEOUT;
		break;
	case FWUPDATE_ERROR_OFFSET:
		msg->completion_code = CC_PARAM_OUT_OF_RANGE;
		break;
	case FWUPDATE_NOT_SUPPORT:
		msg->completion_code = CC_INVALID_PARAM;
		break;
	default:
		msg->completion_code = CC_UNSPECIFIED_ERROR;
		break;
	}
	if (status != FWUPDATE_SUCCESS) {
		LOG_ERR("firmware (0x%02X) update failed cc: %x", target, msg->completion_code);
	}

	return;
}

void pal_get_cxl_version(ipmi_msg *msg)
{
	CHECK_NULL_ARG(msg);

	int ret = 0;
	mctp *mctp_inst = NULL;
	mctp_ext_params ext_params = { 0 };
	uint8_t read_len = 0;
	uint8_t resp_buf[GET_FW_INFO_REVISION_LEN] = { 0 };

	if (get_mctp_info_by_eid(MCTP_EID_CXL, &mctp_inst, &ext_params) == false) {
		msg->completion_code = CC_UNSPECIFIED_ERROR;
		LOG_WRN("===== %s MCTP_EID_CXL", __func__);
		return;
	}

	// CHECK_NULL_ARG(mctp_inst);

	ret = cci_get_chip_fw_version(mctp_inst, ext_params, resp_buf, &read_len);
	LOG_WRN("===== cci_get_chip_fw_version ret%d read_len%d", ret, read_len);
	if (ret == false) {
		msg->completion_code = CC_UNSPECIFIED_ERROR;
	} else {
		LOG_HEXDUMP_WRN(resp_buf, read_len, "===== resp_buf");
		memcpy(&msg->data[0], resp_buf, read_len);
		msg->data_len = read_len;
		msg->completion_code = CC_SUCCESS;
	}

	return;
}
