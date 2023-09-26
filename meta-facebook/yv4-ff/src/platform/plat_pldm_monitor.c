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

#include <logging/log.h>
#include <stdlib.h>

#include "sensor.h"
#include "hal_gpio.h"
#include "pldm.h"

#include "plat_gpio.h"
#include "plat_i2c.h"
#include "plat_sensor_table.h"
#include "plat_pldm_monitor.h"

LOG_MODULE_REGISTER(plat_pldm_monitor);

struct pldm_state_effecter_info plat_state_effecter_table[] = {
	[0 ... PLDM_PLATFORM_OEM_AST1030_GPIO_PIN_NUM_MAX] = {
		.entity_type = PLDM_ENTITY_IO_CONTROLLER,
	},

	[PLDM_PLATFORM_OEM_AST1030_GPIO_PIN_NUM_MAX + 1] = {
		.entity_type = PLDM_ENTITY_OTHER_BUS,
		.effecter_id = PLAT_PLDM_EFFECTER_ID_UART_SWITCH,
	},
};

void plat_pldm_switch_uart(const uint8_t *buf, uint16_t len, uint8_t *resp, uint16_t *resp_len)
{
	CHECK_NULL_ARG(buf);
	CHECK_NULL_ARG(resp);
	CHECK_NULL_ARG(resp_len);

	struct pldm_get_state_effecter_states_resp2 *res_p = 
		(struct pldm_get_state_effecter_states_resp2 *)resp;
	res_p->composite_effecter_count = 1;
	*resp_len = 1;

	uint32_t reg_value = 0;

	reg_value = sys_read32(LPC_HICR9_REG);

	res_p->reg01 = (reg_value >> 24) & 0xFF; // 获取高位字节
	res_p->reg02 = (reg_value >> 16) & 0xFF; // 获取次高位字节
	res_p->reg03 = (reg_value >> 8) & 0xFF;  // 获取次低位字节
	res_p->reg04 = reg_value & 0xFF;         // 获取低位字节
	reg_value = sys_read32(LPC_HICRA_REG);
	res_p->reg11 = (reg_value >> 24) & 0xFF; // 获取高位字节
	res_p->reg12 = (reg_value >> 16) & 0xFF; // 获取次高位字节
	res_p->reg13 = (reg_value >> 8) & 0xFF;  // 获取次低位字节
	res_p->reg14 = reg_value & 0xFF;         // 获取低位字节

	return;
}

uint8_t plat_pldm_set_state_effecter_state_handler(const uint8_t *buf, uint16_t len, uint8_t *resp,
						   uint16_t *resp_len,
						   struct pldm_state_effecter_info *info_p)
{
	CHECK_NULL_ARG_WITH_RETURN(buf, PLDM_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(resp, PLDM_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(resp_len, PLDM_ERROR);
	CHECK_ARG_WITH_RETURN(!len, PLDM_ERROR);

	uint8_t *completion_code_p = resp;
	*resp_len = 1;

	switch (info_p->entity_type) {
	case PLDM_ENTITY_OTHER_BUS:
		plat_pldm_switch_uart(buf, len, resp, resp_len);
		break;
	//TODO: case PLDM_ENTITY_IO_CONTROLLER for GPIO controller
	default:
		LOG_ERR("Unsupport entity type, (%d)", info_p->entity_type);
		*completion_code_p = PLDM_ERROR_INVALID_DATA;
		break;
	}

	return PLDM_SUCCESS;
}
