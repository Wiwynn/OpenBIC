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

#include <math.h>
#include <zephyr.h>
#include <logging/log.h>
#include "libutil.h"
#include "plat_pdr_table.h"
#include "plat_pldm_sensor.h"
#include "pldm_sensor.h"

LOG_MODULE_REGISTER(pldm_sensor);

static struct k_thread pldm_sensor_polling_thread[MAX_SENSOR_THREAD_ID];
static k_tid_t pldm_sensor_polling_tid[MAX_SENSOR_THREAD_ID];
K_THREAD_STACK_EXTERN(pldm_sensor_poll_stack);
K_THREAD_STACK_ARRAY_DEFINE(pldm_sensor_poll_stacks, MAX_SENSOR_THREAD_ID, PLDM_SENSOR_POLL_STACK_SIZE);

pldm_sensor_thread *pldm_sensor_thread_list;
pldm_sensor_info *pldm_sensor_list[MAX_SENSOR_THREAD_ID];

__weak pldm_sensor_thread * plat_load_pldm_sensor_thread()
{
	return NULL;
}

__weak int plat_load_pldm_sensor(int thread_id, pldm_sensor_info *pldm_sensor_list)
{
	return -1;
}

__weak int plat_get_pldm_sensor_count(int thread_id)
{
	return -1;
}

bool is_interval_ready(pldm_sensor_info *pldm_sensor_list)
{
	uint32_t current_time = 0, diff_time = 0;

	current_time = k_uptime_get_32();
	diff_time = current_time - pldm_sensor_list->update_time;

	if (pldm_sensor_list->pdr_numeric_sensor->update_interval * 1000  > diff_time) {
		return false;
	}

	return true;
}

int get_pldm_sensor_info_via_sensor_id(uint16_t sensor_id, float *resolution, float *offset, int8_t *unit_modifier, int *cache, uint8_t *sensor_operational_state)
{
	int t_id = 0, s_id = 0, pldm_sensor_count = 0;

	for (t_id = 0; t_id < MAX_SENSOR_THREAD_ID; t_id++) {
		pldm_sensor_count = plat_get_pldm_sensor_count(t_id);
		for (s_id = 0; s_id < pldm_sensor_count; s_id++) {
			if (sensor_id == pldm_sensor_list[t_id][s_id].pdr_numeric_sensor->sensor_id) {
				// Get from numeric sensor PDR
				*resolution = pldm_sensor_list[t_id][s_id].pdr_numeric_sensor->resolution;
				*offset = pldm_sensor_list[t_id][s_id].pdr_numeric_sensor->offset;
				*unit_modifier = pldm_sensor_list[t_id][s_id].pdr_numeric_sensor->unit_modifier;
				// Get from sensor config
				*cache = pldm_sensor_list[t_id][s_id].pldm_sensor_cfg.cache;
				*sensor_operational_state = pldm_sensor_list[t_id][s_id].pldm_sensor_cfg.cache_status;
				return 0;
			}
		}
	}

	return -1;
}

uint8_t get_pldm_sensor_reading_from_cache(uint16_t sensor_id, int *reading, uint8_t *sensor_operational_state)
{
	float sensor_reading = 0, decimal = 0, resolution = 0, offset = 0;
	int cache_reading = 0;
	int8_t unit_modifier = 0;
	int16_t integer = 0;
	uint8_t *sensor_reading_byte;

	if (get_pldm_sensor_info_via_sensor_id(sensor_id, &resolution, &offset, &unit_modifier, &cache_reading, sensor_operational_state) != 0) {
		// Couldn't find sensor id in pldm_sensor_list
		return PLDM_PLATFORM_INVALID_SENSOR_ID;
	}

	if (resolution == 0) {
		// The value of resolution couldn't be 0
		return PLDM_ERROR_INVALID_DATA;
	}

	// Convert two byte integer, two byte decimal sensor format to float
	sensor_reading_byte = malloc(sizeof(int));
	memcpy (sensor_reading_byte, &cache_reading, sizeof(int));
	integer = sensor_reading_byte[0] | sensor_reading_byte[1] << 8;
    decimal = (float)(sensor_reading_byte[2] | sensor_reading_byte[3] << 8)/1000;
	free(sensor_reading_byte);

	if (integer >= 0) {
      sensor_reading = (float)integer + decimal;
	} else {
      sensor_reading = (float)integer - decimal;
	}

	// Y = converted reading in Units in BMC
	// X = sensor reading report to BMC
	// Y = (X * resolution + offset ) * power (10, unit_modifier)
	// X = (Y * power (10, -1 * unit_modifier) - offset ) / resolution
	*reading = (int)((sensor_reading * power(10, -1 * unit_modifier) - offset ) / resolution);

	return PLDM_SUCCESS;
}

