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
#include <logging/log.h>
#include "pmbus.h"
#include "ast_adc.h"
#include "sensor.h"
#include "hal_gpio.h"
#include "plat_i2c.h"
#include "pex89000.h"
#include "plat_gpio.h"
#include "plat_hook.h"
#include "plat_class.h"
#include "plat_dev.h"
#include "sq52205.h"

LOG_MODULE_REGISTER(plat_sensor_table);

struct k_mutex i2c_2_tca9543_mutex;
struct k_mutex i2c_3_tca9543_mutex;
struct k_mutex i2c_4_pi4msd5v9542_mutex;
struct k_mutex i2c_7_mutex;
struct k_mutex i2c_8_mutex;

sensor_cfg plat_sensor_config[] = {
	/* number,                  type,       port,      address,      offset,
	   access check arg0, arg1, sample_count, cache, cache_status, mux_ADDRess, mux_offset,
	   pre_sensor_read_fn, pre_sensor_read_args, post_sensor_read_fn, post_sensor_read_fn  */

	/** Temperature **/
	{ SENSOR_NUM_TEMP_OUTLET_1, sensor_dev_tmp75, I2C_BUS2, TMP75_IN_ADDR, TMP75_TEMP_OFFSET,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_TEMP_OUTLET_2, sensor_dev_tmp75, I2C_BUS2, TMP75_OUT_ADDR, TMP75_TEMP_OFFSET,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_TEMP_FIO_INLET, sensor_dev_lm75bd118, I2C_BUS10, FIO_THERMAL_ADDR,
	  LM75BD118_TEMP_OFFSET, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },

	/** ADC **/
	{ SENSOR_NUM_VOL_P3V3_AUX, sensor_dev_ast_adc, ADC_PORT3, NONE, NONE, stby_access, 2, 1,
	  SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS,
	  NULL, NULL, NULL, NULL, &adc_asd_init_args[0] },
	{ SENSOR_NUM_VOL_P1V8_PEX, sensor_dev_ast_adc, ADC_PORT4, NONE, NONE, is_dc_access, 1, 1,
	  SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS,
	  NULL, NULL, NULL, NULL, &adc_asd_init_args[0] },
	{ SENSOR_NUM_VOL_P1V2_AUX, sensor_dev_ast_adc, ADC_PORT5, NONE, NONE, stby_access, 1, 1,
	  SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS,
	  NULL, NULL, NULL, NULL, &adc_asd_init_args[0] },
	{ SENSOR_NUM_VOL_P5V_AUX, sensor_dev_ast_adc, ADC_PORT7, NONE, NONE, stby_access, 711, 200,
	  SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS,
	  NULL, NULL, NULL, NULL, &adc_asd_init_args[0] },
	{ SENSOR_NUM_VOL_P1V8_VDD_1, sensor_dev_ast_adc, ADC_PORT10, NONE, NONE, is_dc_access, 1, 1,
	  SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS,
	  NULL, NULL, NULL, NULL, &adc_asd_init_args[0] },
	{ SENSOR_NUM_VOL_P1V8_VDD_2, sensor_dev_ast_adc, ADC_PORT11, NONE, NONE, is_dc_access, 1, 1,
	  SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS,
	  NULL, NULL, NULL, NULL, &adc_asd_init_args[0] },
	{ SENSOR_NUM_VOL_P1V25_VDD_1, sensor_dev_ast_adc, ADC_PORT12, NONE, NONE, is_dc_access, 1,
	  1, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS,
	  NULL, NULL, NULL, NULL, &adc_asd_init_args[0] },
	{ SENSOR_NUM_VOL_P1V25_VDD_2, sensor_dev_ast_adc, ADC_PORT13, NONE, NONE, is_dc_access, 1,
	  1, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS,
	  NULL, NULL, NULL, NULL, &adc_asd_init_args[0] },

	/** VR **/
	{ SENSOR_NUM_TEMP_P0V8_VDD_1, sensor_dev_xdpe15284, I2C_BUS1, XDPE15284D_ADDR,
	  PMBUS_READ_TEMPERATURE_1, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_page[0],
	  post_xdpe15284_read, NULL, NULL },
	{ SENSOR_NUM_VOL_P0V8_VDD_1, sensor_dev_xdpe15284, I2C_BUS1, XDPE15284D_ADDR,
	  PMBUS_READ_VOUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_page[0],
	  post_xdpe15284_read, NULL, NULL },
	{ SENSOR_NUM_CUR_P0V8_VDD_1, sensor_dev_xdpe15284, I2C_BUS1, XDPE15284D_ADDR,
	  PMBUS_READ_IOUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_page[0],
	  post_xdpe15284_read, NULL, NULL },
	{ SENSOR_NUM_PWR_P0V8_VDD_1, sensor_dev_xdpe15284, I2C_BUS1, XDPE15284D_ADDR,
	  PMBUS_READ_POUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_page[0],
	  post_xdpe15284_read, NULL, NULL },

	{ SENSOR_NUM_TEMP_P0V8_VDD_2, sensor_dev_xdpe15284, I2C_BUS1, XDPE15284D_ADDR,
	  PMBUS_READ_TEMPERATURE_1, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_page[1],
	  post_xdpe15284_read, NULL, NULL },
	{ SENSOR_NUM_VOL_P0V8_VDD_2, sensor_dev_xdpe15284, I2C_BUS1, XDPE15284D_ADDR,
	  PMBUS_READ_VOUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_page[1],
	  post_xdpe15284_read, NULL, NULL },
	{ SENSOR_NUM_CUR_P0V8_VDD_2, sensor_dev_xdpe15284, I2C_BUS1, XDPE15284D_ADDR,
	  PMBUS_READ_IOUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_page[1],
	  post_xdpe15284_read, NULL, NULL },
	{ SENSOR_NUM_PWR_P0V8_VDD_2, sensor_dev_xdpe15284, I2C_BUS1, XDPE15284D_ADDR,
	  PMBUS_READ_POUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_xdpe15284_read, &xdpe15284_page[1],
	  post_xdpe15284_read, NULL, NULL },

	/** PEX temp **/
	{ SENSOR_NUM_TEMP_PEX_0, sensor_dev_pex89000, I2C_BUS2, PEX89144_I2CS_ADDR, PEX_TEMP,
	  is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, pre_pex89000_read, &tca9543_configs[0], post_pex89000_read,
	  &tca9543_configs[0], &pex_sensor_init_args[0] },
	{ SENSOR_NUM_TEMP_PEX_1, sensor_dev_pex89000, I2C_BUS3, PEX89144_I2CS_ADDR, PEX_TEMP,
	  is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, pre_pex89000_read, &tca9543_configs[1], post_pex89000_read,
	  &tca9543_configs[1], &pex_sensor_init_args[1] },

	/** SQ52205 **/
	{ SENSOR_NUM_VOL_P12V_1_M_AUX, sensor_dev_sq52205, I2C_BUS2, SQ52205_P1V25_1_ADDR,
	  SQ52205_READ_VOL_OFFSET, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL,
	  &sq52205_init_args[0] },
	{ SENSOR_NUM_CUR_P12V_1_M_AUX, sensor_dev_sq52205, I2C_BUS2, SQ52205_P1V25_1_ADDR,
	  SQ52205_READ_CUR_OFFSET, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL,
	  &sq52205_init_args[0] },
	{ SENSOR_NUM_PWR_P12V_1_M_AUX, sensor_dev_sq52205, I2C_BUS2, SQ52205_P1V25_1_ADDR,
	  SQ52205_READ_PWR_OFFSET, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL,
	  &sq52205_init_args[0] },
	{ SENSOR_NUM_VOL_P12V_2_M_AUX, sensor_dev_sq52205, I2C_BUS2, SQ52205_P1V25_2_ADDR,
	  SQ52205_READ_VOL_OFFSET, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL,
	  &sq52205_init_args[1] },
	{ SENSOR_NUM_CUR_P12V_2_M_AUX, sensor_dev_sq52205, I2C_BUS2, SQ52205_P1V25_2_ADDR,
	  SQ52205_READ_CUR_OFFSET, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL,
	  &sq52205_init_args[1] },
	{ SENSOR_NUM_PWR_P12V_2_M_AUX, sensor_dev_sq52205, I2C_BUS2, SQ52205_P1V25_2_ADDR,
	  SQ52205_READ_PWR_OFFSET, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL,
	  &sq52205_init_args[1] },

	/** INA233 12V 1 **/
	{ SENSOR_NUM_VOL_P12V_ACCL_1, sensor_dev_ina233, I2C_BUS4, INA233_12V_1_7_ADDR,
	  PMBUS_READ_VOUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[0] },
	{ SENSOR_NUM_CUR_P12V_ACCL_1, sensor_dev_ina233, I2C_BUS4, INA233_12V_1_7_ADDR,
	  PMBUS_READ_IOUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[0] },
	{ SENSOR_NUM_PWR_P12V_ACCL_1, sensor_dev_ina233, I2C_BUS4, INA233_12V_1_7_ADDR,
	  PMBUS_READ_POUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[0] },

	/** INA233 12V 2 **/
	{ SENSOR_NUM_VOL_P12V_ACCL_2, sensor_dev_ina233, I2C_BUS4, INA233_12V_2_8_ADDR,
	  PMBUS_READ_VOUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[1] },
	{ SENSOR_NUM_CUR_P12V_ACCL_2, sensor_dev_ina233, I2C_BUS4, INA233_12V_2_8_ADDR,
	  PMBUS_READ_IOUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[1] },
	{ SENSOR_NUM_PWR_P12V_ACCL_2, sensor_dev_ina233, I2C_BUS4, INA233_12V_2_8_ADDR,
	  PMBUS_READ_POUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[1] },

	/** INA233 12V 3 **/
	{ SENSOR_NUM_VOL_P12V_ACCL_3, sensor_dev_ina233, I2C_BUS4, INA233_12V_3_9_ADDR,
	  PMBUS_READ_VOUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[2] },
	{ SENSOR_NUM_CUR_P12V_ACCL_3, sensor_dev_ina233, I2C_BUS4, INA233_12V_3_9_ADDR,
	  PMBUS_READ_IOUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[2] },
	{ SENSOR_NUM_PWR_P12V_ACCL_3, sensor_dev_ina233, I2C_BUS4, INA233_12V_3_9_ADDR,
	  PMBUS_READ_POUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[2] },

	/** INA233 12V 4 **/
	{ SENSOR_NUM_VOL_P12V_ACCL_4, sensor_dev_ina233, I2C_BUS4, INA233_12V_4_10_ADDR,
	  PMBUS_READ_VOUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[3] },
	{ SENSOR_NUM_CUR_P12V_ACCL_4, sensor_dev_ina233, I2C_BUS4, INA233_12V_4_10_ADDR,
	  PMBUS_READ_IOUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[3] },
	{ SENSOR_NUM_PWR_P12V_ACCL_4, sensor_dev_ina233, I2C_BUS4, INA233_12V_4_10_ADDR,
	  PMBUS_READ_POUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[3] },

	/** INA233 12V 5 **/
	{ SENSOR_NUM_VOL_P12V_ACCL_5, sensor_dev_ina233, I2C_BUS4, INA233_12V_5_11_ADDR,
	  PMBUS_READ_VOUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[4] },
	{ SENSOR_NUM_CUR_P12V_ACCL_5, sensor_dev_ina233, I2C_BUS4, INA233_12V_5_11_ADDR,
	  PMBUS_READ_IOUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[4] },
	{ SENSOR_NUM_PWR_P12V_ACCL_5, sensor_dev_ina233, I2C_BUS4, INA233_12V_5_11_ADDR,
	  PMBUS_READ_POUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[4] },

	/** INA233 12V 6 **/
	{ SENSOR_NUM_VOL_P12V_ACCL_6, sensor_dev_ina233, I2C_BUS4, INA233_12V_6_ADDR,
	  PMBUS_READ_VOUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[5] },
	{ SENSOR_NUM_CUR_P12V_ACCL_6, sensor_dev_ina233, I2C_BUS4, INA233_12V_6_ADDR,
	  PMBUS_READ_IOUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[5] },
	{ SENSOR_NUM_PWR_P12V_ACCL_6, sensor_dev_ina233, I2C_BUS4, INA233_12V_6_ADDR,
	  PMBUS_READ_POUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[0],
	  post_ina233_read, &pi4msd5v9542_configs[0], &ina233_init_args[5] },

	/** INA233 12V 7 **/
	{ SENSOR_NUM_VOL_P12V_ACCL_7, sensor_dev_ina233, I2C_BUS4, INA233_12V_1_7_ADDR,
	  PMBUS_READ_VOUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_init_args[6] },
	{ SENSOR_NUM_CUR_P12V_ACCL_7, sensor_dev_ina233, I2C_BUS4, INA233_12V_1_7_ADDR,
	  PMBUS_READ_IOUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_init_args[6] },
	{ SENSOR_NUM_PWR_P12V_ACCL_7, sensor_dev_ina233, I2C_BUS4, INA233_12V_1_7_ADDR,
	  PMBUS_READ_POUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_init_args[6] },

	/** INA233 12V 8 **/
	{ SENSOR_NUM_VOL_P12V_ACCL_8, sensor_dev_ina233, I2C_BUS4, INA233_12V_2_8_ADDR,
	  PMBUS_READ_VOUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_init_args[7] },
	{ SENSOR_NUM_CUR_P12V_ACCL_8, sensor_dev_ina233, I2C_BUS4, INA233_12V_2_8_ADDR,
	  PMBUS_READ_IOUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_init_args[7] },
	{ SENSOR_NUM_PWR_P12V_ACCL_8, sensor_dev_ina233, I2C_BUS4, INA233_12V_2_8_ADDR,
	  PMBUS_READ_POUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_init_args[7] },

	/** INA233 12V 9 **/
	{ SENSOR_NUM_VOL_P12V_ACCL_9, sensor_dev_ina233, I2C_BUS4, INA233_12V_3_9_ADDR,
	  PMBUS_READ_VOUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_init_args[8] },
	{ SENSOR_NUM_CUR_P12V_ACCL_9, sensor_dev_ina233, I2C_BUS4, INA233_12V_3_9_ADDR,
	  PMBUS_READ_IOUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_init_args[8] },
	{ SENSOR_NUM_PWR_P12V_ACCL_9, sensor_dev_ina233, I2C_BUS4, INA233_12V_3_9_ADDR,
	  PMBUS_READ_POUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_init_args[8] },

	/** INA233 12V 10 **/
	{ SENSOR_NUM_VOL_P12V_ACCL_10, sensor_dev_ina233, I2C_BUS4, INA233_12V_4_10_ADDR,
	  PMBUS_READ_VOUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_init_args[9] },
	{ SENSOR_NUM_CUR_P12V_ACCL_10, sensor_dev_ina233, I2C_BUS4, INA233_12V_4_10_ADDR,
	  PMBUS_READ_IOUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_init_args[9] },
	{ SENSOR_NUM_PWR_P12V_ACCL_10, sensor_dev_ina233, I2C_BUS4, INA233_12V_4_10_ADDR,
	  PMBUS_READ_POUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_init_args[9] },

	/** INA233 12V 11 **/
	{ SENSOR_NUM_VOL_P12V_ACCL_11, sensor_dev_ina233, I2C_BUS4, INA233_12V_5_11_ADDR,
	  PMBUS_READ_VOUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_init_args[10] },
	{ SENSOR_NUM_CUR_P12V_ACCL_11, sensor_dev_ina233, I2C_BUS4, INA233_12V_5_11_ADDR,
	  PMBUS_READ_IOUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_init_args[10] },
	{ SENSOR_NUM_PWR_P12V_ACCL_11, sensor_dev_ina233, I2C_BUS4, INA233_12V_5_11_ADDR,
	  PMBUS_READ_POUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_init_args[10] },

	/** INA233 12V 12 **/
	{ SENSOR_NUM_VOL_P12V_ACCL_12, sensor_dev_ina233, I2C_BUS4, INA233_12V_12_ADDR,
	  PMBUS_READ_VOUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_init_args[11] },
	{ SENSOR_NUM_CUR_P12V_ACCL_12, sensor_dev_ina233, I2C_BUS4, INA233_12V_12_ADDR,
	  PMBUS_READ_IOUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_init_args[11] },
	{ SENSOR_NUM_PWR_P12V_ACCL_12, sensor_dev_ina233, I2C_BUS4, INA233_12V_12_ADDR,
	  PMBUS_READ_POUT, is_dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_ina233_read, &pi4msd5v9542_configs[1],
	  post_ina233_read, &pi4msd5v9542_configs[1], &ina233_init_args[11] },
};

