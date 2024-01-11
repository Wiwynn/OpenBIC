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

#include "plat_pldm_bios_control.h"
#include <logging/log.h>
#include "plat_mctp.h"
#include "plat_class.h"
#include "libutil.h"

#include <stdlib.h>

LOG_MODULE_REGISTER(plat_bios_control);

int set_boot_order(uint8_t *boot_sequence)
{
	const uint8_t BOOT_SEQUENCE_COUNT = 6;
	int ret = 0;

	pldm_bios_control_bios_boot_config_setting_value *boot_config =
		malloc(sizeof(pldm_bios_control_bios_boot_config_setting_value));
	boot_config->boot_source_order = malloc(BOOT_SEQUENCE_COUNT * sizeof(uint8_t));
	pldm_bios_attribute_value_data *value_data = malloc(sizeof(pldm_bios_attribute_value_data));
	if (!boot_config || !boot_config->boot_source_order || !value_data) {
		LOG_ERR("%s:%s:%d: Failed to allocate memory.", __FILE__, __func__, __LINE__);
		ret = -1;
		goto exit;
	}

	boot_config->boot_config_type = PLDM_BIOS_CONTROL_BOOT_TYPE_DEFAULT;
	boot_config->order_fail_through_mode = PLDM_BIOS_CONTROL_ORDERED_LIMITED_FAIL_THROUGH;
	boot_config->boot_source_settings_count = BOOT_SEQUENCE_COUNT;
	for (uint8_t i = 0; i < BOOT_SEQUENCE_COUNT; i++) {
		*(boot_config->boot_source_order + i) = *(boot_sequence + i);
	}

	value_data->attribute_handle = get_slot_eid();
	value_data->attribute_type = PLDM_BIOS_CONTROL_ATTRIBUTE_TYPE_BOOT_CONFIG_SETTING;
	value_data->attribute_data = (uint8_t *)boot_config;

	uint16_t boot_order_data_length = sizeof(value_data) - sizeof(void *) +
					  sizeof(boot_config) - sizeof(void *) +
					  (BOOT_SEQUENCE_COUNT * sizeof(uint8_t));

	mctp_ext_params ext_params = { .type = MCTP_MEDIUM_TYPE_SMBUS,
				       .smbus_ext_params.addr = I2C_ADDR_BMC,
				       .ep = MCTP_EID_BMC };

	ret = pldm_bios_control_set_bios_attribute_current_value(find_mctp_by_bus(I2C_BUS_BMC),
								 value_data, boot_order_data_length,
								 (void *)&ext_params);
	if (!ret) {
		LOG_ERR("%s:%s:%d: Failed to set boot order, ret=%d", __FILE__, __func__, __LINE__,
			ret);
	}

exit:
	SAFE_FREE(value_data);
	SAFE_FREE(boot_config->boot_source_order);
	SAFE_FREE(boot_config);

	return ret;
}

int get_boot_order(uint8_t *resp, uint16_t resp_len)
{
	CHECK_NULL_ARG_WITH_RETURN(resp, -1);

	mctp_ext_params ext_params = { .type = MCTP_MEDIUM_TYPE_SMBUS,
				       .smbus_ext_params.addr = I2C_ADDR_BMC,
				       .ep = MCTP_EID_BMC };

	int ret = pldm_bios_control_get_bios_sttribute_current_value_by_handle(
		find_mctp_by_bus(I2C_BUS_BMC), get_slot_eid(), resp, resp_len, (void *)&ext_params);

	if (!ret) {
		LOG_ERR("%s:%s:%d: Failed to get boot order, ret=%d", __FILE__, __func__, __LINE__,
			ret);
	}

	return ret;
}
