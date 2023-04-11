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

#ifndef SPI_BRIDGE_SC18IS606_H
#define SPI_BRIDGE_SC18IS606_H

#define EEPROM_WRITE_DATA_BYTES_CMD 0x02
#define EEPROM_READ_DATA_BYTES_CMD 0x03
#define EEPROM_READ_STATUS_REG_CMD 0x05
#define EEPROM_WRITE_ENABLE_DEFAULT_CMD 0x06
#define EEPROM_READ_CFG_REG_CMD 0x15
#define EEPROM_ERASE_SECTOR_CMD 0x20
#define EEPROM_RESET_ENABLE_CMD 0x66
#define EEPROM_RESET_CMD 0x99
#define EEPROM_ENABLE_4BYTES_MODE_CMD 0xB7
#define EEPROM_CMD_LEN 0x01
#define EEPROM_READ_STATUS_REQ_LEN 0x03
#define EEPROM_ERASE_SECTOR_SIZE (4 * 1024)

#define EEPROM_WRITE_OPERATION_BIT BIT(0)
#define EEPROM_4BYTES_MODE_BIT BIT(5)

#define SC18IS606_WAIT_FLASH_IDLE_RETRY 20
#define SC18IS606_WAIT_FLASH_IDLE_DELAY_US 200
#define SC18IS606_DUMMY_DATA 0xFF
#define SC18IS606_SEND_CMD_DELAY_MS 3

enum SC18IS606_FUNCTION_ID {
	FUNCTION_ID_SPI_WRITE_READ_SS_1 = BIT(0),
	FUNCTION_ID_SPI_WRITE_READ_SS_2 = BIT(1),
	FUNCTION_ID_SPI_WRITE_READ_SS_3 = BIT(2),
	FUNCTION_ID_CONFIG_SPI_INTERFACE = 0xF0,
	FUNCTION_ID_CLEAR_INTERRUPT,
	FUNCTION_ID_IDLE_MODE,
	FUNCTION_ID_GPIO_WRITE = 0xF4,
	FUNCTION_ID_GPIO_READ,
	FUNCTION_ID_GPIO_ENABLE,
	FUNCTION_ID_GPIO_CONFIG,
	FUNCTION_ID_READ_VERSION = 0xFE,
};

enum SC18IS606_OPTION {
	SPI_NONE,
	SPI_READ,
	SPI_WRITE,
};

typedef struct _sc18is606_config_spi_arg {
	uint8_t spi_clock_rate : 2;
	uint8_t mode_selection : 2;
	uint8_t reserved_1 : 1;
	uint8_t order : 1;
	uint8_t reserved_2 : 2;
} sc18is606_config_spi_arg;

typedef struct __attribute__((packed)) _spi_write_read_cfg {
	uint8_t cmd;
	uint32_t offset;
} spi_write_read_cfg;

bool sc18is606_spi_transfer(uint8_t option, uint8_t bus, uint8_t addr, uint8_t function_id,
			    uint8_t *buf, uint16_t buf_len);
bool sc18is606_config_spi(uint8_t bus, uint8_t addr, sc18is606_config_spi_arg arg);
bool sc18is606_write_enable(uint8_t bus, uint8_t addr, uint8_t function_id);
bool sc18is606_sw_reset(uint8_t bus, uint8_t addr, uint8_t function_id);
bool sc18is606_wait_flash_idle(uint8_t bus, uint8_t addr, uint8_t function_id);
bool sc18is606_spi_write(uint8_t bus, uint8_t addr, uint8_t function_id, uint32_t offset,
			 uint8_t *write_buf, uint16_t write_len);
bool sc18is606_spi_read(uint8_t bus, uint8_t addr, uint8_t function_id, uint32_t offset,
			uint8_t *read_buf, uint16_t read_len);
bool sc18is606_fw_update(uint8_t bus, uint8_t addr, uint8_t function_id, uint32_t offset,
			 uint8_t *write_buf, uint16_t write_len);
bool sc18is606_read_status_register(uint8_t bus, uint8_t addr, uint8_t function_id, uint8_t *resp,
				    uint8_t read_len);
bool sc18is606_set_4bytes_mode(uint8_t bus, uint8_t addr, uint8_t function_id);
bool sc18is606_erase_sector(uint8_t bus, uint8_t addr, uint8_t function_id, uint32_t offset);

#endif
