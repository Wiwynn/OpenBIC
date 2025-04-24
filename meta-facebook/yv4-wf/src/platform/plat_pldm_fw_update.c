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
#include <string.h>
#include <logging/log.h>
#include "libutil.h"
#include "pldm.h"
#include "pldm_firmware_update.h"
#include "plat_pldm_fw_update.h"
#include "plat_i2c.h"
#include "plat_pldm_sensor.h"
#include "plat_isr.h"
#include "plat_gpio.h"
#include "plat_power_seq.h"
#include "plat_version.h"
#include "power_status.h"
#include "mctp_ctrl.h"
#include "xdpe12284c.h"
#include "mp2971.h"
#include "ioexp_tca9555.h"
#include "cci.h"
#include "util_spi.h"
#include "plat_pldm_device_identifier.h"

LOG_MODULE_REGISTER(plat_fwupdate);

static struct pldm_downstream_identifier_table *downstream_table = NULL;
static uint8_t downstream_devices_count = 0;

static bool plat_pldm_vr_i2c_info_get(int comp_identifier, uint8_t *bus, uint8_t *addr);
static uint8_t plat_pldm_pre_vr_update(void *fw_update_param);
static uint8_t plat_pldm_post_vr_update(void *fw_update_param);
static bool plat_get_bic_fw_version(void *info_p, uint8_t *buf, uint8_t *len);
static bool plat_get_vr_fw_version(void *info_p, uint8_t *buf, uint8_t *len);
static bool plat_get_cxl_fw_version(void *info_p, uint8_t *buf, uint8_t *len);
static uint8_t plat_pldm_pre_cxl_update(void *fw_update_param);
static uint8_t plat_pldm_post_cxl_update(void *fw_update_param);
static uint8_t pldm_cxl_update(void *fw_update_param);
static void query_downstream_identifier_table_and_count();

enum FIRMWARE_COMPONENT {
	WF_COMPNT_BIC,
	WF_COMPNT_VR_PVDDQ_AB_ASIC1,
	WF_COMPNT_VR_PVDDQ_CD_ASIC1,
	WF_COMPNT_VR_PVDDQ_AB_ASIC2,
	WF_COMPNT_VR_PVDDQ_CD_ASIC2,
	WF_COMPNT_CXL1,
	WF_COMPNT_CXL2,
};

enum VR_TYPE {
	VR_TYPE_UNKNOWN,
	VR_TYPE_INF,
	VR_TYPE_MPS,
};

