#include <stdio.h>
#include <stdlib.h>
#include <drivers/spi_nor.h>
#include "ipmi.h"
#include "plat_ipmi.h"
#include "plat_ipmb.h"
#include "plat_class.h"
#include "libutil.h"

int pal_update_cxl()
{
	const struct device *flash_dev;
	int ret = 0;

	gpio_set(SPI_MASTER_SEL, GPIO_HIGH);
	gpio_set(FM_SPI_MUX_OE_CTL_N, GPIO_LOW);
	flash_dev = device_get_binding("spi1_cs0");
	ret = spi_nor_re_init(flash_dev);
	printf("[%s] ret%d\n", __func__, ret);
	return 0;
}

void OEM_1S_GET_BOARD_ID(ipmi_msg *msg)
{
	if (msg == NULL) {
		printf("%s failed due to parameter *msg is NULL\n", __func__);
		msg->completion_code = CC_UNSPECIFIED_ERROR;
		return;
	}

	if (msg->data_len != 0) {
		msg->completion_code = CC_INVALID_LENGTH;
		return;
	}

	msg->data_len = 1;
	msg->data[0] = get_board_id();
	msg->completion_code = CC_SUCCESS;
}
