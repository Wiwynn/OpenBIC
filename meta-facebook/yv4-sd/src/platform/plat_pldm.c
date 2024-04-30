#include <zephyr.h>
#include <sys/printk.h>
#include <logging/log.h>
#include <logging/log_ctrl.h>
#include <stdlib.h>
#include <stdio.h>
#include "plat_mctp.h"

LOG_MODULE_REGISTER(plat_pldm);

uint8_t plat_pldm_get_tid()
{
	// Set TID as EID
	return plat_get_eid();
}

uint8_t plat_pldm_get_http_boot_data(uint8_t *httpBootData, uint16_t *httpBootDataLen)
{
	pldm_msg pmsg = { 0 };

	pmsg.ext_params.type = MCTP_MEDIUM_TYPE_SMBUS;
	pmsg.ext_params.smbus_ext_params.addr = I2C_ADDR_BMC;
	pmsg.ext_params.ep = MCTP_EID_BMC;

	pmsg.hdr.rq = PLDM_REQUEST;
	pmsg.hdr.pldm_type = PLDM_TYPE_OEM;
	pmsg.hdr.cmd = PLDM_OEM_READ_FILE_IO;

	struct pldm_oem_read_file_io_req *ptr = (struct pldm_oem_read_file_io_req *)malloc(
		sizeof(struct pldm_oem_read_file_io_req));

	ptr->cmd_code = HTTP_BOOT;
	ptr->data_length = 145; // Jeff:一次可以傳送的最大長度
	ptr->transfer_flag = PLDM_START;
	ptr->highOffset = 0;
	ptr->lowOffset = 0;

	pmsg.buf = (uint8_t *)ptr;
	pmsg.len = sizeof(struct pldm_oem_read_file_io_req);

	uint16_t resp_len = 150; // Jeff:一次可以傳送的最大長度

	struct pldm_oem_read_file_io_resp *rbuf = (struct pldm_oem_read_file_io_resp *)malloc(
		sizeof(struct pldm_oem_read_file_io_resp) + sizeof(uint8_t) * resp_len); //resp_data
	if (rbuf == NULL) {
		LOG_ERR("Memory allocation failed.");
		return PLDM_ERROR;
	}

	uint16_t offset = 0;

	while (true) {
		if (!mctp_pldm_read(find_mctp_by_bus(I2C_BUS_BMC), &pmsg, (uint8_t *)rbuf,
				    resp_len)) {
			LOG_ERR("Fail to send OEM HTTP BOOT DATA");
			return PLDM_ERROR_INVALID_DATA;
		}

		memcpy(httpBootData + offset, rbuf->messages, rbuf->data_length);

		ptr->transfer_flag = rbuf->transfer_flag;
		ptr->highOffset = rbuf->highOffset;
		ptr->lowOffset = rbuf->lowOffset;
		pmsg.buf = (uint8_t *)ptr;

		if (rbuf->transfer_flag == PLDM_END || rbuf->transfer_flag == PLDM_START_AND_END) {
			*httpBootDataLen = offset + rbuf->data_length;
			break;
		}

		offset = ((uint16_t)ptr->highOffset << 8) | ptr->lowOffset;
	}

	free(rbuf);
	free(ptr);

	return PLDM_SUCCESS;
}