void get_pldm_sensor_reading(pldm_sensor_info *pldm_sensor_list, int pldm_sensor_count, int thread_id, int sensor_num)
{
	CHECK_NULL_ARG(pldm_sensor_list);

	int reading = 0;
	uint8_t status = SENSOR_UNSPECIFIED_ERROR;

	if (pldm_sensor_list->pldm_sensor_cfg.access_checker(sensor_num) != true) {
		pldm_sensor_list->pldm_sensor_cfg.cache_status = PLDM_SENSOR_UNAVAILABLE;
		return;
	}

	if (pldm_sensor_list->pldm_sensor_cfg.pre_sensor_read_hook) {
		if (!pldm_sensor_list->pldm_sensor_cfg.pre_sensor_read_hook(&pldm_sensor_list->pldm_sensor_cfg, pldm_sensor_list->pldm_sensor_cfg.pre_sensor_read_args)) {
			LOG_ERR("Failed to pre read sensor_num 0x%x of thread %d", sensor_num, thread_id);
			pldm_sensor_list->pldm_sensor_cfg.cache_status = PLDM_SENSOR_FAILED;
			pldm_sensor_list->update_time = k_uptime_get_32();
			return;
		}
	}

	// TODO: Check device ready

	if (pldm_sensor_list->pldm_sensor_cfg.read) {
		status = pldm_sensor_list->pldm_sensor_cfg.read(&pldm_sensor_list->pldm_sensor_cfg, &reading);
		if ((status != SENSOR_READ_SUCCESS) && (status != SENSOR_READ_ACUR_SUCCESS)) {
			LOG_ERR("Failed to read sensor_num 0x%x of thread %d", sensor_num, thread_id);
			pldm_sensor_list->pldm_sensor_cfg.cache_status = PLDM_SENSOR_FAILED;
			pldm_sensor_list->update_time = k_uptime_get_32();
			return;
		}
	}

	if (pldm_sensor_list->pldm_sensor_cfg.post_sensor_read_hook) {
		if (!pldm_sensor_list->pldm_sensor_cfg.post_sensor_read_hook(&pldm_sensor_list->pldm_sensor_cfg, pldm_sensor_list->pldm_sensor_cfg.post_sensor_read_args, &reading)) {
			LOG_ERR("Failed to post read sensor_num 0x%x of thread %d", sensor_num, thread_id);
			pldm_sensor_list->pldm_sensor_cfg.cache_status = PLDM_SENSOR_FAILED;
			pldm_sensor_list->update_time = k_uptime_get_32();
			return;
		}
	}

	pldm_sensor_list->pldm_sensor_cfg.cache_status = PLDM_SENSOR_ENABLED;
	pldm_sensor_list->update_time = k_uptime_get_32();
	pldm_sensor_list->pldm_sensor_cfg.cache = reading;

	LOG_INF("thread_id%d sensor_num0x%x sensor_id0x%x val0x%x", thread_id, sensor_num, pldm_sensor_list->pdr_numeric_sensor->sensor_id, reading);
}

