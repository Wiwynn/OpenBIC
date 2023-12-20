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
#include "util_spi.h"
#include "sensor.h"
#include "pldm_firmware_update.h"
#include "plat_pldm_fw_update.h"
#include "plat_ipmi.h"
#include "plat_gpio.h"
#include "plat_i2c.h"
#include "plat_sensor_table.h"
#include "plat_hook.h"
#include "plat_class.h"
#include "lattice.h"
#include "plat_pldm_device_identifier.h"

LOG_MODULE_REGISTER(plat_fwupdate);

#define CPLD_BUS_13_ADDR 0x40
#define CPLD_USER_CODE_LENGTH 4

#define PLDM_DOWNSTREAM_START_FLAG 1

static uint8_t pldm_pre_cpld_update(void *fw_update_param);
static uint8_t plat_pldm_cpld_update(void *fw_update_param);
static bool get_cpld_user_code(void *info_p, uint8_t *buf, uint8_t *len);

/* PLDM FW update table */
pldm_fw_update_info_t PLDMUPDATE_FW_CONFIG_TABLE[] = {
	{
		.enable = true,
		.comp_classification = COMP_CLASS_TYPE_DOWNSTREAM,
		.comp_identifier = MC_COMPNT_BIC,
		.comp_classification_index = 0x00,
		.pre_update_func = NULL,
		.update_func = pldm_bic_update,
		.pos_update_func = NULL,
		.inf = COMP_UPDATE_VIA_SPI,
		.activate_method = COMP_ACT_SELF,
		.self_act_func = pldm_bic_activate,
		.get_fw_version_fn = NULL,
		.self_apply_work_func = NULL,
		.comp_version_str = "bic",
	},
	{
		.enable = true,
		.comp_classification = COMP_CLASS_TYPE_DOWNSTREAM,
		.comp_identifier = MC_COMPNT_CPLD,
		.comp_classification_index = 0x00,
		.pre_update_func = pldm_pre_cpld_update,
		.update_func = plat_pldm_cpld_update,
		.pos_update_func = NULL,
		.inf = COMP_UPDATE_VIA_I2C,
		.activate_method = COMP_ACT_AC_PWR_CYCLE,
		.self_act_func = NULL,
		.get_fw_version_fn = get_cpld_user_code,
		.self_apply_work_func = NULL,
		.comp_version_str = "cpld",
	},
};

static uint8_t pldm_pre_cpld_update(void *fw_update_param)
{
	CHECK_NULL_ARG_WITH_RETURN(fw_update_param, PLDM_FW_UPDATE_ERROR);

	pldm_fw_update_param_t *p = (pldm_fw_update_param_t *)fw_update_param;

	if (p->inf == COMP_UPDATE_VIA_I2C) {
		p->bus = I2C_BUS13;
		p->addr = CPLD_BUS_13_ADDR;
	}

	return PLDM_FW_UPDATE_SUCCESS;
}

static bool get_cpld_user_code(void *info_p, uint8_t *buf, uint8_t *len)
{
	CHECK_NULL_ARG_WITH_RETURN(buf, false);
	CHECK_NULL_ARG_WITH_RETURN(len, false);
	ARG_UNUSED(info_p);

	bool ret = false;
	uint8_t tmp_buf[4] = { 0 };
	uint32_t read_usrcode = 0;

	ret = cpld_i2c_get_usercode(I2C_BUS13, CPLD_BUS_13_ADDR, &read_usrcode);
	if (ret != true) {
		LOG_ERR("Fail to get CPLD usercode");
		return false;
	}

	memcpy(tmp_buf, &read_usrcode, CPLD_USER_CODE_LENGTH);
	*len = bin2hex(tmp_buf, 4, buf, 8);
	return true;
}

