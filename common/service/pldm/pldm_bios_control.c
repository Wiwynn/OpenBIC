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

#include <logging/log.h>
#include "libutil.h"
#include "pldm.h"
#include "pldm_bios_control.h"

#include <stdlib.h>

LOG_MODULE_DECLARE(pldm);

uint16_t pldm_bios_control_read(void *mctp_p, pldm_bios_control_commands cmd, uint8_t *req,
				uint16_t req_len, uint8_t *rbuf, uint16_t rbuf_len,
				void *ext_params)
{
	/* Return read length zero means read fail */
	CHECK_NULL_ARG_WITH_RETURN(mctp_p, 0);
	CHECK_NULL_ARG_WITH_RETURN(req, 0);
	CHECK_NULL_ARG_WITH_RETURN(rbuf, 0);
	CHECK_NULL_ARG_WITH_RETURN(ext_params, 0);

	pldm_msg msg = { 0 };
	mctp_ext_params *extra_data = (mctp_ext_params *)ext_params;

	msg.ext_params = *extra_data;

	msg.hdr.pldm_type = PLDM_TYPE_BIOS_CTRL_CONF;
	msg.hdr.cmd = cmd;
	msg.hdr.rq = 1;

	msg.buf = req;
	msg.len = req_len;

	return mctp_pldm_read(mctp_p, &msg, rbuf, rbuf_len);
}

__weak int set_boot_order(uint8_t *boot_sequence)
{
	LOG_ERR("%s:%s:%d: Implement in project layer", __FILE__, __func__, __LINE__);
	return -1;
}

__weak int get_boot_order(uint8_t *resp, uint16_t resp_len)
{
	LOG_ERR("%s:%s:%d: Implement in project layer", __FILE__, __func__, __LINE__);
	return -1;
}

int pldm_bios_control_set_bios_attribute_current_value(void *mctp_p,
						       pldm_bios_attribute_value_data *data,
						       uint16_t data_len, void *ext_params)
{
	CHECK_NULL_ARG_WITH_RETURN(mctp_p, -1);
	CHECK_NULL_ARG_WITH_RETURN(data, -1);
	CHECK_NULL_ARG_WITH_RETURN(ext_params, -1);
	int ret = 0;

	pldm_set_bios_attribute_current_value_req *req =
		malloc(sizeof(pldm_set_bios_attribute_current_value_req));
	if (!req) {
		LOG_ERR("%s:%s:%d: Failed to allocate memory.", __FILE__, __func__, __LINE__);
		ret = -1;
		goto exit;
	}

	req->data_transfer_handle = 0x0;
	req->transfer_flag = PLDM_BIOS_CONTROL_TRANSFER_FLAG_START;
	req->value_data = data;

	data_len = sizeof(req) - sizeof(pldm_bios_attribute_value_data *) + data_len;

	uint16_t read_len = 0;
	uint8_t rbuf[5] = { 0 };

	read_len = pldm_bios_control_read(
		mctp_p, PLDM_BIOS_CONTROL_CMD_CODE_SET_BIOS_ATTRIBUTE_CURRENT_VALUE,
		(uint8_t *)&req, data_len, rbuf, ARRAY_SIZE(rbuf), ext_params);

	if ((read_len != 5) || (rbuf[0] != PLDM_SUCCESS)) {
		LOG_ERR("%s:%s:%d: Failed to set BIOS Attribute Current Value, CC=0x%x", __FILE__,
			__func__, __LINE__, rbuf[0]);
		ret = -1;
		goto exit;
	}
exit:
	SAFE_FREE(req);
	return ret;
}

int pldm_bios_control_get_bios_sttribute_current_value_by_handle(void *mctp_p,
								 uint16_t attribute_handle,
								 uint8_t *resp, uint16_t resp_len,
								 void *ext_params)
{
	CHECK_NULL_ARG_WITH_RETURN(mctp_p, -1);
	CHECK_NULL_ARG_WITH_RETURN(ext_params, -1);
	int ret = 0;

	pldm_get_bios_sttribute_current_value_by_handle_req *req =
		malloc(sizeof(pldm_get_bios_sttribute_current_value_by_handle_req));
	const uint16_t read_buf_len = sizeof(pldm_get_bios_sttribute_current_value_by_handle_resp) +
				      resp_len * sizeof(uint8_t);
	pldm_get_bios_sttribute_current_value_by_handle_resp *read_buf = malloc(read_buf_len);
	if (!req || !read_buf) {
		LOG_ERR("%s:%s:%d: Failed to allocate memory.", __FILE__, __func__, __LINE__);
		ret = -1;
		goto exit;
	}

	// data_transfer_handle is ignored when tranfer_operation_flag is get-first-part.
	req->data_transfer_handle = 0x0;
	req->transfer_operation_flag = PLDM_BIOS_CONTROL_TRANSFER_OPERATION_FLAG_GET_FIRST_PART;
	req->attribute_handle = attribute_handle;

	uint16_t read_len = pldm_bios_control_read(
		mctp_p, PLDM_BIOS_CONTROL_CMD_CODE_GET_BIOS_ATTRIBUTE_CURRENT_VALUE_BY_HANDLE,
		(uint8_t *)&req, sizeof(req), (uint8_t *)read_buf, read_buf_len, ext_params);

	if ((read_len != read_buf_len) || (*resp != PLDM_SUCCESS)) {
		LOG_ERR("%s:%s:%d: Failed to get BIOS Attribute Current Value, CC=0x%x", __FILE__,
			__func__, __LINE__, *resp);
		ret = -1;
		goto exit;
	} else {
		memcpy(resp, read_buf->attribute_data, resp_len);
	}

exit:
	SAFE_FREE(req);
	SAFE_FREE(read_buf);

	return ret;
}