sensor_cfg plat_accl_sensor_config[] = {
	/** Nvme Temperature **/
	{ SENSOR_NUM_TEMP_ACCL_FREYA_1, sensor_dev_nvme, NONE, ACCL_FREYA_1_ADDR, NVME_TEMP_OFFSET,
	  NULL, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL, &pca9546_configs[0] },
	{ SENSOR_NUM_TEMP_ACCL_FREYA_2, sensor_dev_nvme, NONE, ACCL_FREYA_2_ADDR, NVME_TEMP_OFFSET,
	  NULL, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL, &pca9546_configs[0] },

	/** Nvme Voltage **/
	{ SENSOR_NUM_VOL_ACCL_FREYA_1_1, sensor_dev_nvme, NONE, ACCL_FREYA_1_ADDR,
	  NVME_VOLTAGE_RAIL_1_OFFSET, NULL, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL,
	  &pca9546_configs[0] },
	{ SENSOR_NUM_VOL_ACCL_FREYA_1_2, sensor_dev_nvme, NONE, ACCL_FREYA_1_ADDR,
	  NVME_VOLTAGE_RAIL_2_OFFSET, NULL, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL,
	  &pca9546_configs[0] },
	{ SENSOR_NUM_VOL_ACCL_FREYA_2_1, sensor_dev_nvme, NONE, ACCL_FREYA_2_ADDR,
	  NVME_VOLTAGE_RAIL_1_OFFSET, NULL, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL,
	  &pca9546_configs[0] },
	{ SENSOR_NUM_VOL_ACCL_FREYA_2_2, sensor_dev_nvme, NONE, ACCL_FREYA_2_ADDR,
	  NVME_VOLTAGE_RAIL_2_OFFSET, NULL, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL,
	  &pca9546_configs[0] },

	/** INA233 Voltage **/
	{ SENSOR_NUM_VOL_ACCL_P12V_EFUSE, sensor_dev_ina233, NONE, ACCL_12V_INA233_ADDR,
	  PMBUS_READ_VOUT, NULL, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL,
	  &pca9546_configs[3] },
	{ SENSOR_NUM_VOL_ACCL_P3V3_1, sensor_dev_ina233, NONE, ACCL_3V3_1_INA233_ADDR,
	  PMBUS_READ_VOUT, NULL, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL,
	  &pca9546_configs[3] },
	{ SENSOR_NUM_VOL_ACCL_P3V3_2, sensor_dev_ina233, NONE, ACCL_3V3_2_INA233_ADDR,
	  PMBUS_READ_VOUT, NULL, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL,
	  &pca9546_configs[3] },

	/** INA233 Current **/
	{ SENSOR_NUM_CUR_ACCL_P12V_EFUSE, sensor_dev_ina233, NONE, ACCL_12V_INA233_ADDR,
	  PMBUS_READ_IOUT, NULL, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL,
	  &pca9546_configs[3] },
	{ SENSOR_NUM_CUR_ACCL_P3V3_1, sensor_dev_ina233, NONE, ACCL_3V3_1_INA233_ADDR,
	  PMBUS_READ_IOUT, NULL, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL,
	  &pca9546_configs[3] },
	{ SENSOR_NUM_CUR_ACCL_P3V3_2, sensor_dev_ina233, NONE, ACCL_3V3_2_INA233_ADDR,
	  PMBUS_READ_IOUT, NULL, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL,
	  &pca9546_configs[3] },

	/** INA233 Power **/
	{ SENSOR_NUM_PWR_ACCL_P12V_EFUSE, sensor_dev_ina233, NONE, ACCL_12V_INA233_ADDR,
	  PMBUS_READ_POUT, NULL, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL,
	  &pca9546_configs[3] },
	{ SENSOR_NUM_PWR_ACCL_P3V3_1, sensor_dev_ina233, NONE, ACCL_3V3_1_INA233_ADDR,
	  PMBUS_READ_POUT, NULL, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL,
	  &pca9546_configs[3] },
	{ SENSOR_NUM_PWR_ACCL_P3V3_2, sensor_dev_ina233, NONE, ACCL_3V3_2_INA233_ADDR,
	  PMBUS_READ_POUT, NULL, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL,
	  &pca9546_configs[3] },
};

