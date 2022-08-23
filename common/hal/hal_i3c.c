#include "hal_i3c.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <zephyr.h>
#include <logging/log.h>
#include "libutil.h"

LOG_MODULE_REGISTER(hal_i3c);

static const struct device *dev_i3c[I3C_MAX_DESC_NUM];
static const struct device *dev_i3c_smq[I3C_MAX_DESC_NUM];
static uint8_t data_buffer[I3C_MAX_XFER_NUM][I3C_MAX_BUFF_SIZE];
static uint8_t data_buf[I3C_MAX_BUFF_SIZE];
static struct i3c_dev_desc i3c_desc_table[I3C_MAX_DESC_NUM];
struct k_mutex i3c_mutex[I3C_MAX_DESC_NUM];

static struct i3c_dev_desc *find_matching_desc(const struct device *dev, uint8_t desc_addr)
{
	struct i3c_dev_desc *desc = NULL;
	int i;

	for (i = 0; i < I3C_MAX_DESC_NUM; i++) {
		desc = &i3c_desc_table[i];
		if (desc->master_dev == dev && desc->info.dynamic_addr == desc_addr) {
			break;
		}
	}

	return desc;
}

int i3c_priv_xfer(I3C_MSG *msg, uint8_t retry)
{
	if (!msg) {
		printf("[%s] recevied null msg\n", __func__);
		return -EFAULT;
	}

	/* Initialization */
	const struct device *dev;
	struct i3c_dev_desc *desc = NULL;
	int addr = -1;
	int ret;

	/* Collect necessary data */
	dev = dev_i3c[msg->bus];
	//addr = msg->target_addr;
	desc = find_matching_desc(dev, addr);

	/* Examine data */
	if (addr < 0) {
		printf("[%s] address not assigned\n", __func__);
		return -ENODEV;
	}

	/* Build xfer data and assign address */
	for (int i = 0; i < I3C_MAX_XFER_NUM; i++) {
		if (!i) {
			/* Data for write */
			msg->xfer[i].rnw = 0;
			msg->xfer[i].data.out = data_buffer[i];
			msg->xfer[i].len = msg->tx_len;
			memcpy(&data_buffer[0], &msg->data[0], msg->tx_len);
		} else {
			/* Data for read */
			msg->xfer[i].rnw = 1;
			msg->xfer[i].data.in = data_buffer[i];
			msg->xfer[i].len = msg->rx_len;
		}
	}

	ret = i3c_master_priv_xfer(desc, msg->xfer, I3C_MAX_XFER_NUM);
	if (ret) {
		printf("[%s] failed to private transfer\n", __func__);
		return ret;
	}

	/* Read out */
	for (int i = 0; i < I3C_MAX_XFER_NUM; i++) {
		if (msg->xfer[i].rnw) {
			for (int k = 0; k < msg->rx_len; k++) {
				printf("0x%02x ", *((uint8_t *)(msg->xfer[i].data.out) + k));
				if(k % 16 == 15) {
					printf("\n");
				}
			}
		}
	}

	return ret;
}


int i3c_slave_mqueue_read(const struct device *dev, uint8_t *dest, int budget);
int i3c_slave_mqueue_write(const struct device *dev, uint8_t *src, int size);

/**
 * @brief application dumps i3c message from dts device slave message queue
 * 
 * @param msg i3c message structure
 * @return 0: complete dumping data from smq
 */
int i3c_smq_read(I3C_MSG *msg)
{
	int ret;

	if (!msg) {
		printf("[%s] null msg\n", __func__);
		return -EINVAL;
	}

	if (!dev_i3c[msg->bus]) {
		printf("[%s] bus%u did not define\n", __func__, msg->bus);
		return -ENODEV;
	}

	ret = k_mutex_lock(&i3c_mutex[msg->bus], K_SECONDS(1));
	if (ret) {
		printf("[%s] k_mutex bus%u locked failed, ret: %d\n", __func__, msg->bus, ret);
		return ret;
	}

	ret = i3c_slave_mqueue_read(dev_i3c_smq[msg->bus], &data_buf[0], msg->rx_len);
	if (ret < 0) {
		printf("[%s] bus%u message queue was empty\n", __func__, msg->bus);
		return -ENODATA;
	}

	k_mutex_unlock(&i3c_mutex[msg->bus]);
	memcpy(&msg->data[0], &data_buf, msg->rx_len);
	return I3C_SMQ_SUCCESS;
}

