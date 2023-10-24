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
#include "util_worker.h"
#include "ioexp_tca9555.h"
#include "hal_gpio.h"
#include "hal_i2c.h"
#include "plat_gpio.h"
#include "plat_power_seq.h"
#include "plat_isr.h"
#include "plat_i2c.h"

LOG_MODULE_REGISTER(plat_isr);

int e1s_pe_reset_control()
{
	int ret = 0;
	uint8_t retry = 5;
	uint8_t io_output_status = 0;
	I2C_MSG msg = { 0 };

	msg.bus = I2C_BUS6;
	msg.target_addr = ADDR_IOE4;
	msg.rx_len = 1;
	msg.tx_len = 1;
	msg.data[0] = TCA9555_OUTPUT_PORT_REG_1;

	ret = i2c_master_read(&msg, retry);
	if (ret != 0) {
		LOG_ERR("Unable to read ioexp bus: %u addr: 0x%02x", msg.bus, msg.target_addr);
		return -1;
	}

	io_output_status = msg.data[0];

	memset(&msg, 0, sizeof(I2C_MSG));

	msg.bus = I2C_BUS6;
	msg.target_addr = ADDR_IOE4;
	msg.tx_len = 2;
	msg.data[0] = TCA9555_OUTPUT_PORT_REG_1;
	msg.data[1] = ((io_output_status | E1S_PE_RESET_BIT) & (~E1S_CLK_BIT));

	ret = i2c_master_write(&msg, retry);

	if (ret != 0) {
		LOG_ERR("Unable to write ioexp bus: %u addr: 0x%02x", msg.bus, msg.target_addr);
		return -1;
	}

	return 0;
}

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
		LOG_ERR("Unable to read ioexp bus: %u addr: 0x%02x", msg.bus, msg.target_addr);
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

void set_ioe4_pin()
{
	int ret = 0;
	uint8_t retry = 5;
	uint8_t io_output_status = 0;
	I2C_MSG msg = { 0 };

	msg.bus = I2C_BUS6;
	msg.target_addr = ADDR_IOE4;
	msg.rx_len = 1;
	msg.tx_len = 1;
	msg.data[0] = TCA9555_CONFIG_REG_1;

	ret = i2c_master_read(&msg, retry);
	if (ret != 0) {
		LOG_ERR("Unable to read ioexp bus: %u addr: 0x%02x", msg.bus, msg.target_addr);
		return;
	}

	io_output_status = msg.data[0];

	memset(&msg, 0, sizeof(I2C_MSG));

	msg.bus = I2C_BUS6;
	msg.target_addr = ADDR_IOE4;
	msg.tx_len = 2;
	msg.data[0] = TCA9555_CONFIG_REG_1;
	msg.data[1] = ((io_output_status & (~E1S_PE_RESET_BIT)) & (~E1S_CLK_BIT)) |
		      E1S_PRESENT_BIT; //Set bit5,6 output and bit2 input

	ret = i2c_master_write(&msg, retry);

	if (ret != 0) {
		LOG_ERR("Unable to write ioexp bus: %u addr: 0x%02x", msg.bus, msg.target_addr);
		return;
	}

	return;
}

void check_ioexp_status()
{
	if (check_e1s_present_status() == 0) {
		e1s_pe_reset_control();
	}
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

K_WORK_DEFINE(ioe_power_on_work, check_ioexp_status);

void ISR_MB_PCIE_RST()
{
	gpio_set(PERST_ASIC1_N_R, gpio_get(RST_PCIE_MB_EXP_N));
	gpio_set(PERST_ASIC2_N_R, gpio_get(RST_PCIE_MB_EXP_N));

	if (gpio_get(RST_PCIE_MB_EXP_N) == GPIO_HIGH) {
		k_work_submit(&ioe_power_on_work);
	}
}
