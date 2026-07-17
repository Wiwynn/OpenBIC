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

#include <string.h>
#include <logging/log.h>
#include "fru.h"
#include "eeprom.h"
#include "hal_i2c.h"
#include "libutil.h"
#include "plat_fru.h"
#include "plat_class.h"

LOG_MODULE_REGISTER(plat_fru);

/*
 * EEPROM on I2C bus 0 (WF_FRU_PORT 0x00), address 0x51.
 * Device type set to NV_ATMEL_24C128 (2-byte addressing, 128 Kbit).
 * Adjust dev_type if the actual chip differs.
 */
const EEPROM_CFG plat_fru_config[] = {
	{
		NV_ATMEL_24C128,
		WF_FRU_ID,
		WF_FRU_PORT,
		WF_FRU_ADDR,
		FRU_DEV_ACCESS_BYTE,
		FRU_START,
		FRU_SIZE,
	},
};

void pal_load_fru_config(void)
{
	memcpy(fru_config, plat_fru_config, sizeof(plat_fru_config));
}

/*
 * check_board_product_name - parse the IPMI FRU board info area and compare
 * the board product name field against @expected.
 *
 * IPMI FRU board area layout (each field is type/length byte + data):
 *   bytes 0-5 : fixed header (format_ver, area_len, language, mfg_date[3])
 *   field 0   : board manufacturer
 *   field 1   : board product name   <-- we read this
 *   field 2   : board serial number
 *   ...
 *
 * Field type/length byte encoding:
 *   bits [7:6] = 0b11 (0xC0) -> ASCII 8-bit
 *   bits [5:0]              -> number of bytes that follow
 *
 * Returns true if the product name matches @expected exactly.
 */
bool check_board_product_name(const char *expected)
{
	CHECK_NULL_ARG_WITH_RETURN(expected, false);

	EEPROM_ENTRY entry = { 0 };
	entry.config = plat_fru_config[WF_FRU_ID];

	/* Step 1: read common header (8 bytes) to locate board area */
	entry.offset = 0;
	entry.data_len = 8;
	if (!eeprom_read(&entry)) {
		LOG_ERR("check_board_product_name: failed to read FRU common header");
		return false;
	}

	if (entry.data[0] != 0x01) {
		LOG_ERR("check_board_product_name: unexpected format version 0x%02x",
			entry.data[0]);
		return false;
	}

	uint16_t board_area_off = (uint16_t)entry.data[3] * 8;
	if (board_area_off == 0) {
		LOG_ERR("check_board_product_name: no board info area in FRU");
		return false;
	}
	LOG_DBG("check_board_product_name: board area at offset 0x%04x", board_area_off);

	/* Step 2: read two consecutive 32-byte chunks from the board area.
	 * The manufacturer (6 bytes) + product name (up to 63 bytes) can span
	 * across the first chunk boundary, so we buffer both at once.
	 */
	uint8_t board_buf[2 * EEPROM_WRITE_SIZE] = { 0 };

	for (uint8_t chunk = 0; chunk < 2; chunk++) {
		entry.offset = board_area_off + chunk * EEPROM_WRITE_SIZE;
		entry.data_len = EEPROM_WRITE_SIZE;
		if (!eeprom_read(&entry)) {
			LOG_ERR("check_board_product_name: failed to read board area chunk %u",
				chunk);
			return false;
		}
		memcpy(&board_buf[chunk * EEPROM_WRITE_SIZE], entry.data, EEPROM_WRITE_SIZE);
	}

	/* Step 3: navigate fields.
	 * Skip fixed header (6 bytes), then skip manufacturer field.
	 */
	uint8_t pos = 6;

	if (pos >= sizeof(board_buf)) {
		LOG_ERR("check_board_product_name: buffer overrun at manufacturer field");
		return false;
	}

	uint8_t mfr_len = board_buf[pos] & 0x3F;
	LOG_DBG("check_board_product_name: manufacturer len=%u", mfr_len);
	pos += 1 + mfr_len;

	if (pos >= sizeof(board_buf)) {
		LOG_ERR("check_board_product_name: buffer overrun at product name field");
		return false;
	}

	/* Step 4: read product name field */
	uint8_t prod_type = board_buf[pos] & 0xC0;
	uint8_t prod_len = board_buf[pos] & 0x3F;
	pos++;

	if (prod_type != 0xC0) {
		LOG_ERR("check_board_product_name: non-ASCII field type 0x%02x, cannot compare",
			prod_type);
		return false;
	}

	if ((pos + prod_len) > sizeof(board_buf)) {
		LOG_ERR("check_board_product_name: product name overruns buffer (pos=%u len=%u)",
			pos, prod_len);
		return false;
	}

	LOG_DBG("check_board_product_name: product name len=%u", prod_len);
	LOG_HEXDUMP_DBG(&board_buf[pos], prod_len, "product name raw:");

	/* Step 5: compare */
	size_t expected_len = strlen(expected);
	if (prod_len != expected_len) {
		LOG_DBG("check_board_product_name: length mismatch (fru=%u, expected=%zu)",
			prod_len, expected_len);
		return false;
	}

	if (memcmp(&board_buf[pos], expected, prod_len) != 0) {
		LOG_DBG("check_board_product_name: product name does not match");
		return false;
	}

	LOG_DBG("check_board_product_name: matched \"%s\"", expected);
	return true;
}

