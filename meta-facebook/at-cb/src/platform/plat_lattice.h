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

#ifndef PLAT_LATTICE_H
#define PLAT_LATTICE_H

#include "lattice.h"
#include "hal_i2c.h"
#include "plat_i2c.h"

#define CPLD_I2C_BUS I2C_BUS3
#define CPLD_FW_UPDATE_I2C_BUS I2C_BUS5
#define CPLD_ADDRESS 0x50
#define CPLD_FW_UPDATE_ADDRESS 0x40

lattice_dev_cfg *pal_lattice_get_dev_config();
lattice_dev_cfg *pal_lattice_get_fw_update_dev_config();

#endif
