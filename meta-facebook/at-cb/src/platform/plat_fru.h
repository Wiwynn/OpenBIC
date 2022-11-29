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

#ifndef PLAT_FRU_H
#define PLAT_FRU_H

#include "plat_i2c.h"
#include "i2c-mux-pca9548a.h"

enum {
	CB_FRU_ID,
	ACCL_1_FRU_ID,
	ACCL_2_FRU_ID,
	ACCL_3_FRU_ID,
	ACCL_4_FRU_ID,
	ACCL_5_FRU_ID,
	ACCL_6_FRU_ID,
	ACCL_7_FRU_ID,
	ACCL_8_FRU_ID,
	ACCL_9_FRU_ID,
	ACCL_10_FRU_ID,
	ACCL_11_FRU_ID,
	ACCL_12_FRU_ID,
	// OTHER_FRU_ID,
	MAX_FRU_ID,
};

#define FRU_CFG_NUM MAX_FRU_ID

#define CB_FRU_PORT I2C_BUS2
#define CB_FRU_ADDR (0xAC >> 1)
#define ACCL_1_6_FRU_PORT I2C_BUS7
#define ACCL_7_12_FRU_PORT I2C_BUS8
#define ACCL_FRU_ADDR (0xAC >> 1)
#define ACCL_1_6_FRU_MUX_ADDR (0xE0 >> 1)
#define ACCL_7_12_FRU_MUX_ADDR (0xE8 >> 1)
#define ACCL_1_7_FRU_MUX_CHAN PCA9548A_CHANNEL_0
#define ACCL_2_8_FRU_MUX_CHAN PCA9548A_CHANNEL_1
#define ACCL_3_9_FRU_MUX_CHAN PCA9548A_CHANNEL_2
#define ACCL_4_10_FRU_MUX_CHAN PCA9548A_CHANNEL_3
#define ACCL_5_11_FRU_MUX_CHAN PCA9548A_CHANNEL_4
#define ACCL_6_12_FRU_MUX_CHAN PCA9548A_CHANNEL_5

#endif
