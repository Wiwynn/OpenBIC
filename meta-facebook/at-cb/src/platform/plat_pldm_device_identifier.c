#include "libutil.h"
#include "pldm_firmware_update.h"
#include "plat_pldm_device_identifier.h"

/* PLDM descriptors table */
struct pldm_descriptor_string PLDM_DEVICE_DESCRIPTOR_TABLE[] = {
	{
		.descriptor_type = PLDM_FWUP_IANA_ENTERPRISE_ID,
		.title_string = NULL,
		.descriptor_data = "0000A015",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Platform",
		.descriptor_data = "Artemis",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Board",
		.descriptor_data = "ColterBay",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Stage",
		.descriptor_data = "PVT",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_LONG_STRING,
		.title_string = NULL,
		.descriptor_data =
			"617374313033305f6269630000000000000000000000000000000000000000000000000000000000",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_SHORT_STRING,
		.title_string = NULL,
		.descriptor_data = "31000000000000000000",
	},
};

struct pldm_descriptor_string CPLD_DESCRIPTOR_TABLE[] = {
	{
		.descriptor_type = PLDM_FWUP_IANA_ENTERPRISE_ID,
		.title_string = NULL,
		.descriptor_data = "0000A015",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Platform",
		.descriptor_data = "Artemis",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Board",
		.descriptor_data = "ColterBay",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Stage",
		.descriptor_data = "PVT",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_LONG_STRING,
		.title_string = NULL,
		.descriptor_data =
			"4c434d5830332d34333030435f63706c640000000000000000000000000000000000000000000000",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_SHORT_STRING,
		.title_string = NULL,
		.descriptor_data = "31000000000000000000",
	},
};

struct pldm_descriptor_string VR_XDPE15284_DESCRIPTOR_TABLE[] = {
	{
		.descriptor_type = PLDM_FWUP_IANA_ENTERPRISE_ID,
		.title_string = NULL,
		.descriptor_data = "0000A015",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Platform",
		.descriptor_data = "Artemis",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Board",
		.descriptor_data = "ColterBay",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Stage",
		.descriptor_data = "PVT",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_LONG_STRING,
		.title_string = NULL,
		.descriptor_data =
			"696e66696e6f6e5f7864706531353238340000000000000000000000000000000000000000000000",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_SHORT_STRING,
		.title_string = NULL,
		.descriptor_data = "31000000000000000000",
	},
};

struct pldm_descriptor_string VR_MP2985_DESCRIPTOR_TABLE[] = {
	{
		.descriptor_type = PLDM_FWUP_IANA_ENTERPRISE_ID,
		.title_string = NULL,
		.descriptor_data = "0000A015",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Platform",
		.descriptor_data = "Artemis",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Board",
		.descriptor_data = "ColterBay",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Stage",
		.descriptor_data = "PVT",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_LONG_STRING,
		.title_string = NULL,
		.descriptor_data =
			"6d70735f6d7032393835000000000000000000000000000000000000000000000000000000000000",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_SHORT_STRING,
		.title_string = NULL,
		.descriptor_data = "31000000000000000000",
	},
};

struct pldm_descriptor_string SWITCH_0_DESCRIPTOR_TABLE[] = {
	{
		.descriptor_type = PLDM_FWUP_IANA_ENTERPRISE_ID,
		.title_string = NULL,
		.descriptor_data = "0000A015",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Platform",
		.descriptor_data = "Artemis",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Board",
		.descriptor_data = "ColterBay",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Stage",
		.descriptor_data = "PVT",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_LONG_STRING,
		.title_string = NULL,
		.descriptor_data =
			"62726f6164636f6d5f70657838393030300000000000000000000000000000000000000000000000",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_SHORT_STRING,
		.title_string = NULL,
		.descriptor_data = "31000000000000000000",
	},
};

struct pldm_descriptor_string SWITCH_1_DESCRIPTOR_TABLE[] = {
	{
		.descriptor_type = PLDM_FWUP_IANA_ENTERPRISE_ID,
		.title_string = NULL,
		.descriptor_data = "0000A015",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Platform",
		.descriptor_data = "Artemis",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Board",
		.descriptor_data = "ColterBay",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Stage",
		.descriptor_data = "PVT",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_LONG_STRING,
		.title_string = NULL,
		.descriptor_data =
			"62726f6164636f6d5f70657838393030300000000000000000000000000000000000000000000000",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_SHORT_STRING,
		.title_string = NULL,
		.descriptor_data = "32000000000000000000",
	},
};

struct pldm_descriptor_string ASIC_PSOC_DESCRIPTOR_TABLE[] = {
	{
		.descriptor_type = PLDM_FWUP_IANA_ENTERPRISE_ID,
		.title_string = NULL,
		.descriptor_data = "0000A015",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Platform",
		.descriptor_data = "Artemis",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Board",
		.descriptor_data = "ColterBay",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Stage",
		.descriptor_data = "PVT",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_LONG_STRING,
		.title_string = NULL,
		.descriptor_data =
			"62726f6164636f6d5f61736963000000000000000000000000000000000000000000000000000000",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_SHORT_STRING,
		.title_string = NULL,
		.descriptor_data = "31000000000000000000",
	},
	{
		.descriptor_type = PLDM_PCI_VENDOR_ID,
		.title_string = NULL,
		.descriptor_data = "1D9B",
	},
	{
		.descriptor_type = PLDM_PCI_DEVICE_ID,
		.title_string = NULL,
		.descriptor_data = "0201",
	},
};