sensor_cfg adm1272_sensor_config_table[] = {
	{ SENSOR_NUM_TEMP_HSC_1, sensor_dev_adm1272, I2C_BUS1, ADM1272_1_ADDR,
	  PMBUS_READ_TEMPERATURE_1, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL,
	  &adm1272_init_args[0] },
	{ SENSOR_NUM_VOL_P51V_STBY_L, sensor_dev_adm1272, I2C_BUS1, ADM1272_1_ADDR, PMBUS_READ_VIN,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &adm1272_init_args[0] },
	{ SENSOR_NUM_VOL_P51V_AUX_L, sensor_dev_adm1272, I2C_BUS1, ADM1272_1_ADDR, PMBUS_READ_VOUT,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &adm1272_init_args[0] },
	{ SENSOR_NUM_CUR_P51V_STBY_L, sensor_dev_adm1272, I2C_BUS1, ADM1272_1_ADDR, PMBUS_READ_IIN,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &adm1272_init_args[0] },
	{ SENSOR_NUM_CUR_P51V_AUX_L, sensor_dev_adm1272, I2C_BUS1, ADM1272_1_ADDR, PMBUS_READ_IOUT,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &adm1272_init_args[0] },
	{ SENSOR_NUM_PWR_P51V_STBY_L, sensor_dev_adm1272, I2C_BUS1, ADM1272_1_ADDR, PMBUS_READ_PIN,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &adm1272_init_args[0] },
	{ SENSOR_NUM_PWR_P51V_AUX_L, sensor_dev_adm1272, I2C_BUS1, ADM1272_1_ADDR, PMBUS_READ_POUT,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &adm1272_init_args[0] },

	{ SENSOR_NUM_TEMP_HSC_2, sensor_dev_adm1272, I2C_BUS1, ADM1272_2_ADDR,
	  PMBUS_READ_TEMPERATURE_1, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL,
	  &adm1272_init_args[1] },
	{ SENSOR_NUM_VOL_P51V_STBY_R, sensor_dev_adm1272, I2C_BUS1, ADM1272_2_ADDR, PMBUS_READ_VIN,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &adm1272_init_args[1] },
	{ SENSOR_NUM_VOL_P51V_AUX_R, sensor_dev_adm1272, I2C_BUS1, ADM1272_2_ADDR, PMBUS_READ_VOUT,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &adm1272_init_args[1] },
	{ SENSOR_NUM_CUR_P51V_STBY_R, sensor_dev_adm1272, I2C_BUS1, ADM1272_2_ADDR, PMBUS_READ_IIN,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &adm1272_init_args[1] },
	{ SENSOR_NUM_CUR_P51V_AUX_R, sensor_dev_adm1272, I2C_BUS1, ADM1272_2_ADDR, PMBUS_READ_IOUT,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &adm1272_init_args[1] },
	{ SENSOR_NUM_PWR_P51V_STBY_R, sensor_dev_adm1272, I2C_BUS1, ADM1272_2_ADDR, PMBUS_READ_PIN,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &adm1272_init_args[1] },
	{ SENSOR_NUM_PWR_P51V_AUX_R, sensor_dev_adm1272, I2C_BUS1, ADM1272_2_ADDR, PMBUS_READ_POUT,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &adm1272_init_args[1] },
};

