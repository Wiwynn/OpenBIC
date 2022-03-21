#include <zephyr.h>
#include <stdlib.h>
#include "ipmi.h"
#include "plat_gpio.h"
#include "plat_func.h"

#define ME_FW_recovery 0x01
#define ME_FW_restore 0x02
#define ME_TO_RECOVERY_DELAY 2000
#define ME_TO_NORMAL_DELAY 8000

enum {
	ME_SET_FAIL = false,
	ME_SET_SUCCESS = true,
};

uint8_t ME_status = ME_INIT_STATUS;

static void set_ME_status(uint8_t ME_CURRENT_STATUS)
{
	if (ME_status != ME_CURRENT_STATUS) {
		ME_status = ME_CURRENT_STATUS;
	}
}

uint8_t get_ME_status()
{
	return ME_status;
}

static bool set_ME_FW_mode(uint8_t ME_FW_mode)
{
	ipmi_msg *me_msg;
	ipmb_error status;

	me_msg = (ipmi_msg *)malloc(sizeof(ipmi_msg));
	if (me_msg == NULL) {
		printk("ME restore msg alloc fail\n");
		return false;
	}

	me_msg->seq_source = 0xFF;
	me_msg->netfn = NETFN_NM_REQ;
	me_msg->cmd = 0xDF; // Get Intel ME FW Capabilities
	me_msg->InF_source = Self_IFs;
	me_msg->InF_target = ME_IPMB_IFs;
	me_msg->data_len = 4;
	me_msg->data[0] = 0x57;
	me_msg->data[1] = 0x01;
	me_msg->data[2] = 0x00;
	me_msg->data[3] = ME_FW_mode;
	status = ipmb_read(me_msg, IPMB_inf_index_map[me_msg->InF_target]);

	if (status != ipmb_error_success) {
		printk("set_ME_FW_mode reach ME fail with status: %x\n", status);
		if (me_msg != NULL) {
			free(me_msg);
		}
		return false;
	}
	if (me_msg != NULL) {
		free(me_msg);
	}
	return true;
}

static bool is_ME_FW_mode(uint8_t ME_FW_mode)
{
	ipmi_msg *me_msg = NULL;
	ipmb_error status = 0xFF;

	me_msg = (ipmi_msg *)malloc(sizeof(ipmi_msg));
	if (me_msg == NULL) {
		printf("ME check ME mode msg alloc fail\n");
		return false;
	}

	me_msg->seq_source = 0xFF;
	me_msg->netfn = NETFN_APP_REQ;
	me_msg->cmd = CMD_APP_GET_SELFTEST_RESULTS;
	me_msg->InF_source = Self_IFs;
	me_msg->InF_target = ME_IPMB_IFs;
	me_msg->data_len = 0;
	status = ipmb_read(me_msg, IPMB_inf_index_map[me_msg->InF_target]);
	if (status == ipmb_error_success) {
		if (me_msg->data_len == 2) {
			// According to ME spec
			// if ME at restore mode, the self-test result is 55 00
			// if ME at recovery mode, the self-test result is 81 02
			if (((ME_FW_mode == ME_FW_recovery) && (me_msg->data[0] == 0x81) &&
			     (me_msg->data[1] == 0x02)) ||
			    ((ME_FW_mode == ME_FW_restore) && (me_msg->data[0] == 0x55) &&
			     (me_msg->data[1] == 0x00))) {
				if (me_msg != NULL) {
					free(me_msg);
				}
				return true;
			} else {
				printf("ME check ME FW mode fail: mode %x data %x %x\n", ME_FW_mode,
				       me_msg->data[0], me_msg->data[1]);
			}
		}
	} else {
		printf("ME get selftest fail with status: %x mode : %x\n", status, ME_FW_mode);
	}
	if (me_msg != NULL) {
		free(me_msg);
	}
	return false;
}

static void ME_enter_restore()
{
	uint8_t retry = 3;
	if (set_ME_FW_mode(ME_FW_restore) == ME_SET_SUCCESS) {
		k_msleep(ME_TO_NORMAL_DELAY);
		for (int i = 0; i < retry; i++) {
			if (is_ME_FW_mode(ME_FW_restore) == true) {
				set_ME_status(ME_NORMAL_STATUS);
				return;
			} else {
				k_msleep(1000);
			}
		}
	}
}

static void ME_enter_recovery()
{
	uint8_t retry = 3;
	set_ME_status(ME_RECOVERY_STATUS);

	for (int i = 0; i < retry; i++) {
		if (set_ME_FW_mode(ME_FW_recovery) == ME_SET_SUCCESS) {
			k_msleep(ME_TO_RECOVERY_DELAY);
			if (is_ME_FW_mode(ME_FW_recovery) == true) {
				return;
			}
		} else {
			k_msleep(10);
		}
	}
}

void set_ME_restore()
{
	if (is_ME_FW_mode(ME_FW_recovery) == true) {
		ME_enter_restore();
		return;
	}
	set_ME_status(ME_NORMAL_STATUS);
}

void pal_warm_reset_prepare()
{
	ME_enter_recovery();
}

void pal_cold_reset_prepare()
{
	ME_enter_recovery();
}

/* BMC reset */
void BMC_reset_handler()
{
	gpio_set(RST_BMC_R_N, GPIO_LOW);
	k_msleep(10);
	gpio_set(RST_BMC_R_N, GPIO_HIGH);
}

K_WORK_DELAYABLE_DEFINE(BMC_reset_work, BMC_reset_handler);
void submit_bmc_warm_reset()
{
	k_work_schedule(&BMC_reset_work, K_MSEC(1000));
}
/* BMC reset */
