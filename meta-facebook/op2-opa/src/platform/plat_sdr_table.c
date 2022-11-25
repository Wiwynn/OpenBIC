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

#include "sdr.h"

#include "plat_sdr_table.h"
#include "plat_sensor_table.h"
#include "plat_ipmb.h"

SDR_Full_sensor plat_1OU_sdr_table[] = {
	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_1OU_TEMP, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
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
		0x55, // UNRT
		0x30, // UCT
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
		"OP_1OU_TEMP_C",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_1OU_E1S_SSD0_P12V_VOLT_V, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_VOL, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x54, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xB0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xFD, // UNRT
		0xFA, // UCT
		0xF8, // UNCT
		0xD3, // LNRT
		0xD5, // LCT
		0xD7, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_1OU_E1S_SSD0_P12V_VOLT_V",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_1OU_E1S_SSD1_P12V_VOLT_V, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_VOL, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x54, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xB0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xFD, // UNRT
		0xFA, // UCT
		0xF8, // UNCT
		0xD3, // LNRT
		0xD5, // LCT
		0xD7, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_1OU_E1S_SSD1_P12V_VOLT_V",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_1OU_E1S_SSD2_P12V_VOLT_V, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_VOL, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x54, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xB0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xFD, // UNRT
		0xFA, // UCT
		0xF8, // UNCT
		0xD3, // LNRT
		0xD5, // LCT
		0xD7, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_1OU_E1S_SSD2_P12V_VOLT_V",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_1OU_P12V_VOLT_V, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_VOL, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x54, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xB0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xFD, // UNRT
		0xFA, // UCT
		0xF8, // UNCT
		0xD3, // LNRT
		0xD5, // LCT
		0xD7, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_1OU_P12V_VOLT_V",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_1OU_E1S_SSD0_P3V3_ADC_VOLT_V, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_VOL, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x74, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xC0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xF3, // UNRT
		0xF1, // UCT
		0xEF, // UNCT
		0xCB, // LNRT
		0xCD, // LCT
		0xD0, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_1OU_E1S_SSD0_P3V3_ADC_VOLT_V",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_1OU_E1S_SSD1_P3V3_ADC_VOLT_V, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_VOL, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x74, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xC0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xF3, // UNRT
		0xF1, // UCT
		0xEF, // UNCT
		0xCB, // LNRT
		0xCD, // LCT
		0xD0, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_1OU_E1S_SSD1_P3V3_ADC_VOLT_V",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_1OU_E1S_SSD2_P3V3_ADC_VOLT_V, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_VOL, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x74, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xC0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xF3, // UNRT
		0xF1, // UCT
		0xEF, // UNCT
		0xCB, // LNRT
		0xCD, // LCT
		0xD0, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_1OU_E1S_SSD2_P3V3_ADC_VOLT_V",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_1OU_P3V3_STBY_ADC_VOLT_V, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_VOL, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x74, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xC0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xF3, // UNRT
		0xF1, // UCT
		0xEF, // UNCT
		0xCB, // LNRT
		0xCD, // LCT
		0xD0, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_1OU_P3V3_STBY_ADC_VOLT_V",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_1OU_P1V8_ADC_VOLT_V, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_VOL, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x78, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xC0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xFC, // UNRT
		0xFA, // UCT
		0xF7, // UNCT
		0xD2, // LNRT
		0xD5, // LCT
		0xD7, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_1OU_P1V8_ADC_VOLT_V",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_1OU_P0V9_ADC_VOLT_V, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_VOL, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x39, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xC0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xFC, // UNRT
		0xFA, // UCT
		0xF7, // UNCT
		0xD2, // LNRT
		0xD5, // LCT
		0xD7, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_1OU_P0V9_ADC_VOLT_V",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_1OU_P1V2_ADC_VOLT_V, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_VOL, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x52, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xC0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xFC, // UNRT
		0xFA, // UCT
		0xF7, // UNCT
		0xD2, // LNRT
		0xD5, // LCT
		0xD7, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_1OU_P1V2_ADC_VOLT_V",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_1OU_E1S_SSD0_P12V_CURR_A, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_AMP, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x86, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xC0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xFC, // UNRT
		0xFA, // UCT
		0xF8, // UNCT
		0x00, // LNRT
		0x00, // LCT
		0x00, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_1OU_E1S_SSD0_P12V_CURR_A",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_1OU_E1S_SSD1_P12V_CURR, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_AMP, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x86, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xC0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xFC, // UNRT
		0xFA, // UCT
		0xF8, // UNCT
		0x00, // LNRT
		0x00, // LCT
		0x00, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_1OU_E1S_SSD1_P12V_CURR_A",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_1OU_E1S_SSD2_P12V_CURR, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_AMP, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x86, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xC0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xFC, // UNRT
		0xFA, // UCT
		0xF8, // UNCT
		0x00, // LNRT
		0x00, // LCT
		0x00, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_1OU_E1S_SSD2_P12V_CURR_A",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_1OU_P12V_CURR_A, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_AMP, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x94, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xC0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xF6, // UNRT
		0xF3, // UCT
		0xF1, // UNCT
		0x00, // LNRT
		0x00, // LCT
		0x00, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_1OU_P12V_CURR_A",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_1OU_E1S_SSD0_P12V_PWR_W, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_WATT, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x01, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0x90, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xFA, // UNRT
		0xF7, // UCT
		0xF5, // UNCT
		0x00, // LNRT
		0x00, // LCT
		0x00, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_1OU_E1S_SSD0_P12V_PWR_W",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_1OU_E1S_SSD1_P12V_PWR, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_WATT, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x01, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0x90, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xFA, // UNRT
		0xF7, // UCT
		0xF5, // UNCT
		0x00, // LNRT
		0x00, // LCT
		0x00, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_1OU_E1S_SSD1_P12V_PWR_W",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_1OU_E1S_SSD2_P12V_PWR, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_WATT, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x01, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0x90, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xFA, // UNRT
		0xF7, // UCT
		0xF5, // UNCT
		0x00, // LNRT
		0x00, // LCT
		0x00, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_1OU_E1S_SSD2_P12V_PWR_W",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_1OU_P12V_PWR_W, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_WATT, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x12, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xA0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xF1, // UNRT
		0xEE, // UCT
		0xEC, // UNCT
		0x00, // LNRT
		0x00, // LCT
		0x00, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_1OU_P12V_PWR_W",
	},
};

