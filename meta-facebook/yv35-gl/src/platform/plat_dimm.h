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

#ifndef PLAT_DIMM_H
#define PLAT_DIMM_H

#include <stdint.h>
#include <stdbool.h>
#include "plat_i3c.h"

#define MAX_COUNT_DIMM 8
#define DIMM_INDEX_BYTE 5
#define DIMM_STATUS_BYTE 7
#define DIMM_INDEX_MIN 0
#define DIMM_INDEX_MAX 7
#define DIMM_PRESENT 0x1

#define DIMM_I3C_MUX_CONTROL_OFFSET 0x0B

#define GET_DIMM_INFO_TIME_MS 1000
#define GET_DIMM_INFO_STACK_SIZE 2304

#define I3C_MUX_TO_CPU 0x0
#define I3C_MUX_TO_BIC 0x1
#define I3C_DIMM_MUX_MUTEX_TIMEOUT_MS 1000

#define I3C_HUB_TO_DIMMABCD 0x7F
#define I3C_HUB_TO_DIMMEFGH 0xBF

#define MAX_LEN_I3C_GET_PMIC_PWR 1

enum DIMM_ID {
	DIMM_ID_A = 0,
	DIMM_ID_B,
	DIMM_ID_C,
	DIMM_ID_D,
	DIMM_ID_E,
	DIMM_ID_F,
	DIMM_ID_G,
	DIMM_ID_H,
	DIMM_ID_UNKNOWN = 0xff,
};

enum I3C_PMIC_ADDR {
	PMIC_A_E_ADDR = 0x48,
	PMIC_B_F_ADDR = 0x4a,
	PMIC_C_G_ADDR = 0x4c,
	PMIC_D_H_ADDR = 0x4e,
};

typedef struct dimm_info {
	bool is_present;
	uint8_t pmic_pwr_data[MAX_LEN_I3C_GET_PMIC_PWR];
} dimm_info;

extern struct k_mutex i3c_dimm_mux_mutex;

void start_get_dimm_info_thread();
void get_dimm_info_handler();
bool is_dimm_prsnt_inited();
void init_i3c_dimm_prsnt_status();
bool get_dimm_presence_status(uint8_t dimm_id);
void set_dimm_presence_status(uint8_t index, uint8_t status);
uint8_t sensor_num_map_dimm_id(uint8_t sensor_num);
bool switch_i3c_dimm_mux(uint8_t i3c_mux_position);
bool is_i3c_mux_to_bic();
int all_brocast_ccc(I3C_MSG *i3c_msg);
void get_pmic_power_raw_data(int dimm_index, uint8_t *data);

#endif