sensor_cfg ltc4286_sensor_config_table[] = {
	{ SENSOR_NUM_TEMP_HSC_1, sensor_dev_ltc4286, I2C_BUS1, LTC4286_1_ADDR,
	  PMBUS_READ_TEMPERATURE_1, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL,
	  &ltc4286_init_args[0] },
	{ SENSOR_NUM_VOL_P51V_STBY_L, sensor_dev_ltc4286, I2C_BUS1, LTC4286_1_ADDR, PMBUS_READ_VIN,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &ltc4286_init_args[0] },
	{ SENSOR_NUM_VOL_P51V_AUX_L, sensor_dev_ltc4286, I2C_BUS1, LTC4286_1_ADDR, PMBUS_READ_VOUT,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &ltc4286_init_args[0] },
	{ SENSOR_NUM_CUR_P51V_STBY_L, sensor_dev_ltc4286, I2C_BUS1, LTC4286_1_ADDR, PMBUS_READ_IIN,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &ltc4286_init_args[0] },
	{ SENSOR_NUM_CUR_P51V_AUX_L, sensor_dev_ltc4286, I2C_BUS1, LTC4286_1_ADDR, PMBUS_READ_IOUT,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &ltc4286_init_args[0] },
	{ SENSOR_NUM_PWR_P51V_STBY_L, sensor_dev_ltc4286, I2C_BUS1, LTC4286_1_ADDR, PMBUS_READ_PIN,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &ltc4286_init_args[0] },
	{ SENSOR_NUM_PWR_P51V_AUX_L, sensor_dev_ltc4286, I2C_BUS1, LTC4286_1_ADDR, PMBUS_READ_POUT,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &ltc4286_init_args[0] },

	{ SENSOR_NUM_TEMP_HSC_2, sensor_dev_ltc4286, I2C_BUS1, LTC4286_2_ADDR,
	  PMBUS_READ_TEMPERATURE_1, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL,
	  &ltc4286_init_args[1] },
	{ SENSOR_NUM_VOL_P51V_STBY_R, sensor_dev_ltc4286, I2C_BUS1, LTC4286_2_ADDR, PMBUS_READ_VIN,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &ltc4286_init_args[1] },
	{ SENSOR_NUM_VOL_P51V_AUX_R, sensor_dev_ltc4286, I2C_BUS1, LTC4286_2_ADDR, PMBUS_READ_VOUT,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &ltc4286_init_args[1] },
	{ SENSOR_NUM_CUR_P51V_STBY_R, sensor_dev_ltc4286, I2C_BUS1, LTC4286_2_ADDR, PMBUS_READ_IIN,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &ltc4286_init_args[1] },
	{ SENSOR_NUM_CUR_P51V_AUX_R, sensor_dev_ltc4286, I2C_BUS1, LTC4286_2_ADDR, PMBUS_READ_IOUT,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &ltc4286_init_args[1] },
	{ SENSOR_NUM_PWR_P51V_STBY_R, sensor_dev_ltc4286, I2C_BUS1, LTC4286_2_ADDR, PMBUS_READ_PIN,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &ltc4286_init_args[1] },
	{ SENSOR_NUM_PWR_P51V_AUX_R, sensor_dev_ltc4286, I2C_BUS1, LTC4286_2_ADDR, PMBUS_READ_POUT,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0,
	  SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &ltc4286_init_args[1] },
};

