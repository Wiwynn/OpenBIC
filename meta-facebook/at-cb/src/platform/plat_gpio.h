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

#ifndef PLAT_GPIO_H
#define PLAT_GPIO_H

#include "hal_gpio.h"

// gpio_cfg(chip, number, is_init, direction, status, int_type, int_callback)
// dedicate gpio A0~A7, B0~B7, C0~C7, D0~D7, E0~E7, total 40 gpios
// Default name: RESERVE_GPIOH0

// clang-format off

// For Pre-DVT BIC GPIO name
#define PRE_DVT_name_gpioA \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOA0) \
	gpio_name_to_num(PRE_DVT_INT_SMB_BIC_PEX0_N_R) \
	gpio_name_to_num(PRE_DVT_INT_SMB_BIC_PEX1_N_R) \
	gpio_name_to_num(PRE_DVT_SMB_P1V25_ALRT_N_R) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOA4) \
	gpio_name_to_num(PRE_DVT_SMB_INA233_ACCL1_6_12V_ALRT_N) \
	gpio_name_to_num(PRE_DVT_SMB_INA233_ACCL7_12_12V_ALRT_N) \
	gpio_name_to_num(PRE_DVT_FIO_PWRBTN_N_R)

#define PRE_DVT_name_gpioB \
	gpio_name_to_num(PRE_DVT_ASD_MUX2_SEL) \
	gpio_name_to_num(PRE_DVT_ASD_MUX2_EN_R4_N) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOB2) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOB3) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOB4) \
	gpio_name_to_num(PRE_DVT_TYPE_C_PLUG_DETECT_R) \
	gpio_name_to_num(PRE_DVT_MEB_STRAP0_N_R) \
	gpio_name_to_num(PRE_DVT_MEB_STRAP1_N_R)

#define PRE_DVT_name_gpioC \
	gpio_name_to_num(PRE_DVT_RST_SMB_MUX0_ACCL_N) \
	gpio_name_to_num(PRE_DVT_RST_SMB_MUX1_ACCL_N) \
	gpio_name_to_num(PRE_DVT_RST_BMC_FROM_ACB_N) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOC3) \
	gpio_name_to_num(PRE_DVT_SPI_ROM0_SEL) \
	gpio_name_to_num(PRE_DVT_SPI_ROM1_SEL) \
	gpio_name_to_num(PRE_DVT_ACB_THERM_OVERT_N) \
	gpio_name_to_num(PRE_DVT_RST_BIC_SELF_HW_RST_N)

#define PRE_DVT_name_gpioD \
	gpio_name_to_num(PRE_DVT_RST_USB_HUB0_N) \
	gpio_name_to_num(PRE_DVT_RST_USB_HUB1_N) \
	gpio_name_to_num(PRE_DVT_RST_USB_HUB2_N) \
	gpio_name_to_num(PRE_DVT_RST_USB_HUB3_N) \
	gpio_name_to_num(PRE_DVT_RST_USB_HUB4_N) \
	gpio_name_to_num(PRE_DVT_RST_USB_HUB5_N) \
	gpio_name_to_num(PRE_DVT_RST_U13_N) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOD7)

#define PRE_DVT_name_gpioE \
	gpio_name_to_num(PRE_DVT_FIO_REV_ID0_R) \
	gpio_name_to_num(PRE_DVT_FIO_REV_ID1_R) \
	gpio_name_to_num(PRE_DVT_FIO_REV_ID2_R) \
	gpio_name_to_num(PRE_DVT_PRSNT_FIO_N) \
	gpio_name_to_num(PRE_DVT_HS1_UV_WARN_N) \
	gpio_name_to_num(PRE_DVT_HS1_OC_WARN_N) \
	gpio_name_to_num(PRE_DVT_HS2_UV_WARN_N) \
	gpio_name_to_num(PRE_DVT_HS2_OC_WARN_N)

#define PRE_DVT_name_gpioF \
	gpio_name_to_num(PRE_DVT_SMB_P0V8_ALERT_N) \
	gpio_name_to_num(PRE_DVT_HS1_FAULT_N) \
	gpio_name_to_num(PRE_DVT_HS2_FAULT_N) \
	gpio_name_to_num(PRE_DVT_ACB_BIC_READY_N) \
	gpio_name_to_num(PRE_DVT_USB2_MUX0_SEL) \
	gpio_name_to_num(PRE_DVT_USB2_MUX1_SEL) \
	gpio_name_to_num(PRE_DVT_USB2_MUX3_SEL) \
	gpio_name_to_num(PRE_DVT_EN_JTAG_BIC_CPLD_N)

