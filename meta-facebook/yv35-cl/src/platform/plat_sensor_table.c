#include "plat_sensor_table.h"

#include <stdio.h>
#include <string.h>

#include "sensor.h"
#include "adc.h"
#include "isl69260.h"
#include "hal_gpio.h"
#include "plat_class.h"
#include "plat_i2c.h"
#include "plat_gpio.h"

SET_GPIO_VALUE_CFG pre_bat_3v = { A_P3V_BAT_SCALED_EN_R, GPIO_HIGH };
SET_GPIO_VALUE_CFG post_bat_3v = { A_P3V_BAT_SCALED_EN_R, GPIO_LOW };

snr_cfg plat_sensor_config[] = {
	/* number,                  type,       port,      address,      offset,
	   access check arg0, arg1, cache, cache_status, mux_address, mux_offset,
	   pre_sensor_read_fn, pre_sensor_read_args, post_sensor_read_fn, post_sensor_read_fn  */

	// temperature
	{ SENSOR_NUM_TEMP_TMP75_IN, TYPE_TMP75, I2C_BUS2, TMP75_IN_ADDR, TMP75_TEMP_OFFSET,
	  stby_access, 0, 0, 0, SENSOR_INIT_STATUS, NONE, NONE, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_TEMP_TMP75_OUT, TYPE_TMP75, I2C_BUS2, TMP75_OUT_ADDR, TMP75_TEMP_OFFSET,
	  stby_access, 0, 0, 0, SENSOR_INIT_STATUS, NONE, NONE, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_TEMP_TMP75_FIO, TYPE_TMP75, I2C_BUS2, TMP75_FIO_ADDR, TMP75_TEMP_OFFSET,
	  stby_access, 0, 0, 0, SENSOR_INIT_STATUS, NONE, NONE, NULL, NULL, NULL, NULL },

	// NVME
	{ SENSOR_NUM_TEMP_SSD0, TYPE_NVME, I2C_BUS2, SSD0_ADDR, SSD0_OFFSET, post_access, 0, 0, 0,
	  SENSOR_INIT_STATUS, SSD0_MUX_ADDR, SSD0_CHANNEL, NULL, NULL, NULL, NULL },

	// PECI
	{ SENSOR_NUM_TEMP_CPU, TYPE_PECI, CPU_PECI_ADDR, NONE, NONE, post_access, 0, 0, 0,
	  SENSOR_INIT_STATUS, NONE, NONE, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_TEMP_CPU_MARGIN, TYPE_PECI, CPU_PECI_ADDR, TEMP_CPU_MARGIN_INDEX,
	  TEMP_CPU_MARGIN_PARAM, post_access, 0, 0, 0, SENSOR_INIT_STATUS, NONE, NONE, NULL, NULL,
	  NULL, NULL },
	{ SENSOR_NUM_TEMP_CPU_TJMAX, TYPE_PECI, CPU_PECI_ADDR, TEMP_CPU_TJMAX_INDEX,
	  TEMP_CPU_TJMAX_PARAM, post_access, 0, 0, 0, SENSOR_INIT_STATUS, NONE, NONE, NULL, NULL,
	  NULL, NULL },
	{ SENSOR_NUM_TEMP_DIMM_A, TYPE_PECI, CPU_PECI_ADDR, TEMP_DIMM_INDEX, TEMP_DIMM_A_PARAM,
	  post_access, 0, 0, 0, SENSOR_INIT_STATUS, NONE, NONE, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_TEMP_DIMM_C, TYPE_PECI, CPU_PECI_ADDR, TEMP_DIMM_INDEX, TEMP_DIMM_C_PARAM,
	  post_access, 0, 0, 0, SENSOR_INIT_STATUS, NONE, NONE, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_TEMP_DIMM_D, TYPE_PECI, CPU_PECI_ADDR, TEMP_DIMM_INDEX, TEMP_DIMM_D_PARAM,
	  post_access, 0, 0, 0, SENSOR_INIT_STATUS, NONE, NONE, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_TEMP_DIMM_E, TYPE_PECI, CPU_PECI_ADDR, TEMP_DIMM_INDEX, TEMP_DIMM_E_PARAM,
	  post_access, 0, 0, 0, SENSOR_INIT_STATUS, NONE, NONE, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_TEMP_DIMM_G, TYPE_PECI, CPU_PECI_ADDR, TEMP_DIMM_INDEX, TEMP_DIMM_G_PARAM,
	  post_access, 0, 0, 0, SENSOR_INIT_STATUS, NONE, NONE, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_TEMP_DIMM_H, TYPE_PECI, CPU_PECI_ADDR, TEMP_DIMM_INDEX, TEMP_DIMM_H_PARAM,
	  post_access, 0, 0, 0, SENSOR_INIT_STATUS, NONE, NONE, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_PWR_CPU, TYPE_PECI, CPU_PECI_ADDR, NONE, NONE, post_access, 0, 0, 0,
	  SENSOR_INIT_STATUS, NONE, NONE, NULL, NULL, NULL, NULL },

	// adc voltage
	{ SENSOR_NUM_VOL_STBY12V, TYPE_ADC, ADC_PORT0, NONE, NONE, stby_access, 667, 100, 0,
	  SENSOR_INIT_STATUS, NONE, NONE, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_VOL_STBY3V, TYPE_ADC, ADC_PORT2, NONE, NONE, stby_access, 2, 1, 0,
	  SENSOR_INIT_STATUS, NONE, NONE, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_VOL_STBY1V05, TYPE_ADC, ADC_PORT3, NONE, NONE, stby_access, 1, 1, 0,
	  SENSOR_INIT_STATUS, NONE, NONE, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_VOL_BAT3V, TYPE_ADC, ADC_PORT4, NONE, NONE, stby_access, 3, 1, 0,
	  SENSOR_INIT_STATUS, NONE, NONE, &bat_3v_set_gpio, &pre_bat_3v, &bat_3v_set_gpio,
	  &post_bat_3v },
	{ SENSOR_NUM_VOL_STBY5V, TYPE_ADC, ADC_PORT9, NONE, NONE, stby_access, 711, 200, 0,
	  SENSOR_INIT_STATUS, NONE, NONE, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_VOL_DIMM12V, TYPE_ADC, ADC_PORT11, NONE, NONE, DC_access, 667, 100, 0,
	  SENSOR_INIT_STATUS, NONE, NONE, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_VOL_STBY1V2, TYPE_ADC, ADC_PORT13, NONE, NONE, stby_access, 1, 1, 0,
	  SENSOR_INIT_STATUS, NONE, NONE, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_VOL_M2_3V3, TYPE_ADC, ADC_PORT14, NONE, NONE, DC_access, 2, 1, 0,
	  SENSOR_INIT_STATUS, NONE, NONE, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_VOL_STBY1V8, TYPE_ADC, ADC_PORT15, NONE, NONE, stby_access, 1, 1, 0,
	  SENSOR_INIT_STATUS, NONE, NONE, NULL, NULL, NULL, NULL },

	// VR voltage
	{ SENSOR_NUM_VOL_PVCCD_HV, TYPE_ISL69260, I2C_BUS5, PVCCD_HV_ADDR, VR_VOL_CMD, DC_access, 0,
	  0, 0, SENSOR_INIT_STATUS, NONE, NONE, isl69260_switch_page, &isl69260_page_data_args[0],
	  NULL, NULL },
	{ SENSOR_NUM_VOL_PVCCINFAON, TYPE_ISL69260, I2C_BUS5, PVCCINFAON_ADDR, VR_VOL_CMD,
	  DC_access, 0, 0, 0, SENSOR_INIT_STATUS, NONE, NONE, isl69260_switch_page,
	  &isl69260_page_data_args[0], NULL, NULL },
	{ SENSOR_NUM_VOL_PVCCFA_EHV, TYPE_ISL69260, I2C_BUS5, PVCCFA_EHV_ADDR, VR_VOL_CMD,
	  DC_access, 0, 0, 0, SENSOR_INIT_STATUS, NONE, NONE, isl69260_switch_page,
	  &isl69260_page_data_args[1], NULL, NULL },
	{ SENSOR_NUM_VOL_PVCCIN, TYPE_ISL69260, I2C_BUS5, PVCCIN_ADDR, VR_VOL_CMD, DC_access, 0, 0,
	  0, SENSOR_INIT_STATUS, NONE, NONE, isl69260_switch_page, &isl69260_page_data_args[0],
	  NULL, NULL },
	{ SENSOR_NUM_VOL_PVCCFA_EHV_FIVRA, TYPE_ISL69260, I2C_BUS5, PVCCFA_EHV_FIVRA_ADDR,
	  VR_VOL_CMD, DC_access, 0, 0, 0, SENSOR_INIT_STATUS, NONE, NONE, isl69260_switch_page,
	  &isl69260_page_data_args[1], NULL, NULL },

	// VR current
	{ SENSOR_NUM_CUR_PVCCD_HV, TYPE_ISL69260, I2C_BUS5, PVCCD_HV_ADDR, VR_CUR_CMD, DC_access, 0,
	  0, 0, SENSOR_INIT_STATUS, NONE, NONE, isl69260_switch_page, &isl69260_page_data_args[0],
	  NULL, NULL },
	{ SENSOR_NUM_CUR_PVCCINFAON, TYPE_ISL69260, I2C_BUS5, PVCCINFAON_ADDR, VR_CUR_CMD,
	  DC_access, 0, 0, 0, SENSOR_INIT_STATUS, NONE, NONE, isl69260_switch_page,
	  &isl69260_page_data_args[0], NULL, NULL },
	{ SENSOR_NUM_CUR_PVCCFA_EHV, TYPE_ISL69260, I2C_BUS5, PVCCFA_EHV_ADDR, VR_CUR_CMD,
	  DC_access, 0, 0, 0, SENSOR_INIT_STATUS, NONE, NONE, isl69260_switch_page,
	  &isl69260_page_data_args[1], NULL, NULL },
	{ SENSOR_NUM_CUR_PVCCIN, TYPE_ISL69260, I2C_BUS5, PVCCIN_ADDR, VR_CUR_CMD, DC_access, 0, 0,
	  0, SENSOR_INIT_STATUS, NONE, NONE, isl69260_switch_page, &isl69260_page_data_args[0],
	  NULL, NULL },
	{ SENSOR_NUM_CUR_PVCCFA_EHV_FIVRA, TYPE_ISL69260, I2C_BUS5, PVCCFA_EHV_FIVRA_ADDR,
	  VR_CUR_CMD, DC_access, 0, 0, 0, SENSOR_INIT_STATUS, NONE, NONE, isl69260_switch_page,
	  &isl69260_page_data_args[1], NULL, NULL },

	// VR temperature
	{ SENSOR_NUM_TEMP_PVCCD_HV, TYPE_ISL69260, I2C_BUS5, PVCCD_HV_ADDR, VR_TEMP_CMD, DC_access,
	  0, 0, 0, SENSOR_INIT_STATUS, NONE, NONE, isl69260_switch_page,
	  &isl69260_page_data_args[0], NULL, NULL },
	{ SENSOR_NUM_TEMP_PVCCINFAON, TYPE_ISL69260, I2C_BUS5, PVCCINFAON_ADDR, VR_TEMP_CMD,
	  DC_access, 0, 0, 0, SENSOR_INIT_STATUS, NONE, NONE, isl69260_switch_page,
	  &isl69260_page_data_args[0], NULL, NULL },
	{ SENSOR_NUM_TEMP_PVCCFA_EHV, TYPE_ISL69260, I2C_BUS5, PVCCFA_EHV_ADDR, VR_TEMP_CMD,
	  DC_access, 0, 0, 0, SENSOR_INIT_STATUS, NONE, NONE, isl69260_switch_page,
	  &isl69260_page_data_args[1], NULL, NULL },
	{ SENSOR_NUM_TEMP_PVCCIN, TYPE_ISL69260, I2C_BUS5, PVCCIN_ADDR, VR_TEMP_CMD, DC_access, 0,
	  0, 0, SENSOR_INIT_STATUS, NONE, NONE, isl69260_switch_page, &isl69260_page_data_args[0],
	  NULL, NULL },
	{ SENSOR_NUM_TEMP_PVCCFA_EHV_FIVRA, TYPE_ISL69260, I2C_BUS5, PVCCFA_EHV_FIVRA_ADDR,
	  VR_TEMP_CMD, DC_access, 0, 0, 0, SENSOR_INIT_STATUS, NONE, NONE, isl69260_switch_page,
	  &isl69260_page_data_args[1], NULL, NULL },

	// VR power
	{ SENSOR_NUM_PWR_PVCCD_HV, TYPE_ISL69260, I2C_BUS5, PVCCD_HV_ADDR, VR_PWR_CMD, DC_access, 0,
	  0, 0, SENSOR_INIT_STATUS, NONE, NONE, isl69260_switch_page, &isl69260_page_data_args[0],
	  NULL, NULL },
	{ SENSOR_NUM_PWR_PVCCINFAON, TYPE_ISL69260, I2C_BUS5, PVCCINFAON_ADDR, VR_PWR_CMD,
	  DC_access, 0, 0, 0, SENSOR_INIT_STATUS, NONE, NONE, isl69260_switch_page,
	  &isl69260_page_data_args[0], NULL, NULL },
	{ SENSOR_NUM_PWR_PVCCFA_EHV, TYPE_ISL69260, I2C_BUS5, PVCCFA_EHV_ADDR, VR_PWR_CMD,
	  DC_access, 0, 0, 0, SENSOR_INIT_STATUS, NONE, NONE, isl69260_switch_page,
	  &isl69260_page_data_args[1], NULL, NULL },
	{ SENSOR_NUM_PWR_PVCCIN, TYPE_ISL69260, I2C_BUS5, PVCCIN_ADDR, VR_PWR_CMD, DC_access, 0, 0,
	  0, SENSOR_INIT_STATUS, NONE, NONE, isl69260_switch_page, &isl69260_page_data_args[0],
	  NULL, NULL },
	{ SENSOR_NUM_PWR_PVCCFA_EHV_FIVRA, TYPE_ISL69260, I2C_BUS5, PVCCFA_EHV_FIVRA_ADDR,
	  VR_PWR_CMD, DC_access, 0, 0, 0, SENSOR_INIT_STATUS, NONE, NONE, isl69260_switch_page,
	  &isl69260_page_data_args[1], NULL, NULL },

	// ME
	{ SENSOR_NUM_TEMP_PCH, TYPE_PCH, I2C_BUS3, PCH_ADDR, ME_SENSOR_NUM_TEMP_PCH, post_access, 0,
	  0, 0, SENSOR_INIT_STATUS, NONE, NONE, NULL, NULL, NULL, NULL },

	// HSC
	{ SENSOR_NUM_TEMP_HSC, TYPE_HSC, I2C_BUS2, HSC_ADDR, HSC_TEMP_CMD, stby_access, 0, 0, 0,
	  SENSOR_INIT_STATUS, NONE, NONE, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_VOL_HSCIN, TYPE_HSC, I2C_BUS2, HSC_ADDR, HSC_VOL_CMD, stby_access, 0, 0, 0,
	  SENSOR_INIT_STATUS, NONE, NONE, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_CUR_HSCOUT, TYPE_HSC, I2C_BUS2, HSC_ADDR, HSC_CUR_CMD, stby_access, 0, 0, 0,
	  SENSOR_INIT_STATUS, NONE, NONE, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_PWR_HSCIN, TYPE_HSC, I2C_BUS2, HSC_ADDR, HSC_PWR_CMD, stby_access, 0, 0, 0,
	  SENSOR_INIT_STATUS, NONE, NONE, NULL, NULL, NULL, NULL }
};

