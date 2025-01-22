#include <stdlib.h>

#include "libutil.h"
#include "pldm_firmware_update.h"
#include "plat_pldm_device_identifier.h"
#include "plat_isr.h"
#include "ioexp_tca9555.h"
#include "hal_gpio.h"
#include "plat_gpio.h"

#include <logging/log.h>

LOG_MODULE_REGISTER(plat_dsidentifier);

struct pldm_descriptor_string PLDM_VR_PVDDQ_AB_ASIC1_DESCRIPTORS[] = {
	{
		.descriptor_type = PLDM_FWUP_IANA_ENTERPRISE_ID,
		.title_string = NULL,
		.descriptor_data = "0000A015",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Platform",
		.descriptor_data = "Yosemite4",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Board",
		.descriptor_data = "WailuaFalls",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "ComponentType",
		.descriptor_data = "VR",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "ComponentInstance",
		.descriptor_data = "1",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_LONG_STRING,
		.title_string = NULL,
		.descriptor_data =
			"00000000000000000000000000000000000000000000000000000000000000000000000000000000",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_SHORT_STRING,
		.title_string = NULL,
		.descriptor_data = "00000000000000000000",
	},
};

struct pldm_descriptor_string PLDM_VR_PVDDQ_CD_ASIC1_DESCRIPTORS[] = {
	{
		.descriptor_type = PLDM_FWUP_IANA_ENTERPRISE_ID,
		.title_string = NULL,
		.descriptor_data = "0000A015",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Platform",
		.descriptor_data = "Yosemite4",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Board",
		.descriptor_data = "WailuaFalls",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "ComponentType",
		.descriptor_data = "VR",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "ComponentInstance",
		.descriptor_data = "2",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_LONG_STRING,
		.title_string = NULL,
		.descriptor_data =
			"00000000000000000000000000000000000000000000000000000000000000000000000000000000",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_SHORT_STRING,
		.title_string = NULL,
		.descriptor_data = "00000000000000000000",
	},
};

struct pldm_descriptor_string PLDM_VR_PVDDQ_AB_ASIC2_DESCRIPTORS[] = {
	{
		.descriptor_type = PLDM_FWUP_IANA_ENTERPRISE_ID,
		.title_string = NULL,
		.descriptor_data = "0000A015",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Platform",
		.descriptor_data = "Yosemite4",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Board",
		.descriptor_data = "WailuaFalls",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "ComponentType",
		.descriptor_data = "VR",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "ComponentInstance",
		.descriptor_data = "3",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_LONG_STRING,
		.title_string = NULL,
		.descriptor_data =
			"00000000000000000000000000000000000000000000000000000000000000000000000000000000",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_SHORT_STRING,
		.title_string = NULL,
		.descriptor_data = "00000000000000000000",
	},
};

struct pldm_descriptor_string PLDM_VR_PVDDQ_CD_ASIC2_DESCRIPTORS[] = {
	{
		.descriptor_type = PLDM_FWUP_IANA_ENTERPRISE_ID,
		.title_string = NULL,
		.descriptor_data = "0000A015",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Platform",
		.descriptor_data = "Yosemite4",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Board",
		.descriptor_data = "WailuaFalls",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "ComponentType",
		.descriptor_data = "VR",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "ComponentInstance",
		.descriptor_data = "4",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_LONG_STRING,
		.title_string = NULL,
		.descriptor_data =
			"00000000000000000000000000000000000000000000000000000000000000000000000000000000",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_SHORT_STRING,
		.title_string = NULL,
		.descriptor_data = "00000000000000000000",
	},
};

struct pldm_descriptor_string PLDM_CXL1_DESCRIPTORS[] = {
	{
		.descriptor_type = PLDM_FWUP_IANA_ENTERPRISE_ID,
		.title_string = NULL,
		.descriptor_data = "0000A015",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Platform",
		.descriptor_data = "Yosemite4",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Board",
		.descriptor_data = "WailuaFalls",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "ComponentType",
		.descriptor_data = "CXL",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "ComponentInstance",
		.descriptor_data = "1",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_LONG_STRING,
		.title_string = NULL,
		.descriptor_data =
			"6D6574612E43584C2E312E566973746172615F325456360000000000000000000000000000000000",
	},
};

