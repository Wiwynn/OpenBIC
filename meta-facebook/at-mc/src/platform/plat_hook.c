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
#include "libutil.h"
#include "sensor.h"
#include "pmbus.h"
#include "plat_hook.h"
#include "common_i2c_mux.h"
#include "i2c-mux-pca954x.h"
#include "i2c-mux-pca984x.h"
#include "plat_sensor_table.h"
#include "ltc2991.h"
#include "plat_i2c.h"
#include "plat_ipmi.h"
#include "plat_class.h"

LOG_MODULE_REGISTER(plat_hook);

/**************************************************************************************************
 * INIT ARGS
**************************************************************************************************/
mp5990_init_arg mp5990_init_args[] = {
	[0] = { .is_init = false,
		.iout_cal_gain = 0x0280,
		.iout_oc_fault_limit = 0x005F,
		.ocw_sc_ref = 0x05A0 },
};

adc_asd_init_arg adc_asd_init_args[] = { [0] = { .is_init = false } };

sq52205_init_arg sq52205_init_args[] = {
	[0] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.001,
	.config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b000,
		.reset_bit = 0b0,
	},
	},
	[1] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.001,
	.config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b000,
		.reset_bit = 0b0,
	},
	},
	[2] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.001,
	.config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b000,
		.reset_bit = 0b0,
	},
	},
	[3] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.001,
	.config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b000,
		.reset_bit = 0b0,
	},
	},
	[4] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.001,
	.config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b000,
		.reset_bit = 0b0,
	},
	},
	[5] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.001,
	.config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b000,
		.reset_bit = 0b0,
	},
	},
	[6] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.001,
	.config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b000,
		.reset_bit = 0b0,
	},
	},
	[7] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.001,
	.config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b000,
		.reset_bit = 0b0,
	},
	},
	[8] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.001,
	.config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b000,
		.reset_bit = 0b0,
	},
	},
	[9] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.001,
	.config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b000,
		.reset_bit = 0b0,
	},
	},
	[10] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.001,
	.config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b000,
		.reset_bit = 0b0,
	},
	},
	[11] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.001,
	.config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b000,
		.reset_bit = 0b0,
	},
	},
};

ina233_init_arg mc_ina233_init_args[] = {
	[0] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.001, .mfr_config_init = true,
	.mfr_config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b0100,
	},
	},
	[1] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.001, .mfr_config_init = true,
	.mfr_config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b0100,
	},
	},
	[2] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.001, .mfr_config_init = true,
	.mfr_config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b0100,
	},
	},
	[3] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.001, .mfr_config_init = true,
	.mfr_config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b0100,
	},
	},
	[4] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.001, .mfr_config_init = true,
	.mfr_config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b0100,
	},
	},
	[5] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.001, .mfr_config_init = true,
	.mfr_config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b0100,
	},
	},
	[6] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.001, .mfr_config_init = true,
	.mfr_config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b0100,
	},
	},
	[7] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.001, .mfr_config_init = true,
	.mfr_config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b0100,
	},
	},
	[8] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.001, .mfr_config_init = true,
	.mfr_config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b0100,
	},
	},
	[9] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.001, .mfr_config_init = true,
	.mfr_config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b0100,
	},
	},
	[10] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.001, .mfr_config_init = true,
	.mfr_config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b0100,
	},
	},
	[11] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.001, .mfr_config_init = true,
	.mfr_config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b0100,
	},
	},
};

