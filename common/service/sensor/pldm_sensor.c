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

#include <zephyr.h>
#include <logging/log.h>
#include "libutil.h"
#include "plat_pldm_sensor.h"
#include "pldm_sensor.h"

LOG_MODULE_REGISTER(pldm_sensor);

static struct k_thread pldm_sensor_polling_thread[MAX_SENSOR_THREAD_ID];
static k_tid_t pldm_sensor_polling_tid[MAX_SENSOR_THREAD_ID];
K_THREAD_STACK_EXTERN(pldm_sensor_poll_stack);
K_THREAD_STACK_ARRAY_DEFINE(pldm_sensor_poll_stacks, MAX_SENSOR_THREAD_ID,
			    PLDM_SENSOR_POLL_STACK_SIZE);

pldm_sensor_thread *pldm_sensor_thread_list;
pldm_sensor_info *pldm_sensor_list[MAX_SENSOR_THREAD_ID];

__weak pldm_sensor_thread *plat_load_pldm_sensor_thread()
{
	return NULL;
}

__weak pldm_sensor_info *plat_load_pldm_sensor(int thread_id)
{
	return NULL;
}

__weak int plat_get_pldm_sensor_count(int thread_id)
{
	return -1;
}

bool is_interval_ready(pldm_sensor_info *pldm_sensor_list)
{
	CHECK_NULL_ARG_WITH_RETURN(pldm_sensor_list, false);

	uint32_t current_time = 0, diff_time = 0;

	current_time = k_uptime_get_32() / 1000;
	diff_time = current_time - pldm_sensor_list->update_time;

	if (pldm_sensor_list->pdr_numeric_sensor.update_interval > diff_time) {
		return false;
	}

	return true;
}

void get_pldm_sensor_reading(sensor_cfg *pldm_sensor_cfg, uint32_t *update_time,
			     int pldm_sensor_count, int thread_id, int sensor_num)
{
	CHECK_NULL_ARG(pldm_sensor_list);
	CHECK_NULL_ARG(update_time);

	int reading = 0;
	uint8_t status = SENSOR_UNSPECIFIED_ERROR;

	if (pldm_sensor_cfg->access_checker(sensor_num) != true) {
		pldm_sensor_cfg->cache_status = PLDM_SENSOR_UNAVAILABLE;
		return;
	}

	if (pldm_sensor_cfg->pre_sensor_read_hook) {
		if (!pldm_sensor_cfg->pre_sensor_read_hook(pldm_sensor_cfg,
							   pldm_sensor_cfg->pre_sensor_read_args)) {
			LOG_ERR("Failed to pre read sensor_num 0x%x of thread %d", sensor_num,
				thread_id);
			pldm_sensor_cfg->cache_status = PLDM_SENSOR_FAILED;
			*update_time = (k_uptime_get_32() / 1000);
			return;
		}
	}

	// TODO: Check device ready

	if (pldm_sensor_cfg->read) {
		status = pldm_sensor_cfg->read(pldm_sensor_cfg, &reading);
		if ((status != SENSOR_READ_SUCCESS) && (status != SENSOR_READ_ACUR_SUCCESS)) {
			LOG_ERR("Failed to read sensor_num 0x%x of thread %d", sensor_num,
				thread_id);
			pldm_sensor_cfg->cache_status = PLDM_SENSOR_FAILED;
			*update_time = (k_uptime_get_32() / 1000);
			return;
		}
	}

	if (pldm_sensor_cfg->post_sensor_read_hook) {
		if (!pldm_sensor_cfg->post_sensor_read_hook(
			    pldm_sensor_cfg, pldm_sensor_cfg->post_sensor_read_args, &reading)) {
			LOG_ERR("Failed to post read sensor_num 0x%x of thread %d", sensor_num,
				thread_id);
			pldm_sensor_cfg->cache_status = PLDM_SENSOR_FAILED;
			*update_time = (k_uptime_get_32() / 1000);
			return;
		}
	}

	pldm_sensor_cfg->cache_status = PLDM_SENSOR_ENABLED;
	*update_time = (k_uptime_get_32() / 1000);
	pldm_sensor_cfg->cache = reading;
}

