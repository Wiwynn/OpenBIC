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
#include <logging/log.h>

#include "ast_adc.h"
#include "sensor.h"
#include "pmbus.h"
#include "plat_i2c.h"
#include "plat_sensor_table.h"

LOG_MODULE_REGISTER(plat_sensor_table);

// clang-format off
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
    { SENSOR_NUM_INLET_TEMP,            sensor_dev_tmp75,       I2C_BUS3,   ADDR_TMP75,         OFFSET_TMP75_TEMP,          stby_access,    0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
    { SENSOR_NUM_CXL_TEMP,              sensor_dev_tmp461,      I2C_BUS2,   ADDR_TMP461,        OFFSET_TMP461_TEMP,         dc_access,      0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
    { SENSOR_NUM_VR_P0V8_ASIC_TEMP,     sensor_dev_xdpe12284c,  I2C_BUS7,   ADDR_P0V8_ASIC,     PMBUS_READ_TEMPERATURE_1,   dc_access,      0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
    { SENSOR_NUM_VR_PVDDQ_CD_TEMP,      sensor_dev_xdpe12284c,  I2C_BUS7,   ADDR_PVDDQ_CD,      PMBUS_READ_TEMPERATURE_1,   dc_access,      0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
    { SENSOR_NUM_VR_P0V85_ASIC_TEMP,    sensor_dev_xdpe12284c,  I2C_BUS7,   ADDR_P0V85_ASIC,    PMBUS_READ_TEMPERATURE_1,   dc_access,      0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
    { SENSOR_NUM_VR_PVDDQ_AB_TEMP,      sensor_dev_xdpe12284c,  I2C_BUS7,   ADDR_PVDDQ_AB,      PMBUS_READ_TEMPERATURE_1,   dc_access,      0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },

    { SENSOR_NUM_INA233_P12V_STBY_VOLT, sensor_dev_ina233,      I2C_BUS1,   ADDR_INA233_P12V,   PMBUS_READ_VOUT,            stby_access,    0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
    { SENSOR_NUM_INA233_P3V3_STBY_VOLT, sensor_dev_ina233,      I2C_BUS1,   ADDR_INA233_P3V3,   PMBUS_READ_VOUT,            stby_access,    0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
    { SENSOR_NUM_ADC_P1V2_STBY_VOLT,    sensor_dev_ast_adc,     ADC_PORT3,  NONE,               NONE,                       stby_access,    0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
    { SENSOR_NUM_ADC_P1V2_ASIC_VOLT,    sensor_dev_ast_adc,     ADC_PORT5,  NONE,               NONE,                       dc_access,      0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
    { SENSOR_NUM_ADC_P1V8_ASIC_VOLT,    sensor_dev_ast_adc,     ADC_PORT6,  NONE,               NONE,                       dc_access,      0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
    { SENSOR_NUM_VR_P0V8_ASIC_VOLT,     sensor_dev_xdpe12284c,  I2C_BUS7,   ADDR_P0V8_ASIC,     PMBUS_READ_VOUT,            dc_access,      0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
    { SENSOR_NUM_VR_PVDDQ_CD_VOLT,      sensor_dev_xdpe12284c,  I2C_BUS7,   ADDR_PVDDQ_CD,      PMBUS_READ_VOUT,            dc_access,      0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
    { SENSOR_NUM_VR_P0V85_ASIC_VOLT,    sensor_dev_xdpe12284c,  I2C_BUS7,   ADDR_P0V85_ASIC,    PMBUS_READ_VOUT,            dc_access,      0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
    { SENSOR_NUM_VR_PVDDQ_AB_VOLT,      sensor_dev_xdpe12284c,  I2C_BUS7,   ADDR_PVDDQ_AB,      PMBUS_READ_VOUT,            dc_access,      0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
    { SENSOR_NUM_ADC_P0V75_ASIC_VOLT,   sensor_dev_ast_adc,     ADC_PORT14, NONE,               NONE,                       dc_access,      0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
    { SENSOR_NUM_ADC_PVPP_AB_VOLT,      sensor_dev_ast_adc,     ADC_PORT8,  NONE,               NONE,                       dc_access,      0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
    { SENSOR_NUM_ADC_PVPP_CD_VOLT,      sensor_dev_ast_adc,     ADC_PORT9,  NONE,               NONE,                       dc_access,      0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
    { SENSOR_NUM_ADC_PVTT_AB_VOLT,      sensor_dev_ast_adc,     ADC_PORT10, NONE,               NONE,                       dc_access,      0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
    { SENSOR_NUM_ADC_PVTT_CD_VOLT,      sensor_dev_ast_adc,     ADC_PORT11, NONE,               NONE,                       dc_access,      0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },

    { SENSOR_NUM_INA233_P12V_STBY_CURR, sensor_dev_ina233,      I2C_BUS1,   ADDR_INA233_P12V,   PMBUS_READ_IOUT,            stby_access,    0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
    { SENSOR_NUM_INA233_P3V3_STBY_CURR, sensor_dev_ina233,      I2C_BUS1,   ADDR_INA233_P3V3,   PMBUS_READ_IOUT,            stby_access,    0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
    { SENSOR_NUM_VR_P0V8_ASIC_CURR,     sensor_dev_xdpe12284c,  I2C_BUS7,   ADDR_P0V8_ASIC,     PMBUS_READ_IOUT,            dc_access,      0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
    { SENSOR_NUM_VR_PVDDQ_CD_CURR,      sensor_dev_xdpe12284c,  I2C_BUS7,   ADDR_PVDDQ_CD,      PMBUS_READ_IOUT,            dc_access,      0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
    { SENSOR_NUM_VR_P0V85_ASIC_CURR,    sensor_dev_xdpe12284c,  I2C_BUS7,   ADDR_P0V85_ASIC,    PMBUS_READ_IOUT,            dc_access,      0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
    { SENSOR_NUM_VR_PVDDQ_AB_CURR,      sensor_dev_xdpe12284c,  I2C_BUS7,   ADDR_PVDDQ_AB,      PMBUS_READ_IOUT,            dc_access,      0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },

    { SENSOR_NUM_INA233_P12V_STBY_PWR,  sensor_dev_ina233,      I2C_BUS1,   ADDR_INA233_P12V,   PMBUS_READ_POUT,            stby_access,    0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
    { SENSOR_NUM_INA233_P3V3_STBY_PWR,  sensor_dev_ina233,      I2C_BUS1,   ADDR_INA233_P3V3,   PMBUS_READ_POUT,            stby_access,    0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
    { SENSOR_NUM_VR_P0V85_ASIC_PWR,     sensor_dev_xdpe12284c,  I2C_BUS7,   ADDR_P0V85_ASIC,    PMBUS_READ_POUT,            dc_access,      0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
    { SENSOR_NUM_VR_PVDDQ_AB_PWR,       sensor_dev_xdpe12284c,  I2C_BUS7,   ADDR_PVDDQ_AB,      PMBUS_READ_POUT,            dc_access,      0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
    { SENSOR_NUM_VR_P0V8_ASIC_PWR,      sensor_dev_xdpe12284c,  I2C_BUS7,   ADDR_P0V8_ASIC,     PMBUS_READ_POUT,            dc_access,      0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
    { SENSOR_NUM_VR_PVDDQ_CD_PWR,       sensor_dev_xdpe12284c,  I2C_BUS7,   ADDR_PVDDQ_CD,      PMBUS_READ_POUT,            dc_access,      0, 0, SAMPLE_COUNT_DEFAULT, POLL_TIME_DEFAULT, ENABLE_SENSOR_POLLING, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
};
// clang-format on

const int SENSOR_CONFIG_SIZE = ARRAY_SIZE(plat_sensor_config);