ina233_init_arg ina233_init_args[] = {
	// JCN11
	[0] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.005, .mfr_config_init = true,
	.mfr_config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b0100,
	},
	},
	[1] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.005, .mfr_config_init = true,
	.mfr_config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b0100,
	},
	},
	// JCN12
	[2] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.005, .mfr_config_init = true,
	.mfr_config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b0100,
	},
	},
	[3] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.005, .mfr_config_init = true,
	.mfr_config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b0100,
	},
	},
	// JCN9
	[4] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.005, .mfr_config_init = true,
	.mfr_config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b0100,
	},
	},
	[5] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.005, .mfr_config_init = true,
	.mfr_config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b0100,
	},
	},
	// JCN10
	[6] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.005, .mfr_config_init = true,
	.mfr_config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b0100,
	},
	},
	[7] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.005, .mfr_config_init = true,
	.mfr_config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b0100,
	},
	},
	// JCN4
	[8] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.005, .mfr_config_init = true,
	.mfr_config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b0100,
	},
	},
	[9] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.005, .mfr_config_init = true,
	.mfr_config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b0100,
	},
	},
	// JCN3
	[10] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.005, .mfr_config_init = true,
	.mfr_config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b0100,
	},
	},
	[11] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.005, .mfr_config_init = true,
	.mfr_config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b0100,
	},
	},
	// JCN2
	[12] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.005, .mfr_config_init = true,
	.mfr_config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b0100,
	},
	},
	[13] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.005, .mfr_config_init = true,
	.mfr_config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b0100,
	},
	},
	// JCN1
	[14] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.005, .mfr_config_init = true,
	.mfr_config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b0100,
	},
	},
	[15] = { .is_init = false, .current_lsb = 0.001, .r_shunt = 0.005, .mfr_config_init = true,
	.mfr_config = {
		.operating_mode =0b111,
		.shunt_volt_time = 0b100,
		.bus_volt_time = 0b100,
		.aver_mode = 0b111, //set 1024 average times
		.rsvd = 0b0100,
	},
	},
};

ltc2991_init_arg ltc2991_init_args[] = {
	// JCN11
	[0] = { .is_init = false,
		.v1_v4_control_operation.value = 0,
		.v5_v8_control_operation.value = 0 },
	[1] = { .is_init = false,
		.v1_v4_control_operation.value = 0,
		.v5_v8_control_operation.value = 0 },
	// JCN12
	[2] = { .is_init = false,
		.v1_v4_control_operation.value = 0,
		.v5_v8_control_operation.value = 0 },
	[3] = { .is_init = false,
		.v1_v4_control_operation.value = 0,
		.v5_v8_control_operation.value = 0 },
	// JCN9
	[4] = { .is_init = false,
		.v1_v4_control_operation.value = 0,
		.v5_v8_control_operation.value = 0 },
	[5] = { .is_init = false,
		.v1_v4_control_operation.value = 0,
		.v5_v8_control_operation.value = 0 },
	// JCN10
	[6] = { .is_init = false,
		.v1_v4_control_operation.value = 0,
		.v5_v8_control_operation.value = 0 },
	[7] = { .is_init = false,
		.v1_v4_control_operation.value = 0,
		.v5_v8_control_operation.value = 0 },
	// JCN4
	[8] = { .is_init = false,
		.v1_v4_control_operation.value = 0,
		.v5_v8_control_operation.value = 0 },
	[9] = { .is_init = false,
		.v1_v4_control_operation.value = 0,
		.v5_v8_control_operation.value = 0 },
	// JCN3
	[10] = { .is_init = false,
		 .v1_v4_control_operation.value = 0,
		 .v5_v8_control_operation.value = 0 },
	[11] = { .is_init = false,
		 .v1_v4_control_operation.value = 0,
		 .v5_v8_control_operation.value = 0 },
	// JCN2
	[12] = { .is_init = false,
		 .v1_v4_control_operation.value = 0,
		 .v5_v8_control_operation.value = 0 },
	[13] = { .is_init = false,
		 .v1_v4_control_operation.value = 0,
		 .v5_v8_control_operation.value = 0 },
	// JCN1
	[14] = { .is_init = false,
		 .v1_v4_control_operation.value = 0,
		 .v5_v8_control_operation.value = 0 },
	[15] = { .is_init = false,
		 .v1_v4_control_operation.value = 0,
		 .v5_v8_control_operation.value = 0 },
};

/**************************************************************************************************
 *  PRE-HOOK/POST-HOOK ARGS
 **************************************************************************************************/
