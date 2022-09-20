#ifndef HAL_I3C_H
#define HAL_I3C_H

#include <zephyr.h>
#include <drivers/i3c/i3c.h>

#if DT_NODE_HAS_STATUS(DT_NODELABEL(i3c0), okay)
#define DEV_I3C_0
#endif

#if DT_NODE_HAS_STATUS(DT_NODELABEL(i3c1), okay)
#define DEV_I3C_1
#endif

#if DT_NODE_HAS_STATUS(DT_NODELABEL(i3c2), okay)
#define DEV_I3C_2
#endif

#if DT_NODE_HAS_STATUS(DT_NODELABEL(i3c3), okay)
#define DEV_I3C_3
#endif

#if DT_NODE_HAS_STATUS(DT_NODELABEL(i3c4), okay)
#define DEV_I3C_4
#endif

#if DT_NODE_HAS_STATUS(DT_NODELABEL(i3c5), okay)
#define DEV_I3C_5
#endif

#if DT_NODE_HAS_STATUS(DT_NODELABEL(i3c6), okay)
#define DEV_I3C_6
#endif

#if DT_NODE_HAS_STATUS(DT_NODELABEL(i3c7), okay)
#define DEV_I3C_7
#endif

#if DT_NODE_EXISTS(DT_NODELABEL(i3c0_smq))
#define DEV_I3CSMQ_0
#endif

#if DT_NODE_EXISTS(DT_NODELABEL(i3c1_smq))
#define DEV_I3CSMQ_1
#endif

#if DT_NODE_EXISTS(DT_NODELABEL(i3c2_smq))
#define DEV_I3CSMQ_2
#endif

#if DT_NODE_EXISTS(DT_NODELABEL(i3c3_smq))
#define DEV_I3CSMQ_3
#endif

#if DT_NODE_EXISTS(DT_NODELABEL(i3c4_smq))
#define DEV_I3CSMQ_4
#endif

#if DT_NODE_EXISTS(DT_NODELABEL(i3c5_smq))
#define DEV_I3CSMQ_5
#endif

#if DT_NODE_EXISTS(DT_NODELABEL(i3c6_smq))
#define DEV_I3CSMQ_6
#endif

#if DT_NODE_EXISTS(DT_NODELABEL(i3c7_smq))
#define DEV_I3CSMQ_7
#endif

#define DEV_I3C(n)		DEV_I3C_##n
#define DEV_I3CSMQ(n)	DEV_I3CSMQ_##n

#define I3C_MAX_NUM 8
#define I3C_MAX_DATA_SIZE 256
#define I3C_DEBUG 0
#define I3C_SMQ_SUCCESS 0
#define I3C_MAX_XFER_NUM 2

typedef struct _I3C_MSG_ {
	uint8_t bus;
	uint8_t tx_len;
	uint8_t rx_len;
	uint8_t target_addr;
	uint8_t data[I3C_MAX_DATA_SIZE];
	struct i3c_priv_xfer xfer[I3C_MAX_XFER_NUM];
	struct i3c_dev_desc *desc;
} I3C_MSG;

void util_init_i3c(void);
int i3c_smq_read(I3C_MSG *msg);
int i3c_smq_write(I3C_MSG *msg);

#endif
