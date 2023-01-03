#include <logging/log.h>

#include "sensor.h"
#include "intel_peci.h"
#include "intel_dimm.h"
#include "power_status.h"
#include "i2c-mux-tca9548.h"
#include "libutil.h"

#include "plat_hook.h"
#include "plat_sensor_table.h"
#include "plat_gpio.h"

LOG_MODULE_REGISTER(plat_hook);

xdpe15284_pre_read_arg xdpe15284_pre_read_args[] = {
	[0] = { 0x0 },
	[1] = { 0x1 },
};

adc_asd_init_arg adc_asd_init_args[] = { [0] = { .is_init = false } };
adm1278_init_arg adm1278_init_args[] = {
	[0] = { .is_init = false, .config = { 0x3F1C }, .r_sense = 0.25 }
};

struct tca9548 mux_conf_addr_0xe2[8] = {
	[0] = { .addr = 0xe2, .chan = 0 }, [1] = { .addr = 0xe2, .chan = 1 },
	[2] = { .addr = 0xe2, .chan = 2 }, [3] = { .addr = 0xe2, .chan = 3 },
	[4] = { .addr = 0xe2, .chan = 4 }, [5] = { .addr = 0xe2, .chan = 5 },
	[6] = { .addr = 0xe2, .chan = 6 }, [7] = { .addr = 0xe2, .chan = 7 },
};

dimm_pre_proc_arg dimm_pre_proc_args[] = {
	[0] = { .is_present_checked = false }, [1] = { .is_present_checked = false },
	[2] = { .is_present_checked = false }, [3] = { .is_present_checked = false },
	[4] = { .is_present_checked = false }, [5] = { .is_present_checked = false }
};

bool pre_xdpe15284_read(uint8_t sensor_num, void *args)
{
	CHECK_NULL_ARG_WITH_RETURN(args, false);

	xdpe15284_pre_read_arg *pre_read_args = (xdpe15284_pre_read_arg *)args;
	uint8_t retry = 5;
	I2C_MSG msg;

	/* set page */
	msg.bus = sensor_config[sensor_config_index_map[sensor_num]].port;
	msg.target_addr = sensor_config[sensor_config_index_map[sensor_num]].target_addr;
	msg.tx_len = 2;
	msg.data[0] = 0x00;
	msg.data[1] = pre_read_args->vr_page;
	if (i2c_master_write(&msg, retry)) {
		printf("pre_xdpe15284_read, set page fail\n");
		return false;
	}
	return true;
}

bool pre_vol_bat3v_read(uint8_t sensor_num, void *args)
{
	ARG_UNUSED(args);

	if (sensor_num == SENSOR_NUM_P3V_BAT_VOL) {
		gpio_set(A_P3V_BAT_SCALED_EN_R, GPIO_HIGH);
		k_msleep(1);
	}

	return true;
}

bool post_vol_bat3v_read(uint8_t sensor_num, void *args, int *reading)
{
	ARG_UNUSED(args);
	ARG_UNUSED(reading);

	if (sensor_num == SENSOR_NUM_P3V_BAT_VOL)
		gpio_set(A_P3V_BAT_SCALED_EN_R, GPIO_LOW);

	return true;
}

bool post_adm1278_power_read(uint8_t sensor_num, void *args, int *reading)
{
	if (!reading)
		return check_reading_pointer_null_is_allowed(sensor_num);
	ARG_UNUSED(args);

	sensor_val *sval = (sensor_val *)reading;
	float val = (float)sval->integer + (sval->fraction / 1000.0);

	sval->integer = (int)val & 0xFFFF;
	sval->fraction = (val - sval->integer) * 1000;
	return true;
}

bool pre_nvme_read(uint8_t sensor_num, void *args)
{
	if (!args)
		return false;
	if (!tca9548_select_chan(sensor_num, (struct tca9548 *)args))
		return false;

	return true;
}
bool post_cpu_margin_read(uint8_t sensor_num, void *args, int *reading)
{
	if (!reading)
		return check_reading_pointer_null_is_allowed(sensor_num);
	ARG_UNUSED(args);

	sensor_val *sval = (sensor_val *)reading;
	sval->integer = -sval->integer; /* for BMC minus */
	return true;
}

bool pre_intel_peci_dimm_read(uint8_t sensor_num, void *args)
{
	if (get_post_status() == false) {
		return true;
	}

	dimm_pre_proc_arg *pre_proc_args = (dimm_pre_proc_arg *)args;
	if (pre_proc_args->is_present_checked == true) {
		return true;
	}

	bool ret = false;
	uint8_t dimm_present_result = 0;
	sensor_cfg cfg = sensor_config[sensor_config_index_map[sensor_num]];
	switch (cfg.offset) {
	case PECI_TEMP_CHANNEL0_DIMM0:
		ret = check_dimm_present(DIMM_CHANNEL_NUM_0, DIMM_NUMBER_0, &dimm_present_result);
		break;
	case PECI_TEMP_CHANNEL1_DIMM0:
		ret = check_dimm_present(DIMM_CHANNEL_NUM_1, DIMM_NUMBER_0, &dimm_present_result);
		break;
	case PECI_TEMP_CHANNEL2_DIMM0:
		ret = check_dimm_present(DIMM_CHANNEL_NUM_2, DIMM_NUMBER_0, &dimm_present_result);
		break;
	case PECI_TEMP_CHANNEL3_DIMM0:
		ret = check_dimm_present(DIMM_CHANNEL_NUM_3, DIMM_NUMBER_0, &dimm_present_result);
		break;
	case PECI_TEMP_CHANNEL4_DIMM0:
		ret = check_dimm_present(DIMM_CHANNEL_NUM_4, DIMM_NUMBER_0, &dimm_present_result);
		break;
	case PECI_TEMP_CHANNEL5_DIMM0:
		ret = check_dimm_present(DIMM_CHANNEL_NUM_5, DIMM_NUMBER_0, &dimm_present_result);
		break;
	case PECI_TEMP_CHANNEL6_DIMM0:
		ret = check_dimm_present(DIMM_CHANNEL_NUM_6, DIMM_NUMBER_0, &dimm_present_result);
		break;
	case PECI_TEMP_CHANNEL7_DIMM0:
		ret = check_dimm_present(DIMM_CHANNEL_NUM_7, DIMM_NUMBER_0, &dimm_present_result);
		break;
	default:
		printf("[%s] input sensor 0x%x offset is invalid, offset: 0x%x\n", __func__,
		       sensor_num, cfg.offset);
		return ret;
	}

	if (ret == false) {
		return ret;
	}

	/* TODO :
	 * Check dimm temperature result is pending because I3C hasn't be ready yet.
	 */

	pre_proc_args->is_present_checked = true;
	return ret;
}

bool post_adm1278_current_read(uint8_t sensor_num, void *args, int *reading)
{
	if (!reading)
		return check_reading_pointer_null_is_allowed(sensor_num);
	ARG_UNUSED(args);

	sensor_val *sval = (sensor_val *)reading;
	float val = (float)sval->integer + (sval->fraction / 1000.0);

	sval->integer = (int)val & 0xFFFF;
	sval->fraction = (val - sval->integer) * 1000;
	return true;
}
