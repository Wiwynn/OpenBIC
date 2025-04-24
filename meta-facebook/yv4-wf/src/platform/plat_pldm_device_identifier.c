#include "libutil.h"
#include "pldm_firmware_update.h"
#include "plat_pldm_device_identifier.h"
#include "plat_isr.h"
#include "ioexp_tca9555.h"
#include "hal_gpio.h"
#include "plat_gpio.h"

#include <logging/log.h>

LOG_MODULE_REGISTER(plat_dsidentifier);

char *slot_number_string = NULL;

// All of the descriptors with zero filled will be replaced with the real data
struct pldm_descriptor_string PLDM_VR_PVDDQ_AB_ASIC1_DESCRIPTORS[] = {
	{
		.descriptor_type = PLDM_FWUP_IANA_ENTERPRISE_ID,
		.title_string = NULL,
		.descriptor_data = "0000A015",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "OpenBMC.CompatibleHardware",
		.descriptor_data =
			"com.meta.Hardware.Yosemite4.WailuaFalls.VR.PVDDQ_AB_ASIC1.Unknown",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "OpenBMC.Name",
		.descriptor_data = "",
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
		.title_string = "OpenBMC.CompatibleHardware",
		.descriptor_data =
			"com.meta.Hardware.Yosemite4.WailuaFalls.VR.PVDDQ_CD_ASIC1.Unknown",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "OpenBMC.Name",
		.descriptor_data = "",
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
		.title_string = "OpenBMC.CompatibleHardware",
		.descriptor_data =
			"com.meta.Hardware.Yosemite4.WailuaFalls.VR.PVDDQ_AB_ASIC2.Unknown",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "OpenBMC.Name",
		.descriptor_data = "",
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
		.title_string = "OpenBMC.CompatibleHardware",
		.descriptor_data =
			"com.meta.Hardware.Yosemite4.WailuaFalls.VR.PVDDQ_CD_ASIC2.Unknown",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "OpenBMC.Name",
		.descriptor_data = "",
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
		.title_string = "OpenBMC.CompatibleHardware",
		.descriptor_data = "com.meta.Hardware.Yosemite4.WailuaFalls.CXL.Vistara_2TV6",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "OpenBMC.Name",
		.descriptor_data = "Vistara_2TV6_CXL1",
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
		.title_string = "OpenBMC.CompatibleHardware",
		.descriptor_data = "com.meta.Hardware.Yosemite4.WailuaFalls.CXL.Vistara_2TV6",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "OpenBMC.Name",
		.descriptor_data = "Vistara_2TV6_CXL2",
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

bool replace_vendor_defined_descriptor(struct pldm_downstream_identifier_table *downstream_table,
				       size_t idx, char *title_string, char *descriptor_data)
{
	char **descriptor_data_ptr = get_descriptor_data(downstream_table[idx].descriptor,
							 downstream_table[idx].descriptor_count,
							 PLDM_FWUP_VENDOR_DEFINED, title_string);
	if (descriptor_data_ptr) {
		*descriptor_data_ptr = descriptor_data;
		return true;
	} else {
		LOG_ERR("Failed to get vendor defined descriptor");
		return false;
	}
}

bool replace_compatible_hardware(struct pldm_downstream_identifier_table *downstream_table,
				 size_t idx, char *compatible_hardware)
{
	if (replace_vendor_defined_descriptor(downstream_table, idx, "CompatibleHardware",
					      compatible_hardware)) {
		return true;
	} else {
		LOG_ERR("Failed to replace compatible hardware");
		return false;
	}
}

bool replace_display_name(struct pldm_downstream_identifier_table *downstream_table, size_t idx,
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
		replace_compatible_hardware(
			d.downstream_table, 0,
			"com.meta.Hardware.Yosemite4.WailuaFalls.VR.PVDDQ_AB_ASIC1.INF_XDPE12284C");
		replace_display_name(d.downstream_table, 0, "INF_XDPE12284C_VR_PVDDQ_AB_ASIC1");
		replace_compatible_hardware(
			d.downstream_table, 1,
			"com.meta.Hardware.Yosemite4.WailuaFalls.VR.PVDDQ_CD_ASIC1.INF_XDPE12284C");
		replace_display_name(d.downstream_table, 1, "INF_XDPE12284C_VR_PVDDQ_CD_ASIC1");
		replace_compatible_hardware(
			d.downstream_table, 2,
			"com.meta.Hardware.Yosemite4.WailuaFalls.VR.PVDDQ_AB_ASIC2.INF_XDPE12284C");
		replace_display_name(d.downstream_table, 2, "INF_XDPE12284C_VR_PVDDQ_AB_ASIC2");
		replace_compatible_hardware(
			d.downstream_table, 3,
			"com.meta.Hardware.Yosemite4.WailuaFalls.VR.PVDDQ_CD_ASIC2.INF_XDPE12284C");
		replace_display_name(d.downstream_table, 3, "INF_XDPE12284C_VR_PVDDQ_CD_ASIC2");
		break;
	case VR_TYPE_MPS:
		replace_compatible_hardware(
			d.downstream_table, 0,
			"com.meta.Hardware.Yosemite4.WailuaFalls.VR.PVDDQ_AB_ASIC1.MPS_MP2971");
		replace_display_name(d.downstream_table, 0, "MPS_MP2971_VR_PVDDQ_AB_ASIC1");
		replace_compatible_hardware(
			d.downstream_table, 1,
			"com.meta.Hardware.Yosemite4.WailuaFalls.VR.PVDDQ_CD_ASIC1.MPS_MP2971");
		replace_display_name(d.downstream_table, 1, "MPS_MP2971_VR_PVDDQ_CD_ASIC1");
		replace_compatible_hardware(
			d.downstream_table, 2,
			"com.meta.Hardware.Yosemite4.WailuaFalls.VR.PVDDQ_AB_ASIC2.MPS_MP2971");
		replace_display_name(d.downstream_table, 2, "MPS_MP2971_VR_PVDDQ_AB_ASIC2");
		replace_compatible_hardware(
			d.downstream_table, 3,
			"com.meta.Hardware.Yosemite4.WailuaFalls.VR.PVDDQ_CD_ASIC2.MPS_MP2971");
		replace_display_name(d.downstream_table, 3, "MPS_MP2971_VR_PVDDQ_CD_ASIC2");
		break;
	default:
		LOG_ERR("Unknown VR device");
	}
	return d;
}