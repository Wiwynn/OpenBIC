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

/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "plat_mctp.h"

#include <zephyr.h>
#include <logging/log.h>
#include "libutil.h"
#include "mctp.h"
#include "mctp_ctrl.h"
#include "pldm.h"
#include "cci.h"
#include "plat_class.h"

LOG_MODULE_REGISTER(plat_mctp);

typedef struct _cxl_mctp_info {
	uint8_t cxl_card_id;
	bool is_set_eid;
} cxl_mctp_info;

static mctp_smbus_port smbus_port[] = {
	{ .conf.smbus_conf.addr = I2C_ADDR_BIC, .conf.smbus_conf.bus = I2C_BUS_BMC },
	{ .conf.smbus_conf.addr = I2C_ADDR_BIC, .conf.smbus_conf.bus = I2C_BUS_CXL },
};

static mctp_route_entry mctp_route_tbl[] = {
	{ .endpoint = MCTP_EID_BMC, .bus = I2C_BUS_BMC, .addr = I2C_ADDR_BMC },
	{ .endpoint = MCTP_EID_CXL, .bus = I2C_BUS_CXL, .addr = I2C_ADDR_CXL },
};

static cxl_mctp_info cxl_info[] = {
	{ .cxl_card_id = CXL_CARD_1, .is_set_eid = false },
	{ .cxl_card_id = CXL_CARD_2, .is_set_eid = false },
	{ .cxl_card_id = CXL_CARD_3, .is_set_eid = false },
	{ .cxl_card_id = CXL_CARD_4, .is_set_eid = false },
	{ .cxl_card_id = CXL_CARD_5, .is_set_eid = false },
	{ .cxl_card_id = CXL_CARD_6, .is_set_eid = false },
	{ .cxl_card_id = CXL_CARD_7, .is_set_eid = false },
	{ .cxl_card_id = CXL_CARD_8, .is_set_eid = false },
};

bool get_cxl_eid_flag(uint8_t cxl_card_id)
{
	uint8_t index = 0;
	for (index = 0; index < ARRAY_SIZE(cxl_info); ++index) {
		if (cxl_card_id == cxl_info[index].cxl_card_id) {
			return cxl_info[index].is_set_eid;
		}
	}

	LOG_ERR("Input cxl card id is invalid, card id: 0x%x", cxl_card_id);
	return false;
}

void set_cxl_eid_flag(uint8_t cxl_card_id, bool value)
{
	uint8_t index = 0;
	for (index = 0; index < ARRAY_SIZE(cxl_info); ++index) {
		if (cxl_card_id == cxl_info[index].cxl_card_id) {
			cxl_info[index].is_set_eid = value;
			return;
		}
	}

	LOG_ERR("Input cxl card id is invalid, card id: 0x%x", cxl_card_id);
}

mctp *find_mctp_by_smbus(uint8_t bus)
{
	uint8_t i;
	for (i = 0; i < ARRAY_SIZE(smbus_port); i++) {
		mctp_smbus_port *p = smbus_port + i;
		if (!p) {
			return NULL;
		}
		if (bus == p->conf.smbus_conf.bus) {
			return p->mctp_inst;
		}
	}
	return NULL;
}

