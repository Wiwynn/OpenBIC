#include <stdio.h>
#include <string.h>
#include "pdr.h"
#include "sensor.h"
#include "plat_pdr_table.h"
#include "plat_sensor_table.h"
#include "plat_ipmb.h"

#include <logging/log.h>

LOG_MODULE_REGISTER(pdr);

extern PDR_numeric_sensor plat_pdr_table[];
extern const int PDR_TABLE_SIZE;

uint32_t pdr_count = 0;
uint16_t pdr_config_size = 0;
PDR_numeric_sensor *numeric_sensor_table;
PDR_INFO *pdr_info;

uint8_t pdr_init(void)
{
	load_pdr_table();

	if (numeric_sensor_table == NULL) {
		LOG_ERR("numeric_sensor_table is NULL");
		return false;
	}

	for (uint32_t i = 0; i < pdr_count; i++) {
		numeric_sensor_table[i].pdr_common_header.record_handle = i & 0xFFFFFFFF;
		numeric_sensor_table[i].pdr_common_header.data_length +=
			(sizeof(PDR_numeric_sensor) - sizeof(PDR_common_header));
	}

	pdr_info->repository_state = PDR_STATE_AVAILABLE;
	pdr_info->record_count = pdr_count;
	pdr_info->repository_size = pdr_count * sizeof(PDR_numeric_sensor);
	pdr_info->largest_record_size = sizeof(PDR_numeric_sensor);

	return true;
}

uint8_t plat_get_pdr_size()
{
	return PDR_TABLE_SIZE;
}

__weak void load_pdr_table(void)
{
	memcpy(numeric_sensor_table, plat_pdr_table, sizeof(PDR_numeric_sensor) * PDR_TABLE_SIZE);
	pdr_count = PDR_TABLE_SIZE;
}
