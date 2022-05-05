#include "plat_class.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hal_gpio.h"
#include "hal_i2c.h"
#include "libutil.h"
#include "plat_gpio.h"
#include "plat_i2c.h"

#define CPLD_ADDR 0x21 // 7-bit address
#define CPLD_CLASS_TYPE_REG 0x05
#define CPLD_2OU_EXPANSION_CARD_REG 0x06
#define CPLD_BOARD_REV_ID_REG 0x08
#define CPLD_1OU_CARD_DETECTION 0x09
#define I2C_DATA_SIZE 5
#define ADC_CHANNEL_NUMBER 16

static uint8_t system_class = SYS_CLASS_1;
static bool is_1ou_present = false;
static bool is_2ou_present = false;
static uint8_t __attribute__((unused)) card_type_1ou = 0;
static uint8_t card_type_2ou = TYPE_UNKNOWN;
static uint8_t board_revision = 0x0F;

uint8_t get_system_class()
{
	return system_class;
}

bool get_1ou_status()
{
	return is_1ou_present;
}

bool get_2ou_status()
{
	return is_2ou_present;
}

uint8_t get_board_revision()
{
	return board_revision;
}

uint8_t get_2ou_cardtype()
{
	return card_type_2ou;
}

enum _1OU_CARD_TYPE_ {
	SI_TEST_CARD = 0x00,
};

/* ADC information for each channel
 * offset: register offset
 * shift: the offset of ADC data
 */
struct ADC_INFO {
	long unsigned int offset;
	int shift;
};

struct ADC_INFO adc_info[ADC_CHANNEL_NUMBER] = {
	{ 0x10, 0 },  { 0x10, 16 },  { 0x14, 0 },  { 0x14, 16 },  { 0x18, 0 },	{ 0x18, 16 },
	{ 0x1C, 0 },  { 0x1C, 16 },  { 0x110, 0 }, { 0x110, 16 }, { 0x114, 0 }, { 0x114, 16 },
	{ 0x118, 0 }, { 0x118, 16 }, { 0x11C, 0 }, { 0x11C, 16 }
};

bool get_adc_voltage(int channel, float *voltage)
{
	if (!voltage) {
		return false;
	}

	if (channel >= ADC_CHANNEL_NUMBER) {
		printf("Invalid ADC channel-%d\n", channel);
		return false;
	}

	uint32_t adc_base_address = 0x7e6e9000, raw_value, reg_value;
	long unsigned int engine_control = 0x0;
	float reference_voltage = 0.0f;
	uint8_t reference_voltage_selection;

	/* Get ADC reference voltage from Aspeed chip
	 * ADC000: Engine Control
	 * [7:6] Reference Voltage Selection
	 * 00b - 2.5V / 01b - 1.2V / 10b and 11b - External Voltage
	 */
	reg_value = sys_read32(adc_base_address + engine_control);
	reference_voltage_selection = (reg_value >> 6) & 0x3;
	if (reference_voltage_selection == 0b00) {
		reference_voltage = 2.5;
	} else if (reference_voltage_selection == 0b01) {
		reference_voltage = 1.2;
	} else {
		printf("Unsupported the external reference voltage\n");
		return false;
	}

	// Read ADC raw value
	reg_value = sys_read32(adc_base_address + adc_info[channel].offset);
	raw_value = (reg_value >> adc_info[channel].shift) & 0x3FF; // 10-bit(0x3FF) resolution

	// Real voltage = raw data * reference voltage / 2 ^ resolution(10)
	*voltage = (raw_value * reference_voltage) / 1024;

	return true;
}

