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

#ifndef PLDM_SENSOR_H
#define PLDM_SENSOR_H

#include <stdlib.h>
#include "sensor.h"
#include "pdr.h"

#define PLDM_SENSOR_POLL_STACK_SIZE 3056

#define PLDM_SENSOR_POLL_TIME_DEFAULT_MS 1000

enum PLDM_SENSOR_STATUS {
	PLDM_SENSOR_ENABLED,
	PLDM_SENSOR_DISABLED,
	PLDM_SENSOR_UNAVAILABLE,
	PLDM_SENSOR_UNKNOWN,
	PLDM_SENSOR_FAILED,
	PLDM_SENSOR_INITIALIZING,
	PLDM_SENSOR_SHUTTING_DOWN,
	PLDM_SENSOR_IN_TEST,
};

typedef struct pldm_sensor_info {
	PDR_numeric_sensor pdr_numeric_sensor;
	uint32_t update_time;
	sensor_cfg pldm_sensor_cfg;
} pldm_sensor_info;

typedef struct pldm_sensor_thread {
	int thread_id;
	char *thread_name;
} pldm_sensor_thread;

void pldm_sensor_monitor_init();
void pldm_sensor_polling_handler(void *arug0, void *arug1, void *arug2);
void get_pldm_sensor_reading(sensor_cfg *pldm_sensor_cfg, uint32_t *update_time,
			     int pldm_sensor_count, int thread_id, int sensor_num);
pldm_sensor_thread *plat_load_pldm_sensor_thread();
pldm_sensor_info *plat_load_pldm_sensor(int thread_id);
int plat_get_pldm_sensor_count(int thread_id);
bool is_interval_ready(pldm_sensor_info *pldm_sensor_list);

#endif
