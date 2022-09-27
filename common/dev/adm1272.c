#include <stdio.h>
#include <string.h>
#include "sensor.h"
#include "hal_i2c.h"
#include "pmbus.h"
#include "adm1272.h"

#define REG_PWR_MONITOR_CFG 0xD4

int adm1272_convert_real_value(uint8_t vrange, uint8_t irange, uint8_t offset, float *val)
{
	if (val == NULL) {
		printf("[%s] input value pointer is NULL\n", __func__);
		return -1;
	}

	int convert_val = (int)*val;
	int convert_coefficient_m = 0;
	int convert_coefficient_b = 0;
	int convert_coefficient_R = 0;

	switch (offset) {
	case PMBUS_READ_VOUT:
		switch (vrange) {
		case VRANGE_0V_TO_60V:
			convert_coefficient_m = 6770;
			break;
		case VRANGE_0V_TO_100V:
			convert_coefficient_m = 4062;
			break;
		}
		convert_coefficient_b = 0;
		convert_coefficient_R = 100;
		break;

	case PMBUS_READ_IOUT:
		switch (irange) {
		case IRANGE_0MV_TO_15MV:
			convert_coefficient_m = 1326;
			break;
		case IRANGE_0MV_TO_30MV:
			convert_coefficient_m = 663;
			break;
		}
		convert_coefficient_b = 20480;
		convert_coefficient_R = 10;
		break;

	case PMBUS_READ_TEMPERATURE_1:
		convert_coefficient_m = 42;
		convert_coefficient_b = 31871;
		convert_coefficient_R = 10;
		break;

	case PMBUS_READ_PIN:
		switch (vrange) {
		case VRANGE_0V_TO_60V:
			switch (irange) {
			case IRANGE_0MV_TO_15MV:
				convert_coefficient_m = 3512;
				convert_coefficient_R = 100;
				break;
			case IRANGE_0MV_TO_30MV:
				convert_coefficient_m = 17561;
				convert_coefficient_R = 1000;
				break;
			}
			break;
		case VRANGE_0V_TO_100V:
			switch (irange) {
			case IRANGE_0MV_TO_15MV:
				convert_coefficient_m = 21071;
				convert_coefficient_R = 1000;
				break;
			case IRANGE_0MV_TO_30MV:
				convert_coefficient_m = 10535;
				convert_coefficient_R = 1000;
				break;
			}
			break;
		}
		convert_coefficient_b = 0;
		break;

	default:
		printf("[%s] offset 0x%x is invalid\n", __func__, offset);
		return -1;
	}

	if (convert_coefficient_m == 0) {
		printf("[%s] convert coefficient m is invalid, vrange: 0x%x, irange: 0x%x\n",
		       __func__, vrange, irange);
		return -1;
	}

	*val = (float)((convert_val)*convert_coefficient_R - convert_coefficient_b) /
	       convert_coefficient_m;

	// Only positive IOUT values are used to avoid returning a negative power
	if ((offset == PMBUS_READ_IOUT) && (*val < 0)) {
		*val = 0;
	}

	return 0;
}

int adm1272_read_pout(uint8_t sensor_num, float *val)
{
	if (val == NULL) {
		printf("[%s] input value pointer is NULL\n", __func__);
		return -1;
	}

	sensor_cfg cfg = sensor_config[sensor_config_index_map[sensor_num]];
	adm1272_init_arg *init_arg =
		(adm1272_init_arg *)sensor_config[sensor_config_index_map[sensor_num]].init_args;

	uint8_t retry = 5;
	int ret = 0;
	float vout = 0;
	float iout = 0;
	I2C_MSG msg;
	msg.bus = cfg.port;
	msg.target_addr = cfg.target_addr;
	msg.tx_len = 1;
	msg.rx_len = 2;
	msg.data[0] = PMBUS_READ_VOUT;

	ret = i2c_master_read(&msg, retry);
	if (ret != 0) {
		printf("[%s] read Vout fail, ret: %d\n", __func__, ret);
		return -1;
	}
	vout = (msg.data[1] << 8) | msg.data[0];
	ret = adm1272_convert_real_value(init_arg->pwr_monitor_cfg.fields.VRANGE,
					 init_arg->pwr_monitor_cfg.fields.IRANGE, PMBUS_READ_VOUT,
					 &vout);
	if (ret != 0) {
		printf("[%s] convert vout value fail\n", __func__);
		return -1;
	}

	memset(&msg, 0, sizeof(msg));
	msg.bus = cfg.port;
	msg.target_addr = cfg.target_addr;
	msg.tx_len = 1;
	msg.rx_len = 2;
	msg.data[0] = PMBUS_READ_IOUT;

	ret = i2c_master_read(&msg, retry);
	if (ret != 0) {
		printf("[%s] read Iout fail, ret: %d\n", __func__, ret);
		return -1;
	}
	iout = (msg.data[1] << 8) | msg.data[0];
	ret = adm1272_convert_real_value(init_arg->pwr_monitor_cfg.fields.VRANGE,
					 init_arg->pwr_monitor_cfg.fields.IRANGE, PMBUS_READ_IOUT,
					 &iout);
	if (ret != 0) {
		printf("[%s] convert iout value fail\n", __func__);
		return -1;
	}

	*val = vout * iout;
	return 0;
}

