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

#ifndef PLAT_PDR_TABLE_H
#define PLAT_PDR_TABLE_H

#include <stdint.h>
#include "pdr.h"

#define MAX_SENSOR_SIZE 60

#define UPDATE_INTERVAL_1S 1
#define UPDATE_INTERVAL_3S 3

enum PDR_SENSOR_INIT_VAL
{
	PDR_SENSOR_NO_INIT = 0,
	PDR_SENSOR_USEINIT_PDR,
	PDR_SENSOR_ENABLE,
	PDR_SENSOR_DISABLE,
};

extern PDR_numeric_sensor pdr_numeric_adc_table[];
extern PDR_numeric_sensor pdr_numeric_vr_table[];


uint16_t plat_get_pdr_size();
void plat_load_pdr_table(PDR_numeric_sensor *numeric_sensor_table);

#endif