#define PRE_DVT_name_gpioG \
	gpio_name_to_num(PRE_DVT_INT_SMB_MEB_0_N_R) \
	gpio_name_to_num(PRE_DVT_INT_SMB_MEB_1_N_R) \
	gpio_name_to_num(PRE_DVT_INT_U228_N) \
	gpio_name_to_num(PRE_DVT_INT_U229_N) \
	gpio_name_to_num(PRE_DVT_INT_U230_N) \
	gpio_name_to_num(PRE_DVT_INT_U233_N) \
	gpio_name_to_num(PRE_DVT_INT_POWER_STATUS_N_R) \
	gpio_name_to_num(PRE_DVT_EN_5V_EFUSE)

#define PRE_DVT_name_gpioH \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOH0) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOH1) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOH2) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOH3) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOH4) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOH5) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOH6) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOH7)

#define PRE_DVT_name_gpioI \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOI0) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOI1) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOI2) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOI3) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOI4) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOI5) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOI6) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOI7)

#define PRE_DVT_name_gpioJ \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOJ0) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOJ1) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOJ2) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOJ3) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOJ4) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOJ5) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOJ6) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOJ7)
	
#define PRE_DVT_name_gpioK \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOK0) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOK1) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOK2) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOK3) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOK4) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOK5) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOK6) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOK7)

#define PRE_DVT_name_gpioL \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOL0) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOL1) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOL2) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOL3) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOL4) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOL5) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOL6) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOL7)

#define PRE_DVT_name_gpioM \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOM0) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOM1) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOM2) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOM3) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOM4) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOM5) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOM6) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOM7)

#define PRE_DVT_name_gpioN \
	gpio_name_to_num(PRE_DVT_RESERVE_GPION0) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPION1) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPION2) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPION3) \
	gpio_name_to_num(PRE_DVT_BOARD_ID1) \
	gpio_name_to_num(PRE_DVT_BOARD_ID2) \
	gpio_name_to_num(PRE_DVT_BOARD_ID3) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPION7)

#define PRE_DVT_name_gpioO \
	gpio_name_to_num(PRE_DVT_BOARD_ID0) \
	gpio_name_to_num(PRE_DVT_REV_ID0) \
	gpio_name_to_num(PRE_DVT_REV_ID1) \
	gpio_name_to_num(PRE_DVT_REV_ID2) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOO4) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOO5) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOO6) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOO7)

#define PRE_DVT_name_gpioP \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOP0) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOP1) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOP2) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOP3) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOP4) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOP5) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOP6) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOP7)

#define PRE_DVT_name_gpioQ \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOQ0) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOQ1) \
  gpio_name_to_num(PRE_DVT_RESERVE_GPIOQ2) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOQ3) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOQ4) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOQ5) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOQ6) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOQ7)

#define PRE_DVT_name_gpioR \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOR0) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOR1) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOR2) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOR3) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOR4) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOR5) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOR6) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOR7)

#define PRE_DVT_name_gpioS \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOS0) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOS1) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOS2) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOS3) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOS4) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOS5) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOS6) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOS7)

#define PRE_DVT_name_gpioT \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOT0) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOT1) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOT2) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOT3) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOT4) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOT5) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOT6) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOT7)

#define PRE_DVT_name_gpioU \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOU0) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOU1) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOU2) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOU3) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOU4) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOU5) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOU6) \
	gpio_name_to_num(PRE_DVT_RESERVE_GPIOU7)

// For Post-DVT BIC GPIO name
#define POST_DVT_name_gpioA \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOA0) \
  gpio_name_to_num(POST_DVT_INT_SMB_BIC_PEX0_N_R) \
  gpio_name_to_num(POST_DVT_INT_SMB_BIC_PEX1_N_R) \
  gpio_name_to_num(POST_DVT_SMB_P1V25_ALRT_N_R) \
  gpio_name_to_num(POST_DVT_INA233_ACCL1_ALRT_N_R) \
  gpio_name_to_num(POST_DVT_INA233_ACCL2_ALRT_N_R) \
  gpio_name_to_num(POST_DVT_INA233_ACCL3_ALRT_N_R) \
  gpio_name_to_num(POST_DVT_FIO_PWRBTN_N_R)

#define POST_DVT_name_gpioB \
  gpio_name_to_num(POST_DVT_ASD_MUX2_SEL) \
  gpio_name_to_num(POST_DVT_ASD_MUX2_EN_R4_N) \
  gpio_name_to_num(POST_DVT_INA233_ACCL4_ALRT_N_R) \
  gpio_name_to_num(POST_DVT_INA233_ACCL5_ALRT_N_R) \
  gpio_name_to_num(POST_DVT_INA233_ACCL6_ALRT_N_R) \
  gpio_name_to_num(POST_DVT_TYPE_C_PLUG_DETECT_R) \
  gpio_name_to_num(POST_DVT_MEB_STRAP0_N_R) \
  gpio_name_to_num(POST_DVT_MEB_STRAP1_N_R)

