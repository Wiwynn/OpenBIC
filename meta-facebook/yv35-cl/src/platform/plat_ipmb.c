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
#include "cmsis_os2.h"
#include <string.h>
#include "plat_i2c.h"
#include "plat_ipmb.h"
#include "plat_ipmi.h"
#include "plat_class.h"

IPMB_config pal_IPMB_config_table[] = {
	// index, interface, channel, bus, channel_target_address, enable_status, self_address,
	// rx_thread_name, tx_thread_name
	{ BMC_IPMB_IDX, I2C_IF, BMC_IPMB, IPMB_I2C_BMC, BMC_I2C_ADDRESS, DISABLE, SELF_I2C_ADDRESS,
	  "RX_BMC_IPMB_TASK", "TX_BMC_IPMB_TASK" },
	{ ME_IPMB_IDX, I2C_IF, ME_IPMB, IPMB_ME_BUS, ME_I2C_ADDRESS, ENABLE, SELF_I2C_ADDRESS,
	  "RX_ME_IPMB_TASK", "TX_ME_IPMB_TASK" },
	{ EXP1_IPMB_IDX, I2C_IF, EXP1_IPMB, IPMB_EXP1_BUS, BIC1_I2C_ADDRESS, DISABLE,
	  SELF_I2C_ADDRESS, "RX_EPX1_IPMB_TASK", "TX_EXP1_IPMB_TASK" },
	{ EXP2_IPMB_IDX, I2C_IF, EXP2_IPMB, IPMB_EXP2_BUS, BIC2_I2C_ADDRESS, DISABLE,
	  SELF_I2C_ADDRESS, "RX_EPX2_IPMB_TASK", "TX_EXP2_IPMB_TASK" },
	{ RESERVED_IDX, RESERVED_IF, RESERVED, RESERVED_BUS, RESERVED_ADDRESS, DISABLE,
	  RESERVED_ADDRESS, "RESERVED_ATTR", "RESERVED_ATTR" },
};

bool pal_load_ipmb_config(void)
{
	uint8_t bic_class = get_system_class();

	// class1 1ou ipmi bus and class2 bb ipmi bus shared same i2c bus
	CARD_STATUS _1ou_status = get_1ou_status();
	if (_1ou_status.present) {
		switch (bic_class) {
		case SYS_CLASS_1:
			pal_IPMB_config_table[EXP1_IPMB_IDX].enable_status = ENABLE;
			break;
		case SYS_CLASS_2:
			pal_IPMB_config_table[EXP1_IPMB_IDX].index = BB_IPMB_IDX;
			pal_IPMB_config_table[BB_IPMB_IDX].channel = BB_IPMB;
			pal_IPMB_config_table[BB_IPMB_IDX].bus = IPMB_BB_BIC_BUS;
			pal_IPMB_config_table[BB_IPMB_IDX].channel_target_address =
				BB_BIC_I2C_ADDRESS;
			pal_IPMB_config_table[BB_IPMB_IDX].rx_thread_name = "RX_BB_BIC_IPMB_TASK";
			pal_IPMB_config_table[BB_IPMB_IDX].tx_thread_name = "TX_BB_BIC_IPMB_TASK";
			pal_IPMB_config_table[BB_IPMB_IDX].enable_status = ENABLE;
			break;
		default:
			printf("[%s] Unknown system class(0x%x)\n", __func__, bic_class);
			break;
		}
	}

	CARD_STATUS _2ou_status = get_2ou_status();
	if (_2ou_status.present) {
		// for dpv2 sku, disable ipmb and set i2c freq to 400Khz for slave devices reading
		// for reset of expansion board, enable ipmb and set i2c freq to 1Mhz
		if ((_2ou_status.card_type & TYPE_2OU_DPV2_16) == TYPE_2OU_DPV2_16) {
			i2c_freq_set(pal_IPMB_config_table[EXP2_IPMB_IDX].bus, I2C_SPEED_FAST, 0);
			pal_IPMB_config_table[EXP2_IPMB_IDX].enable_status = DISABLE;
		} else {
			pal_IPMB_config_table[EXP2_IPMB_IDX].enable_status = ENABLE;
		}
	}

	memcpy(&IPMB_config_table[0], &pal_IPMB_config_table[0], sizeof(pal_IPMB_config_table));
	return true;
}

bool pal_is_interface_use_ipmb(uint8_t interface_index)
{
	switch (interface_index) {
	case BMC_IPMB_IDX:
		return false;
	}
	return true;
}
