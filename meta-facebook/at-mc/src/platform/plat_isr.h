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

#ifndef PLAT_FUNC_H
#define PLAT_FUNC_H

#include <stdint.h>

#define CXL_IOEXP_U15_ADDR (0x44 >> 1)
#define CXL_IOEXP_U17_ADDR (0x48 >> 1)
#define CXL_IOEXP_MUX_CHANNEL 0x08

void cxl_ioexp_alert0();
void cxl_ioexp_alert1();
void cxl_ioexp_alert2();
void cxl_ioexp_alert3();
void cxl_ioexp_alert4();
void cxl_ioexp_alert5();
void cxl_ioexp_alert6();
void cxl_ioexp_alert7();

#endif