snr_cfg fix_class2_sensor_config_table[] = {
	/* number,                  type,       port,      address,      offset,
	   access check arg0, arg1, cache, cache_status, mux_address, mux_offset,
	   pre_sensor_read_fn, pre_sensor_read_args, post_sensor_read_fn, post_sensor_read_fn  */
};

snr_cfg fix_1ou_sensor_config_table[] = {
	/* number,                  type,       port,      address,      offset,
	   access check arg0, arg1, cache, cache_status, mux_address, mux_offset,
	   pre_sensor_read_fn, pre_sensor_read_args, post_sensor_read_fn, post_sensor_read_fn  */
};

snr_cfg fix_dvp_sensor_config_table[] = {
	/* number,                  type,       port,      address,      offset,
	   access check arg0, arg1, cache, cache_status, mux_address, mux_offset,
	   pre_sensor_read_fn, pre_sensor_read_args, post_sensor_read_fn, post_sensor_read_fn  */
};

uint8_t load_sensor_config(void)
{
	memcpy(sensor_config, plat_sensor_config, sizeof(plat_sensor_config));
	return sizeof(plat_sensor_config) / sizeof(snr_cfg);
}

void pal_fix_sensor_config()
{
	// Fix sensor config according to bic type.
	uint8_t fix_sensor_config_num;
	if (get_bic_class()) {
		fix_sensor_config_num = sizeof(fix_class2_sensor_config_table) / sizeof(snr_cfg);
		while (fix_sensor_config_num) {
			add_sensor_config(
				fix_class2_sensor_config_table[fix_sensor_config_num - 1]);
			fix_sensor_config_num--;
		}
	}
	if (get_1ou_status()) {
		fix_sensor_config_num = sizeof(fix_1ou_sensor_config_table) / sizeof(snr_cfg);
		while (fix_sensor_config_num) {
			add_sensor_config(fix_1ou_sensor_config_table[fix_sensor_config_num - 1]);
			fix_sensor_config_num--;
		}
	}
	if (get_2ou_status()) {
		fix_sensor_config_num = sizeof(fix_dvp_sensor_config_table) / sizeof(snr_cfg);
		while (fix_sensor_config_num) {
			add_sensor_config(fix_dvp_sensor_config_table[fix_sensor_config_num - 1]);
			fix_sensor_config_num--;
		}
	}
	if (sensor_config_num != SDR_NUM) {
		printf("fix sensor SDR and config table not match\n");
	}
}
