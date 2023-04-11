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

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <logging/log.h>
#include "libutil.h"
#include "sc18is606.h"
#include "hal_i2c.h"

LOG_MODULE_REGISTER(dev_sc18is606);

bool sc18is606_spi_transfer(uint8_t option, uint8_t bus, uint8_t addr, uint8_t function_id,
			    uint8_t *buf, uint16_t buf_len)
{
	if (buf_len != 0) {
		CHECK_NULL_ARG_WITH_RETURN(buf, false);
	}

	int ret = 0;
	uint8_t retry = 5;
	I2C_MSG msg = { 0 };

	msg.bus = bus;
	msg.target_addr = addr;

	switch (option) {
	case SPI_NONE:
		msg.tx_len = buf_len + 1; // function id + write length
		msg.data[0] = function_id;
		memcpy(&msg.data[1], buf, sizeof(uint8_t) * buf_len);

		ret = i2c_master_write(&msg, retry);
		if (ret != 0) {
			LOG_ERR("i2c write fail, bus: 0x%x, addr: 0x%x, ret: %d, function id: 0x%x",
				bus, addr, ret, function_id);
			return false;
		}

		return true;
	case SPI_WRITE:
		msg.tx_len = buf_len + 1; // function id + write length
		msg.data[0] = function_id;
		memcpy(&msg.data[1], buf, sizeof(uint8_t) * buf_len);
		ret = i2c_master_write(&msg, retry);
		if (ret != 0) {
			LOG_ERR("i2c write fail, bus: 0x%x, addr: 0x%x, ret: %d, function id: 0x%x",
				bus, addr, ret, function_id);
			return false;
		}

		k_msleep(SC18IS606_SEND_CMD_DELAY_MS);

		memset(&msg, 0, sizeof(I2C_MSG));
		msg.bus = bus;
		msg.target_addr = addr;
		msg.tx_len = 1;
		msg.data[0] = FUNCTION_ID_CLEAR_INTERRUPT;
		ret = i2c_master_write(&msg, retry);
		if (ret != 0) {
			LOG_ERR("i2c write fail, bus: 0x%x, addr: 0x%x, ret: %d, function id: 0x%x",
				bus, addr, ret, FUNCTION_ID_CLEAR_INTERRUPT);
			return false;
		}

		return true;
	case SPI_READ:
		msg.rx_len = buf_len;
		ret = i2c_master_read(&msg, retry);
		if (ret != 0) {
			LOG_ERR("i2c read fail, bus: 0x%x, addr: 0x%x, ret: %d, function id: 0x%x",
				bus, addr, ret, function_id);
			return false;
		}

		memcpy(buf, &msg.data[0], sizeof(uint8_t) * buf_len);
		return true;
	default:
		LOG_ERR("Invalid option 0x%x", option);
		return false;
	}
}

bool sc18is606_config_spi(uint8_t bus, uint8_t addr, sc18is606_config_spi_arg arg)
{
	return sc18is606_spi_transfer(SPI_NONE, bus, addr, FUNCTION_ID_CONFIG_SPI_INTERFACE,
				      (uint8_t *)&arg, sizeof(sc18is606_config_spi_arg));
}

bool sc18is606_set_4bytes_mode(uint8_t bus, uint8_t addr, uint8_t function_id)
{
	uint8_t enable_4bytes_mode_cmd = EEPROM_ENABLE_4BYTES_MODE_CMD;

	return sc18is606_spi_transfer(SPI_WRITE, bus, addr, function_id, &enable_4bytes_mode_cmd,
				      sizeof(uint8_t));
}

bool sc18is606_sw_reset(uint8_t bus, uint8_t addr, uint8_t function_id)
{
	bool ret = false;
	uint8_t cmd = EEPROM_RESET_ENABLE_CMD;

	ret = sc18is606_spi_transfer(SPI_WRITE, bus, addr, function_id, &cmd, sizeof(uint8_t));
	if (ret != true) {
		LOG_ERR("Reset enable fail, function id: 0x%x", function_id);
		return ret;
	}

	cmd = EEPROM_RESET_CMD;
	ret = sc18is606_spi_transfer(SPI_WRITE, bus, addr, function_id, &cmd, sizeof(uint8_t));
	if (ret != true) {
		LOG_ERR("SW reset fail, function id: 0x%x", function_id);
	}

	return ret;
}

