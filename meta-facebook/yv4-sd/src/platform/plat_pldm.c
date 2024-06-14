#include <zephyr.h>
#include <sys/printk.h>
#include <logging/log.h>
#include <logging/log_ctrl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/crc.h>
#include "libutil.h"
#include "plat_mctp.h"
#include "plat_ipmi.h"
#include "util_sys.h"
#include "hal_i2c.h"

LOG_MODULE_REGISTER(plat_pldm);

uint8_t plat_pldm_get_tid()
{
	// Set TID as EID
	return plat_get_eid();
}

uint8_t plat_pldm_get_http_boot_data(uint8_t *httpBootData, uint16_t httpBootOffset,
				     uint8_t httpBootReadlen, uint8_t *httpBootResplen,
				     bool *is_end_package)
{
	CHECK_NULL_ARG_WITH_RETURN(httpBootData, PLDM_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(httpBootResplen, PLDM_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(is_end_package, PLDM_ERROR);

	pldm_msg pmsg = { 0 };
	uint8_t bmc_bus = I2C_BUS_BMC;
	uint8_t bmc_interface = pal_get_bmc_interface();
	pmsg.ext_params.ep = MCTP_EID_BMC;

	switch (bmc_interface) {
	case BMC_INTERFACE_I3C:
		bmc_bus = I3C_BUS_BMC;
		pmsg.ext_params.type = MCTP_MEDIUM_TYPE_TARGET_I3C;
		pmsg.ext_params.i3c_ext_params.addr = I3C_STATIC_ADDR_BMC;
		break;
	case BMC_INTERFACE_I2C:
		bmc_bus = I2C_BUS_BMC;
		pmsg.ext_params.type = MCTP_MEDIUM_TYPE_SMBUS;
		pmsg.ext_params.smbus_ext_params.addr = I2C_ADDR_BMC;
		break;
	default:
		LOG_ERR("Invalid BMC interface: 0x%x", bmc_interface);
		return PLDM_ERROR;
	}

	pmsg.hdr.rq = PLDM_REQUEST;
	pmsg.hdr.pldm_type = PLDM_TYPE_OEM;
	pmsg.hdr.cmd = PLDM_OEM_READ_FILE_IO;

	struct pldm_oem_read_file_io_req req = { 0 };
	req.cmd_code = HTTP_BOOT;
	req.data_length = httpBootReadlen;
	req.transfer_flag = PLDM_START;
	req.highoffset = ((httpBootOffset >> 8) & 0xFF);
	req.lowoffset = httpBootOffset & 0xFF;

	pmsg.buf = (uint8_t *)&req;
	pmsg.len = sizeof(struct pldm_oem_read_file_io_req);

	uint16_t resp_len = I2C_MAX_TRANSFER_SIZE;
	struct pldm_oem_read_file_io_resp *rbuf =
		(struct pldm_oem_read_file_io_resp *)malloc(sizeof(uint8_t) * resp_len);
	CHECK_NULL_ARG_WITH_RETURN(rbuf, PLDM_ERROR);

	if (!mctp_pldm_read(find_mctp_by_bus(bmc_bus), &pmsg, (uint8_t *)rbuf, resp_len)) {
		LOG_ERR("Fail to send http boot data command");
		free(rbuf);
		return PLDM_ERROR_INVALID_DATA;
	}

	if (rbuf->data_length > httpBootReadlen) {
		LOG_ERR("Response datalen exceed request, response length: 0x%x, request length: 0x%x",
			rbuf->data_length, httpBootReadlen);
		free(rbuf);
		return PLDM_ERROR_INVALID_LENGTH;
	}

	if (rbuf->transfer_flag == PLDM_END || rbuf->transfer_flag == PLDM_START_AND_END) {
		*is_end_package = true;
	}

	memcpy(httpBootData, rbuf->messages, rbuf->data_length);
	*httpBootResplen = rbuf->data_length;
	free(rbuf);

	return PLDM_SUCCESS;
}

uint8_t plat_pldm_get_http_boot_attr(uint8_t attr, uint8_t *httpBootAttrData,
				     uint8_t httpBootAttrDatalen)
{
	CHECK_NULL_ARG_WITH_RETURN(httpBootAttrData, PLDM_ERROR);

	// Correct all http boot data to calculate data_length and crc32
	bool is_end_package = false;
	uint8_t ret = 0;
	uint8_t *data = (uint8_t *)malloc(sizeof(uint8_t) * HTTP_BOOT_DATA_MAXIMUM);
	uint8_t read_len = I2C_MAX_TRANSFER_SIZE - sizeof(struct pldm_oem_read_file_io_req);
	uint8_t resp_len = 0;
	uint16_t offset = 0;
	uint16_t total_len = 0;

	while (true) {
		if (offset + read_len > HTTP_BOOT_DATA_MAXIMUM) {
			LOG_ERR("Receive http data exceed buffer, offset: 0x%x, read_len: 0x%x",
				offset, read_len);
			goto error_out;
		}

		ret = plat_pldm_get_http_boot_data(data + offset, offset, read_len, &resp_len,
						   &is_end_package);
		if (ret != PLDM_SUCCESS) {
			LOG_ERR("Fail to get all http boot data, ret: 0x%x, offset: 0x%x", ret,
				offset);
			goto error_out;
		}

		if (is_end_package) {
			total_len = offset + resp_len;
			break;
		}

		offset = offset + resp_len;
	}

	switch (attr) {
	case GET_HTTP_BOOT_SIZE:
		if (httpBootAttrDatalen != sizeof(uint16_t)) {
			LOG_ERR("Invalid http hoot attribute: 0x%x data len: 0x%x", attr,
				httpBootAttrDatalen);
			goto error_out;
		}
		httpBootAttrData[0] = total_len & 0xFF;
		httpBootAttrData[1] = (total_len >> 8) & 0xFF;
		break;
	case GET_HTTP_BOOT_CRC32:
		if (httpBootAttrDatalen != sizeof(uint32_t)) {
			LOG_ERR("Invalid http hoot attribute: 0x%x data len: 0x%x", attr,
				httpBootAttrDatalen);
			goto error_out;
		}
		uint32_t crc32_value = crc32_ieee(data, total_len);
		httpBootAttrData[0] = crc32_value & 0xFF;
		httpBootAttrData[1] = (crc32_value >> 8) & 0xFF;
		httpBootAttrData[2] = (crc32_value >> 16) & 0xFF;
		httpBootAttrData[3] = (crc32_value >> 24) & 0xFF;
		break;
	default:
		LOG_ERR("Invalid http hoot attribute: 0x%x", attr);
		goto error_out;
	}

	free(data);
	return PLDM_SUCCESS;

error_out:
	free(data);
	return PLDM_ERROR;
}