void pldm_sensor_polling_handler(void *arug0, void *arug1, void *arug2)
{
	ARG_UNUSED(arug1);
	ARG_UNUSED(arug2);

	int ret = 0, sensor_num = 0;
	int thread_id = (int)arug0;
	int pldm_sensor_count = 0;

	pldm_sensor_count = plat_get_pldm_sensor_count(thread_id);
	if (pldm_sensor_count <= 0) {
		LOG_ERR("Failed to get PLDM sensor count(%d) of thread%d", pldm_sensor_count,
			thread_id);
		return;
	}

	pldm_sensor_list[thread_id] = plat_load_pldm_sensor(thread_id);
	if (pldm_sensor_list[thread_id] == NULL) {
		LOG_ERR("Failed to load PLDM sensor list of thread%d, ret%d", thread_id, ret);
		return;
	}

	for (sensor_num = 0; sensor_num < pldm_sensor_count; sensor_num++) {
		ret = sensor_drive_tbl[pldm_sensor_list[thread_id][sensor_num].pldm_sensor_cfg.type]
			      .init(&pldm_sensor_list[thread_id][sensor_num].pldm_sensor_cfg);
		if (ret < 0) {
			LOG_ERR("Failed to init device0x%x from thread%d",
				pldm_sensor_list[thread_id][sensor_num].pldm_sensor_cfg.type,
				thread_id);
			pldm_sensor_list[thread_id][sensor_num].pldm_sensor_cfg.cache_status =
				PLDM_SENSOR_FAILED;
			continue;
		}
		pldm_sensor_list[thread_id][sensor_num].pdr_numeric_sensor.sensor_init =
			PDR_SENSOR_ENABLE;
	}

	while (1) {
		for (sensor_num = 0; sensor_num < pldm_sensor_count; sensor_num++) {
			if (pldm_sensor_list[thread_id][sensor_num].pdr_numeric_sensor.sensor_init !=
			    PDR_SENSOR_ENABLE) {
				pldm_sensor_list[thread_id][sensor_num]
					.pldm_sensor_cfg.cache_status = PLDM_SENSOR_DISABLED;
				continue;
			}

			if (!is_interval_ready(&pldm_sensor_list[thread_id][sensor_num])) {
				continue;
			}

			get_pldm_sensor_reading(
				&pldm_sensor_list[thread_id][sensor_num].pldm_sensor_cfg,
				&pldm_sensor_list[thread_id][sensor_num].update_time,
				pldm_sensor_count, thread_id, sensor_num);
		}

		k_msleep(PLDM_SENSOR_POLL_TIME_DEFAULT_MS);
	}
}

void pldm_sensor_poll_thread_init()
{
	int i = 0;

	LOG_INF("Init PLDM sensor monitor thread");

	for (i = 0; i < MAX_SENSOR_THREAD_ID; i++) {
		pldm_sensor_polling_tid[i] =
			k_thread_create(&pldm_sensor_polling_thread[i], pldm_sensor_poll_stacks[i],
					K_THREAD_STACK_SIZEOF(pldm_sensor_poll_stacks[i]),
					pldm_sensor_polling_handler, (void *)i, NULL, NULL,
					CONFIG_MAIN_THREAD_PRIORITY, 0, K_NO_WAIT);
		k_thread_name_set(&pldm_sensor_polling_thread[i],
				  pldm_sensor_thread_list[i].thread_name);

		if (pldm_sensor_polling_tid[i] == NULL) {
			LOG_ERR("Failed to create %s to monitor sensor",
				pldm_sensor_thread_list[i].thread_name);
		}
	}

	return;
}

void pldm_sensor_monitor_init()
{

	LOG_INF("Init PDR table");
	uint16_t pdr_size = plat_get_pdr_size();
	if (pdr_size != 0) {
		pdr_init();
	} else {
		LOG_ERR("Platform PDR table not configured");
	}

	pldm_sensor_thread_list = plat_load_pldm_sensor_thread(pldm_sensor_thread_list);
	if (!pldm_sensor_thread_list) {
		LOG_ERR("Failed to load PLDM sensor thread list");
		return;
	}

	pldm_sensor_poll_thread_init();

	return;
}