static uint8_t mctp_msg_recv(void *mctp_p, uint8_t *buf, uint32_t len, mctp_ext_params ext_params)
{
	CHECK_NULL_ARG_WITH_RETURN(mctp_p, MCTP_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(buf, MCTP_ERROR);

	/** first byte is message type and ic **/
	uint8_t msg_type = (buf[0] & MCTP_MSG_TYPE_MASK) >> MCTP_MSG_TYPE_SHIFT;
	uint8_t ic = (buf[0] & MCTP_IC_MASK) >> MCTP_IC_SHIFT;
	(void)ic;

	switch (msg_type) {
	case MCTP_MSG_TYPE_CTRL:
		mctp_ctrl_cmd_handler(mctp_p, buf, len, ext_params);
		break;

	case MCTP_MSG_TYPE_PLDM:
		mctp_pldm_cmd_handler(mctp_p, buf, len, ext_params);
		break;

	case MCTP_MSG_TYPE_CCI:
		mctp_cci_cmd_handler(mctp_p, buf, len, ext_params);
		break;

	default:
		LOG_WRN("unable to find message receive function");
		return MCTP_ERROR;
	}

	return MCTP_SUCCESS;
}

uint8_t get_mctp_info(uint8_t dest_endpoint, mctp **mctp_inst, mctp_ext_params *ext_params)
{
	CHECK_NULL_ARG_WITH_RETURN(mctp_inst, MCTP_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(ext_params, MCTP_ERROR);

	uint8_t ret = MCTP_ERROR;
	uint32_t index = 0;

	for (index = 0; index < ARRAY_SIZE(mctp_route_tbl); index++) {
		mctp_route_entry *port = mctp_route_tbl + index;
		CHECK_NULL_ARG_WITH_RETURN(port, MCTP_ERROR);

		if (port->endpoint == dest_endpoint) {
			*mctp_inst = find_mctp_by_smbus(port->bus);
			CHECK_NULL_ARG_WITH_RETURN(mctp_inst, MCTP_ERROR);

			ext_params->ep = port->endpoint;
			ext_params->type = MCTP_MEDIUM_TYPE_SMBUS;
			ext_params->smbus_ext_params.addr = port->addr;
			ret = MCTP_SUCCESS;
			break;
		}
	}
	return ret;
}

static void set_endpoint_resp_handler(void *args, uint8_t *buf, uint16_t len)
{
	CHECK_NULL_ARG(args);
	CHECK_NULL_ARG(buf);
	LOG_HEXDUMP_INF(buf, len, __func__);
}

static void set_endpoint_resp_timeout(void *args)
{
	CHECK_NULL_ARG(args);
	mctp_ext_params *ext_params = (mctp_ext_params *)args;
	LOG_ERR("Endpoint 0x%x set endpoint fail, addr: 0x%x", ext_params->ep,
		ext_params->smbus_ext_params.addr);
}

void set_cxl_endpoint(uint8_t eid, uint8_t cxl_card_id)
{
	uint8_t ret = 0;
	mctp *mctp_inst = NULL;
	mctp_ctrl_msg msg = { 0 };

	ret = get_mctp_info(eid, &mctp_inst, &msg.ext_params);
	if (ret != MCTP_SUCCESS) {
		LOG_ERR("Get mctp route info fail");
		return;
	}

	CHECK_NULL_ARG(mctp_inst);
	struct _set_eid_req req = { 0 };
	req.op = SET_EID_REQ_OP_SET_EID;
	req.eid = eid;

	msg.hdr.cmd = MCTP_CTRL_CMD_SET_ENDPOINT_ID;
	msg.hdr.rq = MCTP_REQUEST;
	msg.cmd_data = (uint8_t *)&req;
	msg.cmd_data_len = sizeof(req);
	msg.recv_resp_cb_fn = set_endpoint_resp_handler;
	msg.timeout_cb_fn = set_endpoint_resp_timeout;
	msg.timeout_cb_fn_args = &msg.ext_params;

	ret = mctp_ctrl_send_msg(mctp_inst, &msg);
	if (ret == MCTP_SUCCESS) {
		set_cxl_eid_flag(cxl_card_id, SET_EID_FLAG);
	} else {
		LOG_ERR("Send mctp control msg fail");
	}
}

void plat_mctp_init(void)
{
	LOG_INF("plat_mctp_init");

	uint8_t ret = 0;
	uint8_t index = 0;

	for (index = 0; index < ARRAY_SIZE(smbus_port); index++) {
		mctp_smbus_port *port = smbus_port + index;
		CHECK_NULL_ARG(port);

		if (port->conf.smbus_conf.bus == I2C_BUS_CXL) {
			/** BIC will not initialize mctp instance if CXL is not present **/
			if (is_cxl_present() == false) {
				continue;
			}
		}

		/** init mctp for bmc bus **/
		port->mctp_inst = mctp_init();
		CHECK_NULL_ARG(port->mctp_inst);

		ret = mctp_set_medium_configure(port->mctp_inst, MCTP_MEDIUM_TYPE_SMBUS,
						port->conf);
		if (ret != MCTP_SUCCESS) {
			LOG_INF("[%s] mctp set medium configure failed", __func__);
		}

		mctp_reg_msg_rx_func(port->mctp_inst, mctp_msg_recv);
		mctp_start(port->mctp_inst);
	}

	LOG_DBG("mctp_start");
}
