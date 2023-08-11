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

#include <stdio.h>
#include <string.h>
#include <logging/log.h>

#include "plat_hook.h"
#include "plat_sensor_table.h"

LOG_MODULE_REGISTER(plat_hook);

/**************************************************************************************************
 * INIT ARGS
**************************************************************************************************/
// ADC may show abnormal value because of AST1030's bug. Need to define upper/lower bound.
// If BIC reads ADC's value that is out of range, it will read it again.
adc_asd_init_arg ast_adc_init_args[] = {
	[0] = { 
		.is_init = false,
		.deglitch[0] = { .deglitch_en = false, },
		.deglitch[1] = { .deglitch_en = false, },
		.deglitch[2] = { .deglitch_en = false, },
		.deglitch[4] = { .deglitch_en = false, },
		.deglitch[5] = { .deglitch_en = false, },
		.deglitch[6] = { .deglitch_en = false, },
		.deglitch[7] = { .deglitch_en = false, },
	},
	[1] = {
		.is_init = false,
		.deglitch[0] = { .deglitch_en = false, },
		.deglitch[1] = { .deglitch_en = false, },
		.deglitch[3] = { .deglitch_en = false, },
		.deglitch[5] = { .deglitch_en = false, },
		.deglitch[7] = { .deglitch_en = false, },
	}
};

/**************************************************************************************************
 *  PRE-HOOK/POST-HOOK ARGS
 **************************************************************************************************/
vr_pre_proc_arg vr_pre_read_args[] = {
	[0] = { 0x0 },
	[1] = { 0x1 },
};

/**************************************************************************************************
 *  PRE-HOOK/POST-HOOK FUNC
 **************************************************************************************************/
bool pre_vr_read(sensor_cfg *cfg, void *args)
{
	CHECK_NULL_ARG_WITH_RETURN(cfg, false);
	CHECK_NULL_ARG_WITH_RETURN(args, false);

	vr_pre_proc_arg *pre_proc_args = (vr_pre_proc_arg *)args;
	uint8_t retry = 5;
	I2C_MSG msg;

	/* set page */
	msg.bus = cfg->port;
	msg.target_addr = cfg->target_addr;
	msg.tx_len = 2;
	msg.data[0] = 0x00;
	msg.data[1] = pre_proc_args->vr_page;
	if (i2c_master_write(&msg, retry)) {
		LOG_ERR("Failed to set VR page, sensor_num 0x%x", cfg->num);
		return false;
	}
	return true;
}
