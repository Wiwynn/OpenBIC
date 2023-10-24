#ifndef _PLAT_MCTP_h
#define _PLAT_MCTP_h
#include <kernel.h>
#include "storage_handler.h"
#include "pldm.h"

/* init the mctp moduel for platform */
void plat_mctp_init(void);
void send_cmd_to_dev(struct k_timer *timer);
void send_cmd_to_dev_handler(struct k_work *work);
void plat_mctp_init(void);
uint8_t plat_get_mctp_port_count();
mctp_port *plat_get_mctp_port(uint8_t index);

#endif /* _PLAT_MCTP_h */