#define POST_DVT_name_gpioC \
  gpio_name_to_num(POST_DVT_RST_SMB_MUX0_ACCL_N) \
  gpio_name_to_num(POST_DVT_RST_SMB_MUX1_ACCL_N) \
  gpio_name_to_num(POST_DVT_RST_BMC_FROM_ACB_N) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOC3) \
  gpio_name_to_num(POST_DVT_SPI_ROM0_SEL) \
  gpio_name_to_num(POST_DVT_SPI_ROM1_SEL) \
  gpio_name_to_num(POST_DVT_ACB_THERM_OVERT_N) \
  gpio_name_to_num(POST_DVT_RST_BIC_SELF_HW_RST_N)

#define POST_DVT_name_gpioD \
  gpio_name_to_num(POST_DVT_RST_USB_HUB0_N) \
  gpio_name_to_num(POST_DVT_RST_USB_HUB1_N) \
  gpio_name_to_num(POST_DVT_RST_USB_HUB2_N) \
  gpio_name_to_num(POST_DVT_RST_USB_HUB3_N) \
  gpio_name_to_num(POST_DVT_RST_USB_HUB4_N) \
  gpio_name_to_num(POST_DVT_RST_USB_HUB5_N) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOD6) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOD7)

#define POST_DVT_name_gpioE \
  gpio_name_to_num(POST_DVT_FIO_REV_ID0_R) \
  gpio_name_to_num(POST_DVT_FIO_REV_ID1_R) \
  gpio_name_to_num(POST_DVT_FIO_REV_ID2_R) \
  gpio_name_to_num(POST_DVT_PRSNT_FIO_N) \
  gpio_name_to_num(POST_DVT_HS1_UV_WARN_N) \
  gpio_name_to_num(POST_DVT_HS1_OC_WARN_N) \
  gpio_name_to_num(POST_DVT_HS2_UV_WARN_N) \
  gpio_name_to_num(POST_DVT_HS2_OC_WARN_N)

#define POST_DVT_name_gpioF \
  gpio_name_to_num(POST_DVT_SMB_P0V8_ALERT_N) \
  gpio_name_to_num(POST_DVT_HS1_FAULT_N) \
  gpio_name_to_num(POST_DVT_HS2_FAULT_N) \
  gpio_name_to_num(POST_DVT_ACB_BIC_READY_N) \
  gpio_name_to_num(POST_DVT_USB2_MUX0_SEL) \
  gpio_name_to_num(POST_DVT_USB2_MUX1_SEL) \
  gpio_name_to_num(POST_DVT_USB2_MUX3_SEL) \
  gpio_name_to_num(POST_DVT_EN_JTAG_BIC_CPLD_N)

#define POST_DVT_name_gpioG \
  gpio_name_to_num(POST_DVT_INT_SMB_MEB_0_N_R) \
  gpio_name_to_num(POST_DVT_INT_SMB_MEB_1_N_R) \
  gpio_name_to_num(POST_DVT_INT_U228_N) \
  gpio_name_to_num(POST_DVT_INT_U229_N) \
  gpio_name_to_num(POST_DVT_INT_U230_N) \
  gpio_name_to_num(POST_DVT_INT_U233_N) \
  gpio_name_to_num(POST_DVT_INT_POWER_STATUS_N_R) \
  gpio_name_to_num(POST_DVT_EN_5V_EFUSE)

#define POST_DVT_name_gpioH \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOH0) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOH1) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOH2) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOH3) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOH4) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOH5) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOH6) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOH7)

#define POST_DVT_name_gpioI \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOI0) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOI1) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOI2) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOI3) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOI4) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOI5) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOI6) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOI7)

#define POST_DVT_name_gpioJ \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOJ0) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOJ1) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOJ2) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOJ3) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOJ4) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOJ5) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOJ6) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOJ7)

#define POST_DVT_name_gpioK \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOK0) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOK1) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOK2) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOK3) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOK4) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOK5) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOK6) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOK7)

#define POST_DVT_name_gpioL \
  gpio_name_to_num(POST_DVT_P3V3_ACCL12_PG) \
  gpio_name_to_num(POST_DVT_P3V3_ACCL11_PG) \
  gpio_name_to_num(POST_DVT_P3V3_ACCL10_PG) \
  gpio_name_to_num(POST_DVT_P3V3_ACCL9_PG) \
  gpio_name_to_num(POST_DVT_P3V3_ACCL8_PG) \
  gpio_name_to_num(POST_DVT_P3V3_ACCL7_PG) \
  gpio_name_to_num(POST_DVT_P3V3_ACCL6_PG) \
  gpio_name_to_num(POST_DVT_P3V3_ACCL5_PG)

