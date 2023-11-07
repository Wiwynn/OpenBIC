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

#include "plat_i3c.h"

#define DIMM_SPD_A_G_ADDR (0xA0 >> 1)
#define DIMM_SPD_B_H_ADDR (0xA2 >> 1)
#define DIMM_SPD_C_I_ADDR (0xA4 >> 1)
#define DIMM_SPD_D_J_ADDR (0xA6 >> 1)
#define DIMM_SPD_E_K_ADDR (0xA8 >> 1)
#define DIMM_SPD_F_L_ADDR (0xAA >> 1)

#define DIMM_PMIC_A_G_ADDR 0x48
#define DIMM_PMIC_B_H_ADDR 0x49
#define DIMM_PMIC_C_I_ADDR 0x4A
#define DIMM_PMIC_D_J_ADDR 0x4B
#define DIMM_PMIC_E_K_ADDR 0x4C
#define DIMM_PMIC_F_L_ADDR 0x4D

#endif
