#ifndef PLAT_PDR_TABLE_H
#define PLAT_PDR_TABLE_H

#include <stdint.h>

#define MAX_SENSOR_SIZE 60

uint8_t plat_get_pdr_size();
void load_pdr_table(void);

#endif
