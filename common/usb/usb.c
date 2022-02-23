#include <device.h>
#include <drivers/uart.h>
#include <usb/usb_device.h>
#include <logging/log.h>
#include <sys/ring_buffer.h>
#include "ipmi.h"
#include "usb.h"

RING_BUF_DECLARE(ringbuf, RING_BUF_SIZE);

static struct k_sem usbhandle_sem;
static const struct device *dev;

struct k_thread usb_thread;
K_KERNEL_STACK_MEMBER(usb_handler_stack, USB_HANDLER_STACK_SIZE);

static inline void try_ipmi_message(ipmi_msg_cfg *current_msg, int retry)
{
	if (current_msg == NULL) {
		return;
	}

	for (/*retry*/; k_msgq_put(&ipmi_msgq, current_msg, K_NO_WAIT) != 0 && retry >= 0;
	     retry--) {
		k_msgq_purge(&ipmi_msgq);
		printf("USB retrying put ipmi msgq\n");
	}
}

void handle_usb_data(uint8_t *rx_buff, int rx_len)
{
	if (rx_buff == NULL) {
		return;
	}

	uint16_t record_offset;
	static ipmi_msg_cfg current_msg;
	static bool fwupdate_keep_data = false;
	static uint16_t keep_data_len = 0;
	static uint16_t fwupdate_data_len = 0;

	if (DEBUG_USB) {
		printf("USB: len %d, req: %x %x ID: %x %x %x target: %x offset: %x %x %x %x len: %x %x\n",
		       rx_len, rx_buff[0], rx_buff[1], rx_buff[2], rx_buff[3], rx_buff[4],
		       rx_buff[5], rx_buff[6], rx_buff[7], rx_buff[8], rx_buff[9], rx_buff[10],
		       rx_buff[11]);
	}

	// USB driver must receive 64 byte package from bmc
	// it takes 512 + 64 byte package to receive ipmi command + 512 byte image data
	// if cmd fw_update, record next usb package as image until receive complete data
	if ((rx_buff[0] == (NETFN_OEM_1S_REQ << 2)) && (rx_buff[1] == CMD_OEM_1S_FW_UPDATE)) {
		fwupdate_keep_data = true;
	}

	if (fwupdate_keep_data) {
		if ((keep_data_len + rx_len) > IPMI_DATA_MAX_LENGTH) {
			printf("usb fw update recv data over ipmi buff size %d, keep %d, recv %d\n",
			       IPMI_DATA_MAX_LENGTH, keep_data_len, rx_len);
			keep_data_len = 0;
			fwupdate_keep_data = false;
			return;
		} else if (!keep_data_len) { // only fill up ipmb buffer from first package
			current_msg.buffer.netfn = rx_buff[0] >> 2;
			current_msg.buffer.cmd = rx_buff[1];
			current_msg.buffer.InF_source = BMC_USB;
			current_msg.buffer.data_len = rx_len - SIZE_NETFN_CMD;
			fwupdate_data_len = ((rx_buff[11] << 8) | rx_buff[10]);
			memcpy(&current_msg.buffer.data[0], &rx_buff[SIZE_NETFN_CMD],
			       (rx_len - SIZE_NETFN_CMD));
			keep_data_len = rx_len - FWUPDATE_HEADER_SIZE;
		} else {
			record_offset = keep_data_len + FWUPDATE_HEADER_SIZE - SIZE_NETFN_CMD;
			memcpy(&current_msg.buffer.data[record_offset], &rx_buff[0], rx_len);
			current_msg.buffer.data_len += rx_len;
			keep_data_len += rx_len;
		}
		if (keep_data_len == fwupdate_data_len) {
			try_ipmi_message(&current_msg, 3);
			keep_data_len = 0;
			fwupdate_data_len = 0;
			fwupdate_keep_data = false;
		}
	} else {
		current_msg.buffer.netfn = rx_buff[0] >> 2;
		current_msg.buffer.cmd = rx_buff[1];
		current_msg.buffer.InF_source = BMC_USB;
		current_msg.buffer.data_len = rx_len - SIZE_NETFN_CMD;
		memcpy(&current_msg.buffer.data[0], &rx_buff[2], current_msg.buffer.data_len);
		try_ipmi_message(&current_msg, 3);
	}

	return;
}

void usb_write_by_ipmi(ipmi_msg *ipmi_resp)
{
	if (ipmi_resp == NULL) {
		return;
	}

	uint8_t tx_buf[RX_BUFF_SIZE];
	struct ipmi_response *resp = (struct ipmi_response *)tx_buf;

	pack_ipmi_resp(resp, ipmi_resp);

	if (DEBUG_USB) {
		int i;
		printf("usb resp: %x %x %x, ", resp->netfn, resp->cmd, resp->cmplt_code);
		for (i = 0; i < ipmi_resp->data_len; i++)
			printf("0x%x ", resp->data[i]);
		printf("\n");
	}
	uart_fifo_fill(dev, tx_buf,
		       ipmi_resp->data_len + 3); // return netfn + cmd + comltcode + data
}

static void usb_handler(void *arug0, void *arug1, void *arug2)
{
	ARG_UNUSED(arug0);
	ARG_UNUSED(arug1);
	ARG_UNUSED(arug2);
	
	uint8_t rx_buff[RX_BUFF_SIZE];
	int rx_len;
	int i;

	while (1) {
		k_sem_take(&usbhandle_sem, K_FOREVER);
		rx_len = ring_buf_get(&ringbuf, rx_buff, sizeof(rx_buff));
		if (!rx_len) {
			k_msleep(10);
			continue;
		}

		if (DEBUG_USB) {
			printf("Print Data: ");
			for (i = 0; i < rx_len; i++)
				printf("0x%x ", rx_buff[i]);
			printf("\n");
		}
		handle_usb_data(rx_buff, rx_len);
	}
}

static void interrupt_handler(const struct device *dev, void *user_data)
{
	uint8_t rx_buff[RX_BUFF_SIZE];
	int recv_len, rx_len;

	ARG_UNUSED(user_data);

	while (uart_irq_is_pending(dev) && uart_irq_rx_ready(dev)) {
		recv_len = uart_fifo_read(dev, rx_buff, sizeof(rx_buff));

		if (recv_len) {
			rx_len = ring_buf_put(&ringbuf, rx_buff, recv_len);
			if (rx_len < recv_len) {
				printf("Drop %u bytes\n", recv_len - rx_len);
			} else {
				k_sem_give(&usbhandle_sem);
			}
		}
	}
}

void usb_dev_init(void)
{
	int ret;

	ret = usb_enable(NULL);
	if (ret) {
		printf("Failed to enable USB");
		return;
	}

	dev = device_get_binding("CDC_ACM_0");
	if (!dev) {
		printf("CDC ACM device not found");
		return;
	}

	uart_irq_callback_set(dev, interrupt_handler);

	/* Enable rx interrupts */
	uart_irq_rx_enable(dev);

	k_thread_create(&usb_thread, usb_handler_stack, K_THREAD_STACK_SIZEOF(usb_handler_stack),
			usb_handler, NULL, NULL, NULL, CONFIG_MAIN_THREAD_PRIORITY, 0, K_NO_WAIT);
	k_thread_name_set(&usb_thread, "USB_handler");

	uint8_t init_sem_count = RING_BUF_SIZE / RX_BUFF_SIZE;
	k_sem_init(&usbhandle_sem, 0, init_sem_count);
}
