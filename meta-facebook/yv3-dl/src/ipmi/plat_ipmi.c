#include "plat_ipmi.h"

#include <stdio.h>
#include <stdlib.h>

#include "hal_gpio.h"
#include "libutil.h"
#include "ipmi.h"
#include "oem_1s_handler.h"
#include "plat_class.h"
#include "plat_ipmb.h"
#include "plat_gpio.h"
#include "pmbus.h"
#include "plat_sensor_table.h"
#include "util_sys.h"
#include "isl69254iraz_t.h"
#include "xdpe12284c.h"

void OEM_1S_GET_FW_VERSION(ipmi_msg *msg)
{
	if (msg == NULL) {
		return;
	}

	if (msg->data_len != 1) {
		msg->completion_code = CC_INVALID_LENGTH;
		return;
	}

	uint8_t component = msg->data[0];
	ipmb_error status;
	ipmi_msg *bridge_msg;
	I2C_MSG i2c_msg;
	uint8_t retry = 3;

	switch (component) {
	case DL_COMPNT_CPLD:
		msg->completion_code = CC_UNSPECIFIED_ERROR;
		break;
	case DL_COMPNT_BIC:
		msg->data[0] = FIRMWARE_REVISION_1;
		msg->data[1] = FIRMWARE_REVISION_2;
		msg->data_len = 2;
		msg->completion_code = CC_SUCCESS;
		break;
	case DL_COMPNT_ME:
		bridge_msg = (ipmi_msg *)malloc(sizeof(ipmi_msg));
		if (bridge_msg == NULL) {
			msg->completion_code = CC_OUT_OF_SPACE;
			return;
		}
		bridge_msg->data_len = 0;
		bridge_msg->seq_source = 0xff;
		bridge_msg->InF_source = SELF;
		bridge_msg->InF_target = ME_IPMB;
		bridge_msg->netfn = NETFN_APP_REQ;
		bridge_msg->cmd = CMD_APP_GET_DEVICE_ID;

		status = ipmb_read(bridge_msg, IPMB_inf_index_map[bridge_msg->InF_target]);
		if (status != IPMB_ERROR_SUCCESS) {
			printf("ipmb read fail status: %x", status);
			SAFE_FREE(bridge_msg);
			msg->completion_code = CC_BRIDGE_MSG_ERR;
			return;
		} else {
			msg->data[0] = bridge_msg->data[2] & 0x7F;
			msg->data[1] = bridge_msg->data[3] >> 4;
			msg->data[2] = bridge_msg->data[3] & 0x0F;
			msg->data[3] = bridge_msg->data[12];
			msg->data[4] = bridge_msg->data[13] >> 4;
			msg->data_len = 5;
			msg->completion_code = CC_SUCCESS;
			SAFE_FREE(bridge_msg);
		}
		break;
	case DL_COMPNT_PVCCIN:
	case DL_COMPNT_PVCCSA:
	case DL_COMPNT_PVCCIO:
	case DL_COMPNT_P3V3_STBY:
	case DL_COMPNT_PVDDR_ABC:
	case DL_COMPNT_PVDDR_DEF:
		if ((component == DL_COMPNT_PVCCIN) || (component == DL_COMPNT_PVCCSA)) {
			i2c_msg.target_addr = VCCIN_VCCSA_ADDR;
		}
		if ((component == DL_COMPNT_PVCCIO) || (component == DL_COMPNT_P3V3_STBY)) {
			i2c_msg.target_addr = VCCIO_P3V3_STBY_ADDR;
		}
		if (component == DL_COMPNT_PVDDR_ABC) {
			i2c_msg.target_addr = VDDQ_ABC_ADDR;
		}
		if (component == DL_COMPNT_PVDDR_DEF) {
			i2c_msg.target_addr = VDDQ_DEF_ADDR;
		}

		i2c_msg.tx_len = 1;
		i2c_msg.rx_len = 7;
		i2c_msg.bus = I2C_BUS8;
		i2c_msg.data[0] = PMBUS_IC_DEVICE_ID;

		if (i2c_master_read(&i2c_msg, retry)) {
			msg->completion_code = CC_UNSPECIFIED_ERROR;
			return;
		}

		if (memcmp(i2c_msg.data, ISL69254_DEVICE_ID, sizeof(ISL69254_DEVICE_ID)) == 0) {
			/* Renesas isl69254 */

			if (isl69254iraz_t_get_checksum(i2c_msg.bus, i2c_msg.target_addr,
							&(msg->data[0])) == false) {
				msg->completion_code = CC_UNSPECIFIED_ERROR;
				return;
			}

			if (isl69254iraz_t_get_remaining_write(i2c_msg.bus, i2c_msg.target_addr,
							       &(msg->data[4])) == false) {
				msg->completion_code = CC_UNSPECIFIED_ERROR;
				return;
			}

			msg->data[5] = VENDOR_RENESAS;
			msg->data_len = 6;
			msg->completion_code = CC_SUCCESS;

		} else if (memcmp(i2c_msg.data, XDPE12284C_DEVICE_ID,
				  sizeof(XDPE12284C_DEVICE_ID)) == 0) {
			/* Infineon xdpe12284c */
			if (xdpe12284c_get_checksum(i2c_msg.bus, i2c_msg.target_addr,
						    &(msg->data[0])) == false) {
				msg->completion_code = CC_UNSPECIFIED_ERROR;
				return;
			}

			if (xdpe12284c_get_remaining_write(i2c_msg.bus, i2c_msg.target_addr,
							   &(msg->data[4])) == false) {
				msg->completion_code = CC_UNSPECIFIED_ERROR;
				return;
			}

			msg->data[5] = VENDOR_INFINEON;
			msg->data_len = 6;
			msg->completion_code = CC_SUCCESS;
		} else {
			msg->completion_code = CC_UNSPECIFIED_ERROR;
		}
		break;
	default:
		msg->completion_code = CC_UNSPECIFIED_ERROR;
		break;
	}
	return;
}

