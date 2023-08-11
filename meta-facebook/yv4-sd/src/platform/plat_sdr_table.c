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

SDR_Full_sensor plat_sdr_table[] = {
	{
		// INLET Temperature
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
		0x00, // [7:0] M bits
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
		"FF_1OU_BOARD_INLET_TEMP_C",
	},
	{
		// OUTLET Temperature
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_OUTLET_TEMP, // sensor number

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
		0x00, // [7:0] M bits
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
		"MB_OUTLET_TEMP_C",
	},
	{
		// FIO Temperature
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_FIO_TEMP, // sensor number

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
		0x00, // [7:0] M bits
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
		"MB_FIO_TEMP_C",
	},
	// TODO : CPU, DIMMA~DIMML TEMP
	{
		// SSD BOOT Temperature
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_SSD_BOOT_TEMP, // sensor number

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
		0x00, // [7:0] M bits
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
		"MB_SSD_BOOT_TEMP_C",
	},
	{
		// SSD DATA Temperature
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_SSD_DATA_TEMP, // sensor number

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
		0x00, // [7:0] M bits
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
		"MB_SSD_DATA_TEMP_C",
	},
	{
		// VR CPU0 Temperature
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_CPU0_VR_TEMP, // sensor number

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
		0x00, // [7:0] M bits
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
		"MB_VR_CPU0_TEMP_C",
	},
	{
		// VR SOC Temperature
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_SOC_VR_TEMP, // sensor number

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
		0x00, // [7:0] M bits
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
		"MB_VR_SOC_TEMP_C",
	},
	{
		// VR CPU1 Temperature
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_CPU1_VR_TEMP, // sensor number

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
		0x00, // [7:0] M bits
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
		"MB_VR_CPU1_TEMP_C",
	},
	{
		// VR PVDDIO Temperature
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_PVDDIO_VR_TEMP, // sensor number

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
		0x00, // [7:0] M bits
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
		"SENSOR_NUM_PVDDIO_VR_TEMP",
	},
	{
		// VR PVDD11 Temperature
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_PVDD11_VR_TEMP, // sensor number

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
		0x00, // [7:0] M bits
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
		"MB_VR_PVDD11_TEMP_C",
	},

	{
		// ADC P12V STBY Voltage
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_P12V_STBY_VOLT, // sensor number

		IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
		0x00, // entity instance
		IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT |
			IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
		IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
			IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
		IPMI_SDR_SENSOR_TYPE_VOLTAGE, // sensor type
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
		0x00, // [7:0] M bits
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
		"MB_ADC_P12V_STBY_VOLT_V",
	},
	{
		// ADC PVDD18 S5 Voltage
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_PVDD18_S5_VOLT, // sensor number

		IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
		0x00, // entity instance
		IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT |
			IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
		IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
			IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
		IPMI_SDR_SENSOR_TYPE_VOLTAGE, // sensor type
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
		0x00, // [7:0] M bits
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
		"MB_ADC_PVDD18_S5_VOLT_V",
	},
	{
		// ADC P3V3 STBY Voltage
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_P3V3_STBY_VOLT, // sensor number

		IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
		0x00, // entity instance
		IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT |
			IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
		IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
			IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
		IPMI_SDR_SENSOR_TYPE_VOLTAGE, // sensor type
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
		0x00, // [7:0] M bits
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
		"MB_ADC_P3V3_STBY_VOLT_V",
	},
	{
		// ADC P3V BAT Voltage
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_P3V_BAT_VOLT, // sensor number

		IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
		0x00, // entity instance
		IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT |
			IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
		IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
			IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
		IPMI_SDR_SENSOR_TYPE_VOLTAGE, // sensor type
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
		0x00, // [7:0] M bits
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
		"MB_ADC_P3V_BAT_VOLT_V",
	},
	{
		// ADC PVDD33 S5 Voltage
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_PVDD33_S5_VOLT, // sensor number

		IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
		0x00, // entity instance
		IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT |
			IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
		IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
			IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
		IPMI_SDR_SENSOR_TYPE_VOLTAGE, // sensor type
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
		0x00, // [7:0] M bits
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
		"MB_ADC_PVDD33_S5_VOLT_V",
	},
	{
		// ADC P5V STBY Voltage
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_P5V_STBY_VOLT, // sensor number

		IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
		0x00, // entity instance
		IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT |
			IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
		IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
			IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
		IPMI_SDR_SENSOR_TYPE_VOLTAGE, // sensor type
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
		0x00, // [7:0] M bits
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
		"MB_ADC_P5V_STBY_VOLT_V",
	},
	{
		// ADC P12V DIMM0 Voltage
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_P12V_DIMM_0_VOLT, // sensor number

		IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
		0x00, // entity instance
		IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT |
			IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
		IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
			IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
		IPMI_SDR_SENSOR_TYPE_VOLTAGE, // sensor type
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
		0x00, // [7:0] M bits
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
		"MB_ADC_P12V_DIMM_0_VOLT_V",
	},
	{
		// ADC P12V DIMM1 Voltage
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_P12V_DIMM_1_VOLT, // sensor number

		IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
		0x00, // entity instance
		IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT |
			IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
		IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
			IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
		IPMI_SDR_SENSOR_TYPE_VOLTAGE, // sensor type
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
		0x00, // [7:0] M bits
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
		"MB_ADC_P12V_DIMM_1_VOLT_V",
	},
	{
		// ADC P1V2 STBY Voltage
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_P1V2_STBY_VOLT, // sensor number

		IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
		0x00, // entity instance
		IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT |
			IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
		IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
			IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
		IPMI_SDR_SENSOR_TYPE_VOLTAGE, // sensor type
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
		0x00, // [7:0] M bits
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
		"MB_ADC_P1V2_STBY_VOLT_V",
	},
	{
		// ADC P1V8 STBY Voltage
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_P1V8_STBY_VOLT, // sensor number

		IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
		0x00, // entity instance
		IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT |
			IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
		IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
			IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
		IPMI_SDR_SENSOR_TYPE_VOLTAGE, // sensor type
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
		0x00, // [7:0] M bits
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
		"MB_ADC_P1V8_STBY_VOLT_V",
	},
	{
		// ADC SLOT DETECT Voltage
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_SLOT_ADC_DETECT_VOLT, // sensor number

		IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
		0x00, // entity instance
		IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT |
			IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
		IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
			IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
		IPMI_SDR_SENSOR_TYPE_VOLTAGE, // sensor type
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
		0x00, // [7:0] M bits
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
		"MB_ADC_SLOT_DETECT_VOLT_V",
	},
	{
		// ADC SIDECAR DETECT Voltage
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_ADC_SIDECAR_DETECT_VOLT, // sensor number

		IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
		0x00, // entity instance
		IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT |
			IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
		IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
			IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
		IPMI_SDR_SENSOR_TYPE_VOLTAGE, // sensor type
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
		0x00, // [7:0] M bits
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
		"MB_ADC_SIDECAR_DETECT_VOLT_V",
	},

	{
		// VR CPU0 Current
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_CPU0_VR_CURR, // sensor number

		IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
		0x00, // entity instance
		IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT |
			IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
		IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
			IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
		IPMI_SDR_SENSOR_TYPE_CURRENT, // sensor type
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
		0x00, // [7:0] M bits
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
		"MB_VR_CPU0_CURR_A",
	},
	{
		// VR SOC Current
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_SOC_VR_CURR, // sensor number

		IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
		0x00, // entity instance
		IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT |
			IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
		IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
			IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
		IPMI_SDR_SENSOR_TYPE_CURRENT, // sensor type
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
		0x00, // [7:0] M bits
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
		"MB_VR_SOC_CURR_A",
	},
	{
		// VR CPU1 Current
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_CPU1_VR_CURR, // sensor number

		IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
		0x00, // entity instance
		IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT |
			IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
		IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
			IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
		IPMI_SDR_SENSOR_TYPE_CURRENT, // sensor type
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
		0x00, // [7:0] M bits
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
		"MB_VR_CPU1_CURR_A",
	},
	{
		// VR PVDDIO Current
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_PVDDIO_VR_CURR, // sensor number

		IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
		0x00, // entity instance
		IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT |
			IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
		IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
			IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
		IPMI_SDR_SENSOR_TYPE_CURRENT, // sensor type
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
		0x00, // [7:0] M bits
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
		"MB_VR_PVDDIO_CURR_A",
	},
	{
		// VR PVDD11 Current
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_PVDD11_VR_CURR, // sensor number

		IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
		0x00, // entity instance
		IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT |
			IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
		IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
			IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
		IPMI_SDR_SENSOR_TYPE_CURRENT, // sensor type
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
		0x00, // [7:0] M bits
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
		"MB_VR_PVDD11_CURR_A",
	},

	{
		// VR CPU0 PWR
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_CPU0_VR_PWR, // sensor number

		IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
		0x00, // entity instance
		IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT |
			IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
		IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
			IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
		IPMI_SDR_SENSOR_TYPE_POWER_SUPPLY, // sensor type
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
		0x00, // [7:0] M bits
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
		"MB_VR_CPU0_PWR_W",
	},
	{
		// VR SOC PWR
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_SOC_VR_PWR, // sensor number

		IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
		0x00, // entity instance
		IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT |
			IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
		IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
			IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
		IPMI_SDR_SENSOR_TYPE_POWER_SUPPLY, // sensor type
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
		0x00, // [7:0] M bits
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
		"MB_VR_SOC_PWR_W",
	},
	{
		// VR CPU1 PWR
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_CPU1_VR_PWR, // sensor number

		IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
		0x00, // entity instance
		IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT |
			IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
		IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
			IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
		IPMI_SDR_SENSOR_TYPE_POWER_SUPPLY, // sensor type
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
		0x00, // [7:0] M bits
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
		"MB_VR_CPU1_PWR_W",
	},
	{
		// VR PVDDIO PWR
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_PVDDIO_VR_PWR, // sensor number

		IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
		0x00, // entity instance
		IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT |
			IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
		IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
			IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
		IPMI_SDR_SENSOR_TYPE_POWER_SUPPLY, // sensor type
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
		0x00, // [7:0] M bits
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
		"MB_VR_PVDDIO_PWR_W",
	},
	{
		// VR PVDD11 PWR
		0x00,
		0x00, // record ID
		IPMI_SDR_VER_15, // SDR ver
		IPMI_SDR_FULL_SENSOR, // record type
		IPMI_SDR_FULL_SENSOR_MIN_LEN, // size of struct

		SELF_I2C_ADDRESS << 1, // owner id
		0x00, // owner lun
		SENSOR_NUM_PVDD11_VR_PWR, // sensor number

		IPMI_SDR_ENTITY_ID_SYS_BOARD, // entity id
		0x00, // entity instance
		IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_TYPE |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT |
			IPMI_SDR_SENSOR_INIT_DEF_SCAN, // sensor init
		IPMI_SDR_SENSOR_CAP_THRESHOLD_RW |
			IPMI_SDR_SENSOR_CAP_EVENT_CTRL_NO, // sensor capabilities
		IPMI_SDR_SENSOR_TYPE_POWER_SUPPLY, // sensor type
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
		0x00, // [7:0] M bits
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
		"MB_VR_PVDD11_PWR_W",
	},
	// TODO : CPU, DIMMA~DIMML PWR
};

const int SDR_TABLE_SIZE = ARRAY_SIZE(plat_sdr_table);
