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

uint8_t pdr_init(void)
{
	load_pdr_table();
	//sdr_info.start_ID = 0x0000;
	//sdr_info.current_ID = sdr_info.start_ID;

	if (numeric_sensor_table == NULL) {
		LOG_ERR("numeric_sensor_table is NULL");
		return false;
	}

	for (uint32_t i = 0; i < pdr_count; i++) {
		numeric_sensor_table[i].recordHandle = i & 0xFFFFFFFF;
		numeric_sensor_table[i].dataLength += (sizeof(PDR_numeric_sensor) - 10);

		/*if (DEBUG_SENSOR) {
			LOG_DBG("%s ID: 0x%x%x, size: %d, recordlen: %d",
				log_strdup(full_sdr_table[i].ID_str), full_sdr_table[i].record_id_h,
				full_sdr_table[i].record_id_l, full_sdr_table[i].ID_len,
				full_sdr_table[i].record_len);
		}*/
	}

	// Record last SDR record ID to sdr_info
	//sdr_info.last_ID = (full_sdr_table[sdr_count - 1].record_id_h << 8) |
	//		   (full_sdr_table[sdr_count - 1].record_id_l);

	//is_sdr_not_init = false;
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