struct pldm_descriptor_string ASIC_QSPI_DESCRIPTOR_TABLE[] = {
	{
		.descriptor_type = PLDM_FWUP_IANA_ENTERPRISE_ID,
		.title_string = NULL,
		.descriptor_data = "0000A015",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Platform",
		.descriptor_data = "Artemis",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Board",
		.descriptor_data = "ColterBay",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Stage",
		.descriptor_data = "PVT",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_LONG_STRING,
		.title_string = NULL,
		.descriptor_data =
			"62726f6164636f6d5f61736963000000000000000000000000000000000000000000000000000000",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_SHORT_STRING,
		.title_string = NULL,
		.descriptor_data = "32000000000000000000",
	},
	{
		.descriptor_type = PLDM_PCI_VENDOR_ID,
		.title_string = NULL,
		.descriptor_data = "1D9B",
	},
	{
		.descriptor_type = PLDM_PCI_DEVICE_ID,
		.title_string = NULL,
		.descriptor_data = "0201",
	},
};

struct pldm_descriptor_string ASIC_BOOT1_DESCRIPTOR_TABLE[] = {
	{
		.descriptor_type = PLDM_FWUP_IANA_ENTERPRISE_ID,
		.title_string = NULL,
		.descriptor_data = "0000A015",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Platform",
		.descriptor_data = "Artemis",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Board",
		.descriptor_data = "ColterBay",
	},
	{
		.descriptor_type = PLDM_FWUP_VENDOR_DEFINED,
		.title_string = "Stage",
		.descriptor_data = "PVT",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_LONG_STRING,
		.title_string = NULL,
		.descriptor_data =
			"62726f6164636f6d5f61736963000000000000000000000000000000000000000000000000000000",
	},
	{
		.descriptor_type = PLDM_ASCII_MODEL_NUMBER_SHORT_STRING,
		.title_string = NULL,
		.descriptor_data = "33000000000000000000",
	},
	{
		.descriptor_type = PLDM_PCI_VENDOR_ID,
		.title_string = NULL,
		.descriptor_data = "1D9B",
	},
	{
		.descriptor_type = PLDM_PCI_DEVICE_ID,
		.title_string = NULL,
		.descriptor_data = "0201",
	},
};

const uint8_t bic_descriptors_count = ARRAY_SIZE(PLDM_DEVICE_DESCRIPTOR_TABLE);
const uint8_t cpld_descriptors_count = ARRAY_SIZE(CPLD_DESCRIPTOR_TABLE);
const uint8_t vr_xdpe15284_descriptors_count = ARRAY_SIZE(VR_XDPE15284_DESCRIPTOR_TABLE);
const uint8_t vr_mp2985_descriptors_count = ARRAY_SIZE(VR_MP2985_DESCRIPTOR_TABLE);
const uint8_t sw_0_descriptors_count = ARRAY_SIZE(SWITCH_0_DESCRIPTOR_TABLE);
const uint8_t sw_1_descriptors_count = ARRAY_SIZE(SWITCH_1_DESCRIPTOR_TABLE);
const uint8_t asic_psoc_descriptors_count = ARRAY_SIZE(ASIC_PSOC_DESCRIPTOR_TABLE);
const uint8_t asic_qspi_descriptors_count = ARRAY_SIZE(ASIC_QSPI_DESCRIPTOR_TABLE);
const uint8_t asic_boot1_descriptors_count = ARRAY_SIZE(ASIC_BOOT1_DESCRIPTOR_TABLE);

struct pldm_downstream_identifier_table downstream_table[] = {
	{ .descriptor = CPLD_DESCRIPTOR_TABLE, .descriptor_count = cpld_descriptors_count },
	{ .descriptor = VR_XDPE15284_DESCRIPTOR_TABLE,
	  .descriptor_count = vr_xdpe15284_descriptors_count },
	{ .descriptor = SWITCH_0_DESCRIPTOR_TABLE, .descriptor_count = sw_0_descriptors_count },
	{ .descriptor = SWITCH_1_DESCRIPTOR_TABLE, .descriptor_count = sw_1_descriptors_count },
	{ .descriptor = ASIC_PSOC_DESCRIPTOR_TABLE,
	  .descriptor_count = asic_psoc_descriptors_count },
	{ .descriptor = ASIC_QSPI_DESCRIPTOR_TABLE,
	  .descriptor_count = asic_qspi_descriptors_count },
	{ .descriptor = ASIC_BOOT1_DESCRIPTOR_TABLE,
	  .descriptor_count = asic_boot1_descriptors_count },
};

const uint8_t downstream_table_count = ARRAY_SIZE(downstream_table);
