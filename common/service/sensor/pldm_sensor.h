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

// TODO: pldm_sensor要放在sensor的資料夾底下還是創一個新的pldm_sensor資料夾

#ifndef PLDM_SENSOR_H
#define PLDM_SENSOR_H

#include <stdlib.h>
#include "sensor.h"
#include "pdr.h"
#include "pldm_base.h"

#define PLDM_SENSOR_POLL_STACK_SIZE 3056

#define PLDM_SENSOR_POLL_TIME_MS 1000

enum pldm_sensor_operational_state {
	PLDM_SENSOR_ENABLED,
	PLDM_SENSOR_DISABLED,
	PLDM_SENSOR_UNAVAILABLE,
	PLDM_SENSOR_STATUSUNKOWN,
	PLDM_SENSOR_FAILED,
	PLDM_SENSOR_INITIALIZING,
	PLDM_SENSOR_SHUTTINGDOWN,
	PLDM_SENSOR_INTEST
};

typedef struct pldm_sensor_info {
	PDR_numeric_sensor *pdr_numeric_sensor;
	uint32_t update_time;
	sensor_cfg pldm_sensor_cfg;
} pldm_sensor_info;

typedef struct pldm_sensor_thread {
	int thread_id;
	char *thread_name;
} pldm_sensor_thread;

void pldm_sensor_monitor_init();
void pldm_sensor_polling_handler(void *arug0, void *arug1, void *arug2);
pldm_sensor_thread * plat_load_pldm_sensor_thread();
int plat_load_pldm_sensor(int thread_id, pldm_sensor_info *pldm_sensor_list);
int plat_get_pldm_sensor_count(int thread_id);
bool is_interval_ready(pldm_sensor_info *pldm_sensor_list);
uint8_t get_pldm_sensor_reading_from_cache(uint16_t sensor_id, int *reading, uint8_t *sensor_operational_state);

#endif