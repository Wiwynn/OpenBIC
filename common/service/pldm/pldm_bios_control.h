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

#ifndef _PLDM_BIOS_CONTROL_H
#define _PLDM_BIOS_CONTROL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pldm.h"

// 補上這些typedef是從DSP0247來的

typedef enum {
	PLDM_BIOS_CONTROL_CMD_CODE_SET_BIOS_ATTRIBUTE_CURRENT_VALUE = 0x07,
	PLDM_BIOS_CONTROL_CMD_CODE_GET_BIOS_ATTRIBUTE_CURRENT_VALUE_BY_HANDLE = 0x08,
} pldm_bios_control_commands;

typedef enum {
	PLDM_BIOS_CONTROL_ATTRIBUTE_TYPE_BIOS_ENUM = 0x00,
	PLDM_BIOS_CONTROL_ATTRIBUTE_TYPE_STRING = 0x01,
	PLDM_BIOS_CONTROL_ATTRIBUTE_TYPE_PASSWORD = 0x02,
	PLDM_BIOS_CONTROL_ATTRIBUTE_TYPE_INTEGER = 0x03,
	PLDM_BIOS_CONTROL_ATTRIBUTE_TYPE_BOOT_CONFIG_SETTING = 0x04,
	PLDM_BIOS_CONTROL_ATTRIBUTE_TYPE_COLLECTION = 0x05,
	PLDM_BIOS_CONTROL_ATTRIBUTE_TYPE_CONFIG_SET = 0x06,
	PLDM_BIOS_CONTROL_ATTRIBUTE_TYPE_ENUM_RO = 0x80,
	PLDM_BIOS_CONTROL_ATTRIBUTE_TYPE_STRING_RO = 0x81,
	PLDM_BIOS_CONTROL_ATTRIBUTE_TYPE_PASSWORD_RO = 0x82,
	PLDM_BIOS_CONTROL_ATTRIBUTE_TYPE_INTEGER_RO = 0x83,
	PLDM_BIOS_CONTROL_ATTRIBUTE_TYPE_BOOT_CONFIG_SETTIN_RO = 0x84,
	PLDM_BIOS_CONTROL_ATTRIBUTE_TYPE_COLLECTION_RO = 0x85,
	PLDM_BIOS_CONTROL_ATTRIBUTE_TYPE_CONFIG_SET_RO = 0x86
} pldm_bios_control_attribute_types;

typedef enum {
	PLDM_BIOS_CONTROL_BOOT_TYPE_UNKNOWN = 0x0,
	PLDM_BIOS_CONTROL_BOOT_TYPE_DEFAULT = 0x1,
	PLDM_BIOS_CONTROL_BOOT_TYPE_NEXT = 0x2,
	PLDM_BIOS_CONTROL_BOOT_TYPE_DEFAULT_NEXT = 0x3,
	PLDM_BIOS_CONTROL_BOOT_TYPE_ONETIME = 0x4,
	PLDM_BIOS_CONTROL_BOOT_TYPE_DEFAULT_ONETIME = 0x5
} pldm_bios_control_boot_config_type;

typedef enum {
	PLDM_BIOS_CONTROL_SUPPORT_UNORDERED_LIMITED_FAIL_THROUGH = 0x0,
	PLDM_BIOS_CONTROL_SUPPORT_UNORDERED_FAIL_THROUGH = 0x1,
	PLDM_BIOS_CONTROL_SUPPORT_ORDERED_LIMITED_FAIL_THROUGH = 0x2,
	PLDM_BIOS_CONTROL_SUPPORT_ORDERED_FAIL_THROUGH = 0x03,
	PLDM_BIOS_CONTROL_SUPPORT_UNORDERED = 0x04,
	PLDM_BIOS_CONTROL_SUPPORT_ORDERED = 0x05,
	PLDM_BIOS_CONTROL_SUPPORT_LIMITED_FAIL_THROUGH = 0x06,
	PLDM_BIOS_CONTROL_SUPPORT_FAIL_THROUGH = 0x07,
	PLDM_BIOS_CONTROL_SUPPORT_ALL_ORDERED_AND_FAIL_THROUGH_MODE = 0x08
} pldm_bios_control_supported_order_and_fail_through_mode;

