#include <zephyr.h>
#include <stdio.h>
#include <string.h>
#include "plat_isr.h"
#include "power_status.h"
#include "plat_gpio.h"
#include "plat_power_seq.h"

#define POWER_SEQ_CTRL_STACK_SIZE 1000

K_THREAD_STACK_DEFINE(power_thread, POWER_SEQ_CTRL_STACK_SIZE);
struct k_thread power_thread_handler;
k_tid_t power_tid;

void ISR_CL_DC_ON()
{
	set_CL_DC_status(FM_POWER_EN);
	control_power_sequence();
}

void ISR_DC_ON()
{
	set_DC_status(PWRGD_CARD_PWROK);
}

void ISR_DEV_RST()
{
	if (gpio_get(ASIC_DEV_RST_N) == DEVICE_ENABLED) {
		// Enable i2c synchronized during error recovery/uart/ASIC i2c pin
		gpio_set(I2CS_SRSTB_GPIO, DEVICE_ENABLED);
		gpio_set(FM_ISOLATED_EN_N, DEVICE_ENABLED);
		gpio_set(LSFT_SMB_DIMM_EN, DEVICE_ENABLED);
	} else {
		// Disable i2c synchronized during error recovery/uart/ASIC i2c pin
		gpio_set(I2CS_SRSTB_GPIO, DEVICE_DISABLED);
		gpio_set(FM_ISOLATED_EN_N, DEVICE_DISABLED);
		gpio_set(LSFT_SMB_DIMM_EN, DEVICE_DISABLED);
	}
}

void ISR_MB_RST()
{
	if (gpio_get(RST_MB_N) == DEVICE_ENABLED) {
		// Enable ASIC reset pin
		gpio_set(ASIC_PERST0_N, DEVICE_ENABLED);
	} else {
		// Disable ASIC reset pin
		gpio_set(ASIC_PERST0_N, DEVICE_DISABLED);
	}
}

void control_power_sequence()
{
	if (gpio_get(FM_POWER_EN) == POWER_ON) { // CraterLake DC on
		if (gpio_get(PWRGD_CARD_PWROK) == POWER_ON) {
			// If the last stage of power on sequence already power on , no need to recheck power on sequence
			// Update the flag of power on sequence number
			set_power_on_seq(POWER_STAGE_NUM);
		} else {
			// If power on sequence not finished or not started , abort power off thread before creating power on thread
			abort_power_thread();
			init_power_on_thread();
		}
	} else { // CraterLake DC off
		if (gpio_get(CLK_100M_OSC_EN) == DEVICE_DISABLED) {
			// If the last stage of power off sequence already power off , no need to recheck power off sequence
			// Update the flag of power off sequence number
			set_power_off_seq(0);
		} else {
			// If power off sequence not finished or not started , abort power on thread before creating power off thread
			abort_power_thread();
			init_power_off_thread();
		}
	}
}

void init_power_on_thread()
{
	// Avoid re-create thread by checking thread status and thread id
	if (power_tid != NULL && strcmp(k_thread_state_str(power_tid), "dead") != 0) {
		return;
	}
	power_tid = k_thread_create(&power_thread_handler, power_thread,
				    K_THREAD_STACK_SIZEOF(power_thread), control_power_on_sequence,
				    NULL, NULL, NULL, CONFIG_MAIN_THREAD_PRIORITY, 0, K_NO_WAIT);
	k_thread_name_set(&power_thread_handler, "power_on_sequence_thread");
}

void init_power_off_thread()
{
	// Avoid re-create thread by checking thread status and thread id
	if (power_tid != NULL && strcmp(k_thread_state_str(power_tid), "dead") != 0) {
		return;
	}
	power_tid = k_thread_create(&power_thread_handler, power_thread,
				    K_THREAD_STACK_SIZEOF(power_thread), control_power_off_sequence,
				    NULL, NULL, NULL, CONFIG_MAIN_THREAD_PRIORITY, 0, K_NO_WAIT);
	k_thread_name_set(&power_thread_handler, "power_off_sequence_thread");
}

void abort_power_thread()
{
	if (power_tid != NULL && strcmp(k_thread_state_str(power_tid), "dead") != 0) {
		k_thread_abort(power_tid);
	}
}
