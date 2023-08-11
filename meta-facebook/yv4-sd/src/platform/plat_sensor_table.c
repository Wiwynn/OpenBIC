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
#include "plat_i2c.h"
#include "plat_hook.h"
#include "pmbus.h"
#include "ast_adc.h"

const int SENSOR_CONFIG_SIZE = 0;

// clang-format off
sensor_cfg plat_sensor_config[] = {
        /*  
        number,
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

        { SENSOR_NUM_INLET_TEMP,        sensor_dev_tmp75,     I2C_BUS1, ADDR_TMP75_INLET,  OFFSET_TMP75_TEMP,        stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL},
        { SENSOR_NUM_OUTLET_TEMP,       sensor_dev_tmp75,     I2C_BUS1, ADDR_TMP75_OUTLET, OFFSET_TMP75_TEMP,        stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL},
        { SENSOR_NUM_FIO_TEMP,          sensor_dev_tmp75,     I2C_BUS1, ADDR_TMP75_FIO,    OFFSET_TMP75_TEMP,        stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL},
        // TODO : CPU, DIMMA~DIMML TEMP
        { SENSOR_NUM_SSD_BOOT_TEMP,     sensor_dev_nvme,      I2C_BUS1, ADDR_SSD_BOOT,     OFFSET_NVME_TEMP,         post_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL,        NULL,                 NULL, NULL, NULL},
        { SENSOR_NUM_SSD_DATA_TEMP,     sensor_dev_nvme,      I2C_BUS6, ADDR_SSD_DATA,     OFFSET_NVME_TEMP,         post_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL,        NULL,                 NULL, NULL, NULL},
        { SENSOR_NUM_CPU0_VR_TEMP,      sensor_dev_mp2856gut, I2C_BUS4, ADDR_CPU0,         PMBUS_READ_TEMPERATURE_1, vr_access,   0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_vr_read, &vr_pre_read_args[0], NULL, NULL, NULL},
        { SENSOR_NUM_SOC_VR_TEMP,       sensor_dev_mp2856gut, I2C_BUS4, ADDR_SOC,          PMBUS_READ_TEMPERATURE_1, vr_access,   0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_vr_read, &vr_pre_read_args[1], NULL, NULL, NULL},
        { SENSOR_NUM_CPU1_VR_TEMP,      sensor_dev_mp2856gut, I2C_BUS4, ADDR_CPU1,         PMBUS_READ_TEMPERATURE_1, vr_access,   0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_vr_read, &vr_pre_read_args[0], NULL, NULL, NULL},
        { SENSOR_NUM_PVDDIO_VR_TEMP,    sensor_dev_mp2856gut, I2C_BUS4, ADDR_PVDDIO,       PMBUS_READ_TEMPERATURE_1, vr_access,   0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_vr_read, &vr_pre_read_args[1], NULL, NULL, NULL},
        { SENSOR_NUM_PVDD11_VR_TEMP,    sensor_dev_mp2856gut, I2C_BUS4, ADDR_PVDD11,       PMBUS_READ_TEMPERATURE_1, vr_access,   0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_vr_read, &vr_pre_read_args[0], NULL, NULL, NULL},

        { SENSOR_NUM_P12V_STBY_VOLT, 	        sensor_dev_ast_adc, ADC_PORT0, 	NONE, NONE, stby_access, 66,  10,  SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &ast_adc_init_args[0]},
        { SENSOR_NUM_PVDD18_S5_VOLT, 	        sensor_dev_ast_adc, ADC_PORT1, 	NONE, NONE, dc_access, 1,   1,   SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &ast_adc_init_args[0]},
        { SENSOR_NUM_P3V3_STBY_VOLT, 	        sensor_dev_ast_adc, ADC_PORT2, 	NONE, NONE, stby_access, 2,   1,   SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &ast_adc_init_args[0]},
        { SENSOR_NUM_P3V_BAT_VOLT, 	        sensor_dev_ast_adc, ADC_PORT4, 	NONE, NONE, stby_access, 3,   1,   SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &ast_adc_init_args[0]},
        { SENSOR_NUM_PVDD33_S5_VOLT, 	        sensor_dev_ast_adc, ADC_PORT5, 	NONE, NONE, dc_access, 2,   1,   SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &ast_adc_init_args[0]},
        { SENSOR_NUM_P5V_STBY_VOLT, 	        sensor_dev_ast_adc, ADC_PORT6, 	NONE, NONE, stby_access, 711, 200, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &ast_adc_init_args[0]},
        { SENSOR_NUM_P12V_DIMM_0_VOLT, 	        sensor_dev_ast_adc, ADC_PORT7, 	NONE, NONE, dc_access, 66,  10,  SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &ast_adc_init_args[0]},
        { SENSOR_NUM_P12V_DIMM_1_VOLT, 	        sensor_dev_ast_adc, ADC_PORT8,  NONE, NONE, dc_access, 66,  10,  SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &ast_adc_init_args[1]},
        { SENSOR_NUM_P1V2_STBY_VOLT, 	        sensor_dev_ast_adc, ADC_PORT9,  NONE, NONE, stby_access, 1,   1,   SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &ast_adc_init_args[1]},
        { SENSOR_NUM_P1V8_STBY_VOLT,            sensor_dev_ast_adc, ADC_PORT11, NONE, NONE, stby_access, 1,   1,   SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &ast_adc_init_args[1]},
        { SENSOR_NUM_SLOT_ADC_DETECT_VOLT, 	sensor_dev_ast_adc, ADC_PORT13, NONE, NONE, stby_access, 367,   267,   SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &ast_adc_init_args[1]},
        { SENSOR_NUM_ADC_SIDECAR_DETECT_VOLT, 	sensor_dev_ast_adc, ADC_PORT15, NONE, NONE, dc_access, 1,   1,   SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, &ast_adc_init_args[1]},

        { SENSOR_NUM_CPU0_VR_CURR,   sensor_dev_mp2856gut, I2C_BUS4, ADDR_CPU0,   PMBUS_READ_IOUT, vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_vr_read, &vr_pre_read_args[0], NULL, NULL, NULL},
        { SENSOR_NUM_SOC_VR_CURR,    sensor_dev_mp2856gut, I2C_BUS4, ADDR_SOC,    PMBUS_READ_IOUT, vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_vr_read, &vr_pre_read_args[1], NULL, NULL, NULL},
        { SENSOR_NUM_CPU1_VR_CURR,   sensor_dev_mp2856gut, I2C_BUS4, ADDR_CPU1,   PMBUS_READ_IOUT, vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_vr_read, &vr_pre_read_args[0], NULL, NULL, NULL},
        { SENSOR_NUM_PVDDIO_VR_CURR, sensor_dev_mp2856gut, I2C_BUS4, ADDR_PVDDIO, PMBUS_READ_IOUT, vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_vr_read, &vr_pre_read_args[1], NULL, NULL, NULL},
        { SENSOR_NUM_PVDD11_VR_CURR, sensor_dev_mp2856gut, I2C_BUS4, ADDR_PVDD11, PMBUS_READ_IOUT, vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_vr_read, &vr_pre_read_args[0], NULL, NULL, NULL},

        { SENSOR_NUM_CPU0_VR_PWR,   sensor_dev_mp2856gut, I2C_BUS4, ADDR_CPU0,   PMBUS_READ_POUT, vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_vr_read, &vr_pre_read_args[0], NULL, NULL, NULL},
        { SENSOR_NUM_SOC_VR_PWR,    sensor_dev_mp2856gut, I2C_BUS4, ADDR_SOC,    PMBUS_READ_POUT, vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_vr_read, &vr_pre_read_args[1], NULL, NULL, NULL},
        { SENSOR_NUM_CPU1_VR_PWR,   sensor_dev_mp2856gut, I2C_BUS4, ADDR_CPU1,   PMBUS_READ_POUT, vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_vr_read, &vr_pre_read_args[0], NULL, NULL, NULL},
        { SENSOR_NUM_PVDDIO_VR_PWR, sensor_dev_mp2856gut, I2C_BUS4, ADDR_PVDDIO, PMBUS_READ_POUT, vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_vr_read, &vr_pre_read_args[1], NULL, NULL, NULL},
        { SENSOR_NUM_PVDD11_VR_PWR, sensor_dev_mp2856gut, I2C_BUS4, ADDR_PVDD11, PMBUS_READ_POUT, vr_access, 0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, pre_vr_read, &vr_pre_read_args[0], NULL, NULL, NULL},
        // TODO : CPU, DIMMA~DIMML PWR
};
// clang-format on
