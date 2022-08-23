#include "mctp.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/crc.h>
#include <sys/printk.h>
#include <zephyr.h>
#include <logging/log.h>
#include "libutil.h"
#include "hal_i3c.h"
#include "hal_i2c_target.h"

LOG_MODULE_REGISTER(mctp_i3c, LOG_LEVEL_DBG);

#define MCTP_I3C_PEC_ENABLE	0

static uint16_t mctp_i3c_read_data(void *mctp_p, uint8_t *buf, uint32_t len, mctp_ext_params *extra_data)
{
//	if (!mctp_p || !buf || !len || !extra_data)
//		return 0;
//
//	ARG_UNUSED(len);
//
//	int	ret = 0;
//	uint8_t read_data[I3C_MAX_BUFF_SIZE] = { 0 };
//	uint16_t rlen = 0;
//
//	mctp *mctp_inst = (mctp *)mctp_p;
//	I3C_MSG *msg = (I3C_MSG *)malloc(sizeof(I3C_MSG));
//	msg->bus = mctp_inst->medium_conf.i3c_conf.bus;
//	msg->rx_len = 16;
//	ret = i3c_smq_read(msg);
//	
//	i3c_hdr *hdr = (i3c_hdr *)read_data;
//	extra_data->type = MCTP_MEDIUM_TYPE_I3C;
//	extra_data->i3c_ext_params.addr = hdr->src_addr - 1;
//
//	memcpy(buf, msg->data[0], msg->rx_len);

	return 0; // msg->rx_len;

//	/* TODO: read data from smbus */
//	ret = i2c_target_read(mctp_inst->medium_conf.i3c_conf.bus, read_data, I3C_MAX_BUFF_SIZE, &rlen);
//	if (ret) {
//		LOG_ERR("i2c_target_read fail, ret %d\n", ret);
//		return 0;
//	}
//
//	i3c_hdr *hdr = (i3c_hdr *)read_buf;
//
///**
// * Does read data include pec?
// * rlen = 1(mctp cmd code 0x0F) +
// * 		  1(byte count) + N(byte count) + 1(*pec, if exist)
// * so if rlen is equal N + 3, the pec is existing
// */
//	const uint8_t is_pec_exist = ((hdr->byte_count + 3) == rlen) ? 1 : 0;
//
//	if (is_pec_exist) {
//		if (is_pec_vaild(mctp_inst->medium_conf.i3c_conf.addr, read_data, rlen) == false)
//			return 0;
//	}
//
//	if (hdr->cmd_code != MCTP_I3C_CMD_CODE)
//		return 0;
//
//	extra_data->type = MCTP_MEDIUM_TYPE_I3C;
//	extra_data->i3c_ext_params.addr = hdr->src_addr - 1;
//
//	uint8_t rt_size = rlen - sizeof(i3c_hdr) - is_pec_exist;
//	memcpy(buf, read_data + sizeof(i3c_hdr), rt_size);
//
//	return rt_size;
}

static uint16_t mctp_i3c_write_data(void *mctp_p, uint8_t *buf, uint32_t len, mctp_ext_params extra_data)
{
	CHECK_NULL_ARG_WITH_RETURN(mctp_p, MCTP_ERROR);

	mctp *mctp_inst = (mctp *)mctp_p;
	if (extra_data.type != MCTP_MEDIUM_TYPE_I3C) {
		LOG_DBG("mctp medium type incorrect");
		return MCTP_ERROR;
	}

	LOG_HEXDUMP_DBG(buf, len, "buf dump");

	int ret;
	I3C_MSG i3c_msg;
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
	if (!mctp_inst)
		return MCTP_ERROR;

	mctp_inst->medium_conf = medium_conf;
	mctp_inst->read_data = mctp_i3c_read_data;
	mctp_inst->write_data = mctp_i3c_write_data;

	return MCTP_SUCCESS;
}

uint8_t mctp_i3c_deinit(mctp *mctp_inst)
{
	if (!mctp_inst)
		return MCTP_ERROR;

	mctp_inst->read_data = NULL;
	mctp_inst->write_data = NULL;
	memset(&mctp_inst->medium_conf, 0, sizeof(mctp_inst->medium_conf));
	return MCTP_SUCCESS;
}