/* PLDM FW update table */
pldm_fw_update_info_t PLDMUPDATE_FW_CONFIG_TABLE[] = {
	{
		.enable = true,
		.comp_classification = COMP_CLASS_TYPE_DOWNSTREAM,
		.comp_identifier = WF_COMPNT_BIC,
		.comp_classification_index = 0x00,
		.pre_update_func = NULL,
		.update_func = pldm_bic_update,
		.pos_update_func = NULL,
		.inf = COMP_UPDATE_VIA_SPI,
		.activate_method = COMP_ACT_SELF,
		.self_act_func = pldm_bic_activate,
		.get_fw_version_fn = plat_get_bic_fw_version,
		.self_apply_work_func = NULL,
		.comp_version_str = NULL,
	},
	{
		.enable = true,
		.comp_classification = COMP_CLASS_TYPE_DOWNSTREAM,
		.comp_identifier = WF_COMPNT_VR_PVDDQ_AB_ASIC1,
		.comp_classification_index = 0x00,
		.pre_update_func = plat_pldm_pre_vr_update,
		.update_func = pldm_vr_update,
		.pos_update_func = plat_pldm_post_vr_update,
		.inf = COMP_UPDATE_VIA_I2C,
		.activate_method = COMP_ACT_AC_PWR_CYCLE,
		.self_act_func = NULL,
		.get_fw_version_fn = plat_get_vr_fw_version,
	},
	{
		.enable = true,
		.comp_classification = COMP_CLASS_TYPE_DOWNSTREAM,
		.comp_identifier = WF_COMPNT_VR_PVDDQ_CD_ASIC1,
		.comp_classification_index = 0x00,
		.pre_update_func = plat_pldm_pre_vr_update,
		.update_func = pldm_vr_update,
		.pos_update_func = plat_pldm_post_vr_update,
		.inf = COMP_UPDATE_VIA_I2C,
		.activate_method = COMP_ACT_AC_PWR_CYCLE,
		.self_act_func = NULL,
		.get_fw_version_fn = plat_get_vr_fw_version,
	},
	{
		.enable = true,
		.comp_classification = COMP_CLASS_TYPE_DOWNSTREAM,
		.comp_identifier = WF_COMPNT_VR_PVDDQ_AB_ASIC2,
		.comp_classification_index = 0x00,
		.pre_update_func = plat_pldm_pre_vr_update,
		.update_func = pldm_vr_update,
		.pos_update_func = plat_pldm_post_vr_update,
		.inf = COMP_UPDATE_VIA_I2C,
		.activate_method = COMP_ACT_AC_PWR_CYCLE,
		.self_act_func = NULL,
		.get_fw_version_fn = plat_get_vr_fw_version,
	},
	{
		.enable = true,
		.comp_classification = COMP_CLASS_TYPE_DOWNSTREAM,
		.comp_identifier = WF_COMPNT_VR_PVDDQ_CD_ASIC2,
		.comp_classification_index = 0x00,
		.pre_update_func = plat_pldm_pre_vr_update,
		.update_func = pldm_vr_update,
		.pos_update_func = plat_pldm_post_vr_update,
		.inf = COMP_UPDATE_VIA_I2C,
		.activate_method = COMP_ACT_AC_PWR_CYCLE,
		.self_act_func = NULL,
		.get_fw_version_fn = plat_get_vr_fw_version,
	},
	{
		.enable = true,
		.comp_classification = COMP_CLASS_TYPE_DOWNSTREAM,
		.comp_identifier = WF_COMPNT_CXL1,
		.comp_classification_index = 0x00,
		.pre_update_func = plat_pldm_pre_cxl_update,
		.update_func = pldm_cxl_update,
		.pos_update_func = plat_pldm_post_cxl_update,
		.inf = COMP_UPDATE_VIA_SPI,
		.activate_method = COMP_ACT_DC_PWR_CYCLE,
		.self_act_func = NULL,
		.get_fw_version_fn = plat_get_cxl_fw_version,
	},
	{
		.enable = true,
		.comp_classification = COMP_CLASS_TYPE_DOWNSTREAM,
		.comp_identifier = WF_COMPNT_CXL2,
		.comp_classification_index = 0x00,
		.pre_update_func = plat_pldm_pre_cxl_update,
		.update_func = pldm_cxl_update,
		.pos_update_func = plat_pldm_post_cxl_update,
		.inf = COMP_UPDATE_VIA_SPI,
		.activate_method = COMP_ACT_DC_PWR_CYCLE,
		.self_act_func = NULL,
		.get_fw_version_fn = plat_get_cxl_fw_version,
	},
};

// internal helper function to get downstream identifier
void query_downstream_identifier_table_and_count()
{
	struct pldm_downstream_identifier_table_and_count d = get_downstream_identifier_table();
	downstream_table = d.downstream_table;
	downstream_devices_count = d.downstream_devices_count;
}

#define fill(dest, src)                                                                            \
	memcpy(dest, &src, sizeof(src));                                                           \
	dest += sizeof(src);
#define fill_span(dest, src, size)                                                                 \
	memcpy(dest, src, size);                                                                   \
	dest += size;
