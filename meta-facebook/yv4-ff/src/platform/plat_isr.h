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

#include <stdint.h>
#include "ipmi.h"

void ISR_MB_DC_STATUS_CHANGE();
void ISR_MB_PCIE_RST();
void ISR_P0V85_ASIC_POWER_FAULT();
void ISR_P0V8_ASIC_POWER_FAULT();
void ISR_P1V2_ASIC_POWER_FAULT();
void ISR_P1V8_ASIC_POWER_FAULT();

enum POWER_RAIL_FAIL {
	ASIC_P0V8_POWER_RAIL_FAIL = 0x0,
    ASIC_P1V8_POWER_RAIL_FAIL = 0x1,
    ASIC_P1V2_POWER_RAIL_FAIL = 0x2,
    ASIC_P0V85_POWER_RAIL_FAIL = 0x3,
};

#endif
