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

#include <zephyr.h>
#include <stdio.h>
#include <string.h>
#include "cmsis_os.h"
#include "hal_gpio.h"
#include "plat_gpio.h"
#include "plat_isr.h"

#define gpio_name_to_num(x) #x,
char *gpio_name[] = {
	name_gpioA name_gpioB name_gpioC name_gpioD name_gpioE name_gpioF name_gpioG name_gpioH
		name_gpioI name_gpioJ name_gpioK name_gpioL name_gpioM name_gpioN name_gpioO
			name_gpioP name_gpioQ name_gpioR name_gpioS name_gpioT name_gpioU
};
#undef gpio_name_to_num

// clang-format off

/* chip,
 * number,
 * is_init,is_latch,
 * direction,
 * status,
 * property,
 * int_type,
 * int_cb,
*/

GPIO_CFG plat_gpio_cfg[] = {
	/** Group A: 00-07 **/
	{ CHIP_GPIO, 0, ENABLE, DISABLE, GPIO_OUTPUT, GPIO_HIGH, OPEN_DRAIN, GPIO_INT_DISABLE, NULL },
};

// clang-format on

bool pal_load_gpio_config(void)
{
	memcpy(&gpio_cfg[0], &plat_gpio_cfg[0], sizeof(plat_gpio_cfg));
	return 1;
};

void enable_PRDY_interrupt()
{
	gpio_interrupt_conf(H_BMC_PRDY_BUF_N, GPIO_INT_EDGE_FALLING);
}

void disable_PRDY_interrupt()
{
	gpio_interrupt_conf(H_BMC_PRDY_BUF_N, GPIO_INT_DISABLE);
}
