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
#include "plat_class.h"

#include "hal_i3c.h"

LOG_MODULE_REGISTER(plat_mctp);

/* i3c 8-bit addr */
#define I3C_STATIC_ADDR_BMC		0x20
#define I3C_STATIC_ADDR_HD_BIC	0x08
#define I3C_STATIC_ADDR_EXPA_BIC	0x09
#define I3C_STATIC_ADDR_EXPB_BIC	0x0A

/* i3c dev bus */
#define I3C_BUS_HD_BIC 0

int mctp_config_table_size = 1;
mctp_port mctp_config_table[] = {
	{	.channel_target = BMC_IPMB,
		.medium_type = MCTP_MEDIUM_TYPE_TARGET_I3C,
		.conf.i3c_conf.bus = I3C_BUS_HD_BIC,
		.conf.i3c_conf.addr = I3C_STATIC_ADDR_HD_BIC
	},
};

mctp_route_entry mctp_route_tbl[] = {
	{ MCTP_EID_YV35_HD_BIC, I3C_BUS_HD_BIC, I3C_STATIC_ADDR_HD_BIC },
};

static mctp *find_mctp_by_i3c(uint8_t bus)
{
	uint8_t i;
	for (i = 0; i < mctp_config_table_size ; i++) {
		mctp_port *p = mctp_config_table + i;

		if (bus == p->conf.i3c_conf.bus) {
			return p->mctp_inst;
		}
	}

	return NULL;
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

static uint8_t get_mctp_route_info(uint8_t dest_endpoint, void **mctp_inst,
				   mctp_ext_params *ext_params)
{
	CHECK_NULL_ARG_WITH_RETURN(mctp_inst, MCTP_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(ext_params, MCTP_ERROR);

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

void plat_mctp_init(void)
{
	int ret = 0;

	/* init the mctp/pldm instance */
	for (uint8_t i = 0; i < mctp_config_table_size; i++) {

		mctp_port *p = mctp_config_table + i;

        I3C_MSG i3c_msg = {0};

        i3c_msg.bus = p->conf.i3c_conf.bus;

		switch (get_card_type()) {
		// OPA BIC need communicate with SB BIC and OPB BIC
		case CARD_TYPE_OPA:
        	i3c_msg.target_addr = I3C_STATIC_ADDR_EXPA_BIC;
			break;
		// OPB BIC need communicate with OPA BIC
		case CARD_TYPE_OPB:
        	i3c_msg.target_addr = I3C_STATIC_ADDR_EXPB_BIC;
			break;
		default:
			LOG_ERR("Failed to get card type");
			break;
		}

		ret = i3c_target_set_address(&i3c_msg);
		if (ret) {
			LOG_ERR("Set i3c static address failed. bus = 0x%02x, addr = 0x%02x, ret = %d", i3c_msg.bus, i3c_msg.target_addr, ret);
		}

		p->mctp_inst = mctp_init();
		if (!p->mctp_inst) {
			LOG_ERR("mctp_init failed!!");
			continue;
		}

		uint8_t rc = mctp_set_medium_configure(p->mctp_inst, p->medium_type , p->conf);
		if (rc != MCTP_SUCCESS) {
			LOG_INF("mctp set medium configure failed");
		}

		mctp_reg_endpoint_resolve_func(p->mctp_inst, get_mctp_route_info);

		mctp_reg_msg_rx_func(p->mctp_inst, mctp_msg_recv);

		ret = mctp_start(p->mctp_inst);
	}
}

