#include <stdio.h>
#include <stdlib.h>
#include "ipmb.h"
#include "ipmi.h"
#include "pmic.h"
#include "sensor.h"
#include "libutil.h"

void init_memory_req(memory_write_read_req *origin_req)
{
	if (origin_req == NULL) {
		printf("[%s] request NULL\n", __func__);
		return;
	}
	origin_req->intel_id = 0x00000157;
	origin_req->smbus_identifier = 0x0;
	origin_req->smbus_address = 0x0;
	origin_req->addr_size = 0x1;
	origin_req->data_len = 0x1;
	origin_req->addr_value = 0x0;
	memset(origin_req->write_data, 0, MAX_MEMORY_DATA * sizeof(uint8_t));
}

void write_memory_req(memory_write_read_req *write_req, uint8_t smbus_identifier,
		      uint8_t smbus_address, uint32_t addr_value, uint8_t *write_data,
		      uint8_t write_len)
{
	if (write_req == NULL) {
		printf("[%s] request NULL\n", __func__);
		return;
	}
	write_req->smbus_identifier = smbus_identifier;
	write_req->smbus_address = smbus_address;
	write_req->addr_value = addr_value;
	memcpy(write_req->write_data, write_data, write_len);
}

uint8_t pmic_read(uint8_t sensor_num, int *reading)
{
	if (!reading || (sensor_num > SENSOR_NUM_MAX) ||
	    (sensor_config[sensor_config_index_map[sensor_num]].init_args == NULL)) {
		return SENSOR_UNSPECIFIED_ERROR;
	}

	pmic_init_arg *pmic_arg = sensor_config[sensor_config_index_map[sensor_num]].init_args;
	if (pmic_arg->is_init == false) {
		printf("Pmic_read, device isn't initialized\n");
		return SENSOR_NOT_FOUND;
	}

	memory_write_read_req *pmic_req =
		(memory_write_read_req *)malloc(sizeof(memory_write_read_req));
	int val = 0;

	ipmi_msg *pmic_msg = (ipmi_msg *)malloc(sizeof(ipmi_msg));
	if ((pmic_msg == NULL) || (pmic_req == NULL)) {
		printf("[%s] Failed to allocate memory\n", __func__);
		SAFE_FREE(pmic_req);
		SAFE_FREE(pmic_msg);
		return SENSOR_UNSPECIFIED_ERROR;
	}

	uint8_t seq_source = 0xFF;
	init_memory_req(pmic_req);
	write_memory_req(pmic_req, pmic_arg->smbus_bus_identifier, pmic_arg->smbus_addr,
			 PMIC_SWA_ADDR_VAL, NULL, 0);

	uint8_t *data = (uint8_t *)pmic_req;
	*pmic_msg = construct_ipmi_message(seq_source, NETFN_NM_REQ, CMD_SMBUS_READ_MEMORY, SELF,
					   ME_IPMB, PMIC_READ_DATA_LEN, data);
	ipmb_error ipmb_ret = ipmb_read(pmic_msg, IPMB_inf_index_map[pmic_msg->InF_target]);

	if (ipmb_ret != IPMB_ERROR_SUCCESS) {
		printf("Failed to send pmic_read_command ret: 0x%x\n", ipmb_ret);
		SAFE_FREE(pmic_req);
		SAFE_FREE(pmic_msg);
		return SENSOR_FAIL_TO_ACCESS;
	}
	if (pmic_msg->completion_code == CC_SUCCESS) {
		val = pmic_msg->data[3] * 125;
	} else {
		printf("Pmic_read fail CC: 0x%x\n", pmic_msg->completion_code);
		SAFE_FREE(pmic_req);
		SAFE_FREE(pmic_msg);
		return SENSOR_FAIL_TO_ACCESS;
	}
	sensor_val *sval = (sensor_val *)reading;
	memset(sval, 0, sizeof(sensor_val));
	sval->integer = (val / 1000) & 0xFFFF;
	sval->fraction = val - (sval->integer * 1000);

	SAFE_FREE(pmic_req);
	SAFE_FREE(pmic_msg);
	return SENSOR_READ_SUCCESS;
}

uint8_t pmic_init(uint8_t sensor_num)
{
	if (sensor_num > SENSOR_NUM_MAX) {
		return SENSOR_INIT_UNSPECIFIED_ERROR;
	}
	sensor_config[sensor_config_index_map[sensor_num]].read = pmic_read;
	return SENSOR_INIT_SUCCESS;
}
