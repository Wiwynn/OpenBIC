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
};

const int PDR_TABLE_SIZE = ARRAY_SIZE(plat_pdr_table);
uint16_t plat_get_pdr_size()
{
	return PDR_TABLE_SIZE;
}

void plat_load_pdr_table(PDR_numeric_sensor* numeric_sensor_table)
{
	memcpy(numeric_sensor_table, plat_pdr_table, sizeof(plat_pdr_table));
}