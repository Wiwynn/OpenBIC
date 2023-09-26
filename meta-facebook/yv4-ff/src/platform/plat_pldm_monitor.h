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

#ifndef PLAT_PLDM_MONITOR_H
#define PLAT_PLDM_MONITOR_H

#define LPC_BASE_ADDR 0x7E789000 // Refer to Chapter32: LPC Controller in AST1030 datasheet v1.0
#define LPC_HICR9_REG (LPC_BASE_ADDR + 0x98)
#define LPC_HICRA_REG (LPC_BASE_ADDR + 0x9C)

enum plat_pldm_effecter_id {
	PLAT_PLDM_EFFECTER_ID_UART_SWITCH = 0x0003,
};

enum plat_pldm_uart_number {
	UART_VISTARA = 0,
	UART_BIC,
	UART_MAX,
};

extern struct pldm_state_effecter_info plat_state_effecter_table[];

#endif
