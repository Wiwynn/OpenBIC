/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <string.h>

#include "ast_adc.h"
#include "sensor.h"
#include "pmbus.h"
#include "intel_peci.h"

#include "plat_i2c.h"
#include "plat_sensor_table.h"
#include "plat_hook.h"

sensor_cfg plat_sensor_config[] = {
	/*  number,
        type,
        port,
        address,
        offset,
        access check,
        arg0,
        arg1,
        sample_count,
        poll time,
        enable polling,
        cache,
        cache_status,
        pre_sensor_read_fn,
        pre_sensor_read_args,
        post_sensor_read_fn,
        post_sensor_read_args,
        initial args
    */
	//Temp
	{ SENSOR_NUM_MB_INLET_TEMP, sensor_dev_tmp75, I2C_BUS2, INLET_TEP75_ADDR, TMP75_TEMP_OFFSET,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_MB_OUTLET_TEMP, sensor_dev_tmp75, I2C_BUS2, OUTLET_TEP75_ADDR,
	  TMP75_TEMP_OFFSET, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_FIO_TEMP, sensor_dev_tmp75, I2C_BUS2, FIO_ADDR, TMP75_TEMP_OFFSET, stby_access,
	  0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },

	{ SENSOR_NUM_CPU_TEMP, sensor_dev_intel_peci, NONE, CPU_PECI_ADDR, PECI_TEMP_CPU,
	  post_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },

	{ SENSOR_NUM_DIMM_A_TEMP, sensor_dev_intel_peci, NONE, CPU_PECI_ADDR,
	  PECI_TEMP_CHANNEL0_DIMM0, post_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_intel_peci_dimm_read, NULL, NULL, NULL,
	  NULL },
	{ SENSOR_NUM_DIMM_B_TEMP, sensor_dev_intel_peci, NONE, CPU_PECI_ADDR,
	  PECI_TEMP_CHANNEL1_DIMM0, post_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_intel_peci_dimm_read, NULL, NULL, NULL,
	  NULL },
	{ SENSOR_NUM_DIMM_C_TEMP, sensor_dev_intel_peci, NONE, CPU_PECI_ADDR,
	  PECI_TEMP_CHANNEL2_DIMM0, post_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_intel_peci_dimm_read, NULL, NULL, NULL,
	  NULL },
	{ SENSOR_NUM_DIMM_D_TEMP, sensor_dev_intel_peci, NONE, CPU_PECI_ADDR,
	  PECI_TEMP_CHANNEL3_DIMM0, post_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_intel_peci_dimm_read, NULL, NULL, NULL,
	  NULL },
	{ SENSOR_NUM_DIMM_E_TEMP, sensor_dev_intel_peci, NONE, CPU_PECI_ADDR,
	  PECI_TEMP_CHANNEL4_DIMM0, post_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_intel_peci_dimm_read, NULL, NULL, NULL,
	  NULL },
	{ SENSOR_NUM_DIMM_F_TEMP, sensor_dev_intel_peci, NONE, CPU_PECI_ADDR,
	  PECI_TEMP_CHANNEL5_DIMM0, post_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_intel_peci_dimm_read, NULL, NULL, NULL,
	  NULL },
	{ SENSOR_NUM_DIMM_G_TEMP, sensor_dev_intel_peci, NONE, CPU_PECI_ADDR,
	  PECI_TEMP_CHANNEL6_DIMM0, post_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_intel_peci_dimm_read, NULL, NULL, NULL,
	  NULL },
	{ SENSOR_NUM_DIMM_H_TEMP, sensor_dev_intel_peci, NONE, CPU_PECI_ADDR,
	  PECI_TEMP_CHANNEL7_DIMM0, post_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_intel_peci_dimm_read, NULL, NULL, NULL,
	  NULL },

	{ SENSOR_NUM_SSD0_TEMP, sensor_dev_nvme, I2C_BUS2, SSD0_ADDR, SSD0_OFFSET, post_access, 0,
	  0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS,
	  pre_nvme_read, &mux_conf_addr_0xe2[1], NULL, NULL, NULL },

	{ SENSOR_NUM_HSC_TEMP, sensor_dev_adm1278, I2C_BUS2, HSC_ADM1278_ADDR,
	  PMBUS_READ_TEMPERATURE_1, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL,
	  &adm1278_init_args[0] },

	{ SENSOR_NUM_VCCIN_SPS_TEMP, sensor_dev_xdpe15284, I2C_BUS5, PVCCIN_ADDR, VR_TEMP_OFFSET,
	  vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_pre_read_args[0], NULL, NULL, NULL },
	{ SENSOR_NUM_EHV_SPS_TEMP, sensor_dev_xdpe15284, I2C_BUS5, EHV_ADDR, VR_TEMP_OFFSET,
	  vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_pre_read_args[1], NULL, NULL, NULL },
	{ SENSOR_NUM_FIVRA_SPS_TEMP, sensor_dev_xdpe15284, I2C_BUS5, FIVRA_ADDR, VR_TEMP_OFFSET,
	  vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_pre_read_args[0], NULL, NULL, NULL },
	{ SENSOR_NUM_VCCINF_SPS_TEMP, sensor_dev_xdpe15284, I2C_BUS5, INF_ADDR, VR_TEMP_OFFSET,
	  vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_pre_read_args[1], NULL, NULL, NULL },
	{ SENSOR_NUM_VCCD0_SPS_TEMP, sensor_dev_xdpe15284, I2C_BUS5, PVCCD0_ADDR, VR_TEMP_OFFSET,
	  vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_pre_read_args[0], NULL, NULL, NULL },
	{ SENSOR_NUM_VCCD1_SPS_TEMP, sensor_dev_xdpe15284, I2C_BUS5, PVCCD1_ADDR, VR_TEMP_OFFSET,
	  vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_pre_read_args[1], NULL, NULL, NULL },

	{ SENSOR_NUM_SOC_THERM_MARGIN_TEMP, sensor_dev_intel_peci, NONE, CPU_PECI_ADDR,
	  PECI_TEMP_CPU_MARGIN, post_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, post_cpu_margin_read, NULL,
	  NULL },
	{ SENSOR_NUM_CPU_TJMAX_TEMP, sensor_dev_intel_peci, NONE, CPU_PECI_ADDR,
	  PECI_TEMP_CPU_TJMAX, post_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },

	//ADC Voltage
	{ SENSOR_NUM_P12V_STBY_VOL, sensor_dev_ast_adc, ADC_PORT0, NONE, NONE, stby_access, 667,
	  100, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &adc_asd_init_args[0] },
	{ SENSOR_NUM_P3V_BAT_VOL, sensor_dev_ast_adc, ADC_PORT4, NONE, NONE, stby_access, 3, 1,
	  SAMPLE_COUNT_DEFAULT, POLL_TIME_BAT3V, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS,
	  pre_vol_bat3v_read, NULL, post_vol_bat3v_read, NULL, &adc_asd_init_args[0] },
	{ SENSOR_NUM_P3V3_STBY_VOL, sensor_dev_ast_adc, ADC_PORT2, NONE, NONE, stby_access, 2, 1,
	  SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS,
	  NULL, NULL, NULL, NULL, &adc_asd_init_args[0] },
	{ SENSOR_NUM_P1V8_STBY_VOL, sensor_dev_ast_adc, ADC_PORT15, NONE, NONE, stby_access, 1, 1,
	  SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS,
	  NULL, NULL, NULL, NULL, &adc_asd_init_args[0] },
	{ SENSOR_NUM_P1V05_VOL, sensor_dev_ast_adc, ADC_PORT3, NONE, NONE, stby_access, 1, 1,
	  SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS,
	  NULL, NULL, NULL, NULL, &adc_asd_init_args[0] },
	{ SENSOR_NUM_P5V_STBY_VOL, sensor_dev_ast_adc, ADC_PORT9, NONE, NONE, stby_access, 711, 200,
	  SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS,
	  NULL, NULL, NULL, NULL, &adc_asd_init_args[0] },
	{ SENSOR_NUM_P12V_DIMM_VOL, sensor_dev_ast_adc, ADC_PORT11, NONE, NONE, dc_access, 667,
	  100, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &adc_asd_init_args[0] },
	{ SENSOR_NUM_P1V2_STBY_VOL, sensor_dev_ast_adc, ADC_PORT13, NONE, NONE, stby_access, 1, 1,
	  SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS,
	  NULL, NULL, NULL, NULL, &adc_asd_init_args[0] },
	{ SENSOR_NUM_P3V3_M2_VOL, sensor_dev_ast_adc, ADC_PORT14, NONE, NONE, dc_access, 2, 1,
	  SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS,
	  NULL, NULL, NULL, NULL, &adc_asd_init_args[0] },
	{ SENSOR_NUM_PVNN_MAIN_VOL, sensor_dev_ast_adc, ADC_PORT8, NONE, NONE, stby_access, 1, 1,
	  SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS,
	  NULL, NULL, NULL, NULL, &adc_asd_init_args[0] },

	//Voltage
	{ SENSOR_NUM_HSC_INPUT_VOL, sensor_dev_adm1278, I2C_BUS2, HSC_ADM1278_ADDR, PMBUS_READ_VIN,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &adm1278_init_args[0] },

	{ SENSOR_NUM_VCCIN_VR_VOL, sensor_dev_xdpe15284, I2C_BUS5, PVCCIN_ADDR, VR_VOL_OFFSET,
	  vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_pre_read_args[0], NULL, NULL, NULL },
	{ SENSOR_NUM_EHV_VR_VOL, sensor_dev_xdpe15284, I2C_BUS5, EHV_ADDR, VR_VOL_OFFSET, vr_access,
	  0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_pre_read_args[1], NULL, NULL, NULL },
	{ SENSOR_NUM_FIVRA_VR_VOL, sensor_dev_xdpe15284, I2C_BUS5, FIVRA_ADDR, VR_VOL_OFFSET,
	  vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_pre_read_args[0], NULL, NULL, NULL },
	{ SENSOR_NUM_VCCINF_VR_VOL, sensor_dev_xdpe15284, I2C_BUS5, INF_ADDR, VR_VOL_OFFSET,
	  vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_pre_read_args[1], NULL, NULL, NULL },
	{ SENSOR_NUM_VCCDO_VR_VOL, sensor_dev_xdpe15284, I2C_BUS5, PVCCD0_ADDR, VR_VOL_OFFSET,
	  vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_pre_read_args[0], NULL, NULL, NULL },
	{ SENSOR_NUM_VCCD1_VR_VOL, sensor_dev_xdpe15284, I2C_BUS5, PVCCD1_ADDR, VR_VOL_OFFSET,
	  vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_pre_read_args[1], NULL, NULL, NULL },

	//Current
	{ SENSOR_NUM_1OU_HSC_OUTPUT_CUR, sensor_dev_adm1278, I2C_BUS2, HSC_ADM1278_ADDR,
	  PMBUS_READ_IOUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL,
	  &adm1278_init_args[0] },

	{ SENSOR_NUM_VCCIN_VR_CUR, sensor_dev_xdpe15284, I2C_BUS5, PVCCIN_ADDR, VR_CUR_OFFSET,
	  vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_pre_read_args[0], NULL, NULL, NULL },
	{ SENSOR_NUM_EHV_VR_CUR, sensor_dev_xdpe15284, I2C_BUS5, EHV_ADDR, VR_CUR_OFFSET, vr_access,
	  0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_pre_read_args[1], NULL, NULL, NULL },
	{ SENSOR_NUM_FIVRA_VR_CUR, sensor_dev_xdpe15284, I2C_BUS5, FIVRA_ADDR, VR_CUR_OFFSET,
	  vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_pre_read_args[0], NULL, NULL, NULL },
	{ SENSOR_NUM_VCCINF_VR_CUR, sensor_dev_xdpe15284, I2C_BUS5, INF_ADDR, VR_CUR_OFFSET,
	  vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_pre_read_args[1], NULL, NULL, NULL },
	{ SENSOR_NUM_VCCD0_VR_CUR, sensor_dev_xdpe15284, I2C_BUS5, PVCCD0_ADDR, VR_CUR_OFFSET,
	  vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_pre_read_args[0], NULL, NULL, NULL },
	{ SENSOR_NUM_VCCD1_VR_CUR, sensor_dev_xdpe15284, I2C_BUS5, PVCCD1_ADDR, VR_CUR_OFFSET,
	  vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_pre_read_args[1], NULL, NULL, NULL },

	//Power
	{ SENSOR_NUM_1OU_HSC_INPUT_PWR, sensor_dev_adm1278, I2C_BUS2, HSC_ADM1278_ADDR,
	  PMBUS_READ_PIN, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL,
	  &adm1278_init_args[0] },

	{ SENSOR_NUM_VCCIN_VR_PWR, sensor_dev_xdpe15284, I2C_BUS5, PVCCIN_ADDR, VR_PWR_OFFSET,
	  vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_pre_read_args[0], NULL, NULL, NULL },
	{ SENSOR_NUM_EHV_VR_PWR, sensor_dev_xdpe15284, I2C_BUS5, EHV_ADDR, VR_PWR_OFFSET, vr_access,
	  0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_pre_read_args[1], NULL, NULL, NULL },
	{ SENSOR_NUM_FIVRA_VR_PWR, sensor_dev_xdpe15284, I2C_BUS5, FIVRA_ADDR, VR_PWR_OFFSET,
	  vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_pre_read_args[0], NULL, NULL, NULL },
	{ SENSOR_NUM_VCCINF_VR_PWR, sensor_dev_xdpe15284, I2C_BUS5, INF_ADDR, VR_PWR_OFFSET,
	  vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_pre_read_args[1], NULL, NULL, NULL },
	{ SENSOR_NUM_VCCD0_VR_PWR, sensor_dev_xdpe15284, I2C_BUS5, PVCCD0_ADDR, VR_PWR_OFFSET,
	  vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_pre_read_args[0], NULL, NULL, NULL },
	{ SENSOR_NUM_VCCD1_VR_PWR, sensor_dev_xdpe15284, I2C_BUS5, PVCCD1_ADDR, VR_PWR_OFFSET,
	  vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_pre_read_args[1], NULL, NULL, NULL },

	/* TODO:
	 * DIMM power sensors are pending because I3C hasn't be ready yet.
	 */
};

const int SENSOR_CONFIG_SIZE = ARRAY_SIZE(plat_sensor_config);