sensor_cfg q50sn120a1_sensor_config_table[] = {
	{ SENSOR_NUM_TEMP_POWER_BRICK_1, sensor_dev_q50sn120a1, I2C_BUS1, POWER_BRICK_1_ADDR,
	  PMBUS_READ_TEMPERATURE_1, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_VOL_P12V_AUX_1, sensor_dev_q50sn120a1, I2C_BUS1, POWER_BRICK_1_ADDR,
	  PMBUS_READ_VOUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_CUR_P12V_AUX_1, sensor_dev_q50sn120a1, I2C_BUS1, POWER_BRICK_1_ADDR,
	  PMBUS_READ_IOUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_PWR_P12V_AUX_1, sensor_dev_q50sn120a1, I2C_BUS1, POWER_BRICK_1_ADDR,
	  PMBUS_READ_POUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },

	{ SENSOR_NUM_TEMP_POWER_BRICK_2, sensor_dev_q50sn120a1, I2C_BUS1, POWER_BRICK_2_ADDR,
	  PMBUS_READ_TEMPERATURE_1, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_VOL_P12V_AUX_2, sensor_dev_q50sn120a1, I2C_BUS1, POWER_BRICK_2_ADDR,
	  PMBUS_READ_VOUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_CUR_P12V_AUX_2, sensor_dev_q50sn120a1, I2C_BUS1, POWER_BRICK_2_ADDR,
	  PMBUS_READ_IOUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_PWR_P12V_AUX_2, sensor_dev_q50sn120a1, I2C_BUS1, POWER_BRICK_2_ADDR,
	  PMBUS_READ_POUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
};

sensor_cfg bmr3512202_sensor_config_table[] = {
	{ SENSOR_NUM_TEMP_POWER_BRICK_1, sensor_dev_q50sn120a1, I2C_BUS1, POWER_BRICK_1_ADDR,
	  PMBUS_READ_TEMPERATURE_1, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_VOL_P12V_AUX_1, sensor_dev_q50sn120a1, I2C_BUS1, POWER_BRICK_1_ADDR,
	  PMBUS_READ_VOUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_CUR_P12V_AUX_1, sensor_dev_q50sn120a1, I2C_BUS1, POWER_BRICK_1_ADDR,
	  PMBUS_READ_IOUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_PWR_P12V_AUX_1, sensor_dev_q50sn120a1, I2C_BUS1, POWER_BRICK_1_ADDR,
	  PMBUS_READ_POUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },

	{ SENSOR_NUM_TEMP_POWER_BRICK_2, sensor_dev_q50sn120a1, I2C_BUS1, POWER_BRICK_2_ADDR,
	  PMBUS_READ_TEMPERATURE_1, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_VOL_P12V_AUX_2, sensor_dev_q50sn120a1, I2C_BUS1, POWER_BRICK_2_ADDR,
	  PMBUS_READ_VOUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_CUR_P12V_AUX_2, sensor_dev_q50sn120a1, I2C_BUS1, POWER_BRICK_2_ADDR,
	  PMBUS_READ_IOUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_PWR_P12V_AUX_2, sensor_dev_q50sn120a1, I2C_BUS1, POWER_BRICK_2_ADDR,
	  PMBUS_READ_POUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT,
	  ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
};

const int SENSOR_CONFIG_SIZE = ARRAY_SIZE(plat_sensor_config);
const int ACCL_SENSOR_CONFIG_SIZE = ARRAY_SIZE(plat_accl_sensor_config);

void load_sensor_config(void)
{
	memcpy(sensor_config, plat_sensor_config, sizeof(plat_sensor_config));
	sensor_config_count = ARRAY_SIZE(plat_sensor_config);

	// Fix config table in different system/config
	pal_extend_sensor_config();
}

uint8_t pal_get_extend_sensor_config()
{
	uint8_t extend_sensor_config_size = 0;
	uint8_t hsc_module = get_hsc_module();
	uint8_t power_brick_module = get_pwr_brick_module();

	switch (hsc_module) {
	case HSC_MODULE_ADM1272:
		extend_sensor_config_size += ARRAY_SIZE(adm1272_sensor_config_table);
		break;
	case HSC_MODULE_LTC4286:
		extend_sensor_config_size += ARRAY_SIZE(ltc4286_sensor_config_table);
		break;
	default:
		LOG_ERR("Invalid hsc module: 0x%x", hsc_module);
		break;
	}

	switch (power_brick_module) {
	case POWER_BRICK_Q50SN120A1:
		extend_sensor_config_size += ARRAY_SIZE(q50sn120a1_sensor_config_table);
		break;
	case POWER_BRICK_BMR3512202:
		extend_sensor_config_size += ARRAY_SIZE(bmr3512202_sensor_config_table);
		break;
	default:
		LOG_ERR("Invalid power brick module: 0x%x", power_brick_module);
		break;
	}

	return extend_sensor_config_size;
}

void pal_extend_sensor_config()
{
	uint8_t index = 0;
	uint8_t sensor_count = 0;
	uint8_t hsc_module = get_hsc_module();
	uint8_t power_brick_module = get_pwr_brick_module();

	switch (hsc_module) {
	case HSC_MODULE_ADM1272:
		sensor_count = ARRAY_SIZE(adm1272_sensor_config_table);
		for (index = 0; index < sensor_count; index++) {
			add_sensor_config(adm1272_sensor_config_table[index]);
		}
		break;
	case HSC_MODULE_LTC4286:
		sensor_count = ARRAY_SIZE(ltc4286_sensor_config_table);
		for (index = 0; index < sensor_count; index++) {
			add_sensor_config(ltc4286_sensor_config_table[index]);
		}
		break;
	default:
		LOG_ERR("Invalid hsc module: 0x%x", hsc_module);
		break;
	}

	switch (power_brick_module) {
	case POWER_BRICK_Q50SN120A1:
		sensor_count = ARRAY_SIZE(q50sn120a1_sensor_config_table);
		for (index = 0; index < sensor_count; index++) {
			add_sensor_config(q50sn120a1_sensor_config_table[index]);
		}
		break;
	case POWER_BRICK_BMR3512202:
		sensor_count = ARRAY_SIZE(bmr3512202_sensor_config_table);
		for (index = 0; index < sensor_count; index++) {
			add_sensor_config(bmr3512202_sensor_config_table[index]);
		}
		break;
	default:
		LOG_ERR("Invalid power brick module: 0x%x", power_brick_module);
		break;
	}
}

bool is_acb_power_good()
{
	// BIC can check motherboard dc power status by CPLD power good flag
	bool ret = false;
	uint8_t board_revision = get_board_revision();

	switch (board_revision) {
	case POC_STAGE:
	case EVT1_STAGE:
		ret = get_acb_power_status();
		if (ret != true) {
			LOG_ERR("Get acb power status fail");
			return false;
		}

		return get_acb_power_good_flag();
	case EVT2_STAGE:
	case DVT_STAGE:
	case PVT_STAGE:
	case MP_STAGE:
		return get_acb_power_good_flag();
	default:
		LOG_ERR("Invalid board revision: 0x%x", board_revision);
		return false;
	}
}

bool is_dc_access(uint8_t sensor_num)
{
	return is_acb_power_good();
}

bool is_pcie_device_access(uint8_t card_id, uint8_t sensor_num)
{
	if (card_id >= ASIC_CARD_COUNT) {
		LOG_ERR("Invalid card id: 0x%x", card_id);
		return false;
	}

	bool ret = false;
	uint8_t index = 0;
	uint8_t device_status = 0;

	ret = get_accl_sensor_config_index(sensor_num, &index);
	if (ret != true) {
		return ret;
	}

	sensor_cfg cfg = plat_accl_sensor_config[index];
	if (asic_card_info[card_id].card_status == ASIC_CARD_PRESENT) {
		switch (cfg.target_addr) {
		case ACCL_FREYA_1_ADDR:
			device_status = asic_card_info[card_id].asic_1_status;
			break;
		case ACCL_FREYA_2_ADDR:
			device_status = asic_card_info[card_id].asic_2_status;
			break;
		case ACCL_12V_INA233_ADDR:
		case ACCL_3V3_1_INA233_ADDR:
		case ACCL_3V3_2_INA233_ADDR:
			device_status = asic_card_info[card_id].card_status;
			break;
		default:
			LOG_ERR("Invalid access address: 0x%x", cfg.target_addr);
			return false;
		}
	} else {
		return false;
	}

	if (device_status != ASIC_CARD_DEVICE_PRESENT) {
		return false;
	}

	return true;
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
	case I2C_BUS7:
		mutex = &i2c_7_mutex;
		break;
	case I2C_BUS8:
		mutex = &i2c_8_mutex;
		break;
	default:
		LOG_ERR("No support for i2c bus %d mutex", i2c_bus);
		break;
	}

	return mutex;
}

int get_accl_bus(uint8_t card_id, uint8_t sensor_number)
{
	if (card_id >= ASIC_CARD_COUNT) {
		LOG_ERR("Invalid accl card id: 0x%x", card_id);
		return -1;
	}

	return pca9548_configs[card_id].bus;
}

bool get_accl_sensor_config_index(uint8_t sensor_num, uint8_t *index)
{
	CHECK_NULL_ARG_WITH_RETURN(index, false);

	uint8_t i = 0;
	for (i = 0; i < ACCL_SENSOR_CONFIG_SIZE; ++i) {
		if (sensor_num == plat_accl_sensor_config[i].num) {
			*index = i;
			return true;
		}
	}

	LOG_ERR("Fail to find sensor num: 0x%x in ACCL sensor config", sensor_num);
	return false;
}

bool get_accl_mux_config(uint8_t card_id, mux_config *accl_mux)
{
	CHECK_NULL_ARG_WITH_RETURN(accl_mux, false);

	if (card_id >= ASIC_CARD_COUNT) {
		LOG_ERR("Invalid accl card id: 0x%x", card_id);
		return false;
	}

	*accl_mux = pca9548_configs[card_id];
	return true;
}

bool get_mux_channel_config(uint8_t card_id, uint8_t sensor_number, mux_config *channel_mux)
{
	CHECK_NULL_ARG_WITH_RETURN(channel_mux, false);

	if (card_id >= ASIC_CARD_COUNT) {
		LOG_ERR("Invalid accl card id: 0x%x", card_id);
		return false;
	}

	bool ret = false;
	uint8_t index = 0;
	uint8_t accl_bus = get_accl_bus(card_id, sensor_number);
	mux_config *mux_cfg = NULL;

	ret = get_accl_sensor_config_index(sensor_number, &index);
	if (ret != true) {
		return ret;
	}

	sensor_cfg cfg = plat_accl_sensor_config[index];
	CHECK_NULL_ARG_WITH_RETURN(cfg.priv_data, false);

	mux_cfg = cfg.priv_data;
	mux_cfg->bus = accl_bus;
	*channel_mux = *mux_cfg;
	return true;
}

ina233_init_arg *get_accl_init_sensor_config(uint8_t card_id, uint8_t sensor_number)
{
	if (card_id >= ASIC_CARD_COUNT) {
		LOG_ERR("Invalid accl card id: 0x%x", card_id);
		return NULL;
	}

	bool ret = false;
	uint8_t index = 0;
	uint8_t offset = 3;

	ret = get_accl_sensor_config_index(sensor_number, &index);
	if (ret != true) {
		return NULL;
	}

	sensor_cfg cfg = plat_accl_sensor_config[index];
	switch (cfg.target_addr) {
	case ACCL_12V_INA233_ADDR:
		offset = (offset * card_id) + ACCL_12V_INA233_INIT_ARG_OFFSET;
		break;
	case ACCL_3V3_1_INA233_ADDR:
		offset = (offset * card_id) + ACCL_3V3_1_INA233_INIT_ARG_OFFSET;
		break;
	case ACCL_3V3_2_INA233_ADDR:
		offset = (offset * card_id) + ACCL_3V3_2_INA233_INIT_ARG_OFFSET;
		break;
	default:
		LOG_ERR("Invalid accl ina233 address: 0x%x", cfg.target_addr);
		return NULL;
	}

	return &accl_ina233_init_args[offset];
}

void pal_init_drive(sensor_cfg *cfg_table, uint8_t cfg_size, uint8_t card_id)
{
	CHECK_NULL_ARG(cfg_table);

	bool ret = false;
	uint8_t index = 0;
	uint8_t sensor_num = 0;
	uint8_t init_status = 0;
	sensor_cfg *cfg = NULL;

	for (index = 0; index < cfg_size; index++) {
		cfg = &cfg_table[index];
		sensor_num = cfg->num;

		if (is_pcie_device_access(card_id, sensor_num) != true) {
			continue;
		}

		ret = pre_accl_mux_switch(card_id, sensor_num);
		if (ret != true) {
			LOG_ERR("Pre switch mux fail, sensor num: 0x%x, card id: 0x%x", sensor_num,
				card_id);
			continue;
		}

		ret = pal_sensor_drive_init(card_id, cfg, &init_status);
		if (ret == true) {
			if (init_status != SENSOR_INIT_SUCCESS) {
				LOG_ERR("Initial sensor drive fail, sensor num: 0x%x, card id: 0x%x",
					sensor_num, card_id);
			}
		} else {
			LOG_ERR("Map initial sensor function fail, sensor num: 0x%x, card id: 0x%x",
				sensor_num, card_id);
		}

		ret = post_accl_mux_switch(card_id, sensor_num);
		if (ret != true) {
			LOG_ERR("Post switch mux fail, sensor num: 0x%x, card id: 0x%x", sensor_num,
				card_id);
		}
	}
}
