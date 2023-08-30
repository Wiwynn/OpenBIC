#ifndef PLAT_PDR_TABLE_H
#define PLAT_PDR_TABLE_H

#include <stdint.h>
#include "pdr.h"

#define MAX_SENSOR_SIZE 60

uint16_t plat_get_pdr_size();
void plat_load_pdr_table(PDR_numeric_sensor* numeric_sensor_table);

#endif