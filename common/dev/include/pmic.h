#ifndef PMIC_H
#define PMIC_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

//Memory write read request max data len
#define MAX_MEMORY_DATA 31

//PMIC write/read data len
#define PMIC_WRITE_DATA_LEN 14
#define PMIC_READ_DATA_LEN 12

//PMIC write/read memory command
#define CMD_SMBUS_READ_MEMORY 0x47
#define CMD_SMBUS_WRITE_MEMORY 0x48

//PMIC report power/total mode setting
#define WRITE_DEV_REPROT_POWER 0x45
#define WRITE_DEV_REPROT_TOTAL 0xC2

//PMIC total/power/ADC/record register address value
#define PMIC_TOTAL_INDIV_ADDR_VAL 0x0000001A
#define PMIC_PWR_CURR_ADDR_VAL 0x0000001B
#define PMIC_ADC_ADDR_VAL 0x00000030
#define PMIC_SWA_ADDR_VAL 0x0000000C

//PMIC enable ADC bit
#define PMIC_ENABLE_ADC_BIT BIT(7)

//PMIC PMIC setting delay msec
#define ME_COLD_RESET_DELAY_MSEC 1000
#define PMIC_COMMAND_DELAY_MSEC 250

typedef struct _memory_write_read_req_ {
	uint32_t intel_id;
	uint8_t smbus_identifier;
	uint8_t smbus_address;
	uint8_t addr_size;
	uint8_t data_len;
	uint32_t addr_value;
	uint8_t write_data[MAX_MEMORY_DATA];
} memory_write_read_req;

extern void init_memory_req(memory_write_read_req *origin_req);
extern void write_memory_req(memory_write_read_req *write_req, uint8_t smbus_identifier,
			     uint8_t smbus_address, uint32_t addr_value, uint8_t *write_data,
			     uint8_t write_len);

#endif
