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

#include "plat_spi.h"
#include "hal_gpio.h"
#include "plat_gpio.h"
#include "util_spi.h"
#include "plat_i2c.h"

int pal_get_bios_flash_position()
{
	return DEVSPI_SPI1_CS0;
}

bool pal_switch_bios_spi_mux(int gpio_status)
{
	uint8_t retry = 5;
	I2C_MSG msg;

	msg.bus = I2C_BUS5; // for yv4

    // msg.bus = I2C_BUS1; // for hd
	msg.target_addr = CPLD_ADDR;
	msg.tx_len = 2;
	msg.data[0] = CPLD_SPI_OOB_CONTROL_REG;
	if (gpio_status == GPIO_HIGH) {
		msg.data[1] = CPLD_SPI_OOB_FROM_BIC;
	} else {
		msg.data[1] = CPLD_SPI_OOB_FROM_CPU;
	}

	if (i2c_master_write(&msg, retry)) {
		return false;
	}
	return true;
}
