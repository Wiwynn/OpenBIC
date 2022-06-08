#ifndef PLAT_SDR_TABLE_H
#define PLAT_SDR_TABLE_H

#include <stdint.h>
#include "sdr.h"

uint8_t load_sdr_table(void);
SDR_Full_sensor *get_sdr_info(uint8_t *array_size);

#endif
