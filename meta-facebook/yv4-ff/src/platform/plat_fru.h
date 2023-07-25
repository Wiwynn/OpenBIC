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

#define FF_FRU_PORT I2C_BUS3
#define FF_FRU_ADDR (0xA8 >> 1)
#define FRU_CFG_NUM MAX_FRU_ID

enum {
    FF_FRU_ID,
    MAX_FRU_ID,
};

#endif
