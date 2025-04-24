#include "libutil.h"
#include "pldm_firmware_update.h"
#include "plat_pldm_device_identifier.h"
#include "plat_pldm_sensor.h"
#include "plat_class.h"
#include "sensor.h"

#include <logging/log.h>

LOG_MODULE_REGISTER(plat_dsidentifier);

char *slot_number_string = NULL;

// All of the descriptors with zero filled will be replaced with the real data
struct pldm_descriptor_string PLDM_VR_PVDDCR_CPU1_DESCRIPTORS[] = {
	{
		.descriptor_type = PLDM_FWUP_IANA_ENTERPRISE_ID,
		.title_string = NULL,
		.descriptor_data = "0000A015",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "OpenBMC.CompatibleHardware",
		.descriptor_data =
			"com.meta.Hardware.Yosemite4.SentinelDome.VR.PVDDCR_CPU1.Unknown",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "OpenBMC.Name",
		.descriptor_data = "",
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
		.title_string = "OpenBMC.CompatibleHardware",
		.descriptor_data = "com.meta.Hardware.Yosemite4.SentinelDome.VR.PVDD11_S3.Unknown",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "OpenBMC.Name",
		.descriptor_data = "",
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
		.title_string = "OpenBMC.CompatibleHardware",
		.descriptor_data =
			"com.meta.Hardware.Yosemite4.SentinelDome.VR.PVDDCR_CPU0.Unknown",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "OpenBMC.Name",
		.descriptor_data = "",
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
		.title_string = "OpenBMC.CompatibleHardware",
		.descriptor_data = "com.meta.Hardware.Yosemite4.SentinelDome.Retimer.x16.Unknown",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "OpenBMC.Name",
		.descriptor_data = "",
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
		.title_string = "OpenBMC.CompatibleHardware",
		.descriptor_data = "com.meta.Hardware.Yosemite4.SentinelDome.Retimer.x8.Unknown",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "OpenBMC.Name",
		.descriptor_data = "",
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
		.title_string = "OpenBMC.CompatibleHardware",
		.descriptor_data = "com.meta.Hardware.Yosemite4.SentinelDome.BIOS.AMD_TURIN",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "OpenBMC.Name",
		.descriptor_data = "AMD_TURIN_BIOS",
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

bool replace_vendor_defined_descriptor(struct pldm_downstream_identifier_idx_table *downstream_table,
				       size_t idx, char *title_string, char *descriptor_data)
{
	char **descriptor_data_ptr =
		get_descriptor_data(downstream_table[idx].table.descriptor,
				    downstream_table[idx].table.descriptor_count,
				    PLDM_FWUP_VENDOR_DEFINED, title_string);
	if (descriptor_data_ptr) {
		*descriptor_data_ptr = descriptor_data;
		return true;
	} else {
		LOG_ERR("Failed to get vendor defined descriptor");
		return false;
	}
}

bool replace_compatible_hardware(struct pldm_downstream_identifier_idx_table *downstream_table,
				 size_t idx, char *compatible_hardware)
{
	if (replace_vendor_defined_descriptor(downstream_table, idx, "OpenBMC.CompatibleHardware",
					      compatible_hardware)) {
		return true;
	} else {
		LOG_ERR("Failed to replace compatible hardware");
		return false;
	}
}

bool replace_display_name(struct pldm_downstream_identifier_idx_table *downstream_table, size_t idx,
			  char *compatible_hardware)
{
	if (replace_vendor_defined_descriptor(downstream_table, idx, "OpenBMC.Name",
					      compatible_hardware)) {
		return true;
	} else {
		LOG_ERR("Failed to replace display name");
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
		replace_compatible_hardware(
			d.downstream_table, 3,
			"com.meta.Hardware.Yosemite4.SentinelDome.Retimer.x8.ASTERALAB_PT5081LRS");
		replace_display_name(d.downstream_table, 3, "ASTERALAB_PT5081LRS_Retimer_x8");
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
		replace_compatible_hardware(
			d.downstream_table, 0,
			"com.meta.Hardware.Yosemite4.SentinelDome.VR.PVDDCR_CPU1.MPS_MP285x");
		replace_display_name(d.downstream_table, 0, "MPS_MP285x_VR_PVDDCR_CPU1");
		replace_compatible_hardware(
			d.downstream_table, 1,
			"com.meta.Hardware.Yosemite4.SentinelDome.VR.PVDD11_S3.MPS_MP285x");
		replace_display_name(d.downstream_table, 1, "MPS_MP285x_VR_PVDD11_S3");
		replace_compatible_hardware(
			d.downstream_table, 2,
			"com.meta.Hardware.Yosemite4.SentinelDome.VR.PVDDCR_CPU0.MPS_MP285x");
		replace_display_name(d.downstream_table, 2, "MPS_MP285x_VR_PVDDCR_CPU0");
		break;
	case sensor_dev_raa229621:
		replace_compatible_hardware(
			d.downstream_table, 0,
			"com.meta.Hardware.Yosemite4.SentinelDome.VR.PVDDCR_CPU1.RNS_RAA22962x");
		replace_display_name(d.downstream_table, 0, "RNS_RAA22962x_VR_PVDDCR_CPU1");
		replace_compatible_hardware(
			d.downstream_table, 1,
			"com.meta.Hardware.Yosemite4.SentinelDome.VR.PVDD11_S3.RNS_RAA22962x");
		replace_display_name(d.downstream_table, 1, "RNS_RAA22962x_VR_PVDD11_S3");
		replace_compatible_hardware(
			d.downstream_table, 2,
			"com.meta.Hardware.Yosemite4.SentinelDome.VR.PVDDCR_CPU0.RNS_RAA22962x");
		replace_display_name(d.downstream_table, 2, "RNS_RAA22962x_VR_PVDDCR_CPU0");
		break;
	case sensor_dev_tps53689:
		replace_compatible_hardware(
			d.downstream_table, 0,
			"com.meta.Hardware.Yosemite4.SentinelDome.VR.PVDDCR_CPU1.TI_TPS536x5");
		replace_display_name(d.downstream_table, 0, "TI_TPS536x5_VR_PVDDCR_CPU1");
		replace_compatible_hardware(
			d.downstream_table, 1,
			"com.meta.Hardware.Yosemite4.SentinelDome.VR.PVDD11_S3.TI_TPS536x5");
		replace_display_name(d.downstream_table, 1, "TI_TPS536x5_VR_PVDD11_S3");
		replace_compatible_hardware(
			d.downstream_table, 2,
			"com.meta.Hardware.Yosemite4.SentinelDome.VR.PVDDCR_CPU0.TI_TPS536x5");
		replace_display_name(d.downstream_table, 2, "TI_TPS536x5_VR_PVDDCR_CPU0");
		break;
	default:
		LOG_ERR("Unknown VR device");
	}
	return d;
}