bool sc18is606_wait_flash_idle(uint8_t bus, uint8_t addr, uint8_t function_id)
{
	bool ret = false;
	uint8_t index = 0;
	uint8_t status = 0;

	for (index = 0; index < SC18IS606_WAIT_FLASH_IDLE_RETRY; ++index) {
		ret = sc18is606_read_status_register(bus, addr, function_id, &status,
						     sizeof(uint8_t));
		if (ret != true) {
			return ret;
		}

		if (status & EEPROM_WRITE_OPERATION_BIT) {
			k_usleep(SC18IS606_WAIT_FLASH_IDLE_DELAY_US);
			continue;
		} else {
			return true;
		}
	}

	LOG_ERR("Wait flash idle reach retry max");
	return false;
}

bool sc18is606_read_status_register(uint8_t bus, uint8_t addr, uint8_t function_id, uint8_t *resp,
				    uint8_t read_len)
{
	CHECK_NULL_ARG_WITH_RETURN(resp, false);

	bool ret = false;
	uint8_t buf[EEPROM_READ_STATUS_REQ_LEN] = { 0 };

	buf[0] = EEPROM_READ_STATUS_REG_CMD;
	memset(&buf[1], SC18IS606_DUMMY_DATA, EEPROM_READ_STATUS_REQ_LEN - EEPROM_CMD_LEN);

	ret = sc18is606_spi_transfer(SPI_WRITE, bus, addr, function_id, buf,
				     EEPROM_READ_STATUS_REQ_LEN);
	if (ret != true) {
		LOG_ERR("Read status register fail");
		return ret;
	}

	memset(buf, 0, EEPROM_READ_STATUS_REQ_LEN);
	ret = sc18is606_spi_transfer(SPI_READ, bus, addr, function_id, buf,
				     EEPROM_READ_STATUS_REQ_LEN);
	if (ret != true) {
		LOG_ERR("Read status response fail");
		return ret;
	}

	memcpy(resp, &buf[1], read_len);
	return ret;
}

bool sc18is606_write_enable(uint8_t bus, uint8_t addr, uint8_t function_id)
{
	bool ret = false;
	uint8_t write_enable_cmd = EEPROM_WRITE_ENABLE_DEFAULT_CMD;

	ret = sc18is606_spi_transfer(SPI_WRITE, bus, addr, function_id, &write_enable_cmd,
				     sizeof(uint8_t));

	return ret;
}

bool sc18is606_erase_sector(uint8_t bus, uint8_t addr, uint8_t function_id, uint32_t offset)
{
	bool ret = false;
	uint8_t erase_sector_cmd = EEPROM_ERASE_SECTOR_CMD;
	uint8_t data_len = sizeof(uint32_t) + 1;
	uint8_t data_buf[data_len];
	memset(data_buf, 0, data_len);

	data_buf[0] = erase_sector_cmd;
	memcpy(&data_buf[1], &offset, sizeof(uint32_t));

	// The MSB of the data word is transmitted first
	reverse_array(&data_buf[1], sizeof(uint32_t));

	ret = sc18is606_write_enable(bus, addr, function_id);
	if (ret != true) {
		LOG_ERR("Write enable fail before erase sector");
		return ret;
	}

	ret = sc18is606_spi_transfer(SPI_WRITE, bus, addr, function_id, data_buf, data_len);
	if (ret != true) {
		LOG_ERR("Erase sector fail");
	}

	return ret;
}

bool sc18is606_spi_write(uint8_t bus, uint8_t addr, uint8_t function_id, uint32_t offset,
			 uint8_t *write_buf, uint16_t write_len)
{
	CHECK_NULL_ARG_WITH_RETURN(write_buf, false);

	bool ret = false;
	uint8_t cfg_size = sizeof(spi_write_read_cfg);
	uint8_t data_buf[cfg_size + write_len];
	memset(data_buf, 0, cfg_size + write_len);

	spi_write_read_cfg cfg = { 0 };
	cfg.cmd = EEPROM_WRITE_DATA_BYTES_CMD;
	cfg.offset = offset;

	// The MSB of the data word is transmitted first
	memcpy(&data_buf[0], &cfg, cfg_size);
	reverse_array(&data_buf[1], cfg_size - 1);

	memcpy(&data_buf[cfg_size], write_buf, write_len);

	ret = sc18is606_write_enable(bus, addr, function_id);
	if (ret != true) {
		LOG_ERR("Write enable fail");
		return ret;
	}

	ret = sc18is606_spi_transfer(SPI_WRITE, bus, addr, function_id, data_buf,
				     cfg_size + write_len);
	if (ret != true) {
		LOG_ERR("SPI write data fail");
	}

	return ret;
}

