#include <stdio.h>
#include <logging/log.h>
#include "libutil.h"
#include "hal_i2c.h"
#include "common_i2c_mux.h"

LOG_MODULE_REGISTER(common_i2c_mux);

bool init_mutex(struct k_mutex *mutex)
{
	CHECK_NULL_ARG_WITH_RETURN(mutex, false);

	int mutex_status = 0;
	mutex_status = k_mutex_init(mutex);
	if (mutex_status != 0) {
		LOG_ERR("mutex initial fail, status: %d\n", mutex_status);
		return false;
	}

	return true;
}

bool set_mux_channel(mux_config mux_cfg)
{
	int status = 0;
	int retry = 5;

	/* Set channel */
	I2C_MSG mux_msg = { 0 };
	mux_msg.bus = mux_cfg.bus;
	mux_msg.target_addr = mux_cfg.target_addr;
	mux_msg.tx_len = 1;
	mux_msg.data[0] = mux_cfg.channel;

	status = i2c_master_write(&mux_msg, retry);
	if (status != 0) {
		LOG_ERR("set channel fail, status: %d, bus: %d, addr: 0x%x\n", status, mux_cfg.bus,
			mux_cfg.target_addr);
		return false;
	}

	return true;
}
