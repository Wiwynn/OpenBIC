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

#ifndef PLAT_ISR_H
#define PLAT_ISR_H

#include "ipmi.h"

enum GET_SET_M2_OPTION {
	DEVICE_SET_POWER_OFF = 0x00,
	DEVICE_SET_POWER_ON = 0x01,
	DEVICE_GET_POWER_STATUS = 0x03,
};

#define DC_ON_5_SECOND 5
#define DC_OFF_10_SECOND 10
// The PMIC needs a total of 100ms from CAMP signal assertion to complete the write operation
#define READ_PMIC_CRITICAL_ERROR_MS 100
#define PROC_FAIL_START_DELAY_SECOND 10
#define CATERR_START_DELAY_SECOND 2
#define MB_THROTTLE_DELAY_US 4

#define CPLD_ADDR 0x21 // 7-bit address
#define CPLD_1OU_VPP_POWER_STATUS 0x11
#define MAX_1OU_M2_COUNT 4

void send_gpio_interrupt(uint8_t gpio_num);
int get_set_1ou_m2_power(ipmi_msg *msg, uint8_t device_id, uint8_t option);
void ISR_PLTRST();
void ISR_SLP3();
void ISR_DC_ON();
void ISR_BMC_PRDY();
void ISR_PWRGD_CPU();
void ISR_CATERR();
void ISR_DBP_PRSNT();
void ISR_SOC_THMALTRIP();
void ISR_SYS_THROTTLE();
void ISR_HSC_OC();
void ISR_CPU_MEMHOT();
void ISR_CPUVR_HOT();
void ISR_MB_THROTTLE();
void ISR_HSC_THROTTLE();
void ISR_FM_THROTTLE();
void ISR_RMCA();
void ISR_CPU_VPP_INT();

#endif