static uint8_t plat_pldm_cpld_update(void *fw_update_param)
{
	CHECK_NULL_ARG_WITH_RETURN(fw_update_param, PLDM_FW_UPDATE_ERROR);

	pldm_fw_update_param_t *p = (pldm_fw_update_param_t *)fw_update_param;

	CHECK_NULL_ARG_WITH_RETURN(p->data, PLDM_FW_UPDATE_ERROR);

	lattice_update_config_t cpld_update_cfg;
	cpld_update_cfg.interface = p->inf;
	cpld_update_cfg.type = find_type_by_str("LCMXO3-4300C");
	cpld_update_cfg.bus = p->bus;
	cpld_update_cfg.addr = p->addr;
	cpld_update_cfg.data = p->data;
	cpld_update_cfg.data_len = p->data_len;
	cpld_update_cfg.data_ofs = p->data_ofs;

	if (lattice_fwupdate(&cpld_update_cfg) == false) {
		return PLDM_FW_UPDATE_ERROR;
	}

	p->next_len = cpld_update_cfg.next_len;
	p->next_ofs = cpld_update_cfg.next_ofs;

	return PLDM_FW_UPDATE_SUCCESS;
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

void clear_pending_version(uint8_t activate_method)
{
	if (!comp_config || !comp_config_count) {
		LOG_ERR("Component configuration is empty");
		return;
	}

	for (uint8_t i = 0; i < comp_config_count; i++) {
		if (comp_config[i].activate_method == activate_method)
			SAFE_FREE(comp_config[i].pending_version_p);
	}
}

uint8_t plat_pldm_query_device_identifiers(const uint8_t *buf, uint16_t len, uint8_t *resp,
					   uint16_t *resp_len)
{
	CHECK_NULL_ARG_WITH_RETURN(buf, PLDM_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(resp, PLDM_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(resp_len, PLDM_ERROR);

	uint8_t index = 0;
	uint8_t ret = PLDM_ERROR;
	uint8_t length = 0;
	uint8_t *end_of_id_ptr =
		(uint8_t *)resp + sizeof(struct pldm_query_device_identifiers_resp);
	struct pldm_query_device_identifiers_resp *resp_p =
		(struct pldm_query_device_identifiers_resp *)resp;

	resp_p->completion_code = PLDM_ERROR;
	resp_p->descriptor_count = bic_descriptors_count;

	uint16_t total_size_of_descriptor = 0;

	for (index = 0; index < bic_descriptors_count; ++index) {
		ret = fill_descriptor_into_buf(&PLDM_DEVICE_DESCRIPTOR_TABLE[index], end_of_id_ptr,
					       &length, total_size_of_descriptor);
		if (ret != PLDM_SUCCESS) {
			LOG_ERR("Fill device descriptor into buffer fail");
			continue;
		}

		total_size_of_descriptor += length;
		end_of_id_ptr += length;
	}

	resp_p->device_identifiers_len = total_size_of_descriptor;
	*resp_len = sizeof(struct pldm_query_device_identifiers_resp) + total_size_of_descriptor;
	resp_p->completion_code = PLDM_SUCCESS;
	return PLDM_SUCCESS;
}

uint8_t plat_pldm_query_downstream_identifiers(const uint8_t *buf, uint16_t len, uint8_t *resp,
					       uint16_t *resp_len)
{
	CHECK_NULL_ARG_WITH_RETURN(buf, PLDM_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(resp, PLDM_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(resp_len, PLDM_ERROR);

	uint8_t ret = PLDM_ERROR;
	uint8_t index = 0;
	uint8_t length = 0;
	uint8_t *end_of_id_ptr =
		(uint8_t *)resp + sizeof(struct pldm_query_downstream_identifier_resp);
	struct pldm_query_downstream_identifier_req *req_p =
		(struct pldm_query_downstream_identifier_req *)buf;
	struct pldm_query_downstream_identifier_resp *resp_p =
		(struct pldm_query_downstream_identifier_resp *)resp;

	resp_p->completion_code = PLDM_ERROR;
	switch (req_p->transferoperationflag) {
	case PLDM_FW_UPDATE_GET_FIRST_PART:
		req_p->datatransferhandle = 0;
		resp_p->transferflag = PLDM_FW_UPDATE_TRANSFER_START;
		resp_p->nextdatatransferhandle = PLDM_DOWNSTREAM_START_FLAG;

		if (downstream_table_count == 1) {
			resp_p->transferflag = PLDM_FW_UPDATE_TRANSFER_START_AND_END;
		}
		break;
	case PLDM_FW_UPDATE_GET_NEXT_PART:
		if (req_p->datatransferhandle >= downstream_table_count) {
			return ret;
		}
		if (req_p->datatransferhandle == (downstream_table_count - 1)) {
			resp_p->transferflag = PLDM_FW_UPDATE_TRANSFER_END;
		} else {
			resp_p->transferflag = PLDM_FW_UPDATE_TRANSFER_MIDDLE;
			resp_p->nextdatatransferhandle = (req_p->datatransferhandle + 1);
		}
		break;
	default:
		LOG_ERR("Invalid transfer operation flag: 0x%x", req_p->transferoperationflag);
		return ret;
	}

	resp_p->numbwerofdownstreamdevice =
		downstream_table[req_p->datatransferhandle].descriptor_count;
	resp_p->downstreamdeviceindex = req_p->datatransferhandle;

	uint16_t total_size_of_descriptor = 0;
	struct pldm_descriptor_string *descriptor_table =
		downstream_table[req_p->datatransferhandle].descriptor;
	for (index = 0; index < downstream_table[req_p->datatransferhandle].descriptor_count;
	     ++index) {
		ret = fill_descriptor_into_buf(&descriptor_table[index], end_of_id_ptr, &length,
					       total_size_of_descriptor);
		if (ret != PLDM_SUCCESS) {
			LOG_ERR("Fill device descriptor into buffer fail");
			continue;
		}

		total_size_of_descriptor += length;
		end_of_id_ptr += length;
	}

	resp_p->downstreamdevicelength = total_size_of_descriptor + sizeof(uint16_t) +
					 sizeof(resp_p->downstreamdeviceindex) +
					 sizeof(resp_p->downstreamdescriptorcount);
	resp_p->downstreamdescriptorcount = total_size_of_descriptor;
	*resp_len = sizeof(struct pldm_query_downstream_identifier_resp) + total_size_of_descriptor;
	resp_p->completion_code = PLDM_SUCCESS;
	return PLDM_SUCCESS;
}
