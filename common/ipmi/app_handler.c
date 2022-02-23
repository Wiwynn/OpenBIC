#include "app_handler.h"

#include "fru.h"
#include "sdr.h"
#include "guid.h"
#include "plat_i2c.h"
#include "plat_ipmi.h"
#include "plat_guid.h"
#include "util_sys.h"

__weak void APP_GET_DEVICE_ID(ipmi_msg *msg)
{
	if (msg == NULL) {
		return;
	}

	if (msg->data_len != 0) {
		msg->completion_code = CC_INVALID_LENGTH;
		return;
	}

	msg->data[0] = DEVICE_ID;
	msg->data[1] = DEVICE_REVISION;
	msg->data[2] = FIRMWARE_REVISION_1;
	msg->data[3] = FIRMWARE_REVISION_2;
	msg->data[4] = IPMI_VERSION;
	msg->data[5] = ADDITIONAL_DEVICE_SUPPORT;
	msg->data[6] = (IANA_ID & 0xFF);
	msg->data[7] = (IANA_ID >> 8) & 0xFF;
	msg->data[8] = (IANA_ID >> 16) & 0xFF;
	msg->data[9] = (PRODUCT_ID & 0xFF);
	msg->data[10] = (PRODUCT_ID >> 8) & 0xFF;
	msg->data[11] = (AUXILIARY_FW_REVISION >> 24) & 0xFF;
	msg->data[12] = (AUXILIARY_FW_REVISION >> 16) & 0xFF;
	msg->data[13] = (AUXILIARY_FW_REVISION >> 8) & 0xFF;
	msg->data[14] = (AUXILIARY_FW_REVISION & 0xFF);
	msg->data_len = 15;
	msg->completion_code = CC_SUCCESS;

	return;
}

__weak void APP_COLD_RESET(ipmi_msg *msg)
{
	if (msg == NULL) {
		return;
	}

	if (msg->data_len != 0) {
		msg->completion_code = CC_INVALID_LENGTH;
		return;
	}

	submit_bic_cold_reset();

	msg->completion_code = CC_SUCCESS;
	return;
}

__weak void APP_WARM_RESET(ipmi_msg *msg)
{
	if (msg == NULL) {
		return;
	}

	if (msg->data_len != 0) {
		msg->completion_code = CC_INVALID_LENGTH;
		return;
	}

	submit_bic_warm_reset();

	msg->completion_code = CC_SUCCESS;
	return;
}

__weak void APP_GET_SELFTEST_RESULTS(ipmi_msg *msg)
{
	if (msg == NULL) {
		return;
	}

	if (msg->data_len != 0) {
		msg->completion_code = CC_INVALID_LENGTH;
		return;
	}

	EEPROM_ENTRY fru_entry;
	fru_entry.config.dev_id = 0;
	fru_entry.offset = 0;
	fru_entry.data_len = 8;
	FRU_read(&fru_entry);
	uint8_t checksum = 0;
	for (uint8_t i = 0; i < fru_entry.data_len; i++) {
		checksum += fru_entry.data[i];
	}

	SELF_TEST_RESULT res;

	res.result.opFwCorrupt = 0;
	res.result.updateFwCorrupt = 0;
	res.result.sdrRepoEmpty = is_sdr_not_init;
	res.result.ipmbLinesDead = 0;

	if (checksum == 0) {
		res.result.cannotAccessBmcFruDev = 0;
		res.result.internalCorrupt = 0;
	} else {
		res.result.cannotAccessBmcFruDev = 1;
		res.result.internalCorrupt = 1;
	}

	res.result.cannotAccessSdrRepo = is_sdr_not_init;
	res.result.cannotAccessSelDev = 0;

	memcpy(&msg->data[1], &res.result, 1);
	// 55h = No error, 57h = Corrupted or inaccessible data or devices
	msg->data[0] = (msg->data[1] == 0x00) ? 0x55 : 0x57;
	msg->data_len = 2;
	msg->completion_code = CC_SUCCESS;

	return;
}