uint8_t plat_pldm_query_device_identifiers(const uint8_t *buf, uint16_t len, uint8_t *resp,
					   uint16_t *resp_len)
{
	// check if input arguments are valid
	CHECK_NULL_ARG_WITH_RETURN(buf, false);
	CHECK_NULL_ARG_WITH_RETURN(resp, PLDM_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(resp_len, PLDM_ERROR);

	struct pldm_query_device_identifiers_resp *resp_p =
		(struct pldm_query_device_identifiers_resp *)resp;

	resp_p->completion_code = PLDM_SUCCESS;

	// formal descriptors
	const uint32_t iana = sys_cpu_to_be32(40981UL); // meta IANA number
	const uint16_t deviceId = sys_cpu_to_be16(0x2);
	const uint8_t slotNumber =
		plat_get_eid() / 10; // assuming using static EID, invalid if using dynamic EID
	const uint8_t slot[PLDM_ASCII_MODEL_NUMBER_SHORT_STRING_LENGTH] = { (char)(slotNumber +
										   '0') };

	// vendor defined descriptors
	const uint8_t *compatible_hardware_title = "OpenBMC.CompatibleHardware";
	const uint8_t *compatible_hardware_value =
		"com.meta.Hardware.Yosemite4.WailuaFalls.BIC.ASPEED_AST1030";
	const uint8_t *slot_title = "SlotNumber";
	const uint8_t vd_slot_number = slotNumber + '0';
	const uint8_t *slot_value = &vd_slot_number;

	const uint8_t compatible_hardware_title_length = strlen(compatible_hardware_title);
	const uint8_t compatible_hardware_value_length = strlen(compatible_hardware_value);
	const uint8_t slot_title_length = strlen(slot_title);
	const uint8_t slot_value_length = 1;
	const uint16_t vendor_defined_tlv_length = 2;
	const uint16_t compatible_hardware_descriptor_length = vendor_defined_tlv_length +
							       compatible_hardware_title_length +
							       compatible_hardware_value_length;
	const uint16_t slot_descriptor_length =
		vendor_defined_tlv_length + slot_title_length + slot_value_length;

	// tlv has 1 redundant byte for pointer, which is not included in the descriptor length
	const uint8_t tlv_length = 4;

	const struct warpped_tlv {
		uint16_t descriptor_type;
		uint16_t descriptor_length;
		uint8_t title_string_type;
		uint8_t title_string_length;
		const uint8_t *title_string;
		const uint8_t *descriptor_data;
	} tlvs[] = {
		{ PLDM_FWUP_IANA_ENTERPRISE_ID, PLDM_FWUP_IANA_ENTERPRISE_ID_LENGTH, 0, 0, NULL,
		  (uint8_t *)&iana },
		{ PLDM_PCI_DEVICE_ID, PLDM_PCI_DEVICE_ID_LENGTH, 0, 0, NULL, (uint8_t *)&deviceId },
		{ PLDM_ASCII_MODEL_NUMBER_SHORT_STRING, PLDM_ASCII_MODEL_NUMBER_SHORT_STRING_LENGTH,
		  0, 0, NULL, slot },
		{ PLDM_FWUP_VENDOR_DEFINED, compatible_hardware_descriptor_length, PLDM_COMP_ASCII,
		  compatible_hardware_title_length, compatible_hardware_title,
		  compatible_hardware_value },
		{ PLDM_FWUP_VENDOR_DEFINED, slot_descriptor_length, PLDM_COMP_ASCII,
		  slot_title_length, slot_title, slot_value },

	};
	resp_p->descriptor_count = ARRAY_SIZE(tlvs);

	// calculate total size of descriptors
	uint16_t total_size_of_descriptors = 0;
	for (int i = 0; i < resp_p->descriptor_count; i++) {
		total_size_of_descriptors += tlv_length + tlvs[i].descriptor_length;
	}
	resp_p->device_identifiers_len = total_size_of_descriptors;
	LOG_INF("Total size of descriptors: %d", total_size_of_descriptors);

	// check if total size of descriptors is over PLDM_MAX_DATA_SIZE
	if (sizeof(struct pldm_query_device_identifiers_resp) + total_size_of_descriptors >
	    PLDM_MAX_DATA_SIZE) {
		LOG_ERR("QueryDeviceIdentifiers data length is over PLDM_MAX_DATA_SIZE define size %d",
			PLDM_MAX_DATA_SIZE);
		resp_p->completion_code = PLDM_ERROR;
		return PLDM_ERROR;
	}

	// fill response
	uint8_t *resp_ptr = resp + sizeof(struct pldm_query_device_identifiers_resp);
	for (uint8_t i = 0; i < resp_p->descriptor_count; i++) {
		const struct warpped_tlv *tlv = &tlvs[i];
		fill(resp_ptr, tlv->descriptor_type);
		fill(resp_ptr, tlv->descriptor_length);
		uint16_t rest_of_data_length = tlv->descriptor_length;
		if (tlv->descriptor_type == PLDM_FWUP_VENDOR_DEFINED) {
			fill(resp_ptr, tlv->title_string_type);
			fill(resp_ptr, tlv->title_string_length);
			fill_span(resp_ptr, tlv->title_string, tlv->title_string_length);
			rest_of_data_length -= tlv->title_string_length + vendor_defined_tlv_length;
		}
		fill_span(resp_ptr, tlv->descriptor_data, rest_of_data_length);
	}
	*resp_len = sizeof(struct pldm_query_device_identifiers_resp) + total_size_of_descriptors;

	return PLDM_SUCCESS;
}

uint8_t plat_pldm_query_downstream_devices(const uint8_t *buf, uint16_t len, uint8_t *resp,
					   uint16_t *resp_len)
{
	CHECK_NULL_ARG_WITH_RETURN(buf, false);
	CHECK_NULL_ARG_WITH_RETURN(resp, PLDM_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(resp_len, PLDM_ERROR);

	struct pldm_query_downstream_devices_resp *resp_p =
		(struct pldm_query_downstream_devices_resp *)resp;

	resp_p->completion_code = PLDM_SUCCESS;
	resp_p->downstream_device_update_supported = PLDM_FW_UPDATE_SUPPORT_DOWNSTREAM_DEVICES;
	resp_p->number_of_downstream_devices = 6;
	resp_p->max_number_of_downstream_devices = 6;

	resp_p->capabilities.dynamically_attached = 0;
	resp_p->capabilities.dynamically_removed = 0;
	resp_p->capabilities.support_update_simultaneously = 0;

	*resp_len = sizeof(struct pldm_query_downstream_devices_resp);

	return PLDM_SUCCESS;
}

static uint8_t get_returned_devices_start_index(struct pldm_query_downstream_identifier_req *req,
						uint32_t *index)
{
	switch (req->transferoperationflag) {
	case PLDM_FW_UPDATE_GET_FIRST_PART:
		*(index) = 0;
		break;
	case PLDM_FW_UPDATE_GET_NEXT_PART:
		if (req->datatransferhandle >= downstream_devices_count) {
			LOG_ERR("%s:%s:%d: Invalid data transfer handle: 0x%x", __FILE__, __func__,
				__LINE__, req->datatransferhandle);
			return PLDM_FW_UPDATE_CC_INVALID_TRANSFER_HANDLE;
		}
		*(index) = req->datatransferhandle;
		break;
	default:
		LOG_ERR("%s:%s:%d: Invalid transfer operation flag: 0x%x", __FILE__, __func__,
			__LINE__, req->transferoperationflag);
		return PLDM_FW_UPDATE_CC_INVALID_TRANSFER_OPERATION_FLAG;
	}

	return PLDM_SUCCESS;
}

static size_t calculate_descriptors_size(struct pldm_descriptor_string *descriptors, uint8_t count)
{
	size_t size = 0;
	for (size_t i = 0; i < count; i++) {
		size += strlen(descriptors[i].descriptor_data);
		switch (descriptors[i].descriptor_type) {
		case PLDM_FWUP_VENDOR_DEFINED:
			size += sizeof(struct pldm_vendor_defined_descriptor_tlv) +
						descriptors[i].title_string ?
					strlen(descriptors[i].title_string) :
					0;
			break;
		default:
			size += sizeof(struct pldm_descriptor_tlv);
			break;
		}
	}

	return size;
}

static bool remaining_data_can_be_returned_in_one_transaction(uint32_t start_index,
							      uint32_t *next_transaction_index)
{
	if (!downstream_table) {
		query_downstream_identifier_table_and_count();
	}
	size_t total_size = sizeof(pldm_hdr) + sizeof(struct pldm_query_downstream_identifier_resp);
	uint32_t i = start_index;
	while (i < downstream_devices_count) {
		total_size += sizeof(struct pldm_downstream_device) +
			      calculate_descriptors_size(downstream_table[i].descriptor,
							 downstream_table[i].descriptor_count);
		if (total_size >= PLDM_MAX_DATA_SIZE) {
			*next_transaction_index = i;
			return false;
		}

		i++;
	}
	*next_transaction_index = 0;

	return true;
}

uint8_t plat_pldm_query_downstream_identifiers(const uint8_t *buf, uint16_t len, uint8_t *resp,
					       uint16_t *resp_len)
{
	if (!downstream_table) {
		query_downstream_identifier_table_and_count();
	}
	CHECK_NULL_ARG_WITH_RETURN(buf, PLDM_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(resp, PLDM_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(resp_len, PLDM_ERROR);

	uint8_t rc = PLDM_ERROR;

	struct pldm_query_downstream_identifier_req *req_p =
		(struct pldm_query_downstream_identifier_req *)buf;
	struct pldm_query_downstream_identifier_resp *resp_p =
		(struct pldm_query_downstream_identifier_resp *)resp;

	resp_p->completion_code = PLDM_ERROR;

	uint32_t start_index = 0;
	rc = get_returned_devices_start_index(req_p, &start_index);
	if (rc) {
		LOG_ERR("%s:%s:%d: Failed to get returning devices start index.", __FILE__,
			__func__, __LINE__);
		return rc;
	}

	uint32_t next_transaction_index = 0;
	if (remaining_data_can_be_returned_in_one_transaction(start_index,
							      &next_transaction_index)) {
		resp_p->nextdatatransferhandle = 0;
		resp_p->numbwerofdownstreamdevice = downstream_devices_count - start_index;
		switch (req_p->transferoperationflag) {
		case PLDM_FW_UPDATE_GET_FIRST_PART:
			resp_p->transferflag = PLDM_FW_UPDATE_TRANSFER_START_AND_END;
			break;
		case PLDM_FW_UPDATE_GET_NEXT_PART:
			resp_p->transferflag = PLDM_FW_UPDATE_TRANSFER_END;
			break;
		}
	} else {
		resp_p->nextdatatransferhandle = next_transaction_index;
		resp_p->numbwerofdownstreamdevice = resp_p->nextdatatransferhandle - start_index;
		switch (req_p->transferoperationflag) {
		case PLDM_FW_UPDATE_GET_FIRST_PART:
			resp_p->transferflag = PLDM_FW_UPDATE_TRANSFER_START;
			break;
		case PLDM_FW_UPDATE_GET_NEXT_PART:
			resp_p->transferflag = PLDM_FW_UPDATE_TRANSFER_MIDDLE;
			break;
		}
	}

	uint32_t downstream_devices_length = 0;
	uint8_t curr_descriptor_length = 0;
	struct pldm_downstream_device *curr_device =
		(struct pldm_downstream_device
			 *)(resp + sizeof(struct pldm_query_downstream_identifier_resp));
	struct pldm_descriptor_string *curr_descriptors_tbl;

	for (uint32_t i = start_index; i < start_index + resp_p->numbwerofdownstreamdevice; i++) {
		curr_descriptors_tbl = downstream_table[i].descriptor;
		curr_device->downstreamdeviceindex = i + 1;
		curr_device->downstreamdescriptorcount = downstream_table[i].descriptor_count;
		downstream_devices_length += sizeof(struct pldm_downstream_device);
		uint8_t *descriptor_ptr = curr_device->downstreamdescriptors;
		for (uint32_t j = 0; j < downstream_table[i].descriptor_count; j++) {
			rc = fill_descriptor_into_buf(&curr_descriptors_tbl[j], descriptor_ptr,
						      &curr_descriptor_length,
						      downstream_devices_length);
			if (rc) {
				LOG_ERR("%s:%s:%d: Fill device descriptor into buffer fail.",
					__FILE__, __func__, __LINE__);
				return PLDM_ERROR;
			}
			downstream_devices_length += curr_descriptor_length;
			descriptor_ptr += curr_descriptor_length;
		}

		curr_device = (struct pldm_downstream_device *)descriptor_ptr;
	}

	resp_p->downstreamdevicelength = downstream_devices_length;
	*resp_len =
		sizeof(struct pldm_query_downstream_identifier_resp) + downstream_devices_length;
	resp_p->completion_code = PLDM_SUCCESS;

	return PLDM_SUCCESS;
}

void load_pldmupdate_comp_config(void)
{
	if (comp_config) {
		LOG_WRN("PLDM update component table has already been load");
		return;
	}

	comp_config_count = ARRAY_SIZE(PLDMUPDATE_FW_CONFIG_TABLE);
	comp_config = malloc(sizeof(pldm_fw_update_info_t) * comp_config_count);
	if (!comp_config) {
		LOG_ERR("comp_config malloc failed");
		return;
	}

	memcpy(comp_config, PLDMUPDATE_FW_CONFIG_TABLE, sizeof(PLDMUPDATE_FW_CONFIG_TABLE));
}

static bool plat_pldm_vr_i2c_info_get(int comp_identifier, uint8_t *bus, uint8_t *addr)
{
	switch (comp_identifier) {
	case WF_COMPNT_VR_PVDDQ_AB_ASIC1:
		*bus = (uint8_t)I2C_BUS8;
		*addr = (uint8_t)ADDR_VR_PVDDQ_AB_ASIC1;
		break;
	case WF_COMPNT_VR_PVDDQ_CD_ASIC1:
		*bus = (uint8_t)I2C_BUS8;
		*addr = (uint8_t)ADDR_VR_PVDDQ_CD_ASIC1;
		break;
	case WF_COMPNT_VR_PVDDQ_AB_ASIC2:
		*bus = (uint8_t)I2C_BUS3;
		*addr = (uint8_t)ADDR_VR_PVDDQ_AB_ASIC2;
		break;
	case WF_COMPNT_VR_PVDDQ_CD_ASIC2:
		*bus = (uint8_t)I2C_BUS3;
		*addr = (uint8_t)ADDR_VR_PVDDQ_CD_ASIC2;
		break;
	default:
		LOG_ERR("Unknown component identifier for VR");
		return false;
	}
	return true;
}

static uint8_t plat_pldm_pre_vr_update(void *fw_update_param)
{
	CHECK_NULL_ARG_WITH_RETURN(fw_update_param, 1);

	pldm_fw_update_param_t *p = (pldm_fw_update_param_t *)fw_update_param;

	/* Stop sensor polling */
	set_cxl_vr_access(MAX_CXL_ID, false);
	// Wait sensor monitoring thread to stop
	k_msleep(10);

	plat_pldm_vr_i2c_info_get(p->comp_id, &p->bus, &p->addr);

	return 0;
}

static uint8_t plat_pldm_post_vr_update(void *fw_update_param)
{
	ARG_UNUSED(fw_update_param);

	set_cxl_vr_access(MAX_CXL_ID, true);

	return 0;
}

static bool plat_get_cxl_fw_version(void *info_p, uint8_t *buf, uint8_t *len)
{
	CHECK_NULL_ARG_WITH_RETURN(info_p, false);
	CHECK_NULL_ARG_WITH_RETURN(buf, false);
	CHECK_NULL_ARG_WITH_RETURN(len, false);

	pldm_fw_update_info_t *p = (pldm_fw_update_info_t *)info_p;

	uint8_t cxl_eid = plat_get_eid();
	uint8_t cxl_comp_id = p->comp_identifier;
	switch (cxl_comp_id) {
	case WF_COMPNT_CXL1:
		if (get_cxl_ready_status(CXL_ID_1) == false) {
			LOG_WRN("CXL1 not ready");
			return false;
		}
		cxl_eid += 2;
		break;
	case WF_COMPNT_CXL2:
		if (get_cxl_ready_status(CXL_ID_2) == false) {
			LOG_WRN("CXL2 not ready");
			return false;
		}
		cxl_eid += 3;
		break;
	default:
		LOG_ERR("Unknown CXL component ID %d", cxl_comp_id);
		return false;
	}

	mctp *mctp_inst = NULL;
	mctp_ext_params ext_params = { 0 };

	if (!get_mctp_info_by_eid(cxl_eid, &mctp_inst, &ext_params)) {
		LOG_ERR("Fail to get mctp info via eid: %d", cxl_eid);
		return false;
	}

	return cci_get_chip_fw_version(mctp_inst, ext_params, buf, len);
}

static bool plat_get_bic_fw_version(void *info_p, uint8_t *buf, uint8_t *len)
{
	CHECK_NULL_ARG_WITH_RETURN(info_p, false);
	CHECK_NULL_ARG_WITH_RETURN(buf, false);
	CHECK_NULL_ARG_WITH_RETURN(len, false);

	uint8_t tmp_buf[4];
	uint8_t idx = 0;

#ifdef BIC_FW_VERSION_ADD_FRU_NAME
	buf[idx++] = (char)BIC_FW_platform_0;
	buf[idx++] = (char)BIC_FW_platform_1;
#endif
	tmp_buf[0] = BIC_FW_YEAR_MSB;
	tmp_buf[1] = BIC_FW_YEAR_LSB;
	tmp_buf[2] = BIC_FW_WEEK;
	tmp_buf[3] = BIC_FW_VER;

	idx += bin2hex(tmp_buf, 2, &buf[idx], 4);
	buf[idx++] = '.';

	idx += bin2hex(&tmp_buf[2], 1, &buf[idx], 2);
	buf[idx++] = '.';

	idx += bin2hex(&tmp_buf[3], 1, &buf[idx], 2);

	*len = idx;

	return true;
}

static bool plat_get_vr_fw_version(void *info_p, uint8_t *buf, uint8_t *len)
{
	CHECK_NULL_ARG_WITH_RETURN(info_p, false);
	CHECK_NULL_ARG_WITH_RETURN(buf, false);
	CHECK_NULL_ARG_WITH_RETURN(len, false);

	pldm_fw_update_info_t *p = (pldm_fw_update_info_t *)info_p;

	bool ret = false;
	uint8_t bus = 0;
	uint8_t addr = 0;
	uint8_t dev_id = 0;
	uint8_t vr_type = VR_TYPE_UNKNOWN;
	uint32_t version;
	uint16_t remain = 0xFFFF;
	uint8_t value = 0x0;
	uint8_t vr_comp_id = p->comp_identifier;

	get_ioe_value(ADDR_IOE2, TCA9555_OUTPUT_PORT_REG_0, &value);
	switch (vr_comp_id) {
	case WF_COMPNT_VR_PVDDQ_AB_ASIC1:
	case WF_COMPNT_VR_PVDDQ_CD_ASIC1:
		if ((value & IOE_SWITCH_CXL1_VR_TO_BIC) == 0) {
			LOG_WRN("The ASIC1 VR SMBus has not yet been switched to BIC");
			return false;
		}
		break;
	case WF_COMPNT_VR_PVDDQ_AB_ASIC2:
	case WF_COMPNT_VR_PVDDQ_CD_ASIC2:
		if ((value & IOE_SWITCH_CXL2_VR_TO_BIC) == 0) {
			LOG_WRN("The ASIC2 VR SMBus has not yet been switched to BIC");
			return false;
		}
		break;
	default:
		LOG_ERR("Unknown VR component ID %d", vr_comp_id);
		return false;
	}

	plat_pldm_vr_i2c_info_get(p->comp_identifier, &bus, &addr);

	get_ioe_value(ADDR_IOE3, TCA9555_INPUT_PORT_REG_1, &dev_id);
	if ((dev_id & 0x10) == GPIO_LOW) {
		vr_type = VR_TYPE_INF;
	} else {
		vr_type = VR_TYPE_MPS;
	}

	const char *vr_name[] = {
		[VR_TYPE_UNKNOWN] = NULL,
		[VR_TYPE_INF] = "Infineon ",
		[VR_TYPE_MPS] = "MPS ",
	};

	const uint8_t *vr_name_p = vr_name[vr_type];
	set_cxl_vr_access(MAX_CXL_ID, false);
	// Wait sensor monitoring thread to stop
	k_msleep(10);
	switch (vr_type) {
	case VR_TYPE_INF:
		if (!xdpe12284c_get_checksum(bus, addr, (uint8_t *)&version)) {
			LOG_ERR("The VR XDPE12284 version reading failed");
			return ret;
		}

		if (!xdpe12284c_get_remaining_write(bus, addr, &remain)) {
			LOG_ERR("The VR XDPE12284 remaining reading failed");
			return ret;
		}
		break;
	case VR_TYPE_MPS:
		if (!mp2971_get_checksum(bus, addr, &version)) {
			LOG_ERR("Read VR checksum failed");
			return ret;
		}
		break;
	default:
		LOG_ERR("Unknown VR device");
		return ret;
	}

	set_cxl_vr_access(MAX_CXL_ID, true);

	const char *remain_str_p = ", Remaining Write: ";
	uint8_t *buf_p = buf;
	if (!vr_name_p) {
		LOG_ERR("The pointer of VR string name is NULL");
		return ret;
	}
	*len = 0;

	if (PLDM_MAX_DATA_SIZE < (strlen(vr_name_p) + strlen(remain_str_p) + 10)) {
		LOG_ERR("vr version string wiil be too long to operate, failed");
		return ret;
	}

	memcpy(buf_p, vr_name_p, strlen(vr_name_p));
	buf_p += strlen(vr_name_p);
	*len += bin2hex((uint8_t *)&version, 4, buf_p, 8) + strlen(vr_name_p);
	buf_p += 8;

	if (remain != 0xFFFF) {
		memcpy(buf_p, remain_str_p, strlen(remain_str_p));
		buf_p += strlen(remain_str_p);
		remain = (uint8_t)((remain % 10) | (remain / 10 << 4));
		*len += bin2hex((uint8_t *)&remain, 1, buf_p, 2) + strlen(remain_str_p);
		buf_p += 2;
	}

	ret = true;

	return ret;
}

static uint8_t plat_pldm_pre_cxl_update(void *fw_update_param)
{
	CHECK_NULL_ARG_WITH_RETURN(fw_update_param, 1);

	pldm_fw_update_param_t *p = (pldm_fw_update_param_t *)fw_update_param;
	uint8_t cxl_comp_id = p->comp_id;
	uint8_t value = 0;

	if (get_ioe_value(ADDR_IOE1, TCA9555_OUTPUT_PORT_REG_0, &value) != 0) {
		return 1;
	}

	switch (cxl_comp_id) {
	case WF_COMPNT_CXL1:
		// Switch SPI1 MUX to BIC
		value = SETBIT(value, IOE_P05);
		break;
	case WF_COMPNT_CXL2:
		// Switch SPI2 MUX to BIC
		value = SETBIT(value, IOE_P06);
		break;
	default:
		LOG_ERR("Unknown CXL component ID %d", cxl_comp_id);
		return 1;
	}

	set_ioe_value(ADDR_IOE1, TCA9555_OUTPUT_PORT_REG_0, value);

	return 0;
}

static uint8_t plat_pldm_post_cxl_update(void *fw_update_param)
{
	CHECK_NULL_ARG_WITH_RETURN(fw_update_param, 1);

	pldm_fw_update_param_t *p = (pldm_fw_update_param_t *)fw_update_param;
	uint8_t cxl_comp_id = p->comp_id;
	uint8_t value = 0;

	if (get_ioe_value(ADDR_IOE1, TCA9555_OUTPUT_PORT_REG_0, &value) != 0) {
		return 1;
	}

	switch (cxl_comp_id) {
	case WF_COMPNT_CXL1:
		// Switch SPI1 MUX to CXL
		value = CLEARBIT(value, IOE_P05);
		break;
	case WF_COMPNT_CXL2:
		// Switch SPI2 MUX to CXL
		value = CLEARBIT(value, IOE_P06);
		break;
	default:
		LOG_ERR("Unknown CXL component ID %d", cxl_comp_id);
		return 1;
	}

	set_ioe_value(ADDR_IOE1, TCA9555_OUTPUT_PORT_REG_0, value);

	return 0;
}

static uint8_t pldm_cxl_update(void *fw_update_param)
{
	CHECK_NULL_ARG_WITH_RETURN(fw_update_param, 1);

	pldm_fw_update_param_t *p = (pldm_fw_update_param_t *)fw_update_param;

	CHECK_NULL_ARG_WITH_RETURN(p->data, 1);

	uint8_t update_flag = 0;

	// Prepare next data offset and length
	p->next_ofs = p->data_ofs + p->data_len;
	p->next_len = fw_update_cfg.max_buff_size;

	if (p->next_ofs < fw_update_cfg.image_size) {
		if (p->next_ofs + p->next_len > fw_update_cfg.image_size)
			p->next_len = fw_update_cfg.image_size - p->next_ofs;

		if (((p->next_ofs % SECTOR_SZ_64K) + p->next_len) > SECTOR_SZ_64K)
			p->next_len = SECTOR_SZ_64K - (p->next_ofs % SECTOR_SZ_64K);
	} else {
		// Current data is the last packet
		// Set the next data length to 0 to inform the update completely
		p->next_len = 0;
		update_flag = (SECTOR_END_FLAG | NO_RESET_FLAG);
	}

	uint8_t cxl_comp_id = p->comp_id;
	uint8_t spi_device = 0xFF;
	switch (cxl_comp_id) {
	case WF_COMPNT_CXL1:
		spi_device = DEVSPI_SPI1_CS0;
		break;
	case WF_COMPNT_CXL2:
		spi_device = DEVSPI_SPI2_CS0;
		break;
	default:
		LOG_ERR("Unknown CXL component ID %d", cxl_comp_id);
		return 1;
	}

	uint8_t ret = fw_update(p->data_ofs, p->data_len, p->data, update_flag, spi_device);

	CHECK_PLDM_FW_UPDATE_RESULT_WITH_RETURN(p->comp_id, p->data_ofs, p->data_len, ret, 1);

	return 0;
}