#define POST_DVT_name_gpioM \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOM0) \
  gpio_name_to_num(POST_DVT_P3V3_ACCL4_PG) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOM2) \
  gpio_name_to_num(POST_DVT_P3V3_ACCL3_PG) \
  gpio_name_to_num(POST_DVT_P3V3_ACCL2_PG) \
  gpio_name_to_num(POST_DVT_P3V3_ACCL1_PG) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOM6) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOM7)

#define POST_DVT_name_gpioN \
  gpio_name_to_num(POST_DVT_RESERVE_GPION0) \
  gpio_name_to_num(POST_DVT_RESERVE_GPION1) \
  gpio_name_to_num(POST_DVT_RESERVE_GPION2) \
  gpio_name_to_num(POST_DVT_RESERVE_GPION3) \
  gpio_name_to_num(POST_DVT_BOARD_ID1) \
  gpio_name_to_num(POST_DVT_BOARD_ID2) \
  gpio_name_to_num(POST_DVT_BOARD_ID3) \
  gpio_name_to_num(POST_DVT_RESERVE_GPION7)

#define POST_DVT_name_gpioO \
  gpio_name_to_num(POST_DVT_BOARD_ID0) \
  gpio_name_to_num(POST_DVT_REV_ID0) \
  gpio_name_to_num(POST_DVT_REV_ID1) \
  gpio_name_to_num(POST_DVT_REV_ID2) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOO4) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOO5) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOO6) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOO7)

#define POST_DVT_name_gpioP \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOP0) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOP1) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOP2) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOP3) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOP4) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOP5) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOP6) \
  gpio_name_to_num(POST_DVT_INA233_ACCL10_ALRT_N_R)

#define POST_DVT_name_gpioQ \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOQ0) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOQ1) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOQ2) \
  gpio_name_to_num(POST_DVT_INA233_ACCL11_ALRT_N_R) \
  gpio_name_to_num(POST_DVT_INA233_ACCL12_ALRT_N_R) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOQ5) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOQ6) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOQ7)

#define POST_DVT_name_gpioR \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOR0) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOR1) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOR2) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOR3) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOR4) \
  gpio_name_to_num(POST_DVT_INA233_ACCL7_ALRT_N_R) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOR6) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOR7)

#define POST_DVT_name_gpioS \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOS0) \
  gpio_name_to_num(POST_DVT_INA233_ACCL8_ALRT_N_R) \
  gpio_name_to_num(POST_DVT_INA233_ACCL9_ALRT_N_R) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOS3) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOS4) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOS5) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOS6) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOS7)

#define POST_DVT_name_gpioT \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOT0) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOT1) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOT2) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOT3) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOT4) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOT5) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOT6) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOT7)

#define POST_DVT_name_gpioU \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOU0) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOU1) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOU2) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOU3) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOU4) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOU5) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOU6) \
  gpio_name_to_num(POST_DVT_RESERVE_GPIOU7)

// clang-format on

#define gpio_name_to_num(x) x,
enum _PRE_DVT_GPIO_NUMS_ {
	PRE_DVT_name_gpioA PRE_DVT_name_gpioB PRE_DVT_name_gpioC PRE_DVT_name_gpioD
		PRE_DVT_name_gpioE PRE_DVT_name_gpioF PRE_DVT_name_gpioG PRE_DVT_name_gpioH
			PRE_DVT_name_gpioI PRE_DVT_name_gpioJ PRE_DVT_name_gpioK PRE_DVT_name_gpioL
				PRE_DVT_name_gpioM PRE_DVT_name_gpioN PRE_DVT_name_gpioO
					PRE_DVT_name_gpioP PRE_DVT_name_gpioQ PRE_DVT_name_gpioR
						PRE_DVT_name_gpioS PRE_DVT_name_gpioT
							PRE_DVT_name_gpioU
};

enum _POST_DVT_GPIO_NUMS_ {
	POST_DVT_name_gpioA POST_DVT_name_gpioB POST_DVT_name_gpioC POST_DVT_name_gpioD
		POST_DVT_name_gpioE POST_DVT_name_gpioF POST_DVT_name_gpioG POST_DVT_name_gpioH
			POST_DVT_name_gpioI POST_DVT_name_gpioJ POST_DVT_name_gpioK
				POST_DVT_name_gpioL POST_DVT_name_gpioM POST_DVT_name_gpioN
					POST_DVT_name_gpioO POST_DVT_name_gpioP POST_DVT_name_gpioQ
						POST_DVT_name_gpioR POST_DVT_name_gpioS
							POST_DVT_name_gpioT POST_DVT_name_gpioU
};

extern enum _PRE_DVT_GPIO_NUMS_ PRE_DVT_GPIO_NUMS;
extern enum _POST_DVT_GPIO_NUMS_ POST_DVT_GPIO_NUMS;

#undef gpio_name_to_num

void enable_PRDY_interrupt();
void disable_PRDY_interrupt();
void init_board_rev_gpio();

#endif
