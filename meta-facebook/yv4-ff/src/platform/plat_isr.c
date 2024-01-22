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

#include <stdlib.h>
#include <logging/log.h>
#include <drivers/sensor.h>
#include <drivers/pwm.h>

#include "hal_gpio.h"
#include "plat_gpio.h"
#include "plat_power_seq.h"
#include "plat_isr.h"
#include "plat_mctp.h"

LOG_MODULE_REGISTER(plat_isr);

K_WORK_DEFINE(cxl_power_on_work, execute_power_on_sequence);
K_WORK_DEFINE(cxl_power_off_work, execute_power_off_sequence);

static bool is_asic_power_fault_assert = false;

#define ISR_ASIC_POWER_FAULT_HANDLER(power)                                                 \
	void ISR_##power##_ASIC_POWER_FAULT()                                        \
	{                                                                                          \
		uint8_t value = 0;                                                                   \
		value = gpio_get(PWRGD_##power##_ASIC);                              \
		LOG_DBG("FF BIC GPIO%d = %d\n", PWRGD_##power##_ASIC, value);     \
		//debug \
		printk("POWER_EN_R = %d, Sean debug ASIC_EN = %d \n", gpio_get(POWER_EN_R), gpio_get(power##_BIC_ASIC_EN));		\
		if (gpio_get(POWER_EN_R) == POWER_ON) {     \
			uint8_t buf[4];		\
			uint8_t len = 0;		\
			if ((gpio_get(power##_BIC_ASIC_EN) == POWER_ON) &&               \
			    (gpio_get(PWRGD_##power##_ASIC) == POWER_OFF)) {               \
			    if (!is_asic_power_fault_assert) {		\
					buf[len++] = 0x0;		\
					buf[len++] = 0x0;		\
					buf[len++] = ASIC_##power##_POWER_RAIL_FAIL;		\
					buf[len++] = 0x0;		\
					/*byte0 = BIC 0x0/BIOS 0x1, byte1 = error_type(power_rail_fail), byte3 = description, byte4 = action */ \
				    /*send "replace the board"		\
					send_system_status_event(IPMI_EVENT_TYPE_SENSOR_SPECIFIC,                  \
								 //IPMI_EVENT_OFFSET_SYS_E1S_##power##_FAULT,        \
								 //E1S_##device);*/                                    \
					send_event_to_bmc(buf, len);		\
					is_asic_power_fault_assert = true;                        \
				}		\
			} else {                                                                           \
				if ((gpio_get(power##_BIC_ASIC_EN) == POWER_ON) &&       \
				    (gpio_get(PWRGD_##power##_ASIC) == POWER_ON)) {        \
					if (is_asic_power_fault_assert) {                 \
						/*send "deassert"		\
						//send_system_status_event(                                  \
							//IPMI_OEM_EVENT_TYPE_DEASSERT,                      \
							//IPMI_EVENT_OFFSET_SYS_E1S_##power##_FAULT,         \
							//E1S_##device);*/                                    \
						is_asic_power_fault_assert = false;       \
					}                                                                  \
				}                                                                          \
			}                                                                                  \
		}                                                                                  \
	}

ISR_ASIC_POWER_FAULT_HANDLER(P0V85);
ISR_ASIC_POWER_FAULT_HANDLER(P1V2);
ISR_ASIC_POWER_FAULT_HANDLER(P1V8);
ISR_ASIC_POWER_FAULT_HANDLER(P0V8);

void ISR_MB_DC_STATUS_CHANGE()
{
	set_mb_dc_status(POWER_EN_R);

	if (gpio_get(POWER_EN_R) == POWER_ON) {
		k_work_submit(&cxl_power_on_work);
	} else {
		k_work_submit(&cxl_power_off_work);
	}
}

void ISR_MB_PCIE_RST()
{
	gpio_set(PERST_ASIC_N_R, gpio_get(RST_PCIE_MB_EXP_N));
}
