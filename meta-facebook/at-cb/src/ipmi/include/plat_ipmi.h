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

#ifndef PLAT_IPMI_H
#define PLAT_IPMI_H

#include <stdbool.h>
#include <stdint.h>

#define VR_MFR_FW_COMMAND_DATA 0xFD
#define VR_MFR_FW_COMMAND 0xFE
#define VR_FW_VERSION_LEN 4
#define VR_MFR_FW_COMMAND_DATA_LEN 4
#define VR_GET_FIRMWARE_VERSION_CMD 0x01

#define BIC_VERSION_COUNT 7

enum CB_FIRMWARE_COMPONENT {
	CB_COMPNT_BIC,
	CB_COMPNT_CPLD,
	CB_COMPNT_PEX0,
	CB_COMPNT_PEX1,
	CB_COMPNT_XDPE15284,
	CB_COMPNT_MAX,
};

#endif
