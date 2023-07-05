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

#ifndef PLAT_IPMI_H
#define PLAT_IPMI_H

#define BIC_UPDATE_MAX_OFFSET 0x50000
#define BIOS_UPDATE_MAX_OFFSET 0x4000000
#define PM8702_UPDATE_MAX_OFFSET 0x150000
#define PM8702_INITIATE_FW_OFFSET 0x0000

#define PM8702_DEFAULT_NEXT_ACTIVE_SLOT 0
#define PM8702_NO_HBO_RUN_VAL 0
#define PM8702_TRANSFER_FW_DATA_LEN 128
#define PM8702_RETURN_SUCCESS 0x00
#define PM8702_BUSY_DELAY_MS 100
#define PM8702_TRANSFER_DELAY_MS 20
#define PM8702_TRANSFER_FW_HEADER_LEN 128

enum REQ_GET_CARD_TYPE {
	GET_1OU_CARD_TYPE = 0x0,
	GET_2OU_CARD_TYPE,
};

#endif