void init_platform_config()
{
	I2C_MSG i2c_msg;
	uint8_t retry = 3;

	/* According hardware design, BIC can check the class type through GPIOs.
	 * The board ID is "0000" if the class type is class1.
	 * The board ID is "0001" if the class type is calss2.
	 */
	if (gpio_get(BOARD_ID0) == GPIO_HIGH) {
		system_class = SYS_CLASS_2;
	} else {
		system_class = SYS_CLASS_1;
	}

	uint8_t tx_len, rx_len;
	uint8_t class_type = 0x0;
	char *data = (uint8_t *)malloc(I2C_DATA_SIZE * sizeof(uint8_t));
	/* Read the expansion present from CPLD's class type register
	 * CPLD Class Type Register(05h)
	 * Bit[7:4] - Board ID(0000b: Class-1, 0001b: Class-2)
	 * Bit[3] - 2ou x8/x16 Riser Expansion Present
	 * Bit[2] - 1ou Expansion Present Pin
	 * Bit[1:0] - Reserved
	 */
	tx_len = 1;
	rx_len = 1;
	memset(data, 0, I2C_DATA_SIZE);
	data[0] = CPLD_CLASS_TYPE_REG;
	i2c_msg = construct_i2c_message(I2C_BUS1, CPLD_ADDR, tx_len, data, rx_len);
	if (!i2c_master_read(&i2c_msg, retry)) {
		class_type = i2c_msg.data[0];
		is_1ou_present = (class_type & 0x4 ? false : true);
		is_2ou_present = (class_type & 0x8 ? false : true);
	} else {
		printf("Failed to read expansion present from CPLD\n");
	}
	/* Set the class type to CPLD's class type register(the bit[4] of offset 05h) */
	tx_len = 2;
	rx_len = 0;
	memset(data, 0, I2C_DATA_SIZE);
	data[0] = CPLD_CLASS_TYPE_REG;
	data[1] = (((system_class - 1) << 4) & 0x10) | class_type;
	i2c_msg = construct_i2c_message(I2C_BUS1, CPLD_ADDR, tx_len, data, rx_len);
	if (i2c_master_write(&i2c_msg, retry)) {
		printf("Failed to set class type to CPLD)\n");
	}

	/* Get the board revision to CPLD's board rev id reg(the bit[3:0] of offset 08h)
	 * CPLD Board REV ID Register(08h)
	 * Bit[7:4] - Reserved
	 * Bit[3:0] - Board revision
	 */
	tx_len = 1;
	rx_len = 1;
	memset(data, 0, I2C_DATA_SIZE);
	data[0] = CPLD_BOARD_REV_ID_REG;
	i2c_msg = construct_i2c_message(I2C_BUS1, CPLD_ADDR, tx_len, data, rx_len);
	int ret = i2c_master_read(&i2c_msg, retry);
	if (ret == 0) {
		board_revision = i2c_msg.data[0] & 0xF;
	} else {
		printf("Failed to read board ID from CPLD\n");
	}
	printk("BIC class type(class-%d), 1ou present status(%d), 2ou present status(%d), board revision(0x%x)\n",
	       system_class, (int)is_1ou_present, (int)is_2ou_present, board_revision);

	/* BIC judges the 1OU card type according the ADC-6(0-based) voltage.
	 * The 1OU card type is SI test card if the voltage is lower than 0.3V.
	 * And then, BIC sets the type to CL CPLD register(slave address 21h, register 09h)
	 * CPLD register 09h - 1OU Card Detection
	 * - 00h: 1OU SI test card
	 */
	if (is_1ou_present) {
		float voltage;
		bool success = get_adc_voltage(6, &voltage);
		if (success) {
			if (voltage < 0.3) {
				tx_len = 2;
				rx_len = 0;
				memset(data, 0, I2C_DATA_SIZE);
				data[0] = CPLD_1OU_CARD_DETECTION;
				data[1] = SI_TEST_CARD;
				i2c_msg = construct_i2c_message(I2C_BUS1, CPLD_ADDR, tx_len, data,
								rx_len);
				if (i2c_master_write(&i2c_msg, retry)) {
					printf("Failed to set 1OU card detection to CPLD register(0x%x)\n",
					       data[0]);
				}
			} else {
				printf("Unknown the 1OU card type, the voltage of ADC channel-6 is %fV\n",
				       voltage);
			}
		}
	}

	if (is_2ou_present) {
		tx_len = 1;
		rx_len = 1;
		memset(data, 0, I2C_DATA_SIZE);
		data[0] = CPLD_2OU_EXPANSION_CARD_REG;
		i2c_msg = construct_i2c_message(I2C_BUS1, CPLD_ADDR, tx_len, data, rx_len);
		if (!i2c_master_read(&i2c_msg, retry)) {
			switch (i2c_msg.data[0]) {
			case TYPE_2OU_DPV2:
				card_type_2ou = TYPE_2OU_DPV2;
				break;
			case TYPE_2OU_SPE:
				card_type_2ou = TYPE_2OU_SPE;
				break;
			case TYPE_2OU_EXP:
				card_type_2ou = TYPE_2OU_EXP;
				break;
			case TYPE_2OU_DPV2_8:
				card_type_2ou = TYPE_2OU_DPV2_8;
				break;
			case TYPE_2OU_DPV2_16:
				card_type_2ou = TYPE_2OU_DPV2_16;
				break;
			default:
				card_type_2ou = TYPE_UNKNOWN;
				break;
			}
		}
	}
	SAFE_FREE(data);
}