void pldm_sensor_polling_handler(void *arug0, void *arug1, void *arug2)
{
	ARG_UNUSED(arug1);
	ARG_UNUSED(arug2);

	int ret = 0, sensor_num = 0;
	int thread_id = (int) arug0;
	int pldm_sensor_count = 0;

	pldm_sensor_count = plat_get_pldm_sensor_count(thread_id);
	if (pldm_sensor_count <= 0) {
		LOG_ERR("Failed to get PLDM sensor count(%d) of thread%d", pldm_sensor_count, thread_id);
		return;
	}

	pldm_sensor_list[thread_id] = (pldm_sensor_info *)malloc(pldm_sensor_count * sizeof(pldm_sensor_info));
	if (pldm_sensor_list[thread_id] == NULL) {
		LOG_ERR("Failed to allocate memory for thread%d pldm_sensor_list", thread_id);
		return;
	}
	ret = plat_load_pldm_sensor(thread_id, pldm_sensor_list[thread_id]);
	if (ret < 0) {
		LOG_ERR("Failed to load PLDM sensor list of thread%d, ret%d", thread_id, ret);
		return;
	}

	uint16_t current_device = 0;
	for (sensor_num = 0; sensor_num < pldm_sensor_count; sensor_num++) {
		current_device = pldm_sensor_list[thread_id][sensor_num].pldm_sensor_cfg.type;
		ret = sensor_drive_tbl[current_device].init(&pldm_sensor_list[thread_id][sensor_num].pldm_sensor_cfg);
		if (ret < 0) {
			LOG_ERR("Failed to init device0x%x from thread%d", current_device, thread_id);
			pldm_sensor_list[thread_id][sensor_num].pldm_sensor_cfg.cache_status = PLDM_SENSOR_FAILED;
			continue;
		}
		pldm_sensor_list[thread_id][sensor_num].pdr_numeric_sensor->sensor_init = PDR_SENSOR_ENABLE;
	}

	while(1)
	{
		for (sensor_num = 0; sensor_num < pldm_sensor_count; sensor_num++) {
			if (pldm_sensor_list[thread_id][sensor_num].pdr_numeric_sensor->sensor_init != PDR_SENSOR_ENABLE) {
				pldm_sensor_list[thread_id][sensor_num].pldm_sensor_cfg.cache_status = PLDM_SENSOR_DISABLED;
				LOG_INF("sensor_init 0x%x", pldm_sensor_list[thread_id][sensor_num].pdr_numeric_sensor->sensor_init);
				continue;
			}

			if (!is_interval_ready(pldm_sensor_list[thread_id])) {
				continue;
			}

			get_pldm_sensor_reading(&pldm_sensor_list[thread_id][sensor_num], pldm_sensor_count, thread_id, sensor_num);
		}

		k_msleep(PLDM_SENSOR_POLL_TIME_MS);
	}

}

void pldm_sensor_poll_thread_init()
{
	int i = 0;

	for (i = 0; i < MAX_SENSOR_THREAD_ID; i++) {
		LOG_INF("index%d %s", pldm_sensor_thread_list->thread_id, pldm_sensor_thread_list->thread_name);

		pldm_sensor_polling_tid[i] = k_thread_create(&pldm_sensor_polling_thread[i], pldm_sensor_poll_stacks[i],
				K_THREAD_STACK_SIZEOF(pldm_sensor_poll_stacks[i]), pldm_sensor_polling_handler, (void*) pldm_sensor_thread_list->thread_id,
				NULL, NULL, CONFIG_MAIN_THREAD_PRIORITY, 0, K_NO_WAIT);
		k_thread_name_set(&pldm_sensor_polling_thread[i], pldm_sensor_thread_list->thread_name);

		if (pldm_sensor_polling_tid[i] == NULL) {
			LOG_ERR("Failed to create %s to monitor sensor", pldm_sensor_thread_list->thread_name);
		}
	}

	return;
}

void pldm_sensor_monitor_init()
{
	pldm_sensor_thread_list = plat_load_pldm_sensor_thread(pldm_sensor_thread_list);
	if (!pldm_sensor_thread_list) {
		LOG_ERR("Failed to load PLDM sensor thread list");
		return;
	}

	pldm_sensor_poll_thread_init();

	return;
}