bool sc18is606_spi_read(uint8_t bus, uint8_t addr, uint8_t function_id, uint32_t offset,
			uint8_t *read_buf, uint16_t read_len)
{
	CHECK_NULL_ARG_WITH_RETURN(read_buf, false);

	bool ret = false;
	uint8_t cfg_size = sizeof(spi_write_read_cfg);
	uint8_t data_buf[cfg_size + read_len];
	memset(data_buf, 0, cfg_size + read_len);

	spi_write_read_cfg cfg = { 0 };
	cfg.cmd = EEPROM_READ_DATA_BYTES_CMD;
	cfg.offset = offset;

	// The MSB of the data word is transmitted first
	memcpy(&data_buf[0], &cfg, cfg_size);
	reverse_array(&data_buf[1], cfg_size - 1);

	memset(&data_buf[cfg_size], SC18IS606_DUMMY_DATA, read_len);

	ret = sc18is606_spi_transfer(SPI_WRITE, bus, addr, function_id, data_buf,
				     cfg_size + read_len);
	if (ret != true) {
		LOG_ERR("SPI read data fail");
		return ret;
	}

	memset(data_buf, 0, cfg_size + read_len);
	ret = sc18is606_spi_transfer(SPI_READ, bus, addr, function_id, data_buf,
				     cfg_size + read_len);
	if (ret != true) {
		LOG_ERR("Read data from buffer fail");
		return ret;
	}

	memcpy(read_buf, &data_buf[cfg_size], read_len);
	return true;
}

bool sc18is606_fw_update(uint8_t bus, uint8_t addr, uint8_t function_id, uint32_t offset,
			 uint8_t *write_buf, uint16_t write_len)
{
	CHECK_NULL_ARG_WITH_RETURN(write_buf, false);

	bool ret = false;
	uint16_t index = 0;
	uint8_t read_buf[write_len];
	memset(read_buf, 0, write_len);

	ret = sc18is606_wait_flash_idle(bus, addr, function_id);
	if (ret != true) {
		LOG_ERR("Wait flash idle before writing fail, bus: 0x%x, addr: 0x%x, function id: 0x%x",
			bus, addr, function_id);
		return ret;
	}

	ret = sc18is606_spi_write(bus, addr, function_id, offset, write_buf, write_len);
	if (ret != true) {
		LOG_ERR("SPI write fail, bus: 0x%x, addr: 0x%x, function id: 0x%x, offset: 0x%x",
			bus, addr, function_id, offset);
		return ret;
	}

	ret = sc18is606_wait_flash_idle(bus, addr, function_id);
	if (ret != true) {
		LOG_ERR("Wait flash idle after writing fail, bus: 0x%x, addr: 0x%x, function id: 0x%x",
			bus, addr, function_id);
		return ret;
	}

	ret = sc18is606_spi_read(bus, addr, function_id, offset, read_buf, write_len);
	if (ret != true) {
		LOG_ERR("SPI read fail, bus: 0x%x, addr: 0x%x, function id: 0x%x, offset: 0x%x",
			bus, addr, function_id, offset);
		return ret;
	}

	if (memcmp(write_buf, read_buf, write_len) != 0) {
		LOG_ERR("Write data and read data is not match, bus: 0x%x, addr: 0x%x, function id: 0x%x, offset: 0x%x",
			bus, addr, function_id, offset);

		for (index = 0; index < write_len; ++index) {
			if (write_buf[index] != read_buf[index]) {
				LOG_ERR("index: 0x%x, write_data [0x%x] != read_data [0x%x]", index,
					write_buf[index], read_buf[index]);
			}
		}
		return false;
	}

	return ret;
}
