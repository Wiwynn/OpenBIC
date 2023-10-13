#ifndef _PLAT_MCTP_h
#define _PLAT_MCTP_h
#include <kernel.h>
#include "storage_handler.h"
#include "pldm.h"

/* i2c 8 bit address */
#define I2C_ADDR_BIC 0x40
#define I2C_ADDR_BMC 0x20
/* i2c dev bus*/
#define I2C_BUS_BMC 0x02

/* mctp endpoint */
#define MCTP_EID_BMC 0x08
#define MCTP_EID_SELF 0x0A

struct mctp_to_ipmi_header_req {
	uint8_t iana[IANA_LEN];
	uint8_t netfn_lun;
	uint8_t ipmi_cmd;
} __attribute__((__packed__));
;

struct mctp_to_ipmi_header_resp {
	uint8_t completion_code;
	uint8_t netfn_lun;
	uint8_t ipmi_cmd;
	uint8_t ipmi_comp_code;
} __attribute__((__packed__));
;

struct mctp_to_ipmi_sel_req {
	struct mctp_to_ipmi_header_req header;
	struct ipmi_storage_add_sel_req req_data;
} __attribute__((__packed__));

struct mctp_to_ipmi_sel_resp {
	struct mctp_to_ipmi_header_resp header;
	struct ipmi_storage_add_sel_resp resp_data;
} __attribute__((__packed__));

/* init the mctp moduel for platform */
void plat_mctp_init(void);
void send_cmd_to_dev(struct k_timer *timer);
void send_cmd_to_dev_handler(struct k_work *work);
bool mctp_add_sel_to_ipmi(common_addsel_msg_t *sel_msg);
uint8_t plat_get_mctp_port_count();
mctp_port *plat_get_mctp_port(uint8_t index);
uint8_t plat_get_eid();

mctp *find_mctp_by_smbus(uint8_t bus);

#endif /* _PLAT_MCTP_h */
