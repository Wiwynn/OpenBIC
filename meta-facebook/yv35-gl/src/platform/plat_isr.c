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
#include "hal_vw_gpio.h"
#include "power_status.h"
#include <logging/log.h>

LOG_MODULE_REGISTER(plat_isr);

void ISR_POST_COMPLETE(uint8_t gpio_value)
{
	bool is_post_completed = (gpio_value == VW_GPIO_HIGH)? true: false;
	set_post_complete(is_post_completed);
}
