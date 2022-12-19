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

#include "plat_isr.h"

#include <zephyr.h>
#include <logging/log.h>
#include "hal_i2c.h"
#include "hal_gpio.h"
#include "plat_gpio.h"

LOG_MODULE_REGISTER(plat_isr);

void isr_acb_btn()
{
	if (gpio_get(FIO_PWRBTN_N_R) == GPIO_LOW) {
		/* send i2c message to hsc */
		I2C_MSG msg;
		msg.bus = 0;
		msg.target_addr = 0x11;
		msg.rx_len = 1;
		msg.tx_len = 1;
		msg.data[0] = 0xd9;
		uint8_t retry = 1;
		i2c_master_write(&msg, retry);

		K_MSEC(100);
		msg.target_addr = 0x10;
		i2c_master_write(&msg, retry);
	}
}
