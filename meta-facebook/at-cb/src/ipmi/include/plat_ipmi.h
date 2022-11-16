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
#include "plat_gpio.h"

enum ACCESS_COMPNT {
	ACCL_1_COMPNT = 0x01,
	ACCL_2_COMPNT,
	ACCL_3_COMPNT,
	ACCL_4_COMPNT,
	ACCL_5_COMPNT,
	ACCL_6_COMPNT,
	ACCL_7_COMPNT,
	ACCL_8_COMPNT,
	ACCL_9_COMPNT,
	ACCL_10_COMPNT,
	ACCL_11_COMPNT,
	ACCL_12_COMPNT,
	PEX_0_COMPNT,
	PEX_1_COMPNT,
};

enum MUX_CONTROL_GPIO_NETNAME {
	MUX_0_CONTROL_PIN = USB2_MUX0_SEL,
	MUX_1_CONTROL_PIN = USB2_MUX1_SEL,
	MUX_2_CONTROL_PIN = ASD_MUX2_SEL,
	MUX_3_CONTROL_PIN = USB2_MUX3_SEL,
};

enum MUX_0_CONNECT_TARGET {
	MUX0_CONNECT_TO_FIO = GPIO_LOW,
	MUX0_CONNECT_TO_MUX3 = GPIO_HIGH,
};

enum MUX_1_CONNECT_TARGET {
	MUX1_CONNECT_TO_MUX3 = GPIO_LOW,
	MUX1_CONNECT_TO_MUX2 = GPIO_HIGH,
};

enum MUX_2_CONNECT_TARGET {
	MUX2_CONNECT_TO_BIC = GPIO_LOW,
	MUX2_CONNECT_TO_HUB0 = GPIO_HIGH,
};

enum MUX_3_CONNECT_TARGET {
	MUX3_CONNECT_TO_MUX0 = GPIO_LOW,
	MUX3_CONNECT_TO_MUX1 = GPIO_HIGH,
};

#endif
