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

#include <logging/log.h>
#include "libipmi.h"
#include "kcs.h"
#include "rg3mxxb12.h"
#include "power_status.h"
#include "sensor.h"
#include "snoop.h"
#include "apml.h"
#include "hal_gpio.h"
#include "hal_i2c.h"
#include "hal_i3c.h"
#include "util_sys.h"
#include "util_worker.h"
#include "plat_gpio.h"
#include "plat_class.h"
#include "plat_sensor_table.h"
#include "plat_i2c.h"
#include "plat_mctp.h"
#include "plat_apml.h"
#include "plat_i3c.h"
#include "plat_isr.h"
#include "plat_dimm.h"

LOG_MODULE_REGISTER(plat_isr, LOG_LEVEL_DBG);

/*
 *	TODO: I3C hub is supplied by DC power currently. When DC off, it can't be initialized.
 *  	  Therefore, BIC needs to implement a workaround to reinitialize the I3C hub during DC on.
 *        This part will be removed after the hardware design be modified.
 */
void reinit_i3c_hub()
{
	// i3c master initial
	I3C_MSG i3c_msg = { 0 };
	i3c_msg.bus = I3C_BUS_HUB;
	i3c_msg.target_addr = I3C_ADDR_HUB;

	const int rstdaa_count = 2;
	int ret = 0;

	for (int i = 0; i < rstdaa_count; i++) {
		ret = i3c_brocast_ccc(&i3c_msg, I3C_CCC_RSTDAA, I3C_BROADCAST_ADDR);
		if (ret != 0) {
			printf("Error to reset daa. count = %d\n", i);
		}
	}

	ret = i3c_brocast_ccc(&i3c_msg, I3C_CCC_SETAASA, I3C_BROADCAST_ADDR);
	if (ret != 0) {
		printf("Error to set daa\n");
	}

	i3c_attach(&i3c_msg);

	// Initialize I3C HUB
	if (!rg3mxxb12_i3c_mode_only_init(&i3c_msg, LDO_VOLT)) {
		printk("failed to initialize 1ou rg3mxxb12\n");
	}

	// Set FF/WF's EID
	send_cmd_to_dev_handler(NULL);
}

void switch_i3c_dimm_mux_to_cpu()
{
	switch_i3c_dimm_mux(I3C_MUX_CPU_TO_DIMM);
}

K_WORK_DELAYABLE_DEFINE(set_DC_on_5s_work, set_DC_on_delayed_status);
K_WORK_DEFINE(reinit_i3c_work, reinit_i3c_hub);
K_WORK_DEFINE(switch_i3c_dimm_work, switch_i3c_dimm_mux_to_cpu);

#define DC_ON_5_SECOND 5
void ISR_DC_ON()
{
	set_DC_status(PWRGD_CPU_LVC3);

	bool dc_status = get_DC_status();

	if (dc_status) {
		k_work_schedule(&set_DC_on_5s_work, K_SECONDS(DC_ON_5_SECOND));
		k_work_submit(&reinit_i3c_work);
		k_work_submit(&switch_i3c_dimm_work);
	} else {
		set_DC_on_delayed_status();
	}
}

void ISR_POST_COMPLETE()
{
	set_post_status(FM_BIOS_POST_CMPLT_BIC_N);

	pal_check_sbrmi_command_code_length();

	if (get_post_status()) {
		set_tsi_threshold();
		read_cpuid();
	} else {
		if (get_DC_status()) { // Host is reset
			k_work_submit(&switch_i3c_dimm_work);
		}
	}
}

void ISR_BMC_READY()
{
	sync_bmc_ready_pin();
}


// #define FATAL_ERROR_DELAY_MSECOND 500
// typedef struct {
// 	struct k_work_delayable work;
// 	uint8_t ras_status;
// } fatal_error_work_info;

// static void send_apml_alert(struct k_work *work)
// {
// 	fatal_error_work_info *work_info = CONTAINER_OF(work, fatal_error_work_info, work);
// 	if (get_DC_status()) {
// 		LOG_INF("Send apml alert to bmc.");

// 		common_addsel_msg_t sel_msg;
// 		sel_msg.InF_target = BMC_IPMB;
// 		sel_msg.sensor_type = IPMI_OEM_SENSOR_TYPE_SYS_STA;
// 		sel_msg.sensor_number = SENSOR_NUM_SYSTEM_STATUS;
// 		sel_msg.event_type = IPMI_EVENT_TYPE_SENSOR_SPECIFIC;
// 		sel_msg.event_data1 = IPMI_OEM_EVENT_OFFSET_AMD_ALERT_L;
// 		sel_msg.event_data2 = work_info->ras_status;
// 		sel_msg.event_data3 = 0xFF;
// 		if (!common_add_sel_evt_record(&sel_msg)) {
// 			LOG_ERR("Failed to assert ALERT_L event log.");
// 		}

// 		send_apml_alert_to_bmc(work_info->ras_status);
// 	}
// 	SAFE_FREE(work_info);
// }

// void ISR_APML_ALERT()
// {
// 	LOG_WRN("APML ALERT RECEIVE!!");
// 	uint8_t ras_status;
// 	if (apml_read_byte(APML_BUS, SB_RMI_ADDR, SBRMI_RAS_STATUS, &ras_status)) {
// 		LOG_ERR("Failed to read RAS status.");
// 		return;
// 	}

// 	if (ras_status) {
// 		LOG_WRN("Fatal error happened, ras_status 0x%x.", ras_status);
// 		fatal_error_happened();

// 		if (apml_write_byte(APML_BUS, SB_RMI_ADDR, SBRMI_RAS_STATUS, ras_status))
// 			LOG_ERR("Failed to clear ras_status.");

// 		uint8_t status;
// 		if (apml_read_byte(APML_BUS, SB_RMI_ADDR, SBRMI_STATUS, &status))
// 			LOG_ERR("Failed to read RMI status.");

// 		if ((status & 0x02) && (apml_write_byte(APML_BUS, SB_RMI_ADDR, SBRMI_STATUS, 0x02)))
// 			LOG_ERR("Failed to clear SwAlertSts.");

// 		fatal_error_work_info *delay_work = malloc(sizeof(fatal_error_work_info));
// 		if (delay_work == NULL) {
// 			LOG_ERR("Failed to allocate delay_job.");
// 			return;
// 		}
// 		memset(delay_work, 0, sizeof(fatal_error_work_info));

// 		delay_work->ras_status = ras_status;
// 		k_work_init_delayable(&(delay_work->work), send_apml_alert);
// 		k_work_schedule(&(delay_work->work), K_MSEC(FATAL_ERROR_DELAY_MSECOND));
// 	}
// }
