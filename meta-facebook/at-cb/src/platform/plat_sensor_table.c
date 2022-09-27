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

#include "plat_sensor_table.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pmbus.h"
#include "ast_adc.h"
#include "sensor.h"
#include "hal_gpio.h"
#include "plat_i2c.h"
#include "plat_gpio.h"
#include "plat_hook.h"
#include "pex89000.h"

struct k_mutex i2c_2_tca9543_mutex;
struct k_mutex i2c_3_tca9543_mutex;
struct k_mutex i2c_4_pi4msd5v9542_mutex;

sensor_cfg plat_sensor_config[] = {
	/* number,                  type,       port,      address,      offset,
	   access check arg0, arg1, sample_count, cache, cache_status, mux_ADDRess, mux_offset,
	   pre_sensor_read_fn, pre_sensor_read_args, post_sensor_read_fn, post_sensor_read_fn  */

	/** Temperature **/
	{ SENSOR_NUM_TEMP_TMP75_IN, sensor_dev_tmp75, I2C_BUS2, TMP75_IN_ADDR, TMP75_TEMP_OFFSET,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_TEMP_TMP75_OUT, sensor_dev_tmp75, I2C_BUS2, TMP75_OUT_ADDR, TMP75_TEMP_OFFSET,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },

	/** ADC **/
	{ SENSOR_NUM_VOL_P3V3_AUX, sensor_dev_ast_adc, ADC_PORT3, NONE, NONE, stby_access, 2, 1,
	  SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS,
	  NULL, NULL, NULL, NULL, &adc_asd_init_args[0] },
	{ SENSOR_NUM_VOL_P1V8_PEX, sensor_dev_ast_adc, ADC_PORT4, NONE, NONE, stby_access, 1, 1,
	  SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS,
	  NULL, NULL, NULL, NULL, &adc_asd_init_args[0] },
	{ SENSOR_NUM_VOL_P1V2_AUX, sensor_dev_ast_adc, ADC_PORT5, NONE, NONE, stby_access, 1, 1,
	  SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS,
	  NULL, NULL, NULL, NULL, &adc_asd_init_args[0] },
	{ SENSOR_NUM_VOL_P5V_AUX, sensor_dev_ast_adc, ADC_PORT7, NONE, NONE, stby_access, 711, 200,
	  SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS,
	  NULL, NULL, NULL, NULL, &adc_asd_init_args[0] },
	{ SENSOR_NUM_VOL_P1V8_VDD_1, sensor_dev_ast_adc, ADC_PORT10, NONE, NONE, stby_access, 1, 1,
	  SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS,
	  NULL, NULL, NULL, NULL, &adc_asd_init_args[0] },
	{ SENSOR_NUM_VOL_P1V8_VDD_2, sensor_dev_ast_adc, ADC_PORT11, NONE, NONE, stby_access, 1, 1,
	  SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS,
	  NULL, NULL, NULL, NULL, &adc_asd_init_args[0] },
	{ SENSOR_NUM_VOL_P1V25_VDD_1, sensor_dev_ast_adc, ADC_PORT12, NONE, NONE, stby_access, 1, 1,
	  SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS,
	  NULL, NULL, NULL, NULL, &adc_asd_init_args[0] },
	{ SENSOR_NUM_VOL_P1V25_VDD_2, sensor_dev_ast_adc, ADC_PORT13, NONE, NONE, stby_access, 1, 1,
	  SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS,
	  NULL, NULL, NULL, NULL, &adc_asd_init_args[0] },
	{ SENSOR_NUM_VOL_P0V8_VDD_1, sensor_dev_ast_adc, ADC_PORT14, NONE, NONE, stby_access, 1, 1,
	  SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS,
	  NULL, NULL, NULL, NULL, &adc_asd_init_args[0] },
	{ SENSOR_NUM_VOL_P0V8_VDD_1, sensor_dev_ast_adc, ADC_PORT15, NONE, NONE, stby_access, 1, 1,
	  SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS,
	  NULL, NULL, NULL, NULL, &adc_asd_init_args[0] },

	/** HSC 1 **/
	{ SENSOR_NUM_TEMP_HSC_1, sensor_dev_adm1272, I2C_BUS1, ADM1272_1_ADDR,
	  PMBUS_READ_TEMPERATURE_1, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL,
	  &adm1272_init_args[0] },
	{ SENSOR_NUM_VOL_P51V_AUX_L, sensor_dev_adm1272, I2C_BUS1, ADM1272_1_ADDR, PMBUS_READ_VOUT,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &adm1272_init_args[0] },
	{ SENSOR_NUM_CUR_P51V_AUX_L, sensor_dev_adm1272, I2C_BUS1, ADM1272_1_ADDR, PMBUS_READ_IOUT,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &adm1272_init_args[0] },
	{ SENSOR_NUM_PWR_P51V_AUX_L, sensor_dev_adm1272, I2C_BUS1, ADM1272_1_ADDR, PMBUS_READ_POUT,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &adm1272_init_args[0] },

	/** HSC 2 **/
	{ SENSOR_NUM_TEMP_HSC_2, sensor_dev_adm1272, I2C_BUS1, ADM1272_2_ADDR,
	  PMBUS_READ_TEMPERATURE_1, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL,
	  &adm1272_init_args[1] },
	{ SENSOR_NUM_VOL_P51V_AUX_R, sensor_dev_adm1272, I2C_BUS1, ADM1272_2_ADDR, PMBUS_READ_VOUT,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &adm1272_init_args[1] },
	{ SENSOR_NUM_CUR_P51V_AUX_R, sensor_dev_adm1272, I2C_BUS1, ADM1272_2_ADDR, PMBUS_READ_IOUT,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &adm1272_init_args[1] },
	{ SENSOR_NUM_PWR_P51V_AUX_R, sensor_dev_adm1272, I2C_BUS1, ADM1272_2_ADDR, PMBUS_READ_POUT,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &adm1272_init_args[1] },

	/** Power module **/
	{ SENSOR_NUM_VOL_P12V_AUX_1, sensor_dev_q50sn120a1, I2C_BUS1, Q50SN120A1_1_ADDR,
	  PMBUS_READ_VOUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_CUR_P12V_AUX_1, sensor_dev_q50sn120a1, I2C_BUS1, Q50SN120A1_1_ADDR,
	  PMBUS_READ_IOUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_PWR_P12V_AUX_1, sensor_dev_q50sn120a1, I2C_BUS1, Q50SN120A1_1_ADDR,
	  PMBUS_READ_POUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_VOL_P12V_AUX_2, sensor_dev_q50sn120a1, I2C_BUS1, Q50SN120A1_2_ADDR,
	  PMBUS_READ_VOUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_CUR_P12V_AUX_2, sensor_dev_q50sn120a1, I2C_BUS1, Q50SN120A1_2_ADDR,
	  PMBUS_READ_IOUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_PWR_P12V_AUX_2, sensor_dev_q50sn120a1, I2C_BUS1, Q50SN120A1_2_ADDR,
	  PMBUS_READ_POUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },

	/** VR **/
	{ SENSOR_NUM_TEMP_XDPE15284, sensor_dev_xdpe15284, I2C_BUS1, XDPE15284D_ADDR,
	  PMBUS_READ_TEMPERATURE_1, vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_VOL_XDPE15284, sensor_dev_xdpe15284, I2C_BUS1, XDPE15284D_ADDR,
	  PMBUS_READ_VOUT, vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_CUR_XDPE15284, sensor_dev_xdpe15284, I2C_BUS1, XDPE15284D_ADDR,
	  PMBUS_READ_IOUT, vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_PWR_XDPE15284, sensor_dev_xdpe15284, I2C_BUS1, XDPE15284D_ADDR,
	  PMBUS_READ_POUT, vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },

	/** PEX temp **/
	{ SENSOR_NUM_TEMP_PEX_0, sensor_dev_pex89000, I2C_BUS2, PEX89144_I2CS_ADDR, PEX_TEMP,
	  dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, pre_pex89000_read, &tca9543_configs[0], post_pex89000_read,
	  &tca9543_configs[0], &pex_sensor_init_args[0] },
	{ SENSOR_NUM_TEMP_PEX_1, sensor_dev_pex89000, I2C_BUS3, PEX89144_I2CS_ADDR, PEX_TEMP,
	  dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, pre_pex89000_read, &tca9543_configs[1], post_pex89000_read,
	  &tca9543_configs[1], &pex_sensor_init_args[1] },

	/** INA233 3V3 1 **/
	{ SENSOR_NUM_VOL_INA233_3V3_1, sensor_dev_ina233, I2C_BUS4, INA233_3V3_1_7_ADDR,
	  PMBUS_READ_VOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[0] },
	{ SENSOR_NUM_CUR_INA233_3V3_1, sensor_dev_ina233, I2C_BUS4, INA233_3V3_1_7_ADDR,
	  PMBUS_READ_IOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[0] },
	{ SENSOR_NUM_PWR_INA233_3V3_1, sensor_dev_ina233, I2C_BUS4, INA233_3V3_1_7_ADDR,
	  PMBUS_READ_POUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[0] },

	/** INA233 3V3 2 **/
	{ SENSOR_NUM_VOL_INA233_3V3_2, sensor_dev_ina233, I2C_BUS4, INA233_3V3_2_8_ADDR,
	  PMBUS_READ_VOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[1] },
	{ SENSOR_NUM_CUR_INA233_3V3_2, sensor_dev_ina233, I2C_BUS4, INA233_3V3_2_8_ADDR,
	  PMBUS_READ_IOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[1] },
	{ SENSOR_NUM_PWR_INA233_3V3_2, sensor_dev_ina233, I2C_BUS4, INA233_3V3_2_8_ADDR,
	  PMBUS_READ_POUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[1] },

	/** INA233 3V3 3 **/
	{ SENSOR_NUM_VOL_INA233_3V3_3, sensor_dev_ina233, I2C_BUS4, INA233_3V3_3_9_ADDR,
	  PMBUS_READ_VOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[2] },
	{ SENSOR_NUM_CUR_INA233_3V3_3, sensor_dev_ina233, I2C_BUS4, INA233_3V3_3_9_ADDR,
	  PMBUS_READ_IOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[2] },
	{ SENSOR_NUM_PWR_INA233_3V3_3, sensor_dev_ina233, I2C_BUS4, INA233_3V3_3_9_ADDR,
	  PMBUS_READ_POUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[2] },

	/** INA233 3V3 4 **/
	{ SENSOR_NUM_VOL_INA233_3V3_4, sensor_dev_ina233, I2C_BUS4, INA233_3V3_4_10_ADDR,
	  PMBUS_READ_VOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[3] },
	{ SENSOR_NUM_CUR_INA233_3V3_4, sensor_dev_ina233, I2C_BUS4, INA233_3V3_4_10_ADDR,
	  PMBUS_READ_IOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[3] },
	{ SENSOR_NUM_PWR_INA233_3V3_4, sensor_dev_ina233, I2C_BUS4, INA233_3V3_4_10_ADDR,
	  PMBUS_READ_POUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[3] },

	/** INA233 3V3 5 **/
	{ SENSOR_NUM_VOL_INA233_3V3_5, sensor_dev_ina233, I2C_BUS4, INA233_3V3_5_11_ADDR,
	  PMBUS_READ_VOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[4] },
	{ SENSOR_NUM_CUR_INA233_3V3_5, sensor_dev_ina233, I2C_BUS4, INA233_3V3_5_11_ADDR,
	  PMBUS_READ_IOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[4] },
	{ SENSOR_NUM_PWR_INA233_3V3_5, sensor_dev_ina233, I2C_BUS4, INA233_3V3_5_11_ADDR,
	  PMBUS_READ_POUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[4] },

	/** INA233 3V3 6 **/
	{ SENSOR_NUM_VOL_INA233_3V3_6, sensor_dev_ina233, I2C_BUS4, INA233_3V3_6_12_ADDR,
	  PMBUS_READ_VOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[5] },
	{ SENSOR_NUM_CUR_INA233_3V3_6, sensor_dev_ina233, I2C_BUS4, INA233_3V3_6_12_ADDR,
	  PMBUS_READ_IOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[5] },
	{ SENSOR_NUM_PWR_INA233_3V3_6, sensor_dev_ina233, I2C_BUS4, INA233_3V3_6_12_ADDR,
	  PMBUS_READ_POUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[5] },

	/** INA233 3V3 7 **/
	{ SENSOR_NUM_VOL_INA233_3V3_7, sensor_dev_ina233, I2C_BUS4, INA233_3V3_1_7_ADDR,
	  PMBUS_READ_VOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[6] },
	{ SENSOR_NUM_CUR_INA233_3V3_7, sensor_dev_ina233, I2C_BUS4, INA233_3V3_1_7_ADDR,
	  PMBUS_READ_IOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[6] },
	{ SENSOR_NUM_PWR_INA233_3V3_7, sensor_dev_ina233, I2C_BUS4, INA233_3V3_1_7_ADDR,
	  PMBUS_READ_POUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[6] },

	/** INA233 3V3 8 **/
	{ SENSOR_NUM_VOL_INA233_3V3_8, sensor_dev_ina233, I2C_BUS4, INA233_3V3_2_8_ADDR,
	  PMBUS_READ_VOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[7] },
	{ SENSOR_NUM_CUR_INA233_3V3_8, sensor_dev_ina233, I2C_BUS4, INA233_3V3_2_8_ADDR,
	  PMBUS_READ_IOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[7] },
	{ SENSOR_NUM_PWR_INA233_3V3_8, sensor_dev_ina233, I2C_BUS4, INA233_3V3_2_8_ADDR,
	  PMBUS_READ_POUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[7] },

	/** INA233 3V3 9 **/
	{ SENSOR_NUM_VOL_INA233_3V3_9, sensor_dev_ina233, I2C_BUS4, INA233_3V3_3_9_ADDR,
	  PMBUS_READ_VOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[8] },
	{ SENSOR_NUM_CUR_INA233_3V3_9, sensor_dev_ina233, I2C_BUS4, INA233_3V3_3_9_ADDR,
	  PMBUS_READ_IOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[8] },
	{ SENSOR_NUM_PWR_INA233_3V3_9, sensor_dev_ina233, I2C_BUS4, INA233_3V3_3_9_ADDR,
	  PMBUS_READ_POUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[8] },

	/** INA233 3V3 10 **/
	{ SENSOR_NUM_VOL_INA233_3V3_10, sensor_dev_ina233, I2C_BUS4, INA233_3V3_4_10_ADDR,
	  PMBUS_READ_VOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[9] },
	{ SENSOR_NUM_CUR_INA233_3V3_10, sensor_dev_ina233, I2C_BUS4, INA233_3V3_4_10_ADDR,
	  PMBUS_READ_IOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[9] },
	{ SENSOR_NUM_PWR_INA233_3V3_10, sensor_dev_ina233, I2C_BUS4, INA233_3V3_4_10_ADDR,
	  PMBUS_READ_POUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[9] },

	/** INA233 3V3 11 **/
	{ SENSOR_NUM_VOL_INA233_3V3_11, sensor_dev_ina233, I2C_BUS4, INA233_3V3_5_11_ADDR,
	  PMBUS_READ_VOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[10] },
	{ SENSOR_NUM_CUR_INA233_3V3_11, sensor_dev_ina233, I2C_BUS4, INA233_3V3_5_11_ADDR,
	  PMBUS_READ_IOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[10] },
	{ SENSOR_NUM_PWR_INA233_3V3_11, sensor_dev_ina233, I2C_BUS4, INA233_3V3_5_11_ADDR,
	  PMBUS_READ_POUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[10] },

	/** INA233 3V3 12 **/
	{ SENSOR_NUM_VOL_INA233_3V3_12, sensor_dev_ina233, I2C_BUS4, INA233_3V3_6_12_ADDR,
	  PMBUS_READ_VOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[11] },
	{ SENSOR_NUM_CUR_INA233_3V3_12, sensor_dev_ina233, I2C_BUS4, INA233_3V3_6_12_ADDR,
	  PMBUS_READ_IOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[11] },
	{ SENSOR_NUM_PWR_INA233_3V3_12, sensor_dev_ina233, I2C_BUS4, INA233_3V3_6_12_ADDR,
	  PMBUS_READ_POUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[11] },

	/** INA233 3V3 AUX 1 **/
	{ SENSOR_NUM_VOL_INA233_3V3_AUX_1, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_1_7_ADDR,
	  PMBUS_READ_VOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[0] },
	{ SENSOR_NUM_CUR_INA233_3V3_AUX_1, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_1_7_ADDR,
	  PMBUS_READ_IOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[0] },
	{ SENSOR_NUM_PWR_INA233_3V3_AUX_1, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_1_7_ADDR,
	  PMBUS_READ_POUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[0] },

	/** INA233 3V3 AUX 2 **/
	{ SENSOR_NUM_VOL_INA233_3V3_AUX_2, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_2_8_ADDR,
	  PMBUS_READ_VOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[1] },
	{ SENSOR_NUM_CUR_INA233_3V3_AUX_2, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_2_8_ADDR,
	  PMBUS_READ_IOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[1] },
	{ SENSOR_NUM_PWR_INA233_3V3_AUX_2, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_2_8_ADDR,
	  PMBUS_READ_POUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[1] },

	/** INA233 3V3 AUX 3 **/
	{ SENSOR_NUM_VOL_INA233_3V3_AUX_3, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_3_9_ADDR,
	  PMBUS_READ_VOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[2] },
	{ SENSOR_NUM_CUR_INA233_3V3_AUX_3, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_3_9_ADDR,
	  PMBUS_READ_IOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[2] },
	{ SENSOR_NUM_PWR_INA233_3V3_AUX_3, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_3_9_ADDR,
	  PMBUS_READ_POUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[2] },

	/** INA233 3V3 AUX 4 **/
	{ SENSOR_NUM_VOL_INA233_3V3_AUX_4, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_4_10_ADDR,
	  PMBUS_READ_VOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[3] },
	{ SENSOR_NUM_CUR_INA233_3V3_AUX_4, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_4_10_ADDR,
	  PMBUS_READ_IOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[3] },
	{ SENSOR_NUM_PWR_INA233_3V3_AUX_4, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_4_10_ADDR,
	  PMBUS_READ_POUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[3] },

	/** INA233 3V3 AUX 5 **/
	{ SENSOR_NUM_VOL_INA233_3V3_AUX_5, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_5_11_ADDR,
	  PMBUS_READ_VOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[4] },
	{ SENSOR_NUM_CUR_INA233_3V3_AUX_5, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_5_11_ADDR,
	  PMBUS_READ_IOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[4] },
	{ SENSOR_NUM_PWR_INA233_3V3_AUX_5, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_5_11_ADDR,
	  PMBUS_READ_POUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[4] },

	/** INA233 3V3 AUX 6 **/
	{ SENSOR_NUM_VOL_INA233_3V3_AUX_6, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_6_12_ADDR,
	  PMBUS_READ_VOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[5] },
	{ SENSOR_NUM_CUR_INA233_3V3_AUX_6, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_6_12_ADDR,
	  PMBUS_READ_IOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[5] },
	{ SENSOR_NUM_PWR_INA233_3V3_AUX_6, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_6_12_ADDR,
	  PMBUS_READ_POUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[5] },

	/** INA233 3V3 AUX 7 **/
	{ SENSOR_NUM_VOL_INA233_3V3_AUX_7, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_1_7_ADDR,
	  PMBUS_READ_VOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[6] },
	{ SENSOR_NUM_CUR_INA233_3V3_AUX_7, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_1_7_ADDR,
	  PMBUS_READ_IOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[6] },
	{ SENSOR_NUM_PWR_INA233_3V3_AUX_7, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_1_7_ADDR,
	  PMBUS_READ_POUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[6] },

	/** INA233 3V3 AUX 8 **/
	{ SENSOR_NUM_VOL_INA233_3V3_AUX_8, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_2_8_ADDR,
	  PMBUS_READ_VOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[7] },
	{ SENSOR_NUM_CUR_INA233_3V3_AUX_8, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_2_8_ADDR,
	  PMBUS_READ_IOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[7] },
	{ SENSOR_NUM_PWR_INA233_3V3_AUX_8, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_2_8_ADDR,
	  PMBUS_READ_POUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[7] },

	/** INA233 3V3 AUX 9 **/
	{ SENSOR_NUM_VOL_INA233_3V3_AUX_9, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_3_9_ADDR,
	  PMBUS_READ_VOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[8] },
	{ SENSOR_NUM_CUR_INA233_3V3_AUX_9, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_3_9_ADDR,
	  PMBUS_READ_IOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[8] },
	{ SENSOR_NUM_PWR_INA233_3V3_AUX_9, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_3_9_ADDR,
	  PMBUS_READ_POUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[8] },

	/** INA233 3V3 AUX 10 **/
	{ SENSOR_NUM_VOL_INA233_3V3_AUX_10, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_4_10_ADDR,
	  PMBUS_READ_VOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[9] },
	{ SENSOR_NUM_CUR_INA233_3V3_AUX_10, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_4_10_ADDR,
	  PMBUS_READ_IOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[9] },
	{ SENSOR_NUM_PWR_INA233_3V3_AUX_10, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_4_10_ADDR,
	  PMBUS_READ_POUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[9] },

	/** INA233 3V3 AUX 11 **/
	{ SENSOR_NUM_VOL_INA233_3V3_AUX_11, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_5_11_ADDR,
	  PMBUS_READ_VOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[10] },
	{ SENSOR_NUM_CUR_INA233_3V3_AUX_11, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_5_11_ADDR,
	  PMBUS_READ_IOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[10] },
	{ SENSOR_NUM_PWR_INA233_3V3_AUX_11, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_5_11_ADDR,
	  PMBUS_READ_POUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[10] },

	/** INA233 3V3 AUX 12 **/
	{ SENSOR_NUM_VOL_INA233_3V3_AUX_12, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_6_12_ADDR,
	  PMBUS_READ_VOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[11] },
	{ SENSOR_NUM_CUR_INA233_3V3_AUX_12, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_6_12_ADDR,
	  PMBUS_READ_IOUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[11] },
	{ SENSOR_NUM_PWR_INA233_3V3_AUX_12, sensor_dev_ina233, I2C_BUS5, INA233_3V3_AUX_6_12_ADDR,
	  PMBUS_READ_POUT, dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_aux_init_args[11] },

};

const int SENSOR_CONFIG_SIZE = ARRAY_SIZE(plat_sensor_config);

void load_sensor_config(void)
{
	memcpy(sensor_config, plat_sensor_config, sizeof(plat_sensor_config));
	sensor_config_count = ARRAY_SIZE(plat_sensor_config);

	// Fix config table in different system/config
	pal_extend_sensor_config();
}

struct k_mutex *get_i2c_mux_mutex(uint8_t i2c_bus)
{
	struct k_mutex *mutex = NULL;

	switch (i2c_bus) {
	case I2C_BUS2:
		mutex = &i2c_2_tca9543_mutex;
		break;
	case I2C_BUS3:
		mutex = &i2c_3_tca9543_mutex;
		break;
	case I2C_BUS4:
		mutex = &i2c_4_pi4msd5v9542_mutex;
		break;
	default:
		printf("[%s] not support i2c bus %d mutex\n", __func__, i2c_bus);
		break;
	}

	return mutex;
}
