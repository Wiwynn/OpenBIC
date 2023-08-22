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
		/*** PDR common header***/
		{
			//uint32_t record_handle
			//uint8_t PDR_header_version
			//uint8_t PDR_type
			//uint16_t record_change_number
			//uint16_t data_ength
		},

		/***numeric sensor format***/
		//uint16_t PLDM_terminus_handle;
		//uint16_t sensor_id;
		//uint16_t entity_type;
		//uint16_t entity_instance_number;
		//uint16_t container_id;
		//uint8_t sensor_init;
		//uint8_t sensor_auxiliary_names_pdr;
		//uint8_t base_unit;
		//int8_t unit_modifier;
		//uint8_t rate_unit;
		//uint8_t base_oem_unit_handle;
		//uint8_t aux_unit;
		//int8_t aux_unit_modifier;
		//uint8_t auxrate_unit;
		//uint8_t rel;
		//uint8_t aux_oem_unit_handle;
		//uint8_t is_linear;
		//uint8_t sensor_data_size;
		//int32_t resolution;
		//int32_t offset;
		//uint16_t accuracy;
		//uint8_t plus_tolerance;
		//uint8_t minus_tolerance;
		//uint8_t hysteresis;
		//uint8_t supported_thresholds;
		//uint8_t threshold_and_hysteresis_volatility;
		//int32_t state_transition_interval;
		//int32_t update_interval;
		//uint32_t max_readable;
		//uint32_t min_readable;
		//uint8_t range_field_format;
		//uint8_t range_field_support;
		//uint32_t nominal_value;
		//uint32_t normal_max;
		//uint32_t normal_min;
		//uint32_t warning_high;
		//uint32_t warning_low;
		//uint32_t critical_high;
		//uint32_t critical_low;
		//uint32_t fatal_high;
		//uint32_t fatal_low;
	},
};

const int PDR_TABLE_SIZE = ARRAY_SIZE(plat_pdr_table);

void load_pdr_table(void)
{
	memcpy(numeric_sensor_table, plat_pdr_table, sizeof(plat_pdr_table));
	pdr_count = PDR_TABLE_SIZE;
}
