#include <stdio.h>
#include <stdlib.h>
#include "ipmi.h"
#include "plat_ipmi.h"
#include "plat_ipmb.h"
#include "plat_class.h"
#include "libutil.h"

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
