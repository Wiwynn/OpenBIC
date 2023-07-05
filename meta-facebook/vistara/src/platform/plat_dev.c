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
#include "sensor.h"
#include "pmbus.h"
#include "libutil.h"
#include "hal_i2c.h"
#include "plat_dev.h"
#include "util_pmbus.h"
#include "plat_def.h"
#include "pm8702.h"
#include "cci.h"
#include "plat_mctp.h"
#include "util_sys.h"

LOG_MODULE_REGISTER(plat_dev);

#define PM8702_DEFAULT_SENSOR_NUM SENSOR_NUM_TEMP_CXL

pm8702_dev_info pm8702_table[] = {
	{ .is_init = false }, 
};

uint8_t pal_pm8702_read(uint8_t card_id, sensor_cfg *cfg, int *reading)
{
	CHECK_NULL_ARG_WITH_RETURN(cfg, SENSOR_UNSPECIFIED_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(reading, SENSOR_UNSPECIFIED_ERROR);

	if (cfg->num > SENSOR_NUM_MAX) {
		return SENSOR_UNSPECIFIED_ERROR;
	}
	uint8_t port = cfg->port;
	uint8_t address = cfg->target_addr;
	uint8_t pm8702_access = cfg->offset;

	mctp *mctp_inst = NULL;
	mctp_ext_params ext_params = { 0 };
	sensor_val *sval = (sensor_val *)reading;
	if (get_mctp_info_by_eid(port, &mctp_inst, &ext_params) == false) {
		return SENSOR_UNSPECIFIED_ERROR;
	}

	CHECK_NULL_ARG_WITH_RETURN(mctp_inst, SENSOR_UNSPECIFIED_ERROR);

	switch (pm8702_access) {
	case chip_temp:
		if (cci_get_chip_temp(mctp_inst, ext_params, &sval->integer) == false) {
			return SENSOR_NOT_ACCESSIBLE;
		}
		sval->fraction = 0;
		break;
	case dimm_temp:
		if (pm8702_get_dimm_temp(mctp_inst, ext_params, address, &sval->integer,
					 &sval->fraction) == false) {
			return SENSOR_NOT_ACCESSIBLE;
		}
		break;
	default:
		LOG_ERR("Invalid access offset %d", pm8702_access);
		return SENSOR_PARAMETER_NOT_VALID;
	}

	return SENSOR_READ_SUCCESS;
}

uint8_t pal_pm8702_init(uint8_t card_id, sensor_cfg *cfg)
{
	CHECK_NULL_ARG_WITH_RETURN(cfg, SENSOR_INIT_UNSPECIFIED_ERROR);

	if (cfg->num > SENSOR_NUM_MAX) {
		return SENSOR_INIT_UNSPECIFIED_ERROR;
	}

	return SENSOR_INIT_SUCCESS;
}

bool pal_init_pm8702_info(uint8_t cxl_id)
{
	bool ret = false;
	uint8_t pcie_card_id = 0;

	uint8_t *req_buf = NULL;
	uint8_t req_len = GET_FW_INFO_REQ_PL_LEN;
	uint8_t resp_len = sizeof(cci_fw_info_resp);
	uint8_t resp_buf[resp_len];
	memset(resp_buf, 0, sizeof(uint8_t) * resp_len);

	ret = pal_pm8702_command_handler(pcie_card_id, CCI_GET_FW_INFO, req_buf, req_len, resp_buf,
					 &resp_len);
	if (ret != true) {
		LOG_ERR("Fail to get cxl card: 0x%x fw version", cxl_id);
		return false;
	}

	memcpy(&pm8702_table[cxl_id].dev_info, resp_buf, resp_len);
	pm8702_table[cxl_id].is_init = true;
	return true;
}

bool pal_get_pm8702_hbo_status(uint8_t pcie_card_id, uint8_t *resp_buf, uint8_t *resp_len)
{
	CHECK_NULL_ARG_WITH_RETURN(resp_buf, false);
	CHECK_NULL_ARG_WITH_RETURN(resp_len, false);

	bool ret = false;
	uint8_t *req_buf = NULL;
	uint8_t req_len = HBO_STATUS_REQ_PL_LEN;

	ret = pal_pm8702_command_handler(pcie_card_id, PM8702_HBO_STATUS, req_buf, req_len,
					 resp_buf, resp_len);
	if (ret != true) {
		LOG_ERR("Fail to get card id: 0x%x HBO status", pcie_card_id);
	}

	return ret;
}

bool pal_pm8702_transfer_fw(uint8_t pcie_card_id, uint8_t *req_buf, int req_len)
{
	CHECK_NULL_ARG_WITH_RETURN(req_buf, false);

	bool ret = false;
	uint8_t resp_buf[TRANSFER_FW_RESP_PL_LEN];
	uint8_t resp_len = 0;

	ret = pal_pm8702_command_handler(pcie_card_id, PM8702_HBO_TRANSFER_FW, req_buf, req_len,
					 resp_buf, &resp_len);
	if (ret != true) {
		LOG_ERR("Fail to transfer card id: 0x%x firmware", pcie_card_id);
	}

	return ret;
}

bool pal_set_pm8702_active_slot(uint8_t pcie_card_id, uint8_t *req_buf, int req_len)
{
	CHECK_NULL_ARG_WITH_RETURN(req_buf, false);

	bool ret = false;
	uint8_t resp_buf[ACTIVATE_FW_RESP_PL_LEN];
	uint8_t resp_len = 0;

	ret = pal_pm8702_command_handler(pcie_card_id, PM8702_HBO_ACTIVATE_FW, req_buf, req_len,
					 resp_buf, &resp_len);
	if (ret != true) {
		LOG_ERR("Fail to activate card id: 0x%x slot firmware", pcie_card_id);
	}

	return ret;
}

bool pal_pm8702_command_handler(uint8_t pcie_card_id, uint16_t opcode, uint8_t *data_buf,
				int data_len, uint8_t *response, uint8_t *response_len)
{
	if (data_len != 0) {
		CHECK_NULL_ARG_WITH_RETURN(data_buf, false);
	}

	CHECK_NULL_ARG_WITH_RETURN(response, false);
	CHECK_NULL_ARG_WITH_RETURN(response_len, false);
	ARG_UNUSED(pcie_card_id);

	bool ret = false;
	mctp *mctp_inst = NULL;
	mctp_ext_params ext_params = { 0 };

	if (get_mctp_info_by_eid(MCTP_EID_CXL, &mctp_inst, &ext_params) == false) {
		LOG_ERR("Fail to get mctp info via eid: 0x%x", MCTP_EID_CXL);
		return false;
	}

	CHECK_NULL_ARG_WITH_RETURN(mctp_inst, false);

	ret = pm8702_cmd_handler(mctp_inst, ext_params, opcode, data_buf, data_len, response,
				 response_len);

	return true;
}