uint8_t adm1272_read(uint8_t sensor_num, int *reading)
{
	if (reading == NULL) {
		printf("[%s] input reading pointer is NULL\n", __func__);
		return SENSOR_UNSPECIFIED_ERROR;
	}

	if (sensor_num > SENSOR_NUM_MAX) {
		printf("[%s] input sensor number is invalid, sensor number: 0x%x\n", __func__,
		       sensor_num);
		return SENSOR_UNSPECIFIED_ERROR;
	}

	if (sensor_config[sensor_config_index_map[sensor_num]].init_args == NULL) {
		printf("[%s] initial arg is NULL\n", __func__);
		return SENSOR_UNSPECIFIED_ERROR;
	}

	adm1272_init_arg *init_arg =
		(adm1272_init_arg *)sensor_config[sensor_config_index_map[sensor_num]].init_args;
	if (init_arg->is_init == false) {
		printf("[%s] device isn't initialized\n", __func__);
		return SENSOR_UNSPECIFIED_ERROR;
	}

	float val = 0;
	uint8_t retry = 5;
	I2C_MSG msg;
	int ret = 0;
	uint8_t offset = sensor_config[sensor_config_index_map[sensor_num]].offset;

	if (offset != PMBUS_READ_POUT) {
		msg.bus = sensor_config[sensor_config_index_map[sensor_num]].port;
		msg.target_addr = sensor_config[sensor_config_index_map[sensor_num]].target_addr;
		msg.tx_len = 1;
		msg.data[0] = offset;
		msg.rx_len = 2;

		ret = i2c_master_read(&msg, retry);
		if (ret != 0) {
			printf("[%s] i2c read fail, ret: %d, offset: 0x%x\n", __func__, ret,
			       offset);
			return SENSOR_FAIL_TO_ACCESS;
		}
	}

	switch (offset) {
	case PMBUS_READ_VOUT:
	case PMBUS_READ_IOUT:
	case PMBUS_READ_TEMPERATURE_1:
	case PMBUS_READ_PIN:
		val = (msg.data[1] << 8) | msg.data[0];
		ret = adm1272_convert_real_value(init_arg->pwr_monitor_cfg.fields.VRANGE,
						 init_arg->pwr_monitor_cfg.fields.IRANGE, offset,
						 &val);
		break;
	case PMBUS_READ_POUT:
		ret = adm1272_read_pout(sensor_num, &val);
		break;
	default:
		printf("[%s] invalid sensor 0x%x offset 0x%x\n", __func__, sensor_num, offset);
		return SENSOR_UNSPECIFIED_ERROR;
	}

	if (ret != 0) {
		return SENSOR_FAIL_TO_ACCESS;
	}
	sensor_val *sval = (sensor_val *)reading;
	sval->integer = (int)val & 0xFFFF;
	sval->fraction = (val - sval->integer) * 1000;
	return SENSOR_READ_SUCCESS;
}

uint8_t adm1272_init(uint8_t sensor_num)
{
	if (sensor_num > SENSOR_NUM_MAX) {
		printf("[%s] sensor number is invalid, sensor number: 0x%x\n", __func__,
		       sensor_num);
		return SENSOR_INIT_UNSPECIFIED_ERROR;
	}

	adm1272_init_arg *init_args =
		(adm1272_init_arg *)sensor_config[sensor_config_index_map[sensor_num]].init_args;
	uint8_t retry = 5;
	int ret = -1;
	I2C_MSG msg;

	if (init_args->is_need_set_pwr_cfg == false) {
		goto skip_set_pwr_cfg;
	}

	msg.bus = sensor_config[sensor_config_index_map[sensor_num]].port;
	msg.target_addr = sensor_config[sensor_config_index_map[sensor_num]].target_addr;
	msg.tx_len = 3;
	msg.data[0] = REG_PWR_MONITOR_CFG;
	msg.data[1] = init_args->pwr_monitor_cfg.value & 0xFF;
	msg.data[2] = (init_args->pwr_monitor_cfg.value >> 8) & 0xFF;

	ret = i2c_master_write(&msg, retry);
	if (ret != 0) {
		printf("[%s] set power monitor config fail, ret: %d\n", __func__, ret);
		return SENSOR_INIT_UNSPECIFIED_ERROR;
	}
	memset(&msg, 0, sizeof(msg));

skip_set_pwr_cfg:
	msg.bus = sensor_config[sensor_config_index_map[sensor_num]].port;
	msg.target_addr = sensor_config[sensor_config_index_map[sensor_num]].target_addr;
	msg.tx_len = 1;
	msg.data[0] = REG_PWR_MONITOR_CFG;
	msg.rx_len = 2;

	ret = i2c_master_read(&msg, retry);
	if (ret != 0) {
		printf("[%s] read power monitor config fail, ret: %d\n", __func__, ret);
		return SENSOR_INIT_UNSPECIFIED_ERROR;
	}

	init_args->pwr_monitor_cfg.value = ((msg.data[1] << 8) | msg.data[0]);
	init_args->is_init = 1;

	sensor_config[sensor_config_index_map[sensor_num]].read = adm1272_read;
	return SENSOR_INIT_SUCCESS;
}
