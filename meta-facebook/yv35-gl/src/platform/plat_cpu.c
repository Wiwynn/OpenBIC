#include "plat_cpu.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <drivers/peci.h>
#include "intel_peci.h"
#include "ipmi.h"
#include "libipmi.h"
#include "libutil.h"
#include "libutil.h"
#include "hal_peci.h"
#include <logging/log.h>
#include <plat_sensor_table.h>
#include "hal_vw_gpio.h"

LOG_MODULE_REGISTER(pal_cpu);

K_THREAD_STACK_DEFINE(monitor_smiout_stack, MONITOR_SMIOUT_STACK_SIZE);
struct k_thread monitor_smiout_thread;
k_tid_t monitor_smiout_tid;

static uint8_t smi_val;

bool pal_get_cpu_time(uint8_t addr, uint8_t cmd, uint8_t readlen, uint32_t *run_time)
{
	uint8_t writelen = 0x05;
	uint8_t time_buf[4] = { 0x12, 0x1F, 0x00, 0x00 };
	int ret = 0;

	uint8_t *readbuf = (uint8_t *)malloc(readlen * sizeof(uint8_t));
	if (!readbuf) {
		LOG_ERR("Get cpu time fail to allocate readbuf memory");
		return false;
	}

	ret = peci_write(cmd, addr, readlen, readbuf, writelen, time_buf);
	if (ret) {
		LOG_ERR("Get cpu time peci write error");
		goto cleanup;
	}
	if (readbuf[0] != PECI_CC_RSP_SUCCESS) {
		if (readbuf[0] == PECI_CC_ILLEGAL_REQUEST) {
			LOG_ERR("Get cpu time unknown request");
		} else {
			LOG_ERR("Get cpu time peci control hardware, firmware or associated logic error");
		}
		goto cleanup;
	}

	*run_time = readbuf[4];
	*run_time = (*run_time << 8) | readbuf[3];
	*run_time = (*run_time << 8) | readbuf[2];
	*run_time = (*run_time << 8) | readbuf[1];

	SAFE_FREE(readbuf);
	return true;
cleanup:
	SAFE_FREE(readbuf);
	return false;
}

void start_monitor_smi_thread()
{
	LOG_INF("Start thread to monitor SMIOUT");

	monitor_smiout_tid =
		k_thread_create(&monitor_smiout_thread, monitor_smiout_stack,
				K_THREAD_STACK_SIZEOF(monitor_smiout_stack), monitor_smiout_handler,
				NULL, NULL, NULL, CONFIG_MAIN_THREAD_PRIORITY, 0, K_NO_WAIT);
	k_thread_name_set(&monitor_smiout_thread, "monitor_smiout_thread");
}

void monitor_smiout_handler()
{
	time_t t1, t2;
	static bool smi_assert = false;
	common_addsel_msg_t sel_msg;

	sel_msg.InF_target = BMC_IPMB;
	sel_msg.sensor_type = IPMI_OEM_SENSOR_TYPE_SYS_STA;
	sel_msg.sensor_number = SENSOR_NUM_SYSTEM_STATUS;
	sel_msg.event_data1 = IPMI_OEM_EVENT_OFFSET_SYS_SMI90s;
	sel_msg.event_data2 = 0xFF;
	sel_msg.event_data3 = 0xFF;

	while (1) {
		uint32_t sysevt_val = sys_read32(AST_ESPI_BASE + AST_ESPI_SYSEVT);
		smi_val = GETBIT(sysevt_val, SMIOUT_INDEX);

		if ((smi_val == 0) && (smi_assert == false)) {
			t1 = time(NULL);
			while (1) {
				sysevt_val = sys_read32(AST_ESPI_BASE + AST_ESPI_SYSEVT);
				smi_val = GETBIT(sysevt_val, SMIOUT_INDEX);

				if (smi_val == 1) {
					break;
				}

				t2 = time(NULL);
				if ((t2 - t1) >= SMIOUT_TIMEOUT) {
					sel_msg.event_type = IPMI_EVENT_TYPE_SENSOR_SPECIFIC;
					if (!common_add_sel_evt_record(&sel_msg)) {
						LOG_ERR("Failed to add SMIOUT stuck low Assert SEL");
					}
					smi_assert = true;
					break;
				}
			}
		} else if ((smi_val == 1) && (smi_assert == true)) {
			sel_msg.event_type = IPMI_OEM_EVENT_TYPE_DEASSERT;
			if (!common_add_sel_evt_record(&sel_msg)) {
				LOG_ERR("Failed to add SMIOUT stuck low Deassert SEL");
			}
			smi_assert = false;
		} else if ((smi_val == 0) || (smi_val == 1)) {
			k_msleep(MONITOR_SMIOUT_TIME_MS);
		} else {
			LOG_ERR("Unknown status for SMIOUT");
			return;
		}
	}
}

