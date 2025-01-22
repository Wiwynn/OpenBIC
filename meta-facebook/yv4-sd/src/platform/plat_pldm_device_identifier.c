#include <stdlib.h>

#include "libutil.h"
#include "pldm_firmware_update.h"
#include "plat_pldm_device_identifier.h"
#include "plat_pldm_sensor.h"
#include "plat_class.h"
#include "sensor.h"

#include <logging/log.h>

LOG_MODULE_REGISTER(plat_dsidentifier);

// All of the descriptors with zero filled will be replaced with the real data
struct pldm_descriptor_string PLDM_VR_PVDDCR_CPU1_DESCRIPTORS[] = {
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
		.descriptor_data = "SentinelDome",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "ComponentType",
		.descriptor_data = "VR",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "SlotNumber",
		.descriptor_data = NULL,
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "ComponentInstance",
		.descriptor_data = "PVDDCR_CPU1",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_LONG_STRING,
		.title_string = NULL,
		.descriptor_data = NULL,
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_SHORT_STRING,
		.title_string = NULL,
		.descriptor_data = NULL,
	},
};

struct pldm_descriptor_string PLDM_VR_PVDD11_S3_DESCRIPTORS[] = {
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
		.descriptor_data = "SentinelDome",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "ComponentType",
		.descriptor_data = "VR",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "ComponentInstance",
		.descriptor_data = "PVDD11_S3",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "SlotNumber",
		.descriptor_data = NULL,
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_LONG_STRING,
		.title_string = NULL,
		.descriptor_data = NULL,
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_SHORT_STRING,
		.title_string = NULL,
		.descriptor_data = NULL,
	},
};

struct pldm_descriptor_string PLDM_VR_PVDDCR_CPU0_DESCRIPTORS[] = {
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
		.descriptor_data = "SentinelDome",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "ComponentType",
		.descriptor_data = "VR",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "ComponentInstance",
		.descriptor_data = "PVDDCR_CPU0",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "SlotNumber",
		.descriptor_data = NULL,
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_LONG_STRING,
		.title_string = NULL,
		.descriptor_data = NULL,
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_SHORT_STRING,
		.title_string = NULL,
		.descriptor_data = NULL,
	},
};

struct pldm_descriptor_string PLDM_RETIMER_X16_DESCRIPTORS[] = {
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
		.descriptor_data = "SentinelDome",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "ComponentType",
		.descriptor_data = "Retimer",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "SlotNumber",
		.descriptor_data = NULL,
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_LONG_STRING,
		.title_string = NULL,
		.descriptor_data = NULL,
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_SHORT_STRING,
		.title_string = NULL,
		.descriptor_data = NULL,
	},
};

struct pldm_descriptor_string PLDM_RETIMER_X8_DESCRIPTORS[] = {
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
		.descriptor_data = "SentinelDome",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "ComponentType",
		.descriptor_data = "Retimer",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "SlotNumber",
		.descriptor_data = NULL,
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_LONG_STRING,
		.title_string = NULL,
		.descriptor_data = NULL,
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_SHORT_STRING,
		.title_string = NULL,
		.descriptor_data = NULL,
	},
};