SDR_Full_sensor plat_3OU_sdr_table[] = {
	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_3OU_TEMP, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
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
		0x55, // UNRT
		0x30, // UCT
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
		"OP_3OU_TEMP_C",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_3OU_E1S_SSD0_P12V_VOLT_V, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_VOL, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x54, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xB0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xFD, // UNRT
		0xFA, // UCT
		0xF8, // UNCT
		0xD3, // LNRT
		0xD5, // LCT
		0xD7, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_3OU_E1S_SSD0_P12V_VOLT_V",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_3OU_E1S_SSD1_P12V_VOLT_V, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_VOL, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x54, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xB0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xFD, // UNRT
		0xFA, // UCT
		0xF8, // UNCT
		0xD3, // LNRT
		0xD5, // LCT
		0xD7, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_3OU_E1S_SSD1_P12V_VOLT_V",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_3OU_E1S_SSD2_P12V_VOLT_V, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_VOL, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x54, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xB0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xFD, // UNRT
		0xFA, // UCT
		0xF8, // UNCT
		0xD3, // LNRT
		0xD5, // LCT
		0xD7, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_3OU_E1S_SSD2_P12V_VOLT_V",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_3OU_P12V_VOLT_V, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_VOL, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x54, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xB0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xFD, // UNRT
		0xFA, // UCT
		0xF8, // UNCT
		0xD3, // LNRT
		0xD5, // LCT
		0xD7, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_3OU_P12V_VOLT_V",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_3OU_E1S_SSD0_P3V3_ADC_VOLT_V, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_VOL, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x74, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xC0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xF3, // UNRT
		0xF1, // UCT
		0xEF, // UNCT
		0xCB, // LNRT
		0xCD, // LCT
		0xD0, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_3OU_E1S_SSD0_P3V3_ADC_VOLT_V",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_3OU_E1S_SSD1_P3V3_ADC_VOLT_V, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_VOL, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x74, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xC0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xF3, // UNRT
		0xF1, // UCT
		0xEF, // UNCT
		0xCB, // LNRT
		0xCD, // LCT
		0xD0, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_3OU_E1S_SSD1_P3V3_ADC_VOLT_V",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_3OU_E1S_SSD2_P3V3_ADC_VOLT_V, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_VOL, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x74, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xC0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xF3, // UNRT
		0xF1, // UCT
		0xEF, // UNCT
		0xCB, // LNRT
		0xCD, // LCT
		0xD0, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_3OU_E1S_SSD2_P3V3_ADC_VOLT_V",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_3OU_P3V3_STBY_ADC_VOLT_V, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_VOL, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x74, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xC0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xF3, // UNRT
		0xF1, // UCT
		0xEF, // UNCT
		0xCB, // LNRT
		0xCD, // LCT
		0xD0, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_3OU_P3V3_STBY_ADC_VOLT_V",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_3OU_P1V8_ADC_VOLT_V, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_VOL, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x78, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xC0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xFC, // UNRT
		0xFA, // UCT
		0xF7, // UNCT
		0xD2, // LNRT
		0xD5, // LCT
		0xD7, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_3OU_P1V8_ADC_VOLT_V",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_3OU_P0V9_ADC_VOLT_V, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_VOL, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x39, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xC0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xFC, // UNRT
		0xFA, // UCT
		0xF7, // UNCT
		0xD2, // LNRT
		0xD5, // LCT
		0xD7, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_3OU_P0V9_ADC_VOLT_V",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_3OU_P1V2_ADC_VOLT_V, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_VOL, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x52, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xC0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xFC, // UNRT
		0xFA, // UCT
		0xF7, // UNCT
		0xD2, // LNRT
		0xD5, // LCT
		0xD7, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_3OU_P1V2_ADC_VOLT_V",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_3OU_E1S_SSD0_P12V_CURR_A, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_AMP, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x86, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xC0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xFC, // UNRT
		0xFA, // UCT
		0xF8, // UNCT
		0x00, // LNRT
		0x00, // LCT
		0x00, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_3OU_E1S_SSD0_P12V_CURR_A",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_3OU_E1S_SSD1_P12V_CURR, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_AMP, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x86, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xC0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xFC, // UNRT
		0xFA, // UCT
		0xF8, // UNCT
		0x00, // LNRT
		0x00, // LCT
		0x00, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_3OU_E1S_SSD1_P12V_CURR_A",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_3OU_E1S_SSD2_P12V_CURR, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_AMP, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x86, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xC0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xFC, // UNRT
		0xFA, // UCT
		0xF8, // UNCT
		0x00, // LNRT
		0x00, // LCT
		0x00, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_3OU_E1S_SSD2_P12V_CURR_A",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_3OU_P12V_CURR_A, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_AMP, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x94, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xC0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xF6, // UNRT
		0xF3, // UCT
		0xF1, // UNCT
		0x00, // LNRT
		0x00, // LCT
		0x00, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_3OU_P12V_CURR_A",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_3OU_E1S_SSD0_P12V_PWR_W, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_WATT, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x01, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0x90, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xFA, // UNRT
		0xF7, // UCT
		0xF5, // UNCT
		0x00, // LNRT
		0x00, // LCT
		0x00, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_3OU_E1S_SSD0_P12V_PWR_W",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_3OU_E1S_SSD1_P12V_PWR, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_WATT, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x01, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0x90, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xFA, // UNRT
		0xF7, // UCT
		0xF5, // UNCT
		0x00, // LNRT
		0x00, // LCT
		0x00, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_3OU_E1S_SSD1_P12V_PWR_W",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_3OU_E1S_SSD2_P12V_PWR, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_WATT, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x01, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0x90, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xFA, // UNRT
		0xF7, // UCT
		0xF5, // UNCT
		0x00, // LNRT
		0x00, // LCT
		0x00, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_3OU_E1S_SSD2_P12V_PWR_W",
	},

	{
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_3OU_P12V_PWR_W, // sensor number

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
		IPMI_SDR_UCT_SETTABLE | IPMI_SDR_LCT_SETTABLE | IPMI_SDR_UCT_READABLE |
			IPMI_SDR_LCT_READABLE, // threshold mask/ readable threshold mask
		0x80, // sensor unit
		IPMI_SENSOR_UNIT_WATT, // base unit
		0x00, // modifier unit
		IPMI_SDR_LINEAR_LINEAR, // linearization
		0x12, // [7:0] M bits
		0x00, // [9:8] M bits, tolerance
		0x00, // [7:0] B bits
		0x00, // [9:8] B bits, tolerance
		0x00, // [7:4] accuracy , [3:2] accuracy exp, [1:0] sensor direction
		0xA0, // Rexp, Bexp
		0x00, // analog characteristic
		0x00, // nominal reading
		0x00, // normal maximum
		0x00, // normal minimum
		0x00, // sensor maximum reading
		0x00, // sensor minimum reading
		0xF1, // UNRT
		0xEE, // UCT
		0xEC, // UNCT
		0x00, // LNRT
		0x00, // LCT
		0x00, // LNCT
		0x00, // positive-going threshold
		0x00, // negative-going threshold
		0x00, // reserved
		0x00, // reserved
		0x00, // OEM
		IPMI_SDR_STRING_TYPE_ASCII_8, // ID len, should be same as "size of struct"
		"OP_3OU_P12V_PWR_W",
	},
};

/*
 * TODO :
 * Identify 1OU or 3OU and set table size
 */

const int SDR_TABLE_SIZE = ARRAY_SIZE(plat_1OU_sdr_table); // Use 1OU sesnsor table currently

void load_sdr_table(void)
{
	memcpy(full_sdr_table, plat_1OU_sdr_table,
	       sizeof(SDR_Full_sensor) * SDR_TABLE_SIZE); // Use 1OU sesnsor table currently
	sdr_count = SDR_TABLE_SIZE;
}
