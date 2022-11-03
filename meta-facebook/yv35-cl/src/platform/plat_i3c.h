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

#ifndef PLAT_I3C_H
#define PLAT_I3C_H

#include "hal_i3c.h"

#define I3C_BUS1 0		// i2c-7 dts hv-i3c-1
#define I3C_BUS4 3		// i3c-4

enum I3C_PMIC_ADDR
{
	PMIC_A0_A4_ADDR = 0x48,
	PMIC_A2_A6_ADDR = 0x4c,
	PMIC_A3_A7_ADDR = 0x4e,
};

#endif
