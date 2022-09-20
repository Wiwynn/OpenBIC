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

#ifndef LATTICE_H
#define LATTICE_H

#include <stdint.h>

#define LATTICE_REG_GET_USERCODE 0x00000030
#define LATTICE_RES_GET_USERCODE_LEN 4

typedef struct _lattice_dev_cfg {
	uint8_t i2c_bus;
	uint8_t address;
} lattice_dev_cfg;

int lattice_read_usercode(lattice_dev_cfg dev_cfg, uint8_t *usercode);
int lattice_write_register(lattice_dev_cfg dev_cfg, uint8_t *write_data, uint8_t write_len);
int lattice_read_register(lattice_dev_cfg dev_cfg, uint8_t *write_data, uint8_t write_len,
			  uint8_t *read_data, uint8_t read_len);

#endif
