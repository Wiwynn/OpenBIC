#include "plat_sensor_table.h"

#include <stdio.h>
#include <string.h>

#include "ast_adc.h"
#include "sensor.h"
#include "plat_hook.h"
#include "plat_i2c.h"
#include "plat_def.h"

sensor_cfg plat_sensor_config[] = {};

uint8_t load_sensor_config(void)
{
	memcpy(sensor_config, plat_sensor_config, sizeof(plat_sensor_config));
	return ARRAY_SIZE(plat_sensor_config);
}
