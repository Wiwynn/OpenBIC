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

#include "hal_gpio.h"
#include "hal_peci.h"
#include "power_status.h"
#include "util_sys.h"
#include "plat_class.h"
#include "plat_gpio.h"
#include "plat_pmic.h"

SCU_CFG scu_cfg[] = {
	//register    value
	{ 0x7e6e2610, 0xffffffff },
	{ 0x7e6e2614, 0xffffffff },
	{ 0x7e6e2618, 0x30000000 },
	{ 0x7e6e261c, 0x00000F04 },
};

void pal_pre_init()
{
	init_platform_config();
	disable_PRDY_interrupt();
	scu_init(scu_cfg, sizeof(scu_cfg) / sizeof(SCU_CFG));
}

void pal_device_init()
{
	init_me_firmware();

	start_monitor_pmic_error_thread();
}

#include <zephyr.h>
#include <logging/log.h>
LOG_MODULE_REGISTER(TEST_plat_init);
void pal_post_init()
{
	int ret = 0;
	k_msleep(500);
	LOG_ERR("Error");
	LOG_WRN("Warning");
	LOG_INF("Info");
	LOG_DBG("Debug");
	LOG_PRINTK(KERN_EMERG "ret: %d", ret);
	printf("\n");

	uint8_t arr[256];
	for (int i = 0; i < 256; ++i) {
		arr[i] = 256 - i;
	}
	LOG_HEXDUMP_ERR(&arr[0], "Error HexDump");
	LOG_HEXDUMP_WRN(&arr[0], "Warning HexDump");
	LOG_HEXDUMP_INF(&arr[0], "Info HexDump");
	LOG_HEXDUMP_DBG(&arr[0], "Debug HexDump");
}

void pal_set_sys_status()
{
	set_DC_status(PWRGD_SYS_PWROK);
	set_DC_on_delayed_status();
	set_DC_off_delayed_status();
	set_post_status(FM_BIOS_POST_CMPLT_BMC_N);
	set_CPU_power_status(PWRGD_CPU_LVC3);
	set_post_thread();
	set_sys_ready_pin(BIC_READY);
}

#define DEF_PROJ_GPIO_PRIORITY 78

DEVICE_DEFINE(PRE_DEF_PROJ_GPIO, "PRE_DEF_PROJ_GPIO_NAME", &gpio_init, NULL, NULL, NULL,
	      POST_KERNEL, DEF_PROJ_GPIO_PRIORITY, NULL);
