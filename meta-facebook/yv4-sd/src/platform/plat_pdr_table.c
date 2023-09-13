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
};

PDR_numeric_sensor pdr_numeric_adc_table[] = {
	{
		// P12V stby Voltage
		/*** PDR common header***/
		{
			0x00000000, //uint32_t record_handle
			0x01, //uint8_t PDR_header_version
			0x02, //uint8_t PDR_type
			0x0000, //uint16_t record_change_number
			0x0000, //uint16_t data_length
		},

		/***numeric sensor format***/
		0x0000, //uint16_t PLDM_terminus_handle;
		0x0018, //uint16_t sensor_id;
		0x0087, //uint16_t entity_type;
		0x0002, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		PDR_SENSOR_USEINIT_PDR, //uint8_t sensor_init;
		0x00, //uint8_t sensor_auxiliary_names_pdr;
		0x05, //uint8_t base_unit;
		-4, //int8_t unit_modifier;
		0x00, //uint8_t rate_unit;
		0x00, //uint8_t base_oem_unit_handle;
		0x00, //uint8_t aux_unit;
		0x00, //int8_t aux_unit_modifier;
		0x00, //uint8_t auxrate_unit;
		0x00, //uint8_t rel;
		0x00, //uint8_t aux_oem_unit_handle;
		0x00, //uint8_t is_linear;
		0x04, //uint8_t sensor_data_size;
		1, //real32_t resolution;
		0, //real32_t offset;
		0x0000, //uint16_t accuracy;
		0x00, //uint8_t plus_tolerance;
		0x00, //uint8_t minus_tolerance;
		0x00000000, //uint32_t hysteresis;
		0xFF, //uint8_t supported_thresholds;
		0x00, //uint8_t threshold_and_hysteresis_volatility;
		0, //real32_t state_transition_interval;
		UPDATE_INTERVAL_1S, //real32_t update_interval;
		0x0001FA40, //uint32_t max_readable;
		0x0001AF40, //uint32_t min_readable;
		0x04, //uint8_t range_field_format;
		0xFF, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00020460, //uint32_t warning_high;
		0x0001A6A0, //uint32_t warning_low;
		0x00020970, //uint32_t critical_high;
		0x0001A250, //uint32_t critical_low;
		0x00022FE2, //uint32_t fatal_high;
		0x00018A2E, //uint32_t fatal_low;
	},
};

PDR_numeric_sensor pdr_numeric_vr_table[] = {
	{
		// VR PVDD11 Power
		/*** PDR common header***/
		{
			0x00000000, //uint32_t record_handle
			0x01, //uint8_t PDR_header_version
			0x02, //uint8_t PDR_type
			0x0000, //uint16_t record_change_number
			0x0000, //uint16_t data_length
		},

		/***numeric sensor format***/
		0x0000, //uint16_t PLDM_terminus_handle;
		0x002D, //uint16_t sensor_id;
		0x007C, //uint16_t entity_type;
		0x000F, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		PDR_SENSOR_USEINIT_PDR, //uint8_t sensor_init;
		0x00, //uint8_t sensor_auxiliary_names_pdr;
		0x07, //uint8_t base_unit;
		0x00, //int8_t unit_modifier;
		0x00, //uint8_t rate_unit;
		0x00, //uint8_t base_oem_unit_handle;
		0x00, //uint8_t aux_unit;
		0x00, //int8_t aux_unit_modifier;
		0x00, //uint8_t auxrate_unit;
		0x00, //uint8_t rel;
		0x00, //uint8_t aux_oem_unit_handle;
		0x00, //uint8_t is_linear;
		0x10, //uint8_t sensor_data_size;
		0x00000001, //int32_t resolution;
		0x00000000, //int32_t offset;
		0x0000, //uint16_t accuracy;
		0x00, //uint8_t plus_tolerance;
		0x00, //uint8_t minus_tolerance;
		0x00, //uint8_t hysteresis;
		0x3F, //uint8_t supported_thresholds;
		0x00, //uint8_t threshold_and_hysteresis_volatility;
		0x00000000, //int32_t state_transition_interval;
		UPDATE_INTERVAL_3S, //int32_t update_interval;
		0x00000000, //uint32_t max_readable;
		0x00000000, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00000000, //uint32_t warning_high;
		0x00000000, //uint32_t warning_low;
		0x00000000, //uint32_t critical_high;
		0x00000000, //uint32_t critical_low;
		0x00000000, //uint32_t fatal_high;
		0x00000000, //uint32_t fatal_low;
	},
};

uint16_t plat_get_pdr_size()
{
	int total_size = 0;

	total_size += ARRAY_SIZE(pdr_numeric_adc_table);
	//total_size += ARRAY_SIZE(pdr_numeric_vr_table);

	return total_size;
}

void plat_load_pdr_table(PDR_numeric_sensor *numeric_sensor_table)
{
	memcpy(&numeric_sensor_table[0], pdr_numeric_adc_table, sizeof(pdr_numeric_adc_table));
}
