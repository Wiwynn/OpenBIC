/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "plat_mctp.h"

#include <zephyr.h>
#include <sys/printk.h>
#include <logging/log.h>
#include <logging/log_ctrl.h>
#include <stdlib.h>
#include <stdio.h>
#include "mctp.h"
#include "mctp_ctrl.h"
#include "pldm.h"
#include "ipmi.h"
#include "sensor.h"
#include "plat_hook.h"
#include "plat_ipmb.h"

#include "hal_i3c.h"

LOG_MODULE_REGISTER(plat_mctp);

K_TIMER_DEFINE(send_cmd_timer, send_cmd_to_dev, NULL);
K_WORK_DEFINE(send_cmd_work, send_cmd_to_dev_handler);

int mctp_config_table_size = 2;
mctp_port mctp_config_table[] = {
	{	.channel_target = EXP1_IPMB,
		.medium_type = MCTP_MEDIUM_TYPE_CONTROLLER_I3C,
		.conf.i3c_conf.bus = I3C_BUS_CONTROLLER, 
		.conf.i3c_conf.addr = I3C_STATIC_ADDR_EXPA_BIC},
	{	.channel_target = EXP2_IPMB,
		.medium_type = MCTP_MEDIUM_TYPE_CONTROLLER_I3C,
		.conf.i3c_conf.bus = I3C_BUS_CONTROLLER, 
		.conf.i3c_conf.addr = I3C_STATIC_ADDR_EXPB_BIC},
};

mctp_route_entry mctp_route_tbl[] = {
	{ MCTP_EID_BMC, I3C_BUS_CONTROLLER, I3C_STATIC_ADDR_BIC},
};

static mctp *find_mctp_by_i3c(uint8_t target)
{
	uint8_t i;
	for (i = 0; i < mctp_config_table_size; i++) {
		mctp_port *p = mctp_config_table + i;

		if (target == p->channel_target) {
			return p->mctp_inst;
		}
	}

	return NULL;
}

static void set_endpoint_resp_handler(void *args, uint8_t *buf, uint16_t len)
{
	ARG_UNUSED(args);
	CHECK_NULL_ARG(buf);

	LOG_HEXDUMP_DBG(buf, len, __func__);
}

static void set_endpoint_resp_timeout(void *args)
{
	CHECK_NULL_ARG(args);

	mctp_route_entry *p = (mctp_route_entry *)args;
	LOG_DBG("Endpoint 0x%x set endpoint failed on bus %d", p->endpoint, p->bus);
}

static void set_dev_endpoint(void)
{
	for (uint8_t i = 0; i < ARRAY_SIZE(mctp_route_tbl); i++) {
		mctp_route_entry *p = mctp_route_tbl + i;

		/* skip BMC */
		if (p->bus == I3C_BUS_BMC && p->addr == I3C_STATIC_ADDR_BMC)
			continue;

		for (uint8_t j = 0; j < mctp_config_table_size; j++) {
			if (p->bus != mctp_config_table[j].conf.i3c_conf.bus)
				continue;

			struct _set_eid_req req = { 0 };
			req.op = SET_EID_REQ_OP_SET_EID;
			req.eid = p->endpoint;

			mctp_ctrl_msg msg;
			memset(&msg, 0, sizeof(msg));
			msg.ext_params.type = MCTP_MEDIUM_TYPE_SMBUS;
			msg.ext_params.smbus_ext_params.addr = p->addr;

			msg.hdr.cmd = MCTP_CTRL_CMD_SET_ENDPOINT_ID;
			msg.hdr.rq = 1;

			msg.cmd_data = (uint8_t *)&req;
			msg.cmd_data_len = sizeof(req);

			msg.recv_resp_cb_fn = set_endpoint_resp_handler;
			msg.timeout_cb_fn = set_endpoint_resp_timeout;
			msg.timeout_cb_fn_args = p;

			mctp_ctrl_send_msg(find_mctp_by_i3c(p->bus), &msg);
		}
	}
}

static uint8_t mctp_msg_recv(void *mctp_p, uint8_t *buf, uint32_t len, mctp_ext_params ext_params)
{
	CHECK_NULL_ARG_WITH_RETURN(mctp_p, MCTP_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(buf, MCTP_ERROR);

	/* first byte is message type */
	uint8_t msg_type = (buf[0] & MCTP_MSG_TYPE_MASK) >> MCTP_MSG_TYPE_SHIFT;

	switch (msg_type) {
	case MCTP_MSG_TYPE_CTRL:
		mctp_ctrl_cmd_handler(mctp_p, buf, len, ext_params);
		break;

	case MCTP_MSG_TYPE_PLDM:
		mctp_pldm_cmd_handler(mctp_p, buf, len, ext_params);
		break;

	default:
		LOG_WRN("Cannot find message receive function!!");
		return MCTP_ERROR;
	}

	return MCTP_SUCCESS;
}

void send_cmd_to_dev_handler(struct k_work *work)
{
	/* init the device endpoint */
	set_dev_endpoint();
}

void send_cmd_to_dev(struct k_timer *timer)
{
	k_work_submit(&send_cmd_work);
}

void plat_mctp_init(void)
{
	int ret = 0;

	/* init the mctp/pldm instance */
	for (uint8_t i = 0; i < mctp_config_table_size; i++) {
		mctp_port *p = mctp_config_table + i;

		p->mctp_inst = mctp_init();
		if (!p->mctp_inst) {
			LOG_ERR("mctp_init failed!!");
			continue;
		}

		uint8_t rc = mctp_set_medium_configure(p->mctp_inst, p->medium_type, p->conf);
		if (rc != MCTP_SUCCESS) {
			LOG_INF("mctp set medium configure failed");
		}

		mctp_reg_msg_rx_func(p->mctp_inst, mctp_msg_recv);

		LOG_INF("i3c controller : %d", i);
		ret = mctp_start(p->mctp_inst);
	}
}