/** CXL ID mux config **/
mux_config bus_2_pca9548_configs[] = {
	[0] = { .target_addr = 0x70, .channel = PCA9548A_CHANNEL_6 },
	[1] = { .target_addr = 0x70, .channel = PCA9548A_CHANNEL_7 },
	[2] = { .target_addr = 0x70, .channel = PCA9548A_CHANNEL_4 },
	[3] = { .target_addr = 0x70, .channel = PCA9548A_CHANNEL_5 },
	[4] = { .target_addr = 0x70, .channel = PCA9548A_CHANNEL_3 },
	[5] = { .target_addr = 0x70, .channel = PCA9548A_CHANNEL_2 },
	[6] = { .target_addr = 0x70, .channel = PCA9548A_CHANNEL_1 },
	[7] = { .target_addr = 0x70, .channel = PCA9548A_CHANNEL_0 },
};

mux_config bus_4_pca9548_configs[] = {
	[0] = { .target_addr = 0x70, .channel = PCA9548A_CHANNEL_0 },
	[1] = { .target_addr = 0x70, .channel = PCA9548A_CHANNEL_1 },
	[2] = { .target_addr = 0x70, .channel = PCA9548A_CHANNEL_2 },
	[3] = { .target_addr = 0x70, .channel = PCA9548A_CHANNEL_3 },
	/** JCN 13~14 E1.S mux config **/
	[4] = { .target_addr = 0x70, .channel = PCA9548A_CHANNEL_5 },
	[5] = { .target_addr = 0x70, .channel = PCA9548A_CHANNEL_4 },
	[6] = { .target_addr = 0x70, .channel = PCA9548A_CHANNEL_7 },
	[7] = { .target_addr = 0x70, .channel = PCA9548A_CHANNEL_6 },
};

/** JCN 1~4, 9~12 E1.S 0 mux config **/
mux_config bus_8_pca9548_configs[] = {
	[0] = { .target_addr = 0x70, .channel = PCA9548A_CHANNEL_0 },
	[1] = { .target_addr = 0x70, .channel = PCA9548A_CHANNEL_1 },
	[2] = { .target_addr = 0x70, .channel = PCA9548A_CHANNEL_2 },
	[3] = { .target_addr = 0x70, .channel = PCA9548A_CHANNEL_3 },
	[4] = { .target_addr = 0x70, .channel = PCA9548A_CHANNEL_4 },
	[5] = { .target_addr = 0x70, .channel = PCA9548A_CHANNEL_5 },
	[6] = { .target_addr = 0x70, .channel = PCA9548A_CHANNEL_6 },
	[7] = { .target_addr = 0x70, .channel = PCA9548A_CHANNEL_7 },
};

mux_config cxl_mux_configs[] = {
	[0] = { .target_addr = 0x71, .channel = PCA9848_CHANNEL_0 },
	[1] = { .target_addr = 0x71, .channel = PCA9848_CHANNEL_1 },
	[2] = { .target_addr = 0x71, .channel = PCA9848_CHANNEL_2 },
	[3] = { .target_addr = 0x71, .channel = PCA9848_CHANNEL_3 },
	[4] = { .target_addr = 0x71, .channel = PCA9848_CHANNEL_4 },
	[5] = { .target_addr = 0x71, .channel = PCA9848_CHANNEL_5 },
};

vr_page_cfg vr_page_select[] = {
	[0] = { .vr_page = PMBUS_PAGE_0 },
	[1] = { .vr_page = PMBUS_PAGE_1 },
};

pwr_monitor_pre_proc_arg pwr_monitor_pre_proc_args[] = {
	[0] = { { .target_addr = 0x70, .channel = PCA9546A_CHANNEL_0 }, .jcn_number = 0 },
	[1] = { { .target_addr = 0x70, .channel = PCA9546A_CHANNEL_0 }, .jcn_number = 1 },
	[2] = { { .target_addr = 0x70, .channel = PCA9546A_CHANNEL_0 }, .jcn_number = 2 },
	[3] = { { .target_addr = 0x70, .channel = PCA9546A_CHANNEL_0 }, .jcn_number = 3 },
	[4] = { { .target_addr = 0x70, .channel = PCA9546A_CHANNEL_1 }, .jcn_number = 4 },
	[5] = { { .target_addr = 0x70, .channel = PCA9546A_CHANNEL_1 }, .jcn_number = 5 },
	[6] = { { .target_addr = 0x70, .channel = PCA9546A_CHANNEL_1 }, .jcn_number = 6 },
	[7] = { { .target_addr = 0x70, .channel = PCA9546A_CHANNEL_1 }, .jcn_number = 7 },
	[8] = { { .target_addr = 0x70, .channel = PCA9546A_CHANNEL_2 }, .jcn_number = 8 },
	[9] = { { .target_addr = 0x70, .channel = PCA9546A_CHANNEL_2 }, .jcn_number = 9 },
	[10] = { { .target_addr = 0x70, .channel = PCA9546A_CHANNEL_2 }, .jcn_number = 10 },
	[11] = { { .target_addr = 0x70, .channel = PCA9546A_CHANNEL_2 }, .jcn_number = 11 },
};

