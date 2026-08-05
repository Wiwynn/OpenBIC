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

#ifndef PLAT_DEF_H
#define PLAT_DEF_H

#define BMC_USB_PORT "CDC_ACM_0"

#define ENABLE_MCTP_I3C
#define MCTP_I3C_PEC_ENABLE 1
#define PLAT_MCTP_MSG_MAX_SIZE 64

#define ENABLE_PLDM
#define ENABLE_PLDM_SENSOR
#define ENABLE_CCI
#define ENABLE_VISTARA
#define ENABLE_EVENT_TO_BMC

#define ENABLE_RTQ6056

/* Devices not populated on WF.
 * Sensor drivers are pulled in unconditionally by sensor_drive_tbl[] in
 * common/service/sensor/sensor.c, so unused ones have to be opted out here or
 * the linker cannot garbage collect them.
 * WF uses: adc128d818, ast_adc, ina233, max11617, mp2971, nvme, rtq6056,
 * sq52205, tmp461, tmp75, vistara, xdpe12284c.
 */
#define DISABLE_ADM1272
#define DISABLE_ADM1278
#define DISABLE_BMR351
#define DISABLE_CX7
#define DISABLE_EMC1412
#define DISABLE_G788P81U
#define DISABLE_INA230
#define DISABLE_ISL28022
#define DISABLE_ISL69254IRAZ_T
#define DISABLE_ISL69259
#define DISABLE_LM75BD118
#define DISABLE_LTC2991
#define DISABLE_LTC4282
#define DISABLE_LTC4286
#define DISABLE_M88RT51632
#define DISABLE_MAX16550A
#define DISABLE_MP2856GUT
#define DISABLE_MP2985
#define DISABLE_MP5990
#define DISABLE_NCT7718W
#define DISABLE_PCH
#define DISABLE_PEX89000
#define DISABLE_PT5161L
#define DISABLE_Q50SN120A1
#define DISABLE_RAA229621
#define DISABLE_TMP431
#define DISABLE_TPS25990
#define DISABLE_TPS53689
#define DISABLE_XDPE15284
#define DISABLE_XDPE19283B

/* DIMM temperatures are read over the CXL mailbox (sensor_dev_vistara),
 * not through the I3C DIMM / DDR5 PMIC paths.
 */
#define DISABLE_I3C_DIMM
#define DISABLE_DDR5_POWER
#define DISABLE_DDR5_TEMP
#define DISABLE_PMIC

/* VR update: WF only has Infineon XDPE12284C and MPS MP2971 */
#define DISABLE_MPQ8746
#define DISABLE_MP289X
#define DISABLE_TDA38741
#define DISABLE_MP2988

#define BIC_UPDATE_MAX_OFFSET 0xC0000
#define WORKER_STACK_SIZE 2048

#endif
