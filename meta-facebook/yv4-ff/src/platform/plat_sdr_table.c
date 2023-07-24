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

#include "sdr.h"
#include "plat_sdr_table.h"
#include "plat_sensor_table.h"

LOG_MODULE_REGISTER(plat_sdr_table);

SDR_Full_sensor plat_sdr_table[] = {
    {
        // INLET temperature
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_INLET_TEMP, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_DEGREE_C, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x01, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0x00, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0x96, // UNRT
        0x32, // UCT
        0x00, // UNCT
        0x00, // LNRT
        0x00, // LCT
        0x00, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_1OU_BOARD_INLET_TEMP_C",
    },
    {
        // CXL temperature
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_CXL_TEMP, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_DEGREE_C, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x01, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0x00, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0x00, // UNRT
        0x54, // UCT
        0x00, // UNCT
        0x00, // LNRT
        0x00, // LCT
        0x00, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_CXL_CNTR_TEMP_C",
    },
    {
        // VR P0V8 ASIC temperature
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_VR_P0V8_ASIC_TEMP, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_DEGREE_C, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x01, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0x00, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0x00, // UNRT
        0x55, // UCT
        0x00, // UNCT
        0x00, // LNRT
        0x00, // LCT
        0x00, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_VR_P0V8_ASIC_TEMP_C",
    },
    {
        // VR PVDDQ CD temperature
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_VR_PVDDQ_CD_TEMP, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_DEGREE_C, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x01, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0x00, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0x00, // UNRT
        0x55, // UCT
        0x00, // UNCT
        0x00, // LNRT
        0x00, // LCT
        0x00, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_VR_PVDDQ_CD_TEMP_C",
    },
    {
        // VR P0V85 ASIC temperature
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_VR_P0V85_ASIC_TEMP, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_DEGREE_C, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x01, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0x00, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0x00, // UNRT
        0x55, // UCT
        0x00, // UNCT
        0x00, // LNRT
        0x00, // LCT
        0x00, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_VR_P0V85_ASIC_TEMP_C",
    },
    {
        // VR PVDDQ AB temperature
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_VR_PVDDQ_AB_TEMP, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_DEGREE_C, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x01, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0x00, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0x00, // UNRT
        0x55, // UCT
        0x00, // UNCT
        0x00, // LNRT
        0x00, // LCT
        0x00, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_VR_PVDDQ_AB_TEMP_C",
    },
    {
        // INA233 P12V STBY VOLTAGE
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_INA233_P12V_STBY_VOLT, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_VOL, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x3A, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0xD0, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0xF7, // UNRT
        0xE6, // UCT
        0xE3, // UNCT
        0xAE, // LNRT
        0xB9, // LCT
        0xB8, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_INA233_P12V_STBY_VOLT_V",
    },
    {
        // INA233 P3V3 STBY VOLTAGE
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_INA233_P3V3_STBY_VOLT, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_VOL, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x10, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0xD0, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0xFA, // UNRT
        0xDD, // UCT
        0xDF, // UNCT
        0x90, // LNRT
        0xBE, // LCT
        0xC1, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_INA233_P3V3_STBY_VOLT_V",
    },
    {
        // ADC P1V2 STBY VOLTAGE
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_ADC_P1V2_STBY_VOLT, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_VOL, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x05, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0xD0, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0xE8, // UNRT
        0xD5, // UCT
        0xD9, // UNCT
        0xA0, // LNRT
        0xB7, // LCT
        0xBA, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_ADC_P1V2_STBY_VOLT_V",
    },
    {
        // ADC P1V2 ASIC VOLTAGE
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_ADC_P1V2_ASIC_VOLT, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_VOL, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x05, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0xD0, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0xE8, // UNRT
        0xD5, // UCT
        0xD9, // UNCT
        0xA0, // LNRT
        0xB7, // LCT
        0xBA, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_ADC_P1V2_ASIC_VOLT_V",
    },
    {
        // ADC P1V8 ASIC VOLT
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_ADC_P1V8_ASIC_VOLT, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_VOL, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x09, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0xD0, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0xE8, // UNRT
        0xD5, // UCT
        0xD3, // UNCT
        0xA0, // LNRT
        0xBA, // LCT
        0xBB, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_ADC_P1V8_ASIC_VOLT_V",
    },
    {
        // VR P0V8 ASIC VOLTAGE
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_VR_P0V8_ASIC_VOLT, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_VOL, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x05, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0xD0, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0xC0, // UNRT
        0xB4, // UCT
        0xB0, // UNCT
        0x80, // LNRT
        0x8D, // LCT
        0x90, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_VR_P0V8_ASIC_VOLT_V",
    },
    {
        // VR PVDDQ CD VOLT
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_VR_PVDDQ_CD_VOLT, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_VOL, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x06, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0xD0, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0xE8, // UNRT
        0xD9, // UCT
        0xD5, // UNCT
        0xA0, // LNRT
        0xB7, // LCT
        0xBA, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_VR_PVDDQ_CD_VOLT_V",
    },
    {
        // VR P0V85 ASIC VOLT
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_VR_P0V85_ASIC_VOLT, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_VOL, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x05, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0xD0, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0xD1, // UNRT
        0xC4, // UCT
        0xC0, // UNCT
        0x80, // LNRT
        0x8D, // LCT
        0x90, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_VR_P0V85_ASIC_VOLT_V",
    },
    {
        // VR PVDDQ AB VOLTAGE
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_VR_PVDDQ_AB_VOLT, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_VOL, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x05, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0xD0, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0xE8, // UNRT
        0xD5, // UCT
        0xD9, // UNCT
        0xA0, // LNRT
        0xB7, // LCT
        0xBA, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_VR_PVDDQ_AB_VOLT_V",
    },
    {
        // ADC P0V75 ASIC VOLTAGE
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_ADC_P0V75_ASIC_VOLT, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_VOL, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x04, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0xD0, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0xE2, // UNRT
        0xD4, // UCT
        0xD0, // UNCT
        0x95, // LNRT
        0xA4, // LCT
        0xA8, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_ADC_P0V75_ASIC_VOLT_V ",
    },
    {
        // ADC PVPP AB VOLTAGE
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_ADC_PVPP_AB_VOLT, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_VOL, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x10, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0xD0, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0xBC, // UNRT
        0xAF, // UCT
        0xAB, // UNCT
        0x7D, // LNRT
        0x8A, // LCT
        0x8D, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_ADC_PVPP_AB_VOLT_V",
    },
    {
        // ADC PVPP CD VOLT
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_ADC_PVPP_CD_VOLT, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_VOL, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x10, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0xD0, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0xBC, // UNRT
        0xAF, // UCT
        0xAB, // UNCT
        0x7D, // LNRT
        0x8A, // LCT
        0x8D, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_ADC_PVPP_CD_VOLT_V",
    },
    {
        // ADC PVTT AB VOLT
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_ADC_PVTT_AB_VOLT, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_VOL, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x04, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0xD0, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0xB4, // UNRT
        0xA8, // UCT
        0xA5, // UNCT
        0x78, // LNRT
        0x84, // LCT
        0x87, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_ADC_PVTT_AB_VOLT_V",
    },
    {
        // ADC PVTT CD VOLT
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_ADC_PVTT_CD_VOLT, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_VOL, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x04, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0xD0, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0xB4, // UNRT
        0xA8, // UCT
        0xA5, // UNCT
        0x78, // LNRT
        0x84, // LCT
        0x87, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_ADC_PVTT_CD_VOLT_V",
    },
    {
        // INA233 P12V STBY CURR
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_INA233_P12V_STBY_CURR, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_AMP, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x01, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0x00, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0x00, // UNRT
        0x00, // UCT
        0x00, // UNCT
        0x00, // LNRT
        0x00, // LCT
        0x00, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_INA233_P12V_STBY_CURR_A",
    },
    {
        // INA233 P3V3 STBY CURRENT
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_INA233_P3V3_STBY_CURR, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_AMP, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x01, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0x00, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0x00, // UNRT
        0x00, // UCT
        0x00, // UNCT
        0x00, // LNRT
        0x00, // LCT
        0x00, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_INA233_P3V3_STBY_CURR_A",
    },
    {
        // VR P0V8 ASIC CURRENT
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_VR_P0V8_ASIC_CURR, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_AMP, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x0C, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0xD0, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0xA7, // UNRT
        0x7E, // UCT
        0x79, // UNCT
        0x00, // LNRT
        0x00, // LCT
        0x00, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_VR_P0V8_ASIC_CURR_A",
    },
    {
        // VR PVDDQ CD CURRENT
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_VR_PVDDQ_CD_CURR, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_AMP, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x4E, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0xD0, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0xCD, // UNRT
        0xA2, // UCT
        0x9A, // UNCT
        0x00, // LNRT
        0x00, // LCT
        0x00, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_VR_PVDDQ_CD_CURR_A",
    },
    {
        // VR P0V85 ASIC CURRENT
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_VR_P0V85_ASIC_CURR, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_AMP, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x4E, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0xD0, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0x9A, // UNRT
        0x65, // UCT
        0x60, // UNCT
        0x00, // LNRT
        0x00, // LCT
        0x00, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_VR_P0V85_ASIC_CURR_A",
    },
    {
        // VR PVDDQ AB CURRENT
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_VR_PVDDQ_AB_CURR, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_AMP, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x4E, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0xD0, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0xCD, // UNRT
        0xA2, // UCT
        0x9A, // UNCT
        0x00, // LNRT
        0x00, // LCT
        0x00, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_VR_PVDDQ_AB_CURR_A",
    },
    {
        // INA233 P12V STBY POWER
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_INA233_P12V_STBY_PWR, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_WATT, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x01, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0x00, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0x00, // UNRT
        0x00, // UCT
        0x00, // UNCT
        0x00, // LNRT
        0x00, // LCT
        0x00, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_INA233_P12V_STBY_PWR_W",
    },
    {
        // INA233 P3V3 STBY POWER
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_INA233_P3V3_STBY_PWR, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_WATT, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x01, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0x00, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0x00, // UNRT
        0x00, // UCT
        0x00, // UNCT
        0x00, // LNRT
        0x00, // LCT
        0x00, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_INA233_P3V3_STBY_PWR_W",
    },
    {
        // VR P0V85 ASIC POWER
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_VR_P0V85_ASIC_PWR, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_WATT, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x3B, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0xD0, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0xD5, // UNRT
        0x82, // UCT
        0x7A, // UNCT
        0x00, // LNRT
        0x00, // LCT
        0x00, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_VR_P0V85_ASIC_PWR_W",
    },
    {
        // VR PVDDQ AB POWER
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_VR_PVDDQ_AB_PWR, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_WATT, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x62, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0xD0, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0xE4, // UNRT
        0xA7, // UCT
        0x9D, // UNCT
        0x00, // LNRT
        0x00, // LCT
        0x00, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_VR_PVDDQ_AB_PWR_W",
    },
    {
        // VR P0V8 ASIC POWER
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_VR_P0V8_ASIC_PWR, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_WATT, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x0A, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0xD0, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0xC0, // UNRT
        0x88, // UCT
        0x80, // UNCT
        0x00, // LNRT
        0x00, // LCT
        0x00, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_VR_P0V8_ASIC_PWR_W",
    },
    {
        // VR PVDDQ CD POWER
        0x00,
        0x00, // record ID
        IPMI_SDR_VER_15, // SDR ver
        IPMI_SDR_FULL_SENSOR, // record type
        IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

        SELF_I2C_ADDRESS << 1, // owner id
        0x00, // owner lun
        SENSOR_NUM_VR_PVDDQ_CD_PWR, // sensor number

        IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
        0x00, // entity instance
        IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
            IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
            IPMI_SDR_SENSOR_INIT_DEF_EVENT |
            IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
        IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
            IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
        IPMI_SDR_SENSOR_TYPE_TEMPERATURE, // sensor type
        IPMI_SDR_EVENT_TYPE_THRESHOLD, // event/reading type
        0x00, // assert event mask
        IPMI_SDR_CMP_RETURN_LCT | IPMI_SDR_ASSERT_MASK_UCT_HI |
            IPMI_SDR_ASSERT_MASK_LCT_LO, // assert threshold reading mask
        0x00, // deassert event mask
        IPMI_SDR_CMP_RETURN_UCT | IPMI_SDR_DEASSERT_MASK_UCT_LO |
            IPMI_SDR_DEASSERT_MASK_LCT_HI, // deassert threshold reading mask
        0x00, // discrete reading mask/ settable
        IPMI_SDR_UNRT_SETTABLE | IPMI_SDR_UCT_SETTABLE | IPMI_SDR_UNCT_SETTABLE |
        IPMI_SDR_LNRT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_LNCT_SETTABLE |
        IPMI_SDR_UNRT_READABLE | IPMI_SDR_UCT_READABLE | IPMI_SDR_UNCT_READABLE |
        IPMI_SDR_LNRT_READABLE | IPMI_SDR_LCT_READABLE | IPMI_SDR_LNCT_READABLE,
        // threshold mask/ readable threshold mask
        0x00, // sensor unit
        IPMI_SENSOR_UNIT_WATT, // base unit
        0x00, // modifier unit
        IPMI_SDR_LINEAR_LINEAR, // linearization
        0x62, // [7:0] M bits
        0x00, // [9:8] M bits, tolerance
        0x00, // [7:0] B bits
        0x00, // [9:8] B bits, tolerance
        0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
        0xD0, // Rexp, Bexp
        0x00, // analog characteristic
        0x00, // nominal reading
        0x00, // normal maximum
        0x00, // normal minimum
        0x00, // sensor maximum reading
        0x00, // sensor minimum reading
        0xE4, // UNRT
        0xA7, // UCT
        0x9D, // UNCT
        0x00, // LNRT
        0x00, // LCT
        0x00, // LNCT
        0x00, // positive-going threshold
        0x00, // negative-going threshold
        0x00, // reserved
        0x00, // reserved
        0x00, // OEM
        IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
        "FF_VR_PVDDQ_CD_PWR_W",
    },
};

void load_sdr_table(void)
{
	memcpy(full_sdr_table, plat_sdr_table, sizeof(plat_sdr_table));
	sdr_count = ARRAY_SIZE(plat_sdr_table);
}

const int SDR_TABLE_SIZE = ARRAY_SIZE(plat_sdr_table);
