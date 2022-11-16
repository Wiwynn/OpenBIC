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

#include "plat_ipmi.h"

#include <stdio.h>
#include <stdlib.h>
#include <logging/log.h>
#include "ipmi.h"
#include "libutil.h"

LOG_MODULE_DECLARE(ipmi);

void OEM_1S_PRE_ACCESS_COMPNT_SETTING(ipmi_msg *msg)
{
	CHECK_NULL_ARG(msg);

	uint8_t access_compnt = msg->data[0];
	switch (access_compnt) {
	case ACCL_1_COMPNT:
	case ACCL_2_COMPNT:
	case ACCL_3_COMPNT:
	case ACCL_4_COMPNT:
	case ACCL_5_COMPNT:
	case ACCL_6_COMPNT:
	case ACCL_7_COMPNT:
	case ACCL_8_COMPNT:
	case ACCL_9_COMPNT:
	case ACCL_10_COMPNT:
	case ACCL_11_COMPNT:
	case ACCL_12_COMPNT:
	case PEX_0_COMPNT:
	case PEX_1_COMPNT:
		gpio_set(MUX_0_CONTROL_PIN, MUX0_CONNECT_TO_MUX3);
		gpio_set(MUX_1_CONTROL_PIN, MUX1_CONNECT_TO_MUX2);
		gpio_set(MUX_2_CONTROL_PIN, MUX2_CONNECT_TO_HUB0);
		gpio_set(MUX_3_CONTROL_PIN, MUX3_CONNECT_TO_MUX0);
		break;
	default:
		LOG_ERR("Invalid component: 0x%x\n", access_compnt);
		msg->completion_code = CC_PARAM_OUT_OF_RANGE;
		return;
	}

	msg->completion_code = CC_SUCCESS;
	return;
}
