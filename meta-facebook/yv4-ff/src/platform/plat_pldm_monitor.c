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
	LOG_ERR("access plat_pldm_switch_uart successfully");
	CHECK_NULL_ARG(buf);
	CHECK_NULL_ARG(resp);
	CHECK_NULL_ARG(resp_len);

	struct pldm_set_state_effecter_states_req *req_p =
		(struct pldm_set_state_effecter_states_req *)buf;
	uint8_t *completion_code_p = resp;
	*resp_len = 1;

	if (req_p->composite_effecter_count !=
	    PLDM_PLATFORM_OEM_SWITCH_UART_EFFECTER_STATE_FIELD_COUNT) {
		LOG_ERR("Unsupported switch uart effecter count, (%d)",
			req_p->composite_effecter_count);
		*completion_code_p = PLDM_ERROR_INVALID_DATA;
		return;
	}

	set_effecter_state_field_t *uart = &req_p->field[0];

	if (uart->set_request >= PLDM_SET_REQUEST_MAX) {
		LOG_ERR("Invalid switch uart set request (%d)", uart->set_request);
		*completion_code_p = PLDM_PLATFORM_UNSUPPORTED_EFFECTERSTATE;
		return;
	}

	uint8_t uart_number = uart->effecter_state;
	LOG_ERR("uart_number is %d", uart_number);
	uint32_t reg_value = 0;

	switch (uart_number) {
	case UART_VISTARA:
		/* According "HICR9: Host Interface Control Register 9(offset: 98h)" from AST1030 spec,
		 * Write 0101 to bit[11:8] to switch uart to VISTARA
		 */
		reg_value = sys_read32(LPC_HICR9_REG);
		LOG_ERR("original reg is %d", reg_value);
		clear_bits(&reg_value, 8, 11);
		reg_value = SETBITS(reg_value, 0b0101, 8);
		LOG_ERR("changed reg is %d", reg_value);
		sys_write32(reg_value, LPC_HICR9_REG);
		/* According "HICRA: Host Interface Control Register A(offset: 9Ch)" from AST1030 spec,
		 * Write 111 to bit[2:0] to switch uart to VISTARA
		 */
		reg_value = sys_read32(LPC_HICRA_REG);
		LOG_ERR("original reg is %d", reg_value);
		reg_value = SETBITS(reg_value, 0b111, 0);
		LOG_ERR("changed reg is %d", reg_value);
		sys_write32(reg_value, LPC_HICRA_REG);

		break;
	case UART_BIC:
		/* According "HICR9: Host Interface Control Register 9(offset: 98h)" from AST1030 spec,
		 * Write 1010 to bit[11:8] to switch uart to BIC
		 */
		reg_value = sys_read32(LPC_HICR9_REG);
		LOG_ERR("original reg is %d", reg_value);
		clear_bits(&reg_value, 8, 11);
		reg_value = SETBITS(reg_value, 0b1010, 8);
		LOG_ERR("changed reg is %d", reg_value);
		sys_write32(reg_value, LPC_HICR9_REG);

		/* According "HICRA: Host Interface Control Register A(offset: 9Ch)" from AST1030 spec,
		 * Write 000 to bit[2:0] to switch uart to BIC
		 */
		reg_value = sys_read32(LPC_HICRA_REG);
		LOG_ERR("original reg is %d", reg_value);
		clear_bits(&reg_value, 0, 2);
		LOG_ERR("changed reg is %d", reg_value);
		sys_write32(reg_value, LPC_HICRA_REG);

		break;
	default:
		LOG_ERR("Unsupport uart number (%d)", uart_number);
	}
	return;
}

uint8_t plat_pldm_set_state_effecter_state_handler(const uint8_t *buf, uint16_t len, uint8_t *resp,
						   uint16_t *resp_len,
						   struct pldm_state_effecter_info *info_p)
{
	LOG_ERR("Access plat_pldm_set_state_effecter_state_handler successfully");
	CHECK_NULL_ARG_WITH_RETURN(buf, PLDM_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(resp, PLDM_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(resp_len, PLDM_ERROR);
	CHECK_ARG_WITH_RETURN(!len, PLDM_ERROR);

	uint8_t *completion_code_p = resp;
	*resp_len = 1;

	switch (info_p->entity_type) {
	case PLDM_ENTITY_OTHER_BUS:
		LOG_ERR("access plat_pldm_switch_uart");
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
