#ifndef COMMON_I2C_MUX_H
#define COMMON_I2C_MUX_H

#define MUTEX_LOCK_INTERVAL_MS 1000
#define DISABLE_MUX_ALL_CHANNEL_DEFAULT 0

typedef struct _mux_config {
	uint8_t bus;
	uint8_t target_addr;
	uint8_t channel;
} mux_config;

bool init_mutex(struct k_mutex *mutex);
bool set_mux_channel(mux_config mux_cfg);

#endif
