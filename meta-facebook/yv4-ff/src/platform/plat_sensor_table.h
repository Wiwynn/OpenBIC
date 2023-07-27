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

#ifndef PLAT_SENSOR_TABLE_H
#define PLAT_SENSOR_TABLE_H

#include <stdint.h>
#include "sensor.h"

#define ADDR_TMP75 0x49
#define ADDR_TMP461 0x4C
#define ADDR_PVDDQ_AB 0x76
#define ADDR_P0V85_ASIC 0x76
#define ADDR_PVDDQ_CD 0x72
#define ADDR_P0V8_ASIC 0x72
#define ADDR_INA233_P12V 0x45
#define ADDR_INA233_P3V3 0x40

/* define sensors offset */
#define OFFSET_TMP75_TEMP 0x00
#define OFFSET_TMP461_TEMP 0x01

// Threshold sensor number definition

#define SENSOR_NUM_INLET_TEMP 0x50
#define SENSOR_NUM_CXL_TEMP 0x51

#define SENSOR_NUM_INA233_P12V_STBY_VOLT 0x52
#define SENSOR_NUM_ADC_P3V3_STBY_VOLT 0x53
#define SENSOR_NUM_ADC_P1V2_STBY_VOLT 0x54
#define SENSOR_NUM_ADC_P1V2_ASIC_VOLT 0x55
#define SENSOR_NUM_ADC_P1V8_ASIC_VOLT 0x56
#define SENSOR_NUM_ADC_P0V75_ASIC_VOLT 0x57
#define SENSOR_NUM_ADC_PVPP_AB_VOLT 0x58
#define SENSOR_NUM_ADC_PVPP_CD_VOLT 0x59
#define SENSOR_NUM_ADC_PVTT_AB_VOLT 0x5A
#define SENSOR_NUM_ADC_PVTT_CD_VOLT 0x5B

#endif
