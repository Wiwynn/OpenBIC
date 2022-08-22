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

#include "hal_i3c.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <zephyr.h>
#include "libutil.h"

static const struct device *dev_i3c[I3C_MAX_DESC_NUM];
static uint8_t data_buffer[I3C_MAX_XFER_NUM][I3C_MAX_BUFF_SIZE];
static struct i3c_dev_desc i3c_desc_table[I3C_MAX_DESC_NUM];
struct k_mutex i3c_mutex[I3C_MAX_DESC_NUM];

void util_init_i3c(void)
{
	int status;

#ifdef DEV_I3C_0
	dev_i3c[0] = device_get_binding("I3C_0");
	status = k_mutex_init(&i3c_mutex[0]);
	if (status)
		printf("i3c0 mutex init fail\n");
#endif
#ifdef DEV_I3C_1
	dev_i3c[1] = device_get_binding("I3C_1");
	status = k_mutex_init(&i3c_mutex[1]);
	if (status)
		printf("i3c1 mutex init fail\n");
#endif
#ifdef DEV_I3C_2
	dev_i3c[2] = device_get_binding("I3C_2");
	status = k_mutex_init(&i3c_mutex[2]);
	if (status)
		printf("i2c2 mutex init fail\n");
#endif
#ifdef DEV_I3C_3
	dev_i3c[3] = device_get_binding("I3C_3");
	status = k_mutex_init(&i3c_mutex[3]);
	if (status)
		printf("i2c3 mutex init fail\n");
#endif
#ifdef DEV_I3C_4
	dev_i3c[4] = device_get_binding("I3C_4");
	status = k_mutex_init(&i3c_mutex[4]);
	if (status)
		printf("i3c4 mutex init fail\n");
#endif
#ifdef DEV_I3C_5
	dev_i3c[5] = device_get_binding("I3C_5");
	status = k_mutex_init(&i3c_mutex[5]);
	if (status)
		printf("i3c5 mutex init fail\n");
#endif
#ifdef DEV_I3C_6
	dev_i3c[6] = device_get_binding("I3C_6");
	status = k_mutex_init(&i3c_mutex[6]);
	if (status)
		printf("i3c6 mutex init fail\n");
#endif
#ifdef DEV_I3C_7
	dev_i3c[7] = device_get_binding("I3C_7");
	status = k_mutex_init(&i3c_mutex[7]);
	if (status)
		printf("i3c7 mutex init fail\n");
#endif

	ARG_UNUSED(status);
}

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
	addr = msg->target_addr;
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
