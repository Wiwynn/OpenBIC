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
#ifndef TPS53689_H
#define TPS53689_H

#define TI_REG_USER_NVM_INDEX 0xF5
#define TI_REG_USER_NVM_EXECUTE 0xF6

enum TPS536XX_UPDATE_INFO {
	TPS536XX_UPDATE_INFO_LENS = 74,
	TPS536XX_UPDATE_INFO_BYTES = 32,
	TPS536XX_UPDATE_MAX_DATA_SIZE = 288,
	TPS536XX_UPDATE_INFO_START_BYTE = 10,
	TPS536XX_UPDATE_DEVID_BYTE_LENS = 11,

};

struct tps_config {
	uint8_t addr;
	uint8_t crc[2];
	uint8_t devid[6];
	uint8_t data[TPS536XX_UPDATE_MAX_DATA_SIZE];
};

uint8_t tps536c5_dev_id[] = { 0x54, 0x49, 0x53, 0x6C, 0x50, 0x00 };

int tps53689_get_crc(uint8_t bus, uint8_t addr, uint32_t *crc);

#endif