/**************************************************************************************************
 *  PRE-HOOK/POST-HOOK FUNC
 **************************************************************************************************/
bool pre_nvme_read(void *arg0, void *arg1)
{
	CHECK_NULL_ARG_WITH_RETURN(arg0, false);
	CHECK_NULL_ARG_WITH_RETURN(arg1, false);

	sensor_cfg *cfg = (sensor_cfg *)arg0;

	// Select Channel
	bool ret = true;
	int mutex_status = 0;
	mux_config *pre_args = (mux_config *)arg1;
	pre_args->bus = cfg->port;

	struct k_mutex *mutex = get_i2c_mux_mutex(pre_args->bus);
	mutex_status = k_mutex_lock(mutex, K_MSEC(MUTEX_LOCK_INTERVAL_MS));
	if (mutex_status != 0) {
		LOG_ERR("Mutex lock fail, status: %d", mutex_status);
		return false;
	}

	ret = set_mux_channel(*pre_args, MUTEX_LOCK_ENABLE);
	return ret;
}

bool post_nvme_read(void *arg0, void *arg1, int *reading)
{
	CHECK_NULL_ARG_WITH_RETURN(arg0, false);
	ARG_UNUSED(reading);
	ARG_UNUSED(arg1);

	sensor_cfg *cfg = (sensor_cfg *)arg0;

	int unlock_status = 0;
	uint8_t bus = cfg->port;

	struct k_mutex *mutex = get_i2c_mux_mutex(bus);
	if (mutex->lock_count != 0) {
		unlock_status = k_mutex_unlock(mutex);
	}

	if (unlock_status != 0) {
		LOG_ERR("Mutex unlock fail, status: %d", unlock_status);
		return false;
	}

	return true;
}

bool pre_sq52205_read(void *arg0, void *arg1)
{
	CHECK_NULL_ARG_WITH_RETURN(arg0, false);
	CHECK_NULL_ARG_WITH_RETURN(arg1, false);

	sensor_cfg *cfg = (sensor_cfg *)arg0;

	// Select Channel
	bool ret = true;
	int mutex_status = 0;
	uint8_t card_type;

	pwr_monitor_pre_proc_arg *pre_args = (pwr_monitor_pre_proc_arg *)arg1;

	if (get_pcie_card_type(pre_args->jcn_number, &card_type)) {
		LOG_ERR("Fail to get card present status");
		cfg->is_enable_polling = false;
		return false;
	}

	if (card_type == CARD_NOT_PRESENT) {
		cfg->is_enable_polling = false;
		return false;
	}

	mux_config *mux_args = &(pre_args->bus_3_mux_configs);
	mux_args->bus = cfg->port;

	struct k_mutex *mutex = get_i2c_mux_mutex(mux_args->bus);
	mutex_status = k_mutex_lock(mutex, K_MSEC(MUTEX_LOCK_INTERVAL_MS));
	if (mutex_status != 0) {
		LOG_ERR("Mutex lock fail, status: %d", mutex_status);
		return false;
	}

	ret = set_mux_channel(*mux_args, MUTEX_LOCK_ENABLE);
	return ret;
}

