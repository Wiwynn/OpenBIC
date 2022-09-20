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

#include "plat_lattice.h"

#include "lattice.h"

lattice_dev_cfg cpld_cfg[2] = {
	[0] = { .i2c_bus = CPLD_I2C_BUS, .address = CPLD_ADDRESS },
	[1] = { .i2c_bus = CPLD_FW_UPDATE_I2C_BUS, .address = CPLD_FW_UPDATE_ADDRESS },
};

lattice_dev_cfg *pal_lattice_get_dev_config()
{
	return &cpld_cfg[0];
}

lattice_dev_cfg *pal_lattice_get_fw_update_dev_config()
{
	return &cpld_cfg[1];
}
