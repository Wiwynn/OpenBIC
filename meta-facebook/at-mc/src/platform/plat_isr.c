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

#include <string.h>
#include <logging/log.h>
#include "libutil.h"
#include "common_i2c_mux.h"
#include "i2c-mux-pca984x.h"
#include "plat_i2c.h"
#include "plat_fru.h"
#include "plat_sensor_table.h"

LOG_MODULE_REGISTER(plat_isr);

void cxl_device_reset()
{
	int ret = 0;
	uint8_t retry = 5;
	I2C_MSG msg = { 0 };
	msg.bus = I2C_BUS2;
	msg.target_addr = CXL_IOEXP_U15_ADDR;
	msg.rx_len = 1;
	msg.tx_len = 1;
	msg.data[0] = 0x02;

	/** read cxl u15 ioexp r2 status **/
	ret = i2c_master_read(&msg, retry);
	if (ret) {
		LOG_ERR("unable to read ioexp bus%u addr0x%02x", msg.bus, msg.target_addr);
		return;
	}

	/** button press **/
	uint8_t b2_high = msg.data[0] | BIT(2);
	uint8_t b2_low = msg.data[0] & ~BIT(2);

	msg.tx_len = 2;
	msg.data[0] = 0x02;
	msg.data[1] = b2_high;
	ret = i2c_master_write(&msg, retry);
	if (ret) {
		LOG_ERR("unable to read ioexp bus%u addr0x%02x", msg.bus, msg.target_addr);
		return;
	}

	msg.tx_len = 2;
	msg.data[0] = 0x02;
	msg.data[1] = b2_low;
	ret = i2c_master_write(&msg, retry);
	if (ret) {
		LOG_ERR("unable to read ioexp bus%u addr0x%02x", msg.bus, msg.target_addr);
		return;
	}
	k_sleep(K_MSEC(1));

	msg.tx_len = 2;
	msg.data[0] = 0x02;
	msg.data[1] = b2_high;
	ret = i2c_master_write(&msg, retry);
	if (ret) {
		LOG_ERR("unable to read ioexp bus%u addr0x%02x", msg.bus, msg.target_addr);
		return;
	}
}

void cxl_device_reset_examine()
{
	int ret = 0;
	uint8_t retry = 5;
	I2C_MSG msg = { 0 };
	msg.bus = I2C_BUS2;
	msg.target_addr = CXL_IOEXP_U17_ADDR;
	msg.rx_len = 1;
	msg.tx_len = 1;
	msg.data[0] = 0x00;

	/** read cxl u17 ioexp r0 status **/
	ret = i2c_master_read(&msg, retry);
	if (ret) {
		LOG_ERR("unable to read ioexp bus%u addr0x%02x", msg.bus, msg.target_addr);
		return;
	}

	/** examine condition **/
	if ((msg.data[0] & 0x0F) == 0x0F) {
		cxl_device_reset();
	}
}

void cxl_pe_reset_control()
{
	int ret = 0;
	uint8_t retry = 5;
	I2C_MSG msg = { 0 };
	msg.bus = I2C_BUS2;
	msg.target_addr = CXL_IOEXP_U15_ADDR;
	msg.rx_len = 1;
	msg.tx_len = 1;
	msg.data[0] = 0x00;

	/** read cxl u15 ioexp r0 status **/
	ret = i2c_master_read(&msg, retry);
	if (ret) {
		LOG_ERR("unable to read ioexp bus%u addr0x%02x", msg.bus, msg.target_addr);
		return;
	}

	uint8_t r0 = msg.data[0];
	uint8_t r0_p0 = r0 & BIT(0);

	msg.rx_len = 1;
	msg.tx_len = 1;
	msg.data[0] = 0x02;

	/** read cxl u15 ioexp r2 status **/
	ret = i2c_master_read(&msg, retry);
	if (ret) {
		LOG_ERR("unable to read ioexp bus%u addr0x%02x", msg.bus, msg.target_addr);
		return;
	}

	msg.rx_len = 1;
	msg.tx_len = 2;
	msg.data[0] = 0x02;
	/** replace r2-bit6 from r0-bit0 **/
	if (r0_p0) {
		msg.data[1] = r0 & ~BIT(6);
	} else {
		msg.data[1] = r0 | BIT(6);
	}

	ret = i2c_master_write(&msg, retry);
	if (ret) {
		LOG_ERR("unable to read ioexp bus%u addr0x%02x", msg.bus, msg.target_addr);
		return;
	}
}

void cxl_ioexp_alert(uint8_t alert_source)
{
	/** meb mux for cxl channels **/
	mux_config meb_mux = { 0 };
	meb_mux.bus = I2C_BUS2;
	meb_mux.target_addr = CXL_FRU_MUX0_ADDR;
	meb_mux.channel = alert_source;
	
	/** cxl mux for sensor channels **/
	mux_config cxl_mux = { 0 };
	cxl_mux.bus = I2C_BUS2;
	cxl_mux.target_addr = CXL_FRU_MUX1_ADDR;
	cxl_mux.channel = CXL_IOEXP_MUX_CHANNEL;

	struct k_mutex *meb_mutex = get_i2c_mux_mutex(meb_mux.bus);

	/** mutex lock bus **/
	if(k_mutex_lock(meb_mutex, K_MSEC(5000))) {
		LOG_ERR("mutex locked failed bus%u", meb_mux.bus);
		return;
	}

	/** enable mux channel **/
	if (!set_mux_channel(meb_mux)) {
		k_mutex_unlock(meb_mutex);
		return;
	}

	if (!set_mux_channel(cxl_mux)) {
		k_mutex_unlock(meb_mutex);
		return;
	}

	/** execution **/
	cxl_device_reset_examine();
	cxl_pe_reset_control();

	/** mutex unlock bus **/
	k_mutex_unlock(meb_mutex);
}

void cxl_ioexp_alert0()
{
	cxl_ioexp_alert(PCA9848_CHANNEL_0);
}

void cxl_ioexp_alert1()
{
	cxl_ioexp_alert(PCA9848_CHANNEL_1);
}

void cxl_ioexp_alert2()
{
	cxl_ioexp_alert(PCA9848_CHANNEL_2);
}

void cxl_ioexp_alert3()
{
	cxl_ioexp_alert(PCA9848_CHANNEL_3);
}

void cxl_ioexp_alert4()
{
	cxl_ioexp_alert(PCA9848_CHANNEL_4);
}

void cxl_ioexp_alert5()
{
	cxl_ioexp_alert(PCA9848_CHANNEL_5);
}

void cxl_ioexp_alert6()
{
	cxl_ioexp_alert(PCA9848_CHANNEL_6);
}

void cxl_ioexp_alert7()
{
	cxl_ioexp_alert(PCA9848_CHANNEL_7);
}
