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

#include "plat_class.h"
#include "plat_i2c.h"
#include "hal_i2c.h"
#include "util_spi.h"
#include "hal_gpio.h"
#include <drivers/spi_nor.h>

#define CPLD_ADDR 0x21
#define CPLD_SPI_OOB_CONTROL_REG 0x0B
#define CPLD_SPI_OOB_FROM_CPU 0x02
#define CPLD_SPI_OOB_FROM_BIC 0x0B

#define SPI_BASE 0x7e630000
#define CE0_CTRL_REG 0x10
#define CE1_CTRL_REG 0x14
#define SPI_CTRL_FREQ_MASK          0x0F000F00

int pal_get_bios_flash_position()
{
	return DEVSPI_SPI1_CS0;
}

int pal_get_prot_flash_position()
{
	return DEVSPI_SPI2_CS0;
}

bool pal_switch_bios_spi_mux(int gpio_status)
{
	uint8_t retry = 5;
	I2C_MSG msg;

	msg.bus = I2C_BUS1;
	msg.target_addr = CPLD_ADDR;
	msg.tx_len = 2;
	msg.data[0] = CPLD_SPI_OOB_CONTROL_REG;
	if (gpio_status == GPIO_HIGH) {
		msg.data[1] = CPLD_SPI_OOB_FROM_BIC;
	} else {
		msg.data[1] = CPLD_SPI_OOB_FROM_CPU;
	}

	if (i2c_master_write(&msg, retry)) {
		return false;
	}
	return true;
}

int pal_spi_initialization(const struct device *dev)
{
	int ret = spi_nor_re_init(dev);
	if (ret) {
		printk("%s Wiwynn Debug %d\n", __func__, __LINE__);
		return ret;
	}
	/* Workaround:
	 * HD BIC speed down the SPI1/2 freqency to 30MHz
	 * if the ADI MUX is on system.
	 * Judgement conditions:
	 * 1. The Halfdome server board revision is POC or EVB.
	 * 2. The PRoT module is present.(GPIOC6, AUTH_PRSNT_BIC_N is low)
	 * If meet both 1 and 2 conditions,
	 * SPI1/2 need to down speed to 30MHz.
	 */
	uint8_t server_board_revision = get_board_revision();
	bool prot_present = get_prot_present();
	if ((server_board_revision == SYS_BOARD_POC) || (server_board_revision == SYS_BOARD_EVT))
	{
		if (prot_present)
		{
			uint32_t val = sys_read32(SPI_BASE + CE0_CTRL_REG);
			val = (val & (~SPI_CTRL_FREQ_MASK)) | (0 << 24 | 0xC << 8);
			sys_write32(val, SPI_BASE + CE0_CTRL_REG);
			val = sys_read32(SPI_BASE + CE1_CTRL_REG);
			val = (val & (~SPI_CTRL_FREQ_MASK)) | (0 << 24 | 0xC << 8);
			sys_write32(val, SPI_BASE + CE1_CTRL_REG);

			uint32_t val_1 = sys_read32(SPI_BASE + CE0_CTRL_REG);
			uint32_t val_2 = sys_read32(SPI_BASE + CE1_CTRL_REG);
			printk("%s Wiwynn Debug %d SPI10-0x0x%x SPI14-0x0x%x\n", __func__, __LINE__, val_1, val_2);
		}
	}
	return 0;
}
