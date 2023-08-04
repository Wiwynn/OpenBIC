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

#ifndef ADC128_H
#define ADC128_H

#define ADC128_CHANNEL_DISABLE_REG 0x08
#define ADC128_ONE_SHOT_REG 0x09
#define ADC128_ADVANCED_CONFIG_REG 0x0B
#define ADC128_BUSY_STATUS_REG 0x0C

#define ADC128_CHANNEL_0_READING_REG 0x20
#define ADC128_CHANNEL_1_READING_REG 0x21
#define ADC128_CHANNEL_2_READING_REG 0x22
#define ADC128_CHANNEL_3_READING_REG 0x23
#define ADC128_CHANNEL_4_READING_REG 0x24
#define ADC128_CHANNEL_5_READING_REG 0x25
#define ADC128_CHANNEL_6_READING_REG 0x26
#define ADC128_CHANNEL_7_READING_REG 0x27

#define ADC128_INITIATE_SINGLE_CONVERSION_VAL 0x01
#define ADC128_EXTERNAL_REF_ENABLE_INTERNAL_VREF 0b0
#define ADC128_EXTERNAL_REF_ENABLE_VARIABLE_VREF 0b1
#define ADC128_DATA_READY_DELAY_MS 10
#define ADC128_DATA_READY_VAL 0x00

#endif
