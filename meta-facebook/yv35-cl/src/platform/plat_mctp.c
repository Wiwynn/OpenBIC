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

#include "hal_i3c.h"

LOG_MODULE_REGISTER(plat_mctp);

#define MCTP_MSG_TYPE_SHIFT 0
#define MCTP_MSG_TYPE_MASK 0x7F
#define MCTP_IC_SHIFT 7
#define MCTP_IC_MASK 0x80

/* i3c 8-bit addr */
#define I3C_STATIC_ADDR_BIC		0x40
#define I3C_STATIC_ADDR_BMC		0x20

/* i3c dev bus */
#define I3C_BUS_BMC	0

/* mctp endpoint */
#define MCTP_EID_BMC 0x01
#define MCTP_EID_SELF 0x02

K_TIMER_DEFINE(send_cmd_timer, send_cmd_to_dev, NULL);
K_WORK_DEFINE(send_cmd_work, send_cmd_to_dev_handler);

typedef struct _mctp_smbus_port {
	mctp *mctp_inst;
	mctp_medium_conf conf;
	uint8_t user_idx;
} mctp_smbus_port;

typedef struct _mctp_i3c_port {
	mctp *mctp_inst;
	mctp_medium_conf conf;
	uint8_t user_idx;
} mctp_i3c_port;

/* mctp route entry struct */
typedef struct _mctp_route_entry {
	uint8_t endpoint;
	uint8_t bus; /* TODO: only consider smbus/i3c */
	uint8_t addr; /* TODO: only consider smbus/i3c */
} mctp_route_entry;

typedef struct _mctp_msg_handler {
	MCTP_MSG_TYPE type;
	mctp_fn_cb msg_handler_cb;
} mctp_msg_handler;

static mctp_i3c_port i3c_port[] = {
	{ .conf.i3c_conf.bus = I3C_BUS_BMC, .conf.i3c_conf.addr = I3C_STATIC_ADDR_BMC},
};

mctp_route_entry mctp_route_tbl[] = {
	{ MCTP_EID_BMC, I3C_BUS_BMC, I3C_STATIC_ADDR_BMC },
};

static mctp *find_mctp_by_i3c(uint8_t bus)
{
	uint8_t i;
	for (i = 0; i < ARRAY_SIZE(i3c_port); i++) {
		mctp_i3c_port *p = i3c_port + i;

		if (bus == p->conf.i3c_conf.bus)
			return p->mctp_inst;
	}

	return NULL;
}

static void set_endpoint_resp_handler(void *args, uint8_t *buf, uint16_t len)
{
	if (!buf || !len)
		return;
	LOG_HEXDUMP_WRN(buf, len, __func__);
}

static void set_endpoint_resp_timeout(void *args)
{
	mctp_route_entry *p = (mctp_route_entry *)args;
	printk("[%s] Endpoint 0x%x set endpoint failed on bus %d \n", __func__, p->endpoint,
	       p->bus);
}

static void set_dev_endpoint(void)
{
	for (uint8_t i = 0; i < ARRAY_SIZE(mctp_route_tbl); i++) {
		mctp_route_entry *p = mctp_route_tbl + i;

		/* skip BMC */
		if (p->bus == I3C_BUS_BMC && p->addr == I3C_STATIC_ADDR_BMC)
			continue;

		for (uint8_t j = 0; j < ARRAY_SIZE(i3c_port); j++) {
			if (p->bus != i3c_port[j].conf.i3c_conf.bus)
				continue;

			struct _set_eid_req req = { 0 };
			req.op = SET_EID_REQ_OP_SET_EID;
			req.eid = p->endpoint;

			mctp_ctrl_msg *msg = (mctp_ctrl_msg *)malloc(sizeof(mctp_ctrl_msg));
			memset(msg, 0, sizeof(msg));
			msg->ext_params.type = MCTP_MEDIUM_TYPE_SMBUS;
			msg->ext_params.smbus_ext_params.addr = p->addr;

			msg->hdr.cmd = MCTP_CTRL_CMD_SET_ENDPOINT_ID;
			msg->hdr.rq = 1;

			msg->cmd_data = (uint8_t *)&req;
			msg->cmd_data_len = sizeof(req);

			msg->recv_resp_cb_fn = set_endpoint_resp_handler;
			msg->timeout_cb_fn = set_endpoint_resp_timeout;
			msg->timeout_cb_fn_args = p;

			mctp_ctrl_send_msg(find_mctp_by_i3c(p->bus), msg);
			SAFE_FREE(msg);
		}
	}
}

static uint8_t mctp_msg_recv(void *mctp_p, uint8_t *buf, uint32_t len, mctp_ext_params ext_params)
{
	if (!mctp_p || !buf || !len)
		return MCTP_ERROR;

	/* first byte is message type and ic */
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

	default:
		LOG_WRN("Cannot find message receive function!!");
		return MCTP_ERROR;
	}

	return MCTP_SUCCESS;
}

static uint8_t get_mctp_route_info(uint8_t dest_endpoint, void **mctp_inst,
				   mctp_ext_params *ext_params)
{
	if (!mctp_inst || !ext_params)
		return MCTP_ERROR;

	uint8_t rc = MCTP_ERROR;
	uint32_t i;

	for (i = 0; i < ARRAY_SIZE(mctp_route_tbl); i++) {
		mctp_route_entry *p = mctp_route_tbl + i;
		if (p->endpoint == dest_endpoint) {
			*mctp_inst = find_mctp_by_i3c(p->bus);
			ext_params->type = MCTP_MEDIUM_TYPE_SMBUS;
			ext_params->smbus_ext_params.addr = p->addr;
			rc = MCTP_SUCCESS;
			break;
		}
	}

	return rc;
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
	int ret;
	// LOG_INF("plat_mctp_init");
	printf("[%s] platform mctp init\n", __func__);

	/* init the mctp/pldm instance */
	for (uint8_t i = 0; i < ARRAY_SIZE(i3c_port); i++) {
		mctp_i3c_port *p = i3c_port + i;

		p->mctp_inst = mctp_init();
		if (!p->mctp_inst) {
			LOG_ERR("mctp_init failed!!");
			continue;
		}

		uint8_t rc = mctp_set_medium_configure(p->mctp_inst, MCTP_MEDIUM_TYPE_I3C, p->conf);
		if (rc == MCTP_SUCCESS) {
			printf("[%s] success\n", __func__);
		} else {
			printf("[%s] failed\n", __func__);
		}

		printf("[%s] entering mctp reg endpoint\n", __func__);
		mctp_reg_endpoint_resolve_func(p->mctp_inst, get_mctp_route_info);

		printf("[%s] entering mctp reg msg rx\n", __func__);
		mctp_reg_msg_rx_func(p->mctp_inst, mctp_msg_recv);

		printf("[%s] mctp_start\n", __func__);
		ret = mctp_start(p->mctp_inst);
		printf("[%s] complete mctp_start in loop: %u \n", __func__, i);
	}

}