void OEM_1S_GET_GPIO(ipmi_msg *msg)
{
	if (msg == NULL) {
		return;
	}

	// only input enable status
	if (msg->data_len != 0) {
		msg->completion_code = CC_INVALID_LENGTH;
		return;
	}

	uint8_t eight_bit_value = 0, gpio_value = 0;
	// Bump up the gpio_align_table_length to multiple of 8.
	uint8_t gpio_cnt = gpio_align_table_length + (8 - (gpio_align_table_length % 8));
	uint8_t data_len = gpio_cnt / 8;
	msg->data_len = data_len;
	for (uint8_t i = 0; i < gpio_cnt; i++) {
		if ((gpio_align_t[i] == PVCCIO_CPU) || (gpio_align_t[i] == BMC_HARTBEAT_LED_R)) {
			//pass dummy data to bmc, because AST bic do not have this gpio
			gpio_value = 0;
		} else {
			//if i large than length, fill 0 into the last byte
			gpio_value = (i >= gpio_align_table_length) ? 0 : gpio_get(gpio_align_t[i]);
		}

		// clear temporary variable to avoid return wrong GPIO value
		if (i % 8 == 0) {
			eight_bit_value = 0;
		}

		eight_bit_value = eight_bit_value | (gpio_value << (i % 8));
		msg->data[i / 8] = eight_bit_value;
	}
	msg->completion_code = CC_SUCCESS;

	return;
}

