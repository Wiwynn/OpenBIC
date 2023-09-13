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
#include <logging/log.h>
#include "plat_pldm_sensor.h"

LOG_MODULE_REGISTER(plat_pdr_table);

uint16_t plat_get_pdr_size()
{
	int total_size = 0, i = 0;

	for (i = 0; i < MAX_SENSOR_THREAD_ID; i++) {
		total_size += plat_get_pldm_sensor_count(i);
	}

	return total_size;
}
