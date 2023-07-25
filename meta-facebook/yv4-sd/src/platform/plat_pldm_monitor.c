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

#include "sensor.h"
#include "hal_gpio.h"
#include "pldm.h"

#include "plat_gpio.h"
#include "plat_sensor_table.h"
#include "plat_pldm_monitor.h"

LOG_MODULE_REGISTER(plat_pldm_monitor);

/* Define from Platform Level Data Model (PLDM) State 
   Set Specification (DSP0249) Table 15 – Entity ID codes*/
#define PLDM_ENTITY_IO_CONTROLLER 145
/* Chassis-specific entities 8192 - 16383 */
#define PLDM_OEM_ENTITY_LED 8192
#define PLDM_OEM_ENTITY_SSD_LED 8193

enum pldm_plat_effecter_id_high_byte {
	PLAT_EFFECTER_ID_GPIO_HIGH_BYTE = (0xFF << 8)
};

static struct plat_state_effecter_info {
	uint16_t entity_type;
	uint16_t effecter_id;
} plat_state_effecter_table[] = {
	[0 ... PLDM_PLATFORM_OEM_AST1030_GPIO_PIN_NUM_NAX] = {
		.entity_type = PLDM_ENTITY_IO_CONTROLLER,
	},
};

static struct plat_state_effecter_info *find_state_effecter_info(uint16_t effecter_id)
{
	for (uint8_t i = 0; i < ARRAY_SIZE(plat_state_effecter_table); i++) {
		if (plat_state_effecter_table[i].effecter_id == effecter_id)
			return &plat_state_effecter_table[i];
	}

	return NULL;
}

uint8_t plat_pldm_set_state_effecter_state_handler(const uint8_t *buf, uint16_t len, uint8_t *resp,
						   uint16_t *resp_len)
{

	CHECK_NULL_ARG_WITH_RETURN(buf, PLDM_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(resp, PLDM_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(resp_len, PLDM_ERROR);
	CHECK_ARG_WITH_RETURN(!len, PLDM_ERROR);

	struct pldm_set_state_effecter_states_req *req_p =
		(struct pldm_set_state_effecter_states_req *)buf;
	uint8_t *completion_code_p = resp;
	*resp_len = 1;


	if (req_p->composite_effecter_count < 0x01 || req_p->composite_effecter_count > 0x08) {
		*completion_code_p = PLDM_ERROR_INVALID_DATA;
		return PLDM_SUCCESS;
	}


	if (len != (PLDM_SET_STATE_EFFECTER_REQ_NO_STATE_FIELD_BYTES +
		    sizeof(set_effecter_state_field_t) * req_p->composite_effecter_count)) {
		*completion_code_p = PLDM_ERROR_INVALID_LENGTH;
		return PLDM_SUCCESS;
	}

	struct plat_state_effecter_info *info_p = find_state_effecter_info(req_p->effecter_id);

	if (!info_p) {
		LOG_ERR("Can't find effecter ID (0x%x) info", req_p->effecter_id);
		*completion_code_p = PLDM_ERROR_INVALID_DATA;
		return PLDM_SUCCESS;
	}

	switch (info_p->entity_type) {
	case PLDM_ENTITY_IO_CONTROLLER:
		set_effecter_state_gpio_handler(buf, len, resp, resp_len,
						(uint8_t)(info_p->effecter_id & GENMASK(7, 0)));
		break;
	default:
		LOG_ERR("Unsupport entity type, (%d)", info_p->entity_type);
		*completion_code_p = PLDM_ERROR_INVALID_DATA;
		break;
	}

	return PLDM_SUCCESS;
}

uint8_t plat_pldm_get_state_effecter_state_handler(const uint8_t *buf, uint16_t len, uint8_t *resp,
						   uint16_t *resp_len)
{
	CHECK_NULL_ARG_WITH_RETURN(buf, PLDM_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(resp, PLDM_ERROR);
	CHECK_NULL_ARG_WITH_RETURN(resp_len, PLDM_ERROR);
	CHECK_ARG_WITH_RETURN(!len, PLDM_ERROR);

	struct pldm_get_state_effecter_states_req *req_p =
		(struct pldm_get_state_effecter_states_req *)buf;
	uint8_t *completion_code_p = resp;
	*resp_len = 1;

	struct plat_state_effecter_info *info_p = find_state_effecter_info(req_p->effecter_id);

	if (!info_p) {
		LOG_ERR("Can't find effecter ID (0x%x) info", req_p->effecter_id);
		*completion_code_p = PLDM_ERROR_INVALID_DATA;
		return PLDM_SUCCESS;
	}

	switch (info_p->entity_type) {
	case PLDM_ENTITY_IO_CONTROLLER:
		get_effecter_state_gpio_handler(buf, len, resp, resp_len,
						(uint8_t)(info_p->effecter_id & GENMASK(7, 0)));
		break;
	default:
		LOG_ERR("Unsupport entity type, (%d)", info_p->entity_type);
		*completion_code_p = PLDM_ERROR_INVALID_DATA;
		break;
	}

	return PLDM_SUCCESS;
}

void plat_pldm_assign_gpio_effecter_id()
{
	for (uint8_t i = 0; i < PLDM_PLATFORM_OEM_AST1030_GPIO_PIN_NUM_NAX; i++) {
		plat_state_effecter_table[i].effecter_id = (PLAT_EFFECTER_ID_GPIO_HIGH_BYTE | i);
	}
}