/**
 * @brief application writes i3c slave message queue and issues ibi to controller
 * 
 * @param msg i3c message structure
 * @return 0: complete write smq and ibi
 */
int i3c_smq_write(I3C_MSG *msg)
{
	int ret;

	if (!msg) {
		printf("[%s] null msg\n", __func__);
		return -EINVAL;
	}

	if (!dev_i3c[msg->bus]) {
		printf("[%s] bus%u did not define\n", __func__, msg->bus);
		return -ENODEV;
	}

	ret = k_mutex_lock(&i3c_mutex[msg->bus], K_SECONDS(1));
	if (ret) {
		printf("[%s] k_mutex bus%u locked failed, ret: %d\n", __func__, msg->bus, ret);
		return ret;
	}

	memcpy(&data_buf, &msg->data[0], msg->tx_len);
	ret = i3c_slave_mqueue_write(dev_i3c[msg->bus], &data_buf[0], msg->tx_len);
	k_mutex_unlock(&i3c_mutex[msg->bus]);
	return ret;
}

void util_init_i3c(void)
{
#ifdef DEV_I3C_0
	dev_i3c[0] = device_get_binding("I3C_0");
	if (k_mutex_init(&i3c_mutex[0]))
		printf("i3c0 mutex init fail\n");
#endif
#ifdef DEV_I3C_1
	dev_i3c[1] = device_get_binding("I3C_1");
	if (k_mutex_init(&i3c_mutex[1]))
		printf("i3c1 mutex init fail\n");
#endif
#ifdef DEV_I3C_2
	dev_i3c[2] = device_get_binding("I3C_2");
	if (k_mutex_init(&i3c_mutex[2]))
		printf("i2c2 mutex init fail\n");
#endif
#ifdef DEV_I3C_3
	dev_i3c[3] = device_get_binding("I3C_3");
	if (k_mutex_init(&i3c_mutex[3]))
		printf("i2c3 mutex init fail\n");
#endif
#ifdef DEV_I3C_4
	dev_i3c[4] = device_get_binding("I3C_4");
	if (k_mutex_init(&i3c_mutex[4]))
		printf("i3c4 mutex init fail\n");
#endif
#ifdef DEV_I3C_5
	dev_i3c[5] = device_get_binding("I3C_5");
	if (k_mutex_init(&i3c_mutex[5]))
		printf("i3c5 mutex init fail\n");
#endif
#ifdef DEV_I3C_6
	dev_i3c[6] = device_get_binding("I3C_6");
	if (k_mutex_init(&i3c_mutex[6]))
		printf("i3c6 mutex init fail\n");
#endif
#ifdef DEV_I3C_7
	dev_i3c[7] = device_get_binding("I3C_7");
	if (k_mutex_init(&i3c_mutex[7]))
		printf("i3c7 mutex init fail\n");
#endif

#ifdef DEV_I3CSMQ_0
	dev_i3c_smq[0] = device_get_binding("I3C_SMQ_0");
#endif
#ifdef DEV_I3CSMQ_1
	dev_i3c_smq[1] = device_get_binding("I3C_SMQ_1");
#endif
#ifdef DEV_I3CSMQ_2
	dev_i3c_smq[2] = device_get_binding("I3C_SMQ_2");
#endif
#ifdef DEV_I3CSMQ_3
	dev_i3c_smq[3] = device_get_binding("I3C_SMQ_3");
#endif
#ifdef DEV_I3CSMQ_4
	dev_i3c_smq[4] = device_get_binding("I3C_SMQ_4");
#endif
#ifdef DEV_I3CSMQ_5
	dev_i3c_smq[5] = device_get_binding("I3C_SMQ_5");
#endif
#ifdef DEV_I3CSMQ_6
	dev_i3c_smq[6] = device_get_binding("I3C_SMQ_6");
#endif
#ifdef DEV_I3CSMQ_7
	dev_i3c_smq[7] = device_get_binding("I3C_SMQ_7");
#endif
}