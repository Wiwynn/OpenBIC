#ifndef PLAT_IPMI_H
#define PLAT_IPMI_H

#include <stdbool.h>
#include <stdint.h>
#include "ipmi.h"

typedef struct addsel_msg_t {
	uint8_t sensor_type;
	uint8_t sensor_number;
	uint8_t event_type;
	uint8_t event_data1;
	uint8_t event_data2;
	uint8_t event_data3;
} addsel_msg_t;

bool add_sel_evt_record(addsel_msg_t *sel_msg);
void OEM_1S_GET_BOARD_ID(ipmi_msg *msg);

#endif
