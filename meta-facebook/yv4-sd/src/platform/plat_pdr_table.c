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

#include "plat_pdr_table.h"

#include <stdio.h>
#include <string.h>

#include "pdr.h"
#include "sensor.h"
#include "plat_sensor_table.h"
#include <logging/log.h>

LOG_MODULE_REGISTER(plat_pdr_table);

PDR_numeric_sensor plat_pdr_table[] = {
	{
		// P12V STBY ADC voltage
		/*** PDR common header***/
		{
			0x00000000, //uint32_t record_handle
			0x00, //uint8_t PDR_header_version
			0x00, //uint8_t PDR_type
			0x0000, //uint16_t record_change_number
			0x0000, //uint16_t data_ength
		},

		/***numeric sensor format***/
		0x1000, //uint16_t PLDM_terminus_handle;
		0x0020, //uint16_t sensor_id;
		0x8801, //uint16_t entity_type;
		0x1000, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
		0x00, //uint8_t sensor_auxiliary_names_pdr;
		0x05, //uint8_t base_unit;
		0x00, //int8_t unit_modifier;
		0x00, //uint8_t rate_unit;
		0x00, //uint8_t base_oem_unit_handle;
		0x00, //uint8_t aux_unit;
		0x00, //int8_t aux_unit_modifier;
		0x00, //uint8_t auxrate_unit;
		0x00, //uint8_t rel;
		0x00, //uint8_t aux_oem_unit_handle;
		0x00, //uint8_t is_linear;
		0x04, //uint8_t sensor_data_size;
		0x00000000, //int32_t resolution;
		0x00000000, //int32_t offset;
		0x0000, //uint16_t accuracy;
		0x00, //uint8_t plus_tolerance;
		0x00, //uint8_t minus_tolerance;
		0x00, //uint8_t hysteresis;
		0x3F, //uint8_t supported_thresholds;
		0x00, //uint8_t threshold_and_hysteresis_volatility;
		0x00000000, //int32_t state_transition_interval;
		0x00000000, //int32_t update_interval;
		0x00000000, //uint32_t max_readable;
		0x00000000, //uint32_t min_readable;
		0x04, //uint8_t range_field_format;
		0x7F, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x0890000D, //uint32_t warning_high;
		0x2000000A, //uint32_t warning_low;
		0x0DA0000A, //uint32_t critical_high;
		0x1BB0000A, //uint32_t critical_low;
		0x014D000E, //uint32_t fatal_high;
		0x005B000A, //uint32_t fatal_low;
	},
	{
		// PVCCFA_EHV VR voltage
		/*** PDR common header***/
		{
			0x00000000, //uint32_t record_handle
			0x00, //uint8_t PDR_header_version
			0x00, //uint8_t PDR_type
			0x0000, //uint16_t record_change_number
			0x0000, //uint16_t data_ength
		},

		/***numeric sensor format***/
		0x1000, //uint16_t PLDM_terminus_handle;
		0x002D, //uint16_t sensor_id;
		0x8801, //uint16_t entity_type;
		0x1000, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
		0x00, //uint8_t sensor_auxiliary_names_pdr;
		0x05, //uint8_t base_unit;
		0x00, //int8_t unit_modifier;
		0x00, //uint8_t rate_unit;
		0x00, //uint8_t base_oem_unit_handle;
		0x00, //uint8_t aux_unit;
		0x00, //int8_t aux_unit_modifier;
		0x00, //uint8_t auxrate_unit;
		0x00, //uint8_t rel;
		0x00, //uint8_t aux_oem_unit_handle;
		0x00, //uint8_t is_linear;
		0x04, //uint8_t sensor_data_size;
		0x00000000, //int32_t resolution;
		0x00000000, //int32_t offset;
		0x0000, //uint16_t accuracy;
		0x00, //uint8_t plus_tolerance;
		0x00, //uint8_t minus_tolerance;
		0x00, //uint8_t hysteresis;
		0x06, //uint8_t supported_thresholds;
		0x00, //uint8_t threshold_and_hysteresis_volatility;
		0x00000000, //int32_t state_transition_interval;
		0x00000000, //int32_t update_interval;
		0x00000000, //uint32_t max_readable;
		0x00000000, //uint32_t min_readable;
		0x04, //uint8_t range_field_format;
		0x7F, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x0001036E, //uint32_t warning_high;
		0x000102CA, //uint32_t warning_low;
		0x00010380, //uint32_t critical_high;
		0x00010289, //uint32_t critical_low;
		0x00020002, //uint32_t fatal_high;
		0x00000004, //uint32_t fatal_low;
	},
	{
		// TMP75 on board temperature
		/*** PDR common header***/
		{
			0x00000000, //uint32_t record_handle
			0x00, //uint8_t PDR_header_version
			0x00, //uint8_t PDR_type
			0x0000, //uint16_t record_change_number
			0x0000, //uint16_t data_ength
		},

		/***numeric sensor format***/
		0x1000, //uint16_t PLDM_terminus_handle;
		0x0001, //uint16_t sensor_id;
		0x8801, //uint16_t entity_type;
		0x1000, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
		0x00, //uint8_t sensor_auxiliary_names_pdr;
		0x02, //uint8_t base_unit;
		0x00, //int8_t unit_modifier;
		0x00, //uint8_t rate_unit;
		0x00, //uint8_t base_oem_unit_handle;
		0x00, //uint8_t aux_unit;
		0x00, //int8_t aux_unit_modifier;
		0x00, //uint8_t auxrate_unit;
		0x00, //uint8_t rel;
		0x00, //uint8_t aux_oem_unit_handle;
		0x00, //uint8_t is_linear;
		0x04, //uint8_t sensor_data_size;
		0x00000000, //int32_t resolution;
		0x00000000, //int32_t offset;
		0x0000, //uint16_t accuracy;
		0x00, //uint8_t plus_tolerance;
		0x00, //uint8_t minus_tolerance;
		0x00, //uint8_t hysteresis;
		0x06, //uint8_t supported_thresholds;
		0x00, //uint8_t threshold_and_hysteresis_volatility;
		0x00000000, //int32_t state_transition_interval;
		0x00000000, //int32_t update_interval;
		0x00000000, //uint32_t max_readable;
		0x00000000, //uint32_t min_readable;
		0x04, //uint8_t range_field_format;
		0x29, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00000000, //uint32_t warning_high;
		0x00000000, //uint32_t warning_low;
		0x00000000, //uint32_t critical_high;
		0x00340000, //uint32_t critical_low;
		0x00960000, //uint32_t fatal_high;
		0x00000000, //uint32_t fatal_low;
    },
};

const int PDR_TABLE_SIZE = ARRAY_SIZE(plat_pdr_table);

void load_pdr_table(void)
{
	memcpy(numeric_sensor_table, plat_pdr_table, sizeof(plat_pdr_table));
	pdr_count = PDR_TABLE_SIZE;
}
