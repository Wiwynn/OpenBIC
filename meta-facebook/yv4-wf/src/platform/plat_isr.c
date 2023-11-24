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

#include <logging/log.h>
#include "libutil.h"
#include "util_worker.h"
#include "hal_gpio.h"
#include "hal_i2c.h"
#include "plat_gpio.h"
#include "plat_power_seq.h"
#include "plat_isr.h"
#include "plat_i2c.h"

LOG_MODULE_REGISTER(plat_isr);



int check_e1s_present_status()
{
	int ret = 0;
	uint8_t retry = 5;
	uint8_t e1s_present_status = 0;
	I2C_MSG msg = { 0 };

	memset(&msg, 0, sizeof(I2C_MSG));
	msg.bus = I2C_BUS6;
	msg.target_addr = ADDR_IOE4;
	msg.rx_len = 1;
	msg.tx_len = 1;
	msg.data[0] = TCA9555_INPUT_PORT_REG_1;

	ret = i2c_master_read(&msg, retry);

	if (ret != 0) {
		LOG_ERR("Unable to read ioexp bus when checking E1S present: %u addr: 0x%02x",
			msg.bus, msg.target_addr);
		return -1;
	}

	e1s_present_status = msg.data[0] & TCA9555_PORT_2;

	if (e1s_present_status != 0) { // e1s is not present when present pin is low.
		LOG_WRN("E1S is not present");
		return -1;
	} else {
		return 0;
	}
}

void mb_pcie_rst_handler()
{
	get_ioe_value(ADDR_IOE4, TCA9555_INPUT_PORT_REG_1, &value)
	if (check_e1s_present_status() == 0) {
		set_ioe4_control(SET_PE_RST);
	}
}

void e1s_pwr_on_handler()
{
	/* Low activie ASIC_CLK and E1S_CLK */
	uint8_t value = 0;

	if(get_ioe_value(ADDR_IOE4, TCA9555_OUTPUT_PORT_REG_1, &value)== 0) {
		CLEARBIT(value, ASIC_CLK_BIT);
		CLEARBIT(value, E1S_CLK_BIT);
		set_ioe_value(ADDR_IOE4, TCA9555_OUTPUT_PORT_REG_1, value);
	}

	return;
}

static void cxl_ready_handler()
{
	/* TODO:
	 * In normal states, DIMM and PMIC muxs should be switch to BIC after checking CXL heartbeat is ready. However, WF's heartbeat is not ready yet
	 * ,so we need to make the workaround for switch muxs.
	 */

	uint8_t value = 0x0;

	if (get_ioe_value(ADDR_IOE2, TCA9555_OUTPUT_PORT_REG_0, &value) == 0) {
		value |= IOE2_SWITCH_MUX_TO_BIC; // Enable P0~P3 to switch mux to BIC.
		set_ioe_value(ADDR_IOE2, TCA9555_OUTPUT_PORT_REG_0, value);
	}

	return;
}

static void pg_card_off_handler()
{
	uint8_t value = 0x0;
	int ioe2_p0 = 0, ioe2_p3 = 3;

	if (get_ioe_value(ADDR_IOE2, TCA9555_OUTPUT_PORT_REG_0, &value) == 0) {
		LOG_ERR("ioe2 before value: 0x%02x", value);
		CLEARBITS(value, ioe2_p0, ioe2_p3)	// Disable P0~P3 to switch mux to CXL.
		LOG_ERR("ioe2 after value: 0x%02x", value);
		set_ioe_value(ADDR_IOE2, TCA9555_OUTPUT_PORT_REG_0, value);
	}

	return;
}

K_WORK_DEFINE(cxl_power_on_work, execute_power_on_sequence);
K_WORK_DEFINE(cxl_power_off_work, execute_power_off_sequence);

void ISR_MB_DC_STAGUS_CHAGNE()
{
	set_mb_dc_status(FM_POWER_EN_R);

	if (gpio_get(FM_POWER_EN_R) == POWER_ON) {
		//init_power_on_thread(CLK_POWER_ON_STAGE);
		k_work_submit(&cxl_power_on_work);
	} else {
		//init_power_off_thread(DIMM_POWER_OFF_STAGE_1);
		k_work_submit(&cxl_power_off_work);
	}
}

K_WORK_DEFINE(mb_pcie_rst_work, mb_pcie_rst_handler);

void ISR_MB_PCIE_RST()
{
	gpio_set(PERST_ASIC1_N_R, gpio_get(RST_PCIE_MB_EXP_N));
	gpio_set(PERST_ASIC2_N_R, gpio_get(RST_PCIE_MB_EXP_N));

	if (gpio_get(RST_PCIE_MB_EXP_N) == HIGH_ACTIVE) {
		k_work_submit(&mb_pcie_rst_work);
	}
}

K_WORK_DEFINE(e1s_pwr_on_work, e1s_pwr_on_handler);

void ISR_E1S_PWR_ON()
{
	k_work_submit(&e1s_pwr_on_work);
}

K_WORK_DELAYABLE_DEFINE(CXL_READY_thread, cxl_ready_handler);
K_WORK_DEFINE(pg_card_off_work, pg_card_off_handler);

void ISR_PG_CARD_OK()
{
		if (k_work_cancel_delayable(&CXL_READY_thread) != 0) {
			LOG_ERR("Failed to cancel CXL_READY thread");
		}
		k_work_schedule(&CXL_READY_thread, K_SECONDS(CXL_READY_SECONDS));
}
