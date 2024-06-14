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

#ifndef PLAT_PLDM_H
#define PLAT_PLDM_H

uint8_t plat_pldm_get_http_boot_data(uint8_t *httpBootData, uint16_t httpBootOffset,
				     uint8_t httpBootReadlen, uint8_t *httpBootResplen,
				     bool *is_end_package);
uint8_t plat_pldm_get_http_boot_attr(uint8_t attr, uint8_t *httpBootAttrData,
				     uint8_t httpBootAttrDatalen);

#endif