#ifdef CONFIG_ESPI
__weak void APP_GET_SYSTEM_GUID(ipmi_msg *msg)
{
	if (msg == NULL) {
		return;
	}

	uint8_t status;
	EEPROM_ENTRY guid_entry;

	if (msg->data_len != 0) {
		msg->completion_code = CC_INVALID_LENGTH;
		return;
	}

	guid_entry.offset = 0;
	guid_entry.data_len = 16;
	guid_entry.config.dev_id = MB_SYS_GUID_ID;
	status = GUID_read(&guid_entry);

	switch (status) {
	case GUID_READ_SUCCESS:
		msg->data_len = guid_entry.data_len;
		memcpy(&msg->data[0], &guid_entry.data, guid_entry.data_len);
		msg->completion_code = CC_SUCCESS;
		break;
	case GUID_INVALID_ID:
		msg->completion_code = CC_INVALID_PARAM;
		break;
	case GUID_OUT_OF_RANGE:
		msg->completion_code = CC_PARAM_OUT_OF_RANGE;
		break;
	case GUID_FAIL_TO_ACCESS:
		msg->completion_code = CC_UNSPECIFIED_ERROR;
		break;
	default:
		msg->completion_code = CC_UNSPECIFIED_ERROR;
		break;
	}

	return;
}
#endif

__weak void APP_MASTER_WRITE_READ(ipmi_msg *msg)
{
	if (msg == NULL) {
		return;
	}

	uint8_t retry = 3;
	uint8_t bus_7bit;
	I2C_MSG i2c_msg;

	// at least include bus, addr, rx_len, offset
	if (msg->data_len < 4) {
		msg->completion_code = CC_INVALID_LENGTH;
		return;
	}

	// should ignore bit0, all bus public
	bus_7bit = msg->data[0] >> 1;
	if (bus_7bit >= I2C_BUS_MAX_NUM) {
		printf("Accessing invalid bus with IPMI master write read\n");
		msg->completion_code = CC_PARAM_OUT_OF_RANGE;
		return;
	}

	i2c_msg.bus = i2c_bus_to_index[bus_7bit];
	// 8 bit address to 7 bit
	i2c_msg.target_addr = msg->data[1] >> 1;
	i2c_msg.rx_len = msg->data[2];
	i2c_msg.tx_len = msg->data_len - 3;

	if (i2c_msg.tx_len == 0) {
		msg->completion_code = CC_INVALID_DATA_FIELD;
		return;
	}

	memcpy(&i2c_msg.data[0], &msg->data[3], i2c_msg.tx_len);
	msg->data_len = i2c_msg.rx_len;

	if (i2c_msg.rx_len == 0) {
		if (!i2c_master_write(&i2c_msg, retry)) {
			msg->completion_code = CC_SUCCESS;
		} else {
			msg->completion_code = CC_I2C_BUS_ERROR;
		}
	} else {
		if (!i2c_master_read(&i2c_msg, retry)) {
			memcpy(&msg->data[0], &i2c_msg.data, i2c_msg.rx_len);
			msg->completion_code = CC_SUCCESS;
		} else {
			msg->completion_code = CC_I2C_BUS_ERROR;
		}
	}

	return;
}

void IPMI_APP_handler(ipmi_msg *msg)
{
	if (msg == NULL) {
		return;
	}

	switch (msg->cmd) {
	case CMD_APP_GET_DEVICE_ID:
		APP_GET_DEVICE_ID(msg);
		break;
	case CMD_APP_COLD_RESET:
		APP_COLD_RESET(msg);
		break;
	case CMD_APP_WARM_RESET:
		APP_WARM_RESET(msg);
		break;
	case CMD_APP_GET_SELFTEST_RESULTS:
		APP_GET_SELFTEST_RESULTS(msg);
		break;
	case CMD_APP_MASTER_WRITE_READ:
		APP_MASTER_WRITE_READ(msg);
		break;
#ifdef CONFIG_ESPI
	case CMD_APP_GET_SYSTEM_GUID:
		APP_GET_SYSTEM_GUID(msg);
		break;
#endif
	default:
		printf("invalid APP msg netfn: %x, cmd: %x\n", msg->netfn, msg->cmd);
		msg->data_len = 0;
		msg->completion_code = CC_INVALID_CMD;
		break;
	}

	return;
}