typedef enum {
	PLDM_BIOS_CONTROL_TRANSFER_FLAG_START = 0x01,
	PLDM_BIOS_CONTROL_TRANSFER_FLAG_MIDDLE = 0x02,
	PLDM_BIOS_CONTROL_TRANSFER_FLAG_END = 0x04,
	PLDM_BIOS_CONTROL_TRANSFER_FLAG_START_AND_END = 0x05
} pldm_bios_control_transfer_flag;

typedef enum {
	PLDM_BIOS_CONTROL_TRANSFER_OPERATION_FLAG_GET_NEXT_PART = 0x0,
	PLDM_BIOS_CONTROL_TRANSFER_OPERATION_FLAG_GET_FIRST_PART = 0x1
} pldm_bios_control_transfer_operation_flag;

typedef enum {
	PLDM_BIOS_CONTROL_UNORDERED_LIMITED_FAIL_THROUGH = 0x0,
	PLDM_BIOS_CONTROL_UNORDERED_FAIL_THROUGH = 0x1,
	PLDM_BIOS_CONTROL_ORDERED_LIMITED_FAIL_THROUGH = 0x2,
	PLDM_BIOS_CONTROL_ORDERED_FAIL_THROUGH = 0x3
} pldm_bios_control_order_and_fail_through_mode;

typedef struct {
	pldm_bios_control_boot_config_type boot_config_type;
	pldm_bios_control_supported_order_and_fail_through_mode supported_order_fail_through_mode;
	uint8_t minimum_boot_source_settings_count;
	uint8_t maximum_boot_source_settings_count;
	uint8_t possible_boot_source_settings_count;
	uint16_t *boot_source_setting_handles;
} __attribute__((packed)) pldm_bios_control_bios_boot_config_setting_table;

typedef struct {
	pldm_bios_control_boot_config_type boot_config_type;
	pldm_bios_control_order_and_fail_through_mode order_fail_through_mode;
	uint8_t boot_source_settings_count;
	uint8_t *boot_source_order;
} __attribute__((packed)) pldm_bios_control_bios_boot_config_setting_value;

typedef struct {
	uint16_t attribute_handle;
	pldm_bios_control_attribute_types attribute_type;
	uint8_t *attribute_data;
} __attribute__((packed)) pldm_bios_attribute_value_data;

typedef struct {
	uint32_t data_transfer_handle;
	uint8_t transfer_flag;
	pldm_bios_attribute_value_data *value_data;
} __attribute__((packed)) pldm_set_bios_attribute_current_value_req;

typedef struct {
	uint32_t data_transfer_handle;
	uint8_t transfer_operation_flag;
	uint16_t attribute_handle;
} __attribute__((packed)) pldm_get_bios_sttribute_current_value_by_handle_req;

typedef struct {
	uint8_t completion_code;
	uint32_t next_data_transfer_handle;
	uint8_t transfer_flag;
	uint8_t attribute_data[0];
} __attribute__((packed)) pldm_get_bios_sttribute_current_value_by_handle_resp;

int set_boot_order(uint8_t *boot_sequence);
int get_boot_order(uint8_t *resp, uint16_t resp_len);
int pldm_bios_control_set_bios_attribute_current_value(void *mctp_p,
						       pldm_bios_attribute_value_data *data,
						       uint16_t data_len, void *ext_params);
int pldm_bios_control_get_bios_sttribute_current_value_by_handle(void *mctp_p,
								 uint16_t attribute_handle,
								 uint8_t *resp, uint16_t resp_len,
								 void *ext_params);

#ifdef __cplusplus
}
#endif

#endif /*_PLDM_BIOS_CONTROL_H*/
