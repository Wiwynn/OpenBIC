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
/* This h file is only for build test*/
#ifndef PLDM_SENSOR_H
#define PLDM_SENSOR_H

#include "sensor.h"
#include "pdr.h"

typedef struct pldm_sensor_info {
	PDR_numeric_sensor pdr_numeric_sensor;
	uint32_t update_time;
	sensor_cfg pldm_sensor_cfg;
} pldm_sensor_info;
pldm_sensor_info *pldm_sensor_list[3];

typedef struct _PDR_sensor_auxiliary_names {
	PDR_common_header pdr_common_header;
	uint16_t terminus_handle;
	uint16_t sensor_id;
	uint8_t sensor_count;
	uint8_t nameStringCount;
	char nameLanguageTag[3];
	char sensorName[40];
} PDR_sensor_auxiliary_names;
PDR_sensor_auxiliary_names *aux_sensor_name_table[1];

#endif