bool get_without_asic(void)
{
	static bool fru_without_asic = false;
	if (check_board_product_name(WF_BOARD_PRODUCT_WITHOUT_ASIC)) {
		/* board is "Wailua Falls without ASIC" */
		fru_without_asic = true;
		LOG_DBG("Board Product: Wailua Falls without ASIC");
	} else {
		return 0;
	}

	uint8_t blade_config = get_blade_configuration();
	bool blade_config_result = (blade_config == BLADE_CONFIG_without_ASIC);

	if (blade_config_result != fru_without_asic) {
		LOG_INF("Blade config (without_asic: %d) and FRU info (without_asic: %d) mismatch, using FRU result",
			blade_config_result, fru_without_asic);
	}

	return fru_without_asic;
}

/*
 * dump_fru_raw - reads the raw bytes from the FRU EEPROM and logs them.
 *
 * Reads three consecutive 32-byte chunks (96 bytes total) starting at
 * FRU_START so the IPMI FRU common header (first 8 bytes) and area
 * headers are visible. Call this during init or on demand while the
 * FRU format is being investigated.
 *
 * Standard IPMI FRU common header layout (offset from FRU_START):
 *   [0]  format version  (should be 0x01)
 *   [1]  internal area offset  (in multiples of 8 bytes, 0 = absent)
 *   [2]  chassis info area offset
 *   [3]  board info area offset
 *   [4]  product info area offset
 *   [5]  multirecord area offset
 *   [6]  padding
 *   [7]  checksum (zero-sum of bytes 0-7)
 */
void dump_fru_raw(void)
{
	const uint8_t retry = 5;

	/* Step 1: raw I2C probe — check if anything ACKs at bus 0 / 0x51 */
	I2C_MSG probe = { 0 };
	probe.bus = WF_FRU_PORT;
	probe.target_addr = WF_FRU_ADDR;
	probe.tx_len = 1;
	probe.rx_len = 1;
	probe.data[0] = 0x00; /* read from offset 0 using 1-byte address (24C02 style) */

	if (i2c_master_read(&probe, retry) != 0) {
		LOG_ERR("dump_fru_raw: no ACK from bus %d addr 0x%02x — device absent or wrong address",
			WF_FRU_PORT, WF_FRU_ADDR);
		return;
	}
	LOG_DBG("dump_fru_raw: device ACKed at bus %d addr 0x%02x", WF_FRU_PORT, WF_FRU_ADDR);

	/* Step 2: try 2-byte addressed read (24C64/128 style) via eeprom abstraction */
	EEPROM_ENTRY entry = { 0 };
	entry.config = plat_fru_config[WF_FRU_ID];
	entry.data_len = EEPROM_WRITE_SIZE; /* 32 bytes per chunk */

	/* Read three consecutive chunks to cover the common header and first areas.
	 * Standard IPMI FRU common header layout (offset from FRU_START):
	 *   [0] format version  (should be 0x01)
	 *   [1] internal area offset  (in multiples of 8 bytes, 0 = absent)
	 *   [2] chassis info area offset
	 *   [3] board info area offset
	 *   [4] product info area offset
	 *   [5] multirecord area offset
	 *   [6] padding
	 *   [7] checksum (zero-sum of bytes 0-7)
	 */
	for (uint8_t chunk = 0; chunk < 3; chunk++) {
		entry.offset = chunk * EEPROM_WRITE_SIZE;

		if (!eeprom_read(&entry)) {
			LOG_ERR("dump_fru_raw: eeprom_read (2-byte addr) failed at offset 0x%04x"
				" — device may use 1-byte addressing (e.g. 24C02)",
				entry.config.start_offset + entry.offset);
			return;
		}

		LOG_DBG("FRU raw [offset 0x%04x]:", entry.config.start_offset + entry.offset);
		LOG_HEXDUMP_DBG(entry.data, entry.data_len, "");
	}
}
