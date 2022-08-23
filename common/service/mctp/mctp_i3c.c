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

#include "mctp.h"

#include <stdlib.h>
#include <string.h>
#include <zephyr.h>
#include <sys/crc.h>
#include <logging/log.h>
#include "libutil.h"
#include "hal_i3c.h"
#include "mctp_ctrl.h"
#include "pldm.h"

LOG_MODULE_REGISTER(mctp_i3c);

#define MCTP_I3C_PEC_ENABLE 0
#define MCTP_I3C_SOM_MASK 0x80
#define MCTP_I3C_SOM_SHIFT 7
#define MCTP_MSG_TYPE_MASK 0x7F

static uint16_t mctp_i3c_read_smq(void *mctp_p, uint8_t *buf, uint32_t len,
				  mctp_ext_params *extra_data)
{
	CHECK_NULL_ARG_WITH_RETURN(mctp_p, MCTP_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(buf, MCTP_ERROR);
	ARG_UNUSED(len);

	if (extra_data.type != MCTP_MEDIUM_TYPE_I3C) {
		LOG_ERR("mctp medium type incorrect");
		return 0;
	}

	int ret;
	I3C_MSG i3c_msg;
	mctp *mctp_inst = (mctp *)mctp_p;
	i3c_msg.bus = mctp_inst->medium_conf.i3c_conf.bus;
	ret = i3c_smq_read(i3c_msg);
	if (ret < 0) {
		LOG_ERR("i3c smq read failed");
		return 0;
	}
	return ret;
//	if (ret < 0) {
//		LOG_DBG("message queue was empty or device not found");
//		return MCTP_ERROR;
//	}
//	i3c_msg.rx_len = ret;
//
//	/** check som(start of msg) validity **/
//	if (((i3c_msg.data[3] & MCTP_I3C_SOM_MASK) >> MCTP_I3C_SOM_SHIFT) && (count != 0)) {
//		count = 0;
//		LOG_DBG("mctp data was not valid, som flaged but count was not init");
//		return MCTP_ERROR;
//	}
//
//	/** check mctp message type **/
//	switch(i3c_msg.data[4] & MCTP_MSG_TYPE_MASK) {
//	case MCTP_MSG_TYPE_CTRL:
//		mctp_ctrl_hdr *mctp_ctrl_header = (mctp_ctrl_hdr *)(i3c_msg.data + 4);
//		break;
//	case MCTP_MSG_TYPE_PLDM:
//		pldm_hdr *pldm_hdr_msg = (pldm_hdr *)(i3c_msg.data + 4);
//		switch(pldm_hdr_msg->pldm_type) {
//		case PLDM_TYPE_OEM:
//
//			break;
//		default:
//			break;
//		}
//		break;
//	case MCTP_MSG_TYPE_NCSI:
//		break;
//	default:
//		LOG_ERR("invalid mctp messsage type");
//		break;
//	}
//
//	// send mctp_tx
//
//	count = 0;
//	return MCTP_SUCCESS;
}

static uint16_t mctp_i3c_write_smq(void *mctp_p, uint8_t *buf, uint32_t len,
				   mctp_ext_params extra_data)
{
	CHECK_NULL_ARG_WITH_RETURN(mctp_p, MCTP_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(buf, MCTP_ERROR);

	if (extra_data.type != MCTP_MEDIUM_TYPE_I3C) {
		LOG_DBG("mctp medium type incorrect");
		return MCTP_ERROR;
	}

	int ret;
	I3C_MSG i3c_msg;
	mctp *mctp_inst = (mctp *)mctp_p;
	i3c_msg.bus = mctp_inst->medium_conf.i3c_conf.bus;
	/** mctp package **/
	memcpy(&i3c_msg.data[0], buf, len);
	/** +1 pec; +0 no pec **/
	if (MCTP_I3C_PEC_ENABLE) {
		i3c_msg.tx_len = len + 1;
		/** pec byte use 7-degree polynomial with 0 init value and false reverse **/
		i3c_msg.data[len + 1] = crc8(&i3c_msg.data[0], len, 0x07, 0x00, false);
	} else {
		i3c_msg.tx_len = len;
	}

	LOG_HEXDUMP_DBG(&i3c_msg.data[0], i3c_msg.tx_len, "i3c msg dump");

	ret = i3c_smq_write(&i3c_msg);
	if (ret < 0) {
		LOG_DBG("i3c smq write failed");
		return MCTP_ERROR;
	}

	return MCTP_SUCCESS;
}

uint8_t mctp_i3c_init(mctp *mctp_inst, mctp_medium_conf medium_conf)
{
	CHECK_NULL_ARG_WITH_RETURN(mctp_inst, MCTP_ERROR);

	mctp_inst->medium_conf = medium_conf;
	mctp_inst->read_data = mctp_i3c_read_smq;
	mctp_inst->write_data = mctp_i3c_write_smq;

	return MCTP_SUCCESS;
}

uint8_t mctp_i3c_deinit(mctp *mctp_inst)
{
	CHECK_NULL_ARG_WITH_RETURN(mctp_inst, MCTP_ERROR);

	mctp_inst->read_data = NULL;
	mctp_inst->write_data = NULL;
	memset(&mctp_inst->medium_conf, 0, sizeof(mctp_inst->medium_conf));
	return MCTP_SUCCESS;
}
