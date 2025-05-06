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
#include <stdlib.h>
#include <shell/shell.h>
#include <device.h>
#include <drivers/i3c/i3c.h>
#include "plat_i3c_oem_shell.h"

void cmd_reset_i3c_0(const struct shell *shell, size_t argc, char **argv)
{
	shell_print(shell, "[DEBUG KAY][Checkpoint 1] Start cmd_reset_i3c_0");
	const struct device *dev = device_get_binding("I3C_0");

	if (!dev) {
		shell_error(shell, "[DEBUG KAY][Checkpoint 1.1] Failed to get I3C_0 device");
		return;
	}

	i3c_aspeed_reset_and_callback(dev);

	shell_print(shell, "[DEBUG KAY][Checkpoint 3] End cmd_reset_i3c_0");
	return;
}