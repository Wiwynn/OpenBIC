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
		// Inlet Temperature
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
		0x0001, //uint16_t sensor_id;
		0x0089, //uint16_t entity_type;
		0x0001, //uint16_t entity_instance_number;
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
		0x00000000, //int32_t update_interval;
		0x000000FF, //uint32_t max_readable;
		0x00000000, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00000000, //uint32_t warning_high;
		0x00000000, //uint32_t warning_low;
		0x0000003C, //uint32_t critical_high;
		0x00000000, //uint32_t critical_low;
		0x00000096, //uint32_t fatal_high;
		0x00000000, //uint32_t fatal_low;
	},
	{
		// Outlet Temperature
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
		0x0002, //uint16_t sensor_id;
		0x0089, //uint16_t entity_type;
		0x0002, //uint16_t entity_instance_number;
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
		0x00000000, //int32_t update_interval;
		0x000000FF, //uint32_t max_readable;
		0x00000000, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00000000, //uint32_t warning_high;
		0x00000000, //uint32_t warning_low;
		0x00000050, //uint32_t critical_high;
		0x00000000, //uint32_t critical_low;
		0x00000096, //uint32_t fatal_high;
		0x00000000, //uint32_t fatal_low;
	},
	{
		// FIO Temperature
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
		0x0003, //uint16_t sensor_id;
		0x0089, //uint16_t entity_type;
		0x0003, //uint16_t entity_instance_number;
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
		0x00000000, //int32_t update_interval;
		0x000000FF, //uint32_t max_readable;
		0x00000000, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00000000, //uint32_t warning_high;
		0x00000000, //uint32_t warning_low;
		0x00000028, //uint32_t critical_high;
		0x00000000, //uint32_t critical_low;
		0x00000096, //uint32_t fatal_high;
		0x00000000, //uint32_t fatal_low;
	},
	{
		// CPU Temperature
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
		0x0004, //uint16_t sensor_id;
		0x0087, //uint16_t entity_type;
		0x0001, //uint16_t entity_instance_number;
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
		0x00000000, //int32_t update_interval;
		0x000000FF, //uint32_t max_readable;
		0x00000000, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00000000, //uint32_t warning_high;
		0x00000000, //uint32_t warning_low;
		0x0000005B, //uint32_t critical_high;
		0x00000000, //uint32_t critical_low;
		0x00000000, //uint32_t fatal_high;
		0x00000000, //uint32_t fatal_low;
	},
	{
		// DIMMA Temperature
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
		0x0005, //uint16_t sensor_id;
		0x008E, //uint16_t entity_type;
		0x0001, //uint16_t entity_instance_number;
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
		0x00000000, //int32_t update_interval;
		0x000000FF, //uint32_t max_readable;
		0x00000000, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00000000, //uint32_t warning_high;
		0x00000000, //uint32_t warning_low;
		0x00000055, //uint32_t critical_high;
		0x00000000, //uint32_t critical_low;
		0x00000000, //uint32_t fatal_high;
		0x00000000, //uint32_t fatal_low;
	},

	{
		// DIMMB Temperature
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
		0x0006, //uint16_t sensor_id;
		0x008E, //uint16_t entity_type;
		0x0002, //uint16_t entity_instance_number;
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
		0x00000000, //int32_t update_interval;
		0x000000FF, //uint32_t max_readable;
		0x00000000, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00000000, //uint32_t warning_high;
		0x00000000, //uint32_t warning_low;
		0x00000055, //uint32_t critical_high;
		0x00000000, //uint32_t critical_low;
		0x00000000, //uint32_t fatal_high;
		0x00000000, //uint32_t fatal_low;
	},
	{
		// DIMMC Temperature
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
		0x0007, //uint16_t sensor_id;
		0x008E, //uint16_t entity_type;
		0x0003, //uint16_t entity_instance_number;
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
		0x00000000, //int32_t update_interval;
		0x000000FF, //uint32_t max_readable;
		0x00000000, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00000000, //uint32_t warning_high;
		0x00000000, //uint32_t warning_low;
		0x00000055, //uint32_t critical_high;
		0x00000000, //uint32_t critical_low;
		0x00000000, //uint32_t fatal_high;
		0x00000000, //uint32_t fatal_low;
	},
	{
		// DIMMD Temperature
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
		0x0008, //uint16_t sensor_id;
		0x008E, //uint16_t entity_type;
		0x0004, //uint16_t entity_instance_number;
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
		0x00000000, //int32_t update_interval;
		0x000000FF, //uint32_t max_readable;
		0x00000000, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00000000, //uint32_t warning_high;
		0x00000000, //uint32_t warning_low;
		0x00000055, //uint32_t critical_high;
		0x00000000, //uint32_t critical_low;
		0x00000000, //uint32_t fatal_high;
		0x00000000, //uint32_t fatal_low;
	},
	{
		// DIMME Temperature
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
		0x0009, //uint16_t sensor_id;
		0x008E, //uint16_t entity_type;
		0x0005, //uint16_t entity_instance_number;
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
		0x00000000, //int32_t update_interval;
		0x000000FF, //uint32_t max_readable;
		0x00000000, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00000000, //uint32_t warning_high;
		0x00000000, //uint32_t warning_low;
		0x00000055, //uint32_t critical_high;
		0x00000000, //uint32_t critical_low;
		0x00000000, //uint32_t fatal_high;
		0x00000000, //uint32_t fatal_low;
	},
	{
		// DIMMF Temperature
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
		0x000A, //uint16_t sensor_id;
		0x008E, //uint16_t entity_type;
		0x0006, //uint16_t entity_instance_number;
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
		0x00000000, //int32_t update_interval;
		0x000000FF, //uint32_t max_readable;
		0x00000000, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00000000, //uint32_t warning_high;
		0x00000000, //uint32_t warning_low;
		0x00000055, //uint32_t critical_high;
		0x00000000, //uint32_t critical_low;
		0x00000000, //uint32_t fatal_high;
		0x00000000, //uint32_t fatal_low;
	},
	{
		// DIMMG Temperature
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
		0x000B, //uint16_t sensor_id;
		0x008E, //uint16_t entity_type;
		0x0007, //uint16_t entity_instance_number;
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
		0x00000000, //int32_t update_interval;
		0x000000FF, //uint32_t max_readable;
		0x00000000, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00000000, //uint32_t warning_high;
		0x00000000, //uint32_t warning_low;
		0x00000055, //uint32_t critical_high;
		0x00000000, //uint32_t critical_low;
		0x00000000, //uint32_t fatal_high;
		0x00000000, //uint32_t fatal_low;
	},
	{
		// DIMMH Temperature
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
		0x000C, //uint16_t sensor_id;
		0x008E, //uint16_t entity_type;
		0x0008, //uint16_t entity_instance_number;
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
		0x00000000, //int32_t update_interval;
		0x000000FF, //uint32_t max_readable;
		0x00000000, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00000000, //uint32_t warning_high;
		0x00000000, //uint32_t warning_low;
		0x00000055, //uint32_t critical_high;
		0x00000000, //uint32_t critical_low;
		0x00000000, //uint32_t fatal_high;
		0x00000000, //uint32_t fatal_low;
	},
	{
		// DIMMI Temperature
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
		0x000D, //uint16_t sensor_id;
		0x008E, //uint16_t entity_type;
		0x0009, //uint16_t entity_instance_number;
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
		0x00000000, //int32_t update_interval;
		0x000000FF, //uint32_t max_readable;
		0x00000000, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00000000, //uint32_t warning_high;
		0x00000000, //uint32_t warning_low;
		0x00000055, //uint32_t critical_high;
		0x00000000, //uint32_t critical_low;
		0x00000000, //uint32_t fatal_high;
		0x00000000, //uint32_t fatal_low;
	},
	{
		// DIMMJ Temperature
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
		0x000E, //uint16_t sensor_id;
		0x008E, //uint16_t entity_type;
		0x000A, //uint16_t entity_instance_number;
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
		0x00000000, //int32_t update_interval;
		0x000000FF, //uint32_t max_readable;
		0x00000000, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00000000, //uint32_t warning_high;
		0x00000000, //uint32_t warning_low;
		0x00000055, //uint32_t critical_high;
		0x00000000, //uint32_t critical_low;
		0x00000000, //uint32_t fatal_high;
		0x00000000, //uint32_t fatal_low;
	},
	{
		// DIMMK Temperature
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
		0x000F, //uint16_t sensor_id;
		0x008E, //uint16_t entity_type;
		0x000B, //uint16_t entity_instance_number;
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
		0x00000000, //int32_t update_interval;
		0x000000FF, //uint32_t max_readable;
		0x00000000, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00000000, //uint32_t warning_high;
		0x00000000, //uint32_t warning_low;
		0x00000055, //uint32_t critical_high;
		0x00000000, //uint32_t critical_low;
		0x00000000, //uint32_t fatal_high;
		0x00000000, //uint32_t fatal_low;
	},
	{
		// DIMML Temperature
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
		0x0010, //uint16_t sensor_id;
		0x008E, //uint16_t entity_type;
		0x000C, //uint16_t entity_instance_number;
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
		0x00000000, //int32_t update_interval;
		0x000000FF, //uint32_t max_readable;
		0x00000000, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00000000, //uint32_t warning_high;
		0x00000000, //uint32_t warning_low;
		0x00000055, //uint32_t critical_high;
		0x00000000, //uint32_t critical_low;
		0x00000000, //uint32_t fatal_high;
		0x00000000, //uint32_t fatal_low;
	},
	{
		// SSD Boot Temperature
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
		0x0011, //uint16_t sensor_id;
		0x006F, //uint16_t entity_type;
		0x0001, //uint16_t entity_instance_number;
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
		0x00000000, //int32_t update_interval;
		0x000000FF, //uint32_t max_readable;
		0x00000000, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00000000, //uint32_t warning_high;
		0x00000000, //uint32_t warning_low;
		0x0000004D, //uint32_t critical_high;
		0x00000000, //uint32_t critical_low;
		0x0000005D, //uint32_t fatal_high;
		0x00000000, //uint32_t fatal_low;
	},
	{
		// SSD Data Temperature
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
		0x0012, //uint16_t sensor_id;
		0x006F, //uint16_t entity_type;
		0x0002, //uint16_t entity_instance_number;
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
		0x00000000, //int32_t update_interval;
		0x000000FF, //uint32_t max_readable;
		0x00000000, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00000000, //uint32_t warning_high;
		0x00000000, //uint32_t warning_low;
		0x0000004D, //uint32_t critical_high;
		0x00000000, //uint32_t critical_low;
		0x0000005D, //uint32_t fatal_high;
		0x00000000, //uint32_t fatal_low;
	},
	{
		// VR CPU0 Temperature
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
		0x0013, //uint16_t sensor_id;
		0x007C, //uint16_t entity_type;
		0x0001, //uint16_t entity_instance_number;
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
		0x00000000, //int32_t update_interval;
		0x000000FF, //uint32_t max_readable;
		0x00000000, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00000000, //uint32_t warning_high;
		0x00000000, //uint32_t warning_low;
		0x00000064, //uint32_t critical_high;
		0x00000000, //uint32_t critical_low;
		0x0000007D, //uint32_t fatal_high;
		0x00000000, //uint32_t fatal_low;
	},
	{
		// VR SOC Temperature
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
		0x0014, //uint16_t sensor_id;
		0x007C, //uint16_t entity_type;
		0x0002, //uint16_t entity_instance_number;
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
		0x00000000, //int32_t update_interval;
		0x000000FF, //uint32_t max_readable;
		0x00000000, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00000000, //uint32_t warning_high;
		0x00000000, //uint32_t warning_low;
		0x00000064, //uint32_t critical_high;
		0x00000000, //uint32_t critical_low;
		0x0000007D, //uint32_t fatal_high;
		0x00000000, //uint32_t fatal_low;
	},
	{
		// VR CPU1 Temperature
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
		0x0015, //uint16_t sensor_id;
		0x007C, //uint16_t entity_type;
		0x0003, //uint16_t entity_instance_number;
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
		0x00000000, //int32_t update_interval;
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
	{
		// VR PVDDIO Temperature
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
		0x0016, //uint16_t sensor_id;
		0x007C, //uint16_t entity_type;
		0x0004, //uint16_t entity_instance_number;
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
		0x00000000, //int32_t update_interval;
		0x000000FF, //uint32_t max_readable;
		0x00000000, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00000000, //uint32_t warning_high;
		0x00000000, //uint32_t warning_low;
		0x00000064, //uint32_t critical_high;
		0x00000000, //uint32_t critical_low;
		0x0000007D, //uint32_t fatal_high;
		0x00000000, //uint32_t fatal_low;
	},
	{
		// VR PVDD11 Temperature
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
		0x0017, //uint16_t sensor_id;
		0x007C, //uint16_t entity_type;
		0x0005, //uint16_t entity_instance_number;
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
		0x00000000, //int32_t update_interval;
		0x000000FF, //uint32_t max_readable;
		0x00000000, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00000000, //uint32_t warning_high;
		0x00000000, //uint32_t warning_low;
		0x00000064, //uint32_t critical_high;
		0x00000000, //uint32_t critical_low;
		0x0000007D, //uint32_t fatal_high;
		0x00000000, //uint32_t fatal_low;
	},
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
		0x00, //uint8_t sensor_init;
		0x00, //uint8_t sensor_auxiliary_names_pdr;
		0x05, //uint8_t base_unit;
		-0x04, //int8_t unit_modifier;
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
		0x00000000, //int32_t update_interval;
		0x0001FA40, //uint32_t max_readable;
		0x0001AF40, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
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
	{
		// PVDD18 S5 Voltage
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
		0x0019, //uint16_t sensor_id;
		0x0087, //uint16_t entity_type;
		0x0003, //uint16_t entity_instance_number;
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
		0x00000000, //int32_t update_interval;
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
	{
		// P3V3 stby Voltage
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
		0x001A, //uint16_t sensor_id;
		0x0087, //uint16_t entity_type;
		0x0004, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
		0x00, //uint8_t sensor_auxiliary_names_pdr;
		0x05, //uint8_t base_unit;
		-0x05, //int8_t unit_modifier;
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
		0x00000000, //int32_t update_interval;
		0x00054984, //uint32_t max_readable;
		0x0004C89C, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00056496, //uint32_t warning_high;
		0x0004B01E, //uint32_t warning_low;
		0x00057279, //uint32_t critical_high;
		0x0004A3DF, //uint32_t critical_low;
		0x0005D750, //uint32_t fatal_high;
		0x00040740, //uint32_t fatal_low;
	},
	{
		// P3V BAT Voltage
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
		0x001B, //uint16_t sensor_id;
		0x0087, //uint16_t entity_type;
		0x0005, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
		0x00, //uint8_t sensor_auxiliary_names_pdr;
		0x05, //uint8_t base_unit;
		-0x04, //int8_t unit_modifier;
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
		0x00015180, //int32_t update_interval;
		0x000084D0, //uint32_t max_readable;
		0x00006F54, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00008778, //uint32_t warning_high;
		0x00006D1A, //uint32_t warning_low;
		0x000088CC, //uint32_t critical_high;
		0x00006BFD, //uint32_t critical_low;
		0x00000000, //uint32_t fatal_high;
		0x00000000, //uint32_t fatal_low;
	},
	{
		// PVDD33 S5 Voltage
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
		0x001C, //uint16_t sensor_id;
		0x0087, //uint16_t entity_type;
		0x0006, //uint16_t entity_instance_number;
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
		0x00000000, //int32_t update_interval;
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
	{
		// P5V stby Voltage
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
		0x001D, //uint16_t sensor_id;
		0x0087, //uint16_t entity_type;
		0x0007, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
		0x00, //uint8_t sensor_auxiliary_names_pdr;
		0x05, //uint8_t base_unit;
		-0x04, //int8_t unit_modifier;
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
		0x00000000, //int32_t update_interval;
		0x0000D6D8, //uint32_t max_readable;
		0x0000B98C, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x0000DB24, //uint32_t warning_high;
		0x0000B5D6, //uint32_t warning_low;
		0x0000DD4A, //uint32_t critical_high;
		0x0000B3FB, //uint32_t critical_low;
		0x0000E290, //uint32_t fatal_high;
		0x00009C40, //uint32_t fatal_low;
	},
	{
		// P12V DIMM0 Voltage
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
		0x001E, //uint16_t sensor_id;
		0x0087, //uint16_t entity_type;
		0x0008, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
		0x00, //uint8_t sensor_auxiliary_names_pdr;
		0x05, //uint8_t base_unit;
		-0x03, //int8_t unit_modifier;
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
		0x00000000, //int32_t update_interval;
		0x000035E8, //uint32_t max_readable;
		0x000027D8, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x000036FC, //uint32_t warning_high;
		0x0000270C, //uint32_t warning_low;
		0x00003786, //uint32_t critical_high;
		0x000026A6, //uint32_t critical_low;
		0x00000000, //uint32_t fatal_high;
		0x00000000, //uint32_t fatal_low;
	},
	{
		// P12V DIMM1 Voltage
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
		0x001F, //uint16_t sensor_id;
		0x0087, //uint16_t entity_type;
		0x0009, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
		0x00, //uint8_t sensor_auxiliary_names_pdr;
		0x05, //uint8_t base_unit;
		-0x03, //int8_t unit_modifier;
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
		0x00000000, //int32_t update_interval;
		0x000035E8, //uint32_t max_readable;
		0x000027D8, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x000036FC, //uint32_t warning_high;
		0x0000270C, //uint32_t warning_low;
		0x00003786, //uint32_t critical_high;
		0x000026A6, //uint32_t critical_low;
		0x00000000, //uint32_t fatal_high;
		0x00000000, //uint32_t fatal_low;
	},
	{
		// P1V2 stby Voltage
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
		0x0020, //uint16_t sensor_id;
		0x0087, //uint16_t entity_type;
		0x000A, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
		0x00, //uint8_t sensor_auxiliary_names_pdr;
		0x05, //uint8_t base_unit;
		-0x04, //int8_t unit_modifier;
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
		0x00000000, //int32_t update_interval;
		0x00003138, //uint32_t max_readable;
		0x00002C88, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00003234, //uint32_t warning_high;
		0x00002BA4, //uint32_t warning_low;
		0x000032B2, //uint32_t critical_high;
		0x00002B32, //uint32_t critical_low;
		0x00000000, //uint32_t fatal_high;
		0x00000000, //uint32_t fatal_low;
	},
	{
		// P1V8 stby Voltage
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
		0x0021, //uint16_t sensor_id;
		0x0087, //uint16_t entity_type;
		0x000B, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
		0x00, //uint8_t sensor_auxiliary_names_pdr;
		0x05, //uint8_t base_unit;
		-0x04, //int8_t unit_modifier;
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
		0x00000000, //int32_t update_interval;
		0x000049D4, //uint32_t max_readable;
		0x000042CC, //uint32_t min_readable;
		0x10, //uint8_t range_field_format;
		0x78, //uint8_t range_field_support;
		0x00000000, //uint32_t nominal_value;
		0x00000000, //uint32_t normal_max;
		0x00000000, //uint32_t normal_min;
		0x00004B4E, //uint32_t warning_high;
		0x00004176, //uint32_t warning_low;
		0x00004C0B, //uint32_t critical_high;
		0x000040CB, //uint32_t critical_low;
		0x00005190, //uint32_t fatal_high;
		0x00003840, //uint32_t fatal_low;
	},
	{
		// Slot detect Voltage
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
		0x0022, //uint16_t sensor_id;
		0x0087, //uint16_t entity_type;
		0x000C, //uint16_t entity_instance_number;
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
		0x00000000, //int32_t update_interval;
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
	{
		// Sidecar detect stby Voltage
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
		0x0023, //uint16_t sensor_id;
		0x0087, //uint16_t entity_type;
		0x000D, //uint16_t entity_instance_number;
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
		0x00000000, //int32_t update_interval;
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
	{
		// VR CPU0 Current
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
		0x0024, //uint16_t sensor_id;
		0x007C, //uint16_t entity_type;
		0x0006, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
		0x00, //uint8_t sensor_auxiliary_names_pdr;
		0x06, //uint8_t base_unit;
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
		0x00000000, //int32_t update_interval;
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
	{
		// VR SOC Current
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
		0x0025, //uint16_t sensor_id;
		0x007C, //uint16_t entity_type;
		0x0006, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
		0x00, //uint8_t sensor_auxiliary_names_pdr;
		0x06, //uint8_t base_unit;
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
		0x00000000, //int32_t update_interval;
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
	{
		// VR CPU1 Current
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
		0x0026, //uint16_t sensor_id;
		0x007C, //uint16_t entity_type;
		0x0008, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
		0x00, //uint8_t sensor_auxiliary_names_pdr;
		0x06, //uint8_t base_unit;
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
		0x00000000, //int32_t update_interval;
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
	{
		// VR PVDDIO Current
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
		0x0027, //uint16_t sensor_id;
		0x007C, //uint16_t entity_type;
		0x0009, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
		0x00, //uint8_t sensor_auxiliary_names_pdr;
		0x06, //uint8_t base_unit;
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
		0x00000000, //int32_t update_interval;
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
	{
		// VR PVDDII Current
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
		0x0028, //uint16_t sensor_id;
		0x007C, //uint16_t entity_type;
		0x000A, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
		0x00, //uint8_t sensor_auxiliary_names_pdr;
		0x06, //uint8_t base_unit;
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
		0x00000000, //int32_t update_interval;
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
	{
		// VR CPU0 Power
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
		0x0029, //uint16_t sensor_id;
		0x007C, //uint16_t entity_type;
		0x000B, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
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
		0x00000000, //int32_t update_interval;
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
	{
		// VR SOC Power
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
		0x002A, //uint16_t sensor_id;
		0x007C, //uint16_t entity_type;
		0x000C, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
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
		0x00000000, //int32_t update_interval;
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
	{
		// VR CPU1 Power
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
		0x002B, //uint16_t sensor_id;
		0x007C, //uint16_t entity_type;
		0x000D, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
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
		0x00000000, //int32_t update_interval;
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
	{
		// VR PVDDIO Power
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
		0x002C, //uint16_t sensor_id;
		0x007C, //uint16_t entity_type;
		0x000E, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
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
		0x00000000, //int32_t update_interval;
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
		0x00, //uint8_t sensor_init;
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
		0x00000000, //int32_t update_interval;
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
	{
		// CPU Power
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
		0x002E, //uint16_t sensor_id;
		0x0087, //uint16_t entity_type;
		0x000E, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
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
		0x00000000, //int32_t update_interval;
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
	{
		// DIMMA Power
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
		0x002F, //uint16_t sensor_id;
		0x008E, //uint16_t entity_type;
		0x000D, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
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
		0x00000000, //int32_t update_interval;
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
	{
		// DIMMB Power
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
		0x0030, //uint16_t sensor_id;
		0x008E, //uint16_t entity_type;
		0x000E, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
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
		0x00000000, //int32_t update_interval;
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
	{
		// DIMMC Power
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
		0x0031, //uint16_t sensor_id;
		0x008E, //uint16_t entity_type;
		0x000F, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
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
		0x00000000, //int32_t update_interval;
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
	{
		// DIMMD Power
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
		0x0032, //uint16_t sensor_id;
		0x008E, //uint16_t entity_type;
		0x0010, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
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
		0x00000000, //int32_t update_interval;
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
	{
		// DIMME Power
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
		0x0033, //uint16_t sensor_id;
		0x008E, //uint16_t entity_type;
		0x0011, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
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
		0x00000000, //int32_t update_interval;
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
	{
		// DIMMF Power
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
		0x0034, //uint16_t sensor_id;
		0x008E, //uint16_t entity_type;
		0x0012, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
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
		0x00000000, //int32_t update_interval;
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
	{
		// DIMMG Power
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
		0x0035, //uint16_t sensor_id;
		0x008E, //uint16_t entity_type;
		0x0013, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
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
		0x00000000, //int32_t update_interval;
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
	{
		// DIMMH Power
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
		0x0036, //uint16_t sensor_id;
		0x008E, //uint16_t entity_type;
		0x0014, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
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
		0x00000000, //int32_t update_interval;
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
	{
		// DIMMI Power
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
		0x0037, //uint16_t sensor_id;
		0x008E, //uint16_t entity_type;
		0x0015, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
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
		0x00000000, //int32_t update_interval;
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
	{
		// DIMMJ Power
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
		0x0038, //uint16_t sensor_id;
		0x008E, //uint16_t entity_type;
		0x0016, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
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
		0x00000000, //int32_t update_interval;
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
	{
		// DIMMK Power
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
		0x0039, //uint16_t sensor_id;
		0x008E, //uint16_t entity_type;
		0x0017, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
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
		0x00000000, //int32_t update_interval;
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
	{
		// DIMML Power
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
		0x003A, //uint16_t sensor_id;
		0x008E, //uint16_t entity_type;
		0x0018, //uint16_t entity_instance_number;
		0x0000, //uint16_t container_id;
		0x00, //uint8_t sensor_init;
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
		0x00000000, //int32_t update_interval;
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

const int PDR_TABLE_SIZE = ARRAY_SIZE(plat_pdr_table);

void load_pdr_table(void)
{
	memcpy(numeric_sensor_table, plat_pdr_table, sizeof(plat_pdr_table));
	pdr_count = PDR_TABLE_SIZE;
}