struct pldm_descriptor_string PLDM_CXL2_DESCRIPTORS[] = {
	{
		.descriptor_type = PLDM_FWUP_IANA_ENTERPRISE_ID,
		.title_string = NULL,
		.descriptor_data = "0000A015",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Platform",
		.descriptor_data = "Yosemite4",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Board",
		.descriptor_data = "WailuaFalls",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "ComponentType",
		.descriptor_data = "CXL",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "ComponentInstance",
		.descriptor_data = "2",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_LONG_STRING,
		.title_string = NULL,
		.descriptor_data =
			"6D6574612E43584C2E322E566973746172615F325456360000000000000000000000000000000000",
	},
};

// internal helper function to get descriptor data
char **get_descriptor_data(struct pldm_descriptor_string *descriptors, size_t descriptor_count,
			   enum pldm_firmware_update_descriptor_types descriptor_type,
			   char *title_string)
{
	for (size_t i = 0; i < descriptor_count; i++) {
		if (descriptors[i].descriptor_type == descriptor_type) {
			if (descriptor_type == PLDM_FWUP_VENDOR_DEFINED) {
				if (strcmp(descriptors[i].title_string, title_string) == 0) {
					return &descriptors[i].descriptor_data;
				}
			} else {
				return &descriptors[i].descriptor_data;
			}
		}
	}
	return NULL;
}

// internal helper function to convert string to ascii
char *string_to_ascii(char *str, char *ascii, size_t len)
{
	size_t i = 0;
	for (i = 0; i < len; i++) {
		if (str[i] == '\0') {
			break;
		}
		sprintf(ascii + i * 2, "%02X", str[i]);
	}
	for (; i < len; i++) {
		sprintf(ascii + i * 2, "%02X", '\0');
	}
	ascii[len * 2] = '\0';
	return ascii;
}

// internal helper function to replace model number string
bool replace_model_number_long_string(struct pldm_downstream_identifier_table *downstream_table,
				      size_t idx, char *model_number)
{
	char **descriptor_data = get_descriptor_data(downstream_table[idx].descriptor,
						     downstream_table[idx].descriptor_count,
						     PLDM_ASCII_MODEL_NUMBER_LONG_STRING, NULL);
	if (descriptor_data && *descriptor_data) {
		char *buf = malloc(PLDM_ASCII_MODEL_NUMBER_LONG_STRING_LENGTH * 2 + 1);
		string_to_ascii(model_number, buf, PLDM_ASCII_MODEL_NUMBER_LONG_STRING_LENGTH);
		*descriptor_data = buf;
		return true;
	} else {
		LOG_ERR("Failed to get model number long string");
		return false;
	}
}

// internal helper function to replace model number string
bool replace_model_number_short_string(struct pldm_downstream_identifier_table *downstream_table,
				       size_t idx, char *model_number)
{
	char **descriptor_data = get_descriptor_data(downstream_table[idx].descriptor,
						     downstream_table[idx].descriptor_count,
						     PLDM_ASCII_MODEL_NUMBER_SHORT_STRING, NULL);
	if (descriptor_data && *descriptor_data) {
		char *buf = malloc(PLDM_ASCII_MODEL_NUMBER_LONG_STRING_LENGTH * 2 + 1);
		string_to_ascii(model_number, buf, PLDM_ASCII_MODEL_NUMBER_SHORT_STRING_LENGTH);
		*descriptor_data = buf;
		return true;
	} else {
		LOG_ERR("Failed to get model number short string");
		return false;
	}
}

