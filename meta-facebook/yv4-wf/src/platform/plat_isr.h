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

#include <kernel.h>
#include "ioexp_tca9555.h"

#ifndef PLAT_ISR_H
#define PLAT_ISR_H

#define CXL_READY_SECONDS 30
#define IOE_READY_MSEC 1000


void ISR_MB_DC_STAGUS_CHAGNE();
void ISR_MB_PCIE_RST();
void ISR_E1S_PWR_ON();
void ISR_PG_CARD_OK();

#endif
