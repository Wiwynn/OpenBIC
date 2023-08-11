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

#define ADDR_TMP75_INLET (0x92 >> 1)
#define ADDR_TMP75_OUTLET (0x98 >> 1)
#define ADDR_TMP75_FIO (0x90 >> 1)
#define ADDR_SSD_BOOT (0xD4 >> 1)
#define ADDR_SSD_DATA (0xD4 >> 1)
#define ADDR_CPU0 (0X4F >> 1)
#define ADDR_SOC (0X4F >> 1)
#define ADDR_CPU1 (0X4E >> 1)
#define ADDR_PVDDIO (0X4E >> 1)
#define ADDR_PVDD11 (0X4B >> 1)

#define OFFSET_TMP75_TEMP 0x00
#define OFFSET_NVME_TEMP 0x00

#define SENSOR_NUM_INLET_TEMP 0x01
#define SENSOR_NUM_OUTLET_TEMP 0x02
#define SENSOR_NUM_FIO_TEMP 0x03
#define SENSOR_NUM_CPU_TEMP 0x04
#define SENSOR_NUM_DIMM_A_TEMP 0x05
#define SENSOR_NUM_DIMM_B_TEMP 0x06
#define SENSOR_NUM_DIMM_C_TEMP 0x07
#define SENSOR_NUM_DIMM_D_TEMP 0x08
#define SENSOR_NUM_DIMM_E_TEMP 0x09
#define SENSOR_NUM_DIMM_F_TEMP 0x0A
#define SENSOR_NUM_DIMM_G_TEMP 0x0B
#define SENSOR_NUM_DIMM_H_TEMP 0x0C
#define SENSOR_NUM_DIMM_I_TEMP 0x0D
#define SENSOR_NUM_DIMM_J_TEMP 0x0E
#define SENSOR_NUM_DIMM_K_TEMP 0x0F
#define SENSOR_NUM_DIMM_L_TEMP 0x10
#define SENSOR_NUM_SSD_BOOT_TEMP 0x11
#define SENSOR_NUM_SSD_DATA_TEMP 0x12
#define SENSOR_NUM_CPU0_VR_TEMP 0x13
#define SENSOR_NUM_SOC_VR_TEMP 0x14
#define SENSOR_NUM_CPU1_VR_TEMP 0x15
#define SENSOR_NUM_PVDDIO_VR_TEMP 0x16
#define SENSOR_NUM_PVDD11_VR_TEMP 0x17

#define SENSOR_NUM_P12V_STBY_VOLT 0x18
#define SENSOR_NUM_PVDD18_S5_VOLT 0x19
#define SENSOR_NUM_P3V3_STBY_VOLT 0x1A
#define SENSOR_NUM_P3V_BAT_VOLT 0x1B
#define SENSOR_NUM_PVDD33_S5_VOLT 0x1C
#define SENSOR_NUM_P5V_STBY_VOLT 0x1D
#define SENSOR_NUM_P12V_DIMM_0_VOLT 0x1E
#define SENSOR_NUM_P12V_DIMM_1_VOLT 0x1F
#define SENSOR_NUM_P1V2_STBY_VOLT 0x20
#define SENSOR_NUM_P1V8_STBY_VOLT 0x21
#define SENSOR_NUM_SLOT_ADC_DETECT_VOLT 0x22
#define SENSOR_NUM_ADC_SIDECAR_DETECT_VOLT 0x23

#define SENSOR_NUM_CPU0_VR_CURR 0x24
#define SENSOR_NUM_SOC_VR_CURR 0x25
#define SENSOR_NUM_CPU1_VR_CURR 0x26
#define SENSOR_NUM_PVDDIO_VR_CURR 0x27
#define SENSOR_NUM_PVDD11_VR_CURR 0x28

#define SENSOR_NUM_CPU0_VR_PWR 0x29
#define SENSOR_NUM_SOC_VR_PWR 0x2A
#define SENSOR_NUM_CPU1_VR_PWR 0x2B
#define SENSOR_NUM_PVDDIO_VR_PWR 0x2C
#define SENSOR_NUM_PVDD11_VR_PWR 0x2D
#define SENSOR_NUM_CPU_PWR 0x2E
#define SENSOR_NUM_DIMM_A_PWR 0x2F
#define SENSOR_NUM_DIMM_B_PWR 0x30
#define SENSOR_NUM_DIMM_C_PWR 0x31
#define SENSOR_NUM_DIMM_D_PWR 0x32
#define SENSOR_NUM_DIMM_E_PWR 0x33
#define SENSOR_NUM_DIMM_F_PWR 0x34
#define SENSOR_NUM_DIMM_G_PWR 0x35
#define SENSOR_NUM_DIMM_H_PWR 0x36
#define SENSOR_NUM_DIMM_I_PWR 0x37
#define SENSOR_NUM_DIMM_J_PWR 0x38
#define SENSOR_NUM_DIMM_K_PWR 0x39
#define SENSOR_NUM_DIMM_L_PWR 0x3A

#define POLL_TIME_BAT3V 3600 // sec

#endif