bool post_sq52205_read(void *arg0, void *arg1, int *reading)
{
	CHECK_NULL_ARG_WITH_RETURN(arg0, false);
	ARG_UNUSED(reading);
	ARG_UNUSED(arg1);

	sensor_cfg *cfg = (sensor_cfg *)arg0;

	int unlock_status = 0;
	uint8_t bus = cfg->port;

	struct k_mutex *mutex = get_i2c_mux_mutex(bus);
	if (mutex->lock_count != 0) {
		unlock_status = k_mutex_unlock(mutex);
	}

	if (unlock_status != 0) {
		LOG_ERR("Mutex unlock fail, status: %d", unlock_status);
		return false;
	}

	return true;
}

bool pre_cxl_switch_mux(uint8_t sensor_num, uint8_t pcie_card_id)
{
	mux_config card_mux = { 0 };
	mux_config cxl_mux = { 0 };
	bool ret = get_pcie_card_mux_config(pcie_card_id, sensor_num, &card_mux, &cxl_mux);
	if (ret != true) {
		return ret;
	}

	int mutex_status = 0;
	struct k_mutex *mutex = get_i2c_mux_mutex(MEB_CXL_BUS);
	mutex_status = k_mutex_lock(mutex, K_MSEC(MUTEX_LOCK_INTERVAL_MS));
	if (mutex_status != 0) {
		LOG_ERR("Mutex lock fail, status: %d", mutex_status);
		return false;
	}

	// Switch card mux
	ret = set_mux_channel(card_mux, MUTEX_LOCK_ENABLE);
	if (ret != true) {
		LOG_ERR("Switch card mux fail");
		k_mutex_unlock(mutex);
		return false;
	}

	// Switch cxl mux
	ret = set_mux_channel(cxl_mux, MUTEX_LOCK_ENABLE);
	if (ret != true) {
		LOG_ERR("Switch cxl mux fail");
		k_mutex_unlock(mutex);
		return false;
	}

	return true;
}

bool post_cxl_switch_mux(uint8_t sensor_num, uint8_t pcie_card_id)
{
	int unlock_status = 0;
	struct k_mutex *mutex = get_i2c_mux_mutex(MEB_CXL_BUS);
	unlock_status = k_mutex_unlock(mutex);
	if (unlock_status != 0) {
		LOG_ERR("Mutex unlock fail, status: %d", unlock_status);
		return false;
	}

	return true;
}

bool pre_cxl_vr_read(void *arg0, void *arg1)
{
	CHECK_NULL_ARG_WITH_RETURN(arg0, false);
	CHECK_NULL_ARG_WITH_RETURN(arg1, false);

	sensor_cfg *cfg = (sensor_cfg *)arg0;

	vr_page_cfg *vr_page_sel = (vr_page_cfg *)arg1;
	uint8_t retry = 5;
	I2C_MSG msg = { 0 };

	/* set page */
	msg.bus = cfg->port;
	msg.target_addr = cfg->target_addr;
	msg.tx_len = 2;
	msg.data[0] = 0x00;
	msg.data[1] = vr_page_sel->vr_page;

	if (i2c_master_write(&msg, retry)) {
		LOG_ERR("Set page fail");
		return false;
	}
	return true;
}

bool post_cxl_xdpe12284c_read(void *arg0, void *arg1, int *reading)
{
	CHECK_NULL_ARG_WITH_RETURN(arg0, false);
	ARG_UNUSED(arg1);

	sensor_cfg *cfg = (sensor_cfg *)arg0;

	if (reading == NULL) {
		return check_reading_pointer_null_is_allowed(cfg);
	}

	sensor_val *sval = (sensor_val *)reading;
	float val = (float)sval->integer + (sval->fraction / 1000.0);
	switch (cfg->offset) {
	case PMBUS_READ_IOUT:
		if (val < (-2)) {
			LOG_ERR("Sensor %x unexpected current reading", cfg->num);
			return false;
		}

		//the tolerance of current is -2 amps.
		if (val < 0) {
			sval->integer = 0;
			sval->fraction = 0;
		}
		break;
	case PMBUS_READ_POUT:
		if (val < (-4)) {
			LOG_ERR("Sensor %x unexpected power reading", cfg->num);
			return false;
		}

		//the tolerance of power is -4 watts.
		if (val < 0) {
			sval->integer = 0;
			sval->fraction = 0;
		}
		break;
	default:
		break;
	}

	return true;
}
