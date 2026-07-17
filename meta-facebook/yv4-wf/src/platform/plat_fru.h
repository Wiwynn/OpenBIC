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

#include "eeprom.h"
#include "fru.h"

enum {
	WF_FRU_ID,
	MAX_FRU_ID,
};

#define FRU_CFG_NUM MAX_FRU_ID

/* EEPROM on I2C bus 0, address 0x51 */
#define WF_FRU_PORT 0x00
#define WF_FRU_ADDR 0x51

#define WF_BOARD_PRODUCT_WITHOUT_ASIC "Wailua Falls without ASIC"

void dump_fru_raw(void);
bool check_board_product_name(const char *expected);
bool get_without_asic(void);

#endif