void OEM_1S_GET_GPIO_CONFIG(ipmi_msg *msg)
{
	if (msg == NULL) {
		return;
	}

	// Bump up the gpio_align_table_length to multiple of 8.
	uint8_t gpio_cnt = gpio_align_table_length + (8 - (gpio_align_table_length % 8));
	uint8_t data_len = gpio_cnt / 8;
	if (msg->data_len != data_len) {
		msg->completion_code = CC_INVALID_LENGTH;
		return;
	}

	uint8_t gpio_select_table[data_len];
	uint8_t direction, intr_status, intr_type, trigger_type;
	uint8_t index = 0;
	memcpy(gpio_select_table, &msg->data[0], msg->data_len);
	for (uint8_t i = 0; i < gpio_cnt; i++) {
		if ((i <= gpio_align_table_length) && (gpio_select_table[i / 8] & (1 << (i % 8)))) {
			if ((gpio_align_t[i] == PVCCIO_CPU) ||
			    (gpio_align_t[i] == BMC_HARTBEAT_LED_R)) {
				//pass dummy data to bmc, because AST bic do not have this gpio
				msg->data[index++] = 0x0;
			} else {
				direction =
					get_gpio_direction(gpio_align_t[i]); //GPIO pin direction
				intr_status = get_gpio_interrupt_enable(
					gpio_align_t[i]); //Interrupt enable or disable
				intr_type = get_gpio_interrupt_type(
					gpio_align_t[i]); //Level or Edge trigger
				trigger_type = get_gpio_interrupt_trigger_mode(
					gpio_align_t[i]); //trigger type:both,falling,rising

				msg->data[index++] = direction | (intr_status << 1) |
						     (intr_type << 2) | (trigger_type << 3);
			}
		}
	}
	msg->data_len = index;
	msg->completion_code = CC_SUCCESS;

	return;
}

void OEM_1S_GET_SET_GPIO(ipmi_msg *msg)
{
	if (msg == NULL) {
		return;
	}

	uint8_t completion_code = CC_INVALID_DATA_FIELD;
	uint8_t gpio_num = 0;
	if (msg->data[1] < gpio_align_table_length) {
		gpio_num = gpio_align_t[msg->data[1]];
	} else {
		msg->completion_code = CC_INVALID_DATA_FIELD;
		msg->data_len = 0;
		return;
	}

	if ((gpio_num == PVCCIO_CPU) || (gpio_num == BMC_HARTBEAT_LED_R)) {
		msg->completion_code = CC_NOT_SUPP_IN_CURR_STATE;
		msg->data_len = 0;
		return;
	}

	switch (msg->data[0]) {
	case GET_GPIO_OUTPUT_STATUS:
		if (msg->data_len == 2) {
			msg->data[0] = gpio_num;
			msg->data[1] = gpio_get(gpio_num);
			completion_code = CC_SUCCESS;
		}
		break;
	case SET_GPIO_OUTPUT_STATUS:
		if (msg->data_len == 3) {
			msg->data[0] = gpio_num;
			gpio_conf(gpio_num, GPIO_OUTPUT);
			gpio_set(gpio_num, msg->data[2]);
			msg->data[1] = gpio_get(gpio_num);
			completion_code = CC_SUCCESS;
		}
		break;
	case GET_GPIO_DIRECTION_STATUS:
		if (msg->data_len == 2) {
			msg->data[0] = gpio_num;
			msg->data[1] = get_gpio_direction(gpio_num);
			completion_code = CC_SUCCESS;
		}
		break;
	case SET_GPIO_DIRECTION_STATUS:
		if (msg->data_len == 3) {
			if (msg->data[2]) {
				gpio_conf(gpio_num, GPIO_OUTPUT);
			} else {
				gpio_conf(gpio_num, GPIO_INPUT);
			}
			msg->data[0] = gpio_num;
			msg->data[1] = msg->data[2];
			completion_code = CC_SUCCESS;
		}
		break;
	default:
		printf("[%s] Unknown options(0x%x)", __func__, msg->data[0]);
		break;
	}

	if (completion_code != CC_SUCCESS) {
		msg->data_len = 0;
	} else {
		msg->data_len = 2; // Return GPIO number, status
	}
	msg->completion_code = completion_code;
	return;
}