struct pldm_downstream_identifier_table downstream_table[] = {
	{ .descriptor = PLDM_VR_PVDDQ_AB_ASIC1_DESCRIPTORS,
	  .descriptor_count = ARRAY_SIZE(PLDM_VR_PVDDQ_AB_ASIC1_DESCRIPTORS) },
	{ .descriptor = PLDM_VR_PVDDQ_CD_ASIC1_DESCRIPTORS,
	  .descriptor_count = ARRAY_SIZE(PLDM_VR_PVDDQ_CD_ASIC1_DESCRIPTORS) },
	{ .descriptor = PLDM_VR_PVDDQ_AB_ASIC2_DESCRIPTORS,
	  .descriptor_count = ARRAY_SIZE(PLDM_VR_PVDDQ_AB_ASIC2_DESCRIPTORS) },
	{ .descriptor = PLDM_VR_PVDDQ_CD_ASIC2_DESCRIPTORS,
	  .descriptor_count = ARRAY_SIZE(PLDM_VR_PVDDQ_CD_ASIC2_DESCRIPTORS) },
	{ .descriptor = PLDM_CXL1_DESCRIPTORS,
	  .descriptor_count = ARRAY_SIZE(PLDM_CXL1_DESCRIPTORS) },
	{ .descriptor = PLDM_CXL2_DESCRIPTORS,
	  .descriptor_count = ARRAY_SIZE(PLDM_CXL2_DESCRIPTORS) },
};
const uint8_t downstream_devices_count = ARRAY_SIZE(downstream_table);

// detect VR devices attribute and replace model number strings
struct pldm_downstream_identifier_table_and_count get_downstream_identifier_table()
{
	struct pldm_downstream_identifier_table_and_count d = { .downstream_devices_count =
									downstream_devices_count,
								.downstream_table =
									downstream_table };

	enum VR_TYPE {
		VR_TYPE_UNKNOWN,
		VR_TYPE_INF,
		VR_TYPE_MPS,
	};

	uint8_t dev_id = 0;
	enum VR_TYPE vr_type = VR_TYPE_UNKNOWN;
	get_ioe_value(ADDR_IOE3, TCA9555_INPUT_PORT_REG_1, &dev_id);
	if ((dev_id & 0x10) == GPIO_LOW) {
		vr_type = VR_TYPE_INF;
	} else {
		vr_type = VR_TYPE_MPS;
	}

	switch (vr_type) {
	case VR_TYPE_INF:
		replace_model_number_long_string(d.downstream_table, 0,
						 "meta.VR.1.Infienon_XDPE12284C");
		replace_model_number_long_string(d.downstream_table, 1,
						 "meta.VR.2.Infienon_XDPE12284C");
		replace_model_number_long_string(d.downstream_table, 2,
						 "meta.VR.3.Infienon_XDPE12284C");
		replace_model_number_long_string(d.downstream_table, 3,
						 "meta.VR.4.Infienon_XDPE12284C");
		replace_model_number_short_string(d.downstream_table, 0, "1");
		replace_model_number_short_string(d.downstream_table, 1, "1");
		replace_model_number_short_string(d.downstream_table, 2, "1");
		replace_model_number_short_string(d.downstream_table, 3, "1");
		break;
	case VR_TYPE_MPS:
		replace_model_number_long_string(d.downstream_table, 0, "meta.VR.1.MPS_MP2971");
		replace_model_number_long_string(d.downstream_table, 1, "meta.VR.2.MPS_MP2971");
		replace_model_number_long_string(d.downstream_table, 2, "meta.VR.3.MPS_MP2971");
		replace_model_number_long_string(d.downstream_table, 3, "meta.VR.4.MPS_MP2971");
		replace_model_number_short_string(d.downstream_table, 0, "2");
		replace_model_number_short_string(d.downstream_table, 1, "2");
		replace_model_number_short_string(d.downstream_table, 2, "2");
		replace_model_number_short_string(d.downstream_table, 3, "2");
		break;
	default:
		LOG_ERR("Unknown VR device");
	}
	return d;
}