#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sensor.h"
#include "hal_i2c.h"
#include "libutil.h"
#include "pmbus.h"

#define LTC4286_MFR_CONFIG1 0xF2
#define I2C_DATA_SIZE 5

enum VRANGE_SELECT {
	VRANGE_SELECT_25_6_V = 0x0,
	VRANGE_SELECT_102_4_V = 0x1,
	BOTH = 0x2,
};

enum SENSOR_TYPE {
	VOLTAGE = 0x0,
	CURRENT = 0x1,
	POWER = 0x2,
	TEMPERATURE = 0x3,
};

struct LTC4286_MBR_TABLE {
	uint8_t type;
	uint8_t voltage_range;
	float M;
	bool is_multiplied_by_rsense;
	float R;
	float B;
};

/* Following the datasheet (table 3 in page 16),
   the real sensor value is calculated as
   (1 / M) * raw value * (10^(-R)) - B
   And the M, B and R vaues are depended on different sensor type and voltage range.
   The table is defined in ltc4286_mbr_table.
    (1) type - sensor type(voltage, current and etc.)
    (2) voltage_range - voltage range for VIN and VOUT measurements
    (3) M - PMBus M value
    (4) is_multiplied_by_rsense - if M value should be multiplied by r_sense or not.
    (5) R - PMBus R value
    (6) B - PMBus B value
 */
struct LTC4286_MBR_TABLE ltc4286_mbr_table[] = {
	{ VOLTAGE, VRANGE_SELECT_102_4_V, 32, false, 0.1, 0 },
	{ VOLTAGE, VRANGE_SELECT_25_6_V, 128, false, 0.1, 0 },
	{ CURRENT, BOTH, 1024, true, 0.001, 0 },
	{ POWER, VRANGE_SELECT_102_4_V, 1, true, 0.0001, 0 },
	{ POWER, VRANGE_SELECT_25_6_V, 4, true, 0.0001, 0 },
	{ TEMPERATURE, BOTH, 1, false, 1, 273.15 },
};

uint8_t ltc4286_read(uint8_t sensor_num, int *reading)
{
	if ((reading == NULL) ||
	    (sensor_config[sensor_config_index_map[sensor_num]].init_args == NULL)) {
		return SENSOR_UNSPECIFIED_ERROR;
	}

	ltc4286_init_arg *init_arg =
		(ltc4286_init_arg *)sensor_config[sensor_config_index_map[sensor_num]].init_args;
	if (init_arg->is_init == false) {
		printf("[%s], device isn't initialized\n", __func__);
		return SENSOR_UNSPECIFIED_ERROR;
	}

	float rsense = init_arg->r_sense / 1000;

	uint8_t retry = 5;
	double val;
	I2C_MSG msg;

	sensor_cfg *cfg = &sensor_config[sensor_config_index_map[sensor_num]];

	msg.bus = cfg->port;
	msg.target_addr = cfg->target_addr;
	msg.tx_len = 1;
	msg.rx_len = 2;
	msg.data[0] = cfg->offset;
	if (i2c_master_read(&msg, retry)) {
		return SENSOR_FAIL_TO_ACCESS;
	}

	// Choose the corresponding sensor type
	uint8_t type = 0xFF;
	switch (cfg->offset) {
	case PMBUS_READ_VIN:
	case PMBUS_READ_VOUT:
		type = VOLTAGE;
		break;
	case PMBUS_READ_IOUT:
		type = CURRENT;
		break;
	case PMBUS_READ_TEMPERATURE_1:
		type = TEMPERATURE;
		break;
	case PMBUS_READ_PIN:
		type = POWER;
		break;
	default:
		return SENSOR_NOT_FOUND;
	}

	/* Iterate the LTC4286 MBR table to
	 * find the corresponding MBR values by the sensor type and voltage range selection
	 */
	uint8_t index = 0xFF;
	for (int cnt = 0; cnt < ARRAY_SIZE(ltc4286_mbr_table); cnt++) {
		if (type == ltc4286_mbr_table[cnt].type) {
			if ((ltc4286_mbr_table[cnt].voltage_range == BOTH) ||
			    (ltc4286_mbr_table[cnt].voltage_range ==
			     init_arg->mfr_config_1.fields.vrange_select)) {
				index = cnt;
			} else {
				continue;
			}
		}
		if (cnt == ARRAY_SIZE(ltc4286_mbr_table)) {
			printf("[%s] Undifined the type(0x%x) in LTC4286 MBR table\n", __func__,
			       type);
			return SENSOR_UNSPECIFIED_ERROR;
		}
	}

	// Multiplied by r_sense value if it needs
	float M = ltc4286_mbr_table[index].M;
	if (ltc4286_mbr_table[index].is_multiplied_by_rsense) {
		M *= rsense;
	}

	// real value = (1 / M) * raw_value * R - B;
	val = (1 / M) * ((msg.data[1] << 8) | msg.data[0]) * ltc4286_mbr_table[index].R -
	      ltc4286_mbr_table[index].B;

	sensor_val *sval = (sensor_val *)reading;
	memset(sval, 0, sizeof(*sval));

	sval->integer = (int32_t)val;
	sval->fraction = (int32_t)(val * 1000) % 1000;

	return SENSOR_READ_SUCCESS;
}

uint8_t ltc4286_init(uint8_t sensor_num)
{
	if (!sensor_config[sensor_config_index_map[sensor_num]].init_args) {
		printf("<error> LTC4286 init args are not provided!\n");
		return SENSOR_INIT_UNSPECIFIED_ERROR;
	}

	I2C_MSG msg;
	char *data = (uint8_t *)malloc(I2C_DATA_SIZE * sizeof(uint8_t));
	uint8_t bus = sensor_config[sensor_config_index_map[sensor_num]].port;
	uint8_t target_addr = sensor_config[sensor_config_index_map[sensor_num]].target_addr;
	uint8_t tx_len = 0, rx_len = 0;
	uint8_t retry = 5;

	ltc4286_init_arg *init_args =
		(ltc4286_init_arg *)sensor_config[sensor_config_index_map[sensor_num]].init_args;
	if (init_args->is_init) {
		goto init_param;
	}

	// Set MFR_CONFIG_1 register value
	tx_len = 3;
	rx_len = 0;
	data[0] = LTC4286_MFR_CONFIG1;
	data[1] = init_args->mfr_config_1.value & 0xFF;
	data[2] = (init_args->mfr_config_1.value >> 8) & 0xFF;
	msg = construct_i2c_message(bus, target_addr, tx_len, data, rx_len);
	if (i2c_master_write(&msg, retry) != 0) {
		printf("Failed to set LTC4286 register(0x%x)\n", data[0]);
		goto cleanup;
	}

init_param:
	// Read MFR_CONFIG_1 register value
	tx_len = 1;
	rx_len = 3;
	data[0] = LTC4286_MFR_CONFIG1;
	msg = construct_i2c_message(bus, target_addr, tx_len, data, rx_len);
	if (i2c_master_write(&msg, retry) != 0) {
		printf("Failed to read LTC4286 register(0x%x)\n", data[0]);
		init_args->is_init = false;
		goto cleanup;
	}
	if (msg.data[0] == LTC4286_MFR_CONFIG1) {
		init_args->mfr_config_1.value = (msg.data[1] | (msg.data[2] << 8));
	}

	init_args->is_init = true;

cleanup:
	SAFE_FREE(data);

	sensor_config[sensor_config_index_map[sensor_num]].read = ltc4286_read;
	return SENSOR_INIT_SUCCESS;
}