struct pldm_descriptor_string PLDM_BIOS_DESCRIPTORS[] = {
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
		.descriptor_data = "SentinelDome",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "ComponentType",
		.descriptor_data = "BIOS",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "SlotNumber",
		.descriptor_data = NULL,
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_LONG_STRING,
		.title_string = NULL,
		.descriptor_data =
			// "com.meta.BIOS.AMD_TURIN"
		"636F6D2E6D6574612E42494F532E414D445F545552494E0000000000000000000000000000000000",
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
bool replace_model_number_long_string(struct pldm_downstream_identifier_idx_table *downstream_table,
				      size_t idx, char *model_number)
{
	char **descriptor_data = get_descriptor_data(downstream_table[idx].table.descriptor,
						     downstream_table[idx].table.descriptor_count,
						     PLDM_ASCII_MODEL_NUMBER_LONG_STRING, NULL);
	if (descriptor_data) {
		if (*descriptor_data) {
			free(*descriptor_data);
		}
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
bool replace_model_number_short_string(struct pldm_downstream_identifier_idx_table *downstream_table,
				       size_t idx, char *model_number)
{
	char **descriptor_data = get_descriptor_data(downstream_table[idx].table.descriptor,
						     downstream_table[idx].table.descriptor_count,
						     PLDM_ASCII_MODEL_NUMBER_SHORT_STRING, NULL);
	if (descriptor_data) {
		if (*descriptor_data) {
			free(*descriptor_data);
		}
		char *buf = malloc(PLDM_ASCII_MODEL_NUMBER_SHORT_STRING_LENGTH * 2 + 1);
		string_to_ascii(model_number, buf, PLDM_ASCII_MODEL_NUMBER_SHORT_STRING_LENGTH);
		*descriptor_data = buf;
		return true;
	} else {
		LOG_ERR("Failed to get model number short string");
		return false;
	}
}

bool replace_slot_number(struct pldm_downstream_identifier_idx_table *downstream_table, size_t idx,
			 uint8_t slot_number)
{
	char **descriptor_data = get_descriptor_data(downstream_table[idx].table.descriptor,
						     downstream_table[idx].table.descriptor_count,
						     PLDM_FWUP_VENDOR_DEFINED, "SlotNumber");
	if (descriptor_data) {
		if (*descriptor_data) {
			free(*descriptor_data);
		}
		char *buf = malloc(2);
		buf[0] = (char)(slot_number + '0');
		buf[1] = '\0';
		*descriptor_data = buf;
		return true;
	} else {
		LOG_ERR("Failed to get slot number descriptor");
		return false;
	}
}

struct pldm_downstream_identifier_idx_table downstream_table_with_retimer[] = {
	{ 1,
	  { .descriptor = PLDM_VR_PVDDCR_CPU1_DESCRIPTORS,
	    .descriptor_count = ARRAY_SIZE(PLDM_VR_PVDDCR_CPU1_DESCRIPTORS) } },
	{ 2,
	  { .descriptor = PLDM_VR_PVDD11_S3_DESCRIPTORS,
	    .descriptor_count = ARRAY_SIZE(PLDM_VR_PVDD11_S3_DESCRIPTORS) } },
	{ 3,
	  { .descriptor = PLDM_VR_PVDDCR_CPU0_DESCRIPTORS,
	    .descriptor_count = ARRAY_SIZE(PLDM_VR_PVDDCR_CPU0_DESCRIPTORS) } },
	{ 5,
	  { .descriptor = PLDM_RETIMER_X8_DESCRIPTORS,
	    .descriptor_count = ARRAY_SIZE(PLDM_RETIMER_X8_DESCRIPTORS) } },
	{ 6,
	  { .descriptor = PLDM_BIOS_DESCRIPTORS,
	    .descriptor_count = ARRAY_SIZE(PLDM_BIOS_DESCRIPTORS) } },
};
const uint8_t downstream_devices_with_retimer_count = ARRAY_SIZE(downstream_table_with_retimer);

struct pldm_downstream_identifier_idx_table downstream_table_without_retimer[] = {
	{ 1,
	  { .descriptor = PLDM_VR_PVDDCR_CPU1_DESCRIPTORS,
	    .descriptor_count = ARRAY_SIZE(PLDM_VR_PVDDCR_CPU1_DESCRIPTORS) } },
	{ 2,
	  { .descriptor = PLDM_VR_PVDD11_S3_DESCRIPTORS,
	    .descriptor_count = ARRAY_SIZE(PLDM_VR_PVDD11_S3_DESCRIPTORS) } },
	{ 3,
	  { .descriptor = PLDM_VR_PVDDCR_CPU0_DESCRIPTORS,
	    .descriptor_count = ARRAY_SIZE(PLDM_VR_PVDDCR_CPU0_DESCRIPTORS) } },
	{ 6,
	  { .descriptor = PLDM_BIOS_DESCRIPTORS,
	    .descriptor_count = ARRAY_SIZE(PLDM_BIOS_DESCRIPTORS) } },
};
const uint8_t downstream_devices_without_retimer_count =
	ARRAY_SIZE(downstream_table_without_retimer);

// detect VR and retimer devices attribute and replace model number strings
struct pldm_downstream_identifier_table_and_count get_downstream_identifier_table()
{
	struct pldm_downstream_identifier_table_and_count d = { .downstream_devices_count = 0,
								.downstream_table = NULL };
	bool has_retimers = (get_retimer_type() != RETIMER_TYPE_NO_RETIMER);
	if (has_retimers) {
		d.downstream_table = downstream_table_with_retimer;
		d.downstream_devices_count = downstream_devices_with_retimer_count;
		// up to now, asteralab PT5161LRS and PT5081LRS are the only retimers
		replace_model_number_long_string(d.downstream_table, 4,
						 "com.meta.Retimer.ASTERALAB_PT5081LRS");
		replace_model_number_short_string(d.downstream_table, 4, "1");
	} else {
		d.downstream_table = downstream_table_without_retimer;
		d.downstream_devices_count = downstream_devices_without_retimer_count;
	}

	uint8_t vr_dev = VR_DEVICE_UNKNOWN;
	if (plat_pldm_sensor_get_vr_dev(&vr_dev) != 0) {
		LOG_ERR("Failed to get VR device");
		return d;
	}
	switch (vr_dev) {
	case sensor_dev_mp2856gut:
		replace_model_number_long_string(d.downstream_table, 0, "com.meta.VR.1.MPS_MP285x");
		replace_model_number_long_string(d.downstream_table, 1, "com.meta.VR.2.MPS_MP285x");
		replace_model_number_long_string(d.downstream_table, 2, "com.meta.VR.3.MPS_MP285x");
		replace_model_number_short_string(d.downstream_table, 0, "1");
		replace_model_number_short_string(d.downstream_table, 1, "1");
		replace_model_number_short_string(d.downstream_table, 2, "1");
		break;
	case sensor_dev_raa229621:
		replace_model_number_long_string(d.downstream_table, 0,
						 "com.meta.VR.1.RNS_RAA22962x");
		replace_model_number_long_string(d.downstream_table, 1,
						 "com.meta.VR.2.RNS_RAA22962x");
		replace_model_number_long_string(d.downstream_table, 2,
						 "com.meta.VR.3.RNS_RAA22962x");
		replace_model_number_short_string(d.downstream_table, 0, "2");
		replace_model_number_short_string(d.downstream_table, 1, "2");
		replace_model_number_short_string(d.downstream_table, 2, "2");
		break;
	case sensor_dev_tps53689:
		replace_model_number_long_string(d.downstream_table, 0,
						 "com.meta.VR.1.TI_TPS536x5");
		replace_model_number_long_string(d.downstream_table, 1,
						 "com.meta.VR.2.TI_TPS536x5");
		replace_model_number_long_string(d.downstream_table, 2,
						 "com.meta.VR.3.TI_TPS536x5");
		replace_model_number_short_string(d.downstream_table, 0, "3");
		replace_model_number_short_string(d.downstream_table, 1, "3");
		replace_model_number_short_string(d.downstream_table, 2, "3");
		break;
	default:
		replace_model_number_long_string(d.downstream_table, 0, "");
		replace_model_number_long_string(d.downstream_table, 1, "");
		replace_model_number_long_string(d.downstream_table, 2, "");
		replace_model_number_short_string(d.downstream_table, 0, "");
		replace_model_number_short_string(d.downstream_table, 1, "");
		replace_model_number_short_string(d.downstream_table, 2, "");
		LOG_ERR("Unknown VR device");
	}
	// replace slot number with real slot number
	// assuming the slot number is eid / 10
	uint8_t slot_number = plat_get_eid() / 10;
	for (size_t i = 0; i < d.downstream_devices_count; i++) {
		replace_slot_number(d.downstream_table, i, slot_number);
	}
	return d;
}