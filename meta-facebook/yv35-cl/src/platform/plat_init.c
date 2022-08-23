#include "hal_gpio.h"
#include "hal_peci.h"
#include "power_status.h"
#include "util_sys.h"
#include "plat_class.h"
#include "plat_gpio.h"
#include "plat_pmic.h"
#include "plat_mctp.h"
#include <stdio.h>

#include <stdlib.h>
#include "hal_i3c.h"
#include "libutil.h"

SCU_CFG scu_cfg[] = {
	//register    value
	{ 0x7e6e2610, 0xffffffff },
	{ 0x7e6e2614, 0xffffffff },
	{ 0x7e6e2618, 0x30000000 },
	{ 0x7e6e261c, 0x00000F04 },
};

void pal_pre_init()
{
	init_platform_config();
	disable_PRDY_interrupt();
	scu_init(scu_cfg, sizeof(scu_cfg) / sizeof(SCU_CFG));
}

void pal_post_init()
{
	int ret;
	I3C_MSG *msg_write = (I3C_MSG *)malloc(sizeof(I3C_MSG));
	msg_write->bus = 0;
	msg_write->tx_len = 255;
	for (int i = 0; i <= msg_write->tx_len; ++i) {
		msg_write->data[i] = msg_write->tx_len - i;
	}

	k_msleep(120000);

	ret = i3c_smq_write(msg_write);
	printf("[%s] i3c_smq_write ret: 0x%02x\n", __func__, ret);

	k_msleep(60000);

	I3C_MSG *msg_read = (I3C_MSG *)malloc(sizeof(I3C_MSG));
	msg_read->bus = 0;
	msg_read->rx_len = 16;
	ret = i3c_smq_read(msg_read);
	printf("[%s] i3c_smq_read ret: 0x%02x\n", __func__, ret);

	//plat_mctp_init();
	printf("[%s] Complete post init \n", __func__);// Debug code
}

void pal_device_init()
{
	init_me_firmware();

	start_monitor_pmic_error_thread();
}

void pal_set_sys_status()
{
	set_DC_status(PWRGD_SYS_PWROK);
	set_DC_on_delayed_status();
	set_DC_off_delayed_status();
	set_post_status(FM_BIOS_POST_CMPLT_BMC_N);
	set_CPU_power_status(PWRGD_CPU_LVC3);
	set_post_thread();
	set_sys_ready_pin(BIC_READY);
}

#define DEF_PROJ_GPIO_PRIORITY 78

DEVICE_DEFINE(PRE_DEF_PROJ_GPIO, "PRE_DEF_PROJ_GPIO_NAME", &gpio_init, NULL, NULL, NULL,
	      POST_KERNEL, DEF_PROJ_GPIO_PRIORITY, NULL);
