#ifndef PLAT_SENSOR_TABLE_H
#define PLAT_SENSOR_TABLE_H

#include <stdint.h>
/* define configuration for sensors */
#define NIC_TEMP_OFFSET 0x01
#define TMP75_TEMP_OFFSET 0x00
#define NIC_ADDR (0x3E >> 1)
#define NIC_0_POWER_MONITOR_ADDR (0x80 >> 1)
#define NIC_1_POWER_MONITOR_ADDR (0x82 >> 1)
#define NIC_2_POWER_MONITOR_ADDR (0x84 >> 1)
#define NIC_3_POWER_MONITOR_ADDR (0x86 >> 1)
#define NIC_4_POWER_MONITOR_ADDR (0x88 >> 1)
#define NIC_5_POWER_MONITOR_ADDR (0x8A >> 1)
#define NIC_6_POWER_MONITOR_ADDR (0x8C >> 1)
#define NIC_7_POWER_MONITOR_ADDR (0x8E >> 1)

#define HSC_MP5990_ADDR (0x40 >> 1)

#define PEX_0_1_P0V8_VR_ADDR (0xC0 >> 1)
#define PEX_2_3_P0V8_VR_ADDR (0xC4 >> 1)

#define PEX_0_P1V25_POWER_MONITOR_ADDR (0x80 >> 1)
#define PEX_1_P1V25_POWER_MONITOR_ADDR (0x82 >> 1)
#define PEX_2_P1V25_POWER_MONITOR_ADDR (0x88 >> 1)
#define PEX_3_P1V25_POWER_MONITOR_ADDR (0x8A >> 1)
#define PEX_P1V8_POWER_MONITOR_ADDR (0x98 >> 1)

#define PEX_SWITCH_I2C_ADDR (0xD8 >> 1)
#define PEX_MAX_NUMBER 4

#define SYSTEM_INLET_TEMP_ADDR (0x90 >> 1)
#define SYSTEM_OUTLET_TEMP_L1_ADDR (0x90 >> 1)
#define SYSTEM_OUTLET_TEMP_L2_ADDR (0x94 >> 1)
#define SYSTEM_OUTLET_TEMP_R1_ADDR (0x98 >> 1)
#define SYSTEM_OUTLET_TEMP_R2_ADDR (0x9C >> 1)

#define SSD_COMMON_ADDR (0xD4 >> 1)
#define SSD_OFFSET 0x00
#define SSD_0_POWER_MONITOR_ADDR (0x80 >> 1)
#define SSD_1_POWER_MONITOR_ADDR (0x82 >> 1)
#define SSD_2_POWER_MONITOR_ADDR (0x84 >> 1)
#define SSD_3_POWER_MONITOR_ADDR (0x86 >> 1)
#define SSD_4_POWER_MONITOR_ADDR (0x88 >> 1)
#define SSD_5_POWER_MONITOR_ADDR (0x8A >> 1)
#define SSD_6_POWER_MONITOR_ADDR (0x8C >> 1)
#define SSD_7_POWER_MONITOR_ADDR (0x8E >> 1)
#define SSD_8_POWER_MONITOR_ADDR (0x90 >> 1)
#define SSD_9_POWER_MONITOR_ADDR (0x92 >> 1)
#define SSD_10_POWER_MONITOR_ADDR (0x94 >> 1)
#define SSD_11_POWER_MONITOR_ADDR (0x96 >> 1)
#define SSD_12_POWER_MONITOR_ADDR (0x98 >> 1)
#define SSD_13_POWER_MONITOR_ADDR (0x9A >> 1)
#define SSD_14_POWER_MONITOR_ADDR (0x9C >> 1)
#define SSD_15_POWER_MONITOR_ADDR (0x9E >> 1)

/*  threshold sensor number, 1 based  */
#define SENSOR_NUM_TEMP_NIC_0 0x01
#define SENSOR_NUM_VOLT_NIC_0 0x02
#define SENSOR_NUM_IOUT_NIC_0 0x03
#define SENSOR_NUM_POUT_NIC_0 0x04

#define SENSOR_NUM_TEMP_NIC_1 0x05
#define SENSOR_NUM_VOLT_NIC_1 0x06
#define SENSOR_NUM_IOUT_NIC_1 0x07
#define SENSOR_NUM_POUT_NIC_1 0x08

#define SENSOR_NUM_TEMP_NIC_2 0x0A
#define SENSOR_NUM_VOLT_NIC_2 0x0B
#define SENSOR_NUM_IOUT_NIC_2 0x0C
#define SENSOR_NUM_POUT_NIC_2 0x0D

#define SENSOR_NUM_TEMP_NIC_3 0x11
#define SENSOR_NUM_VOLT_NIC_3 0x12
#define SENSOR_NUM_IOUT_NIC_3 0x13
#define SENSOR_NUM_POUT_NIC_3 0x14

#define SENSOR_NUM_TEMP_NIC_4 0x15
#define SENSOR_NUM_VOLT_NIC_4 0x16
#define SENSOR_NUM_IOUT_NIC_4 0x17
#define SENSOR_NUM_POUT_NIC_4 0x18

#define SENSOR_NUM_TEMP_NIC_5 0x1A
#define SENSOR_NUM_VOLT_NIC_5 0x1B
#define SENSOR_NUM_IOUT_NIC_5 0x1C
#define SENSOR_NUM_POUT_NIC_5 0x1D

#define SENSOR_NUM_TEMP_NIC_6 0x21
#define SENSOR_NUM_VOLT_NIC_6 0x22
#define SENSOR_NUM_IOUT_NIC_6 0x23
#define SENSOR_NUM_POUT_NIC_6 0x24

#define SENSOR_NUM_TEMP_NIC_7 0x25
#define SENSOR_NUM_VOLT_NIC_7 0x26
#define SENSOR_NUM_IOUT_NIC_7 0x27
#define SENSOR_NUM_POUT_NIC_7 0x28

#define SENSOR_NUM_TEMP_PDB_HSC 0x2A
#define SENSOR_NUM_VOUT_PDB_HSC 0x2B
#define SENSOR_NUM_IOUT_PDB_HSC 0x2C
#define SENSOR_NUM_POUT_PDB_HSC 0x2D

#define SENSOR_NUM_BB_P12V_AUX 0x30
#define SENSOR_NUM_BB_P5V_AUX 0x31
#define SENSOR_NUM_BB_P3V3_AUX 0x32
#define SENSOR_NUM_BB_P1V2_AUX 0x33
#define SENSOR_NUM_BB_P3V3 0x34
#define SENSOR_NUM_BB_P1V8_PEX0 0x35
#define SENSOR_NUM_BB_P1V8_PEX1 0x36
#define SENSOR_NUM_BB_P1V8_PEX2 0x37
#define SENSOR_NUM_BB_P1V8_PEX3 0x38

#define SENSOR_NUM_TEMP_PEX_0 0x40
#define SENSOR_NUM_P0V8_VOLT_PEX_0 0x41
#define SENSOR_NUM_P0V8_IOUT_PEX_0 0x42
#define SENSOR_NUM_P0V8_POUT_PEX_0 0x43
#define SENSOR_NUM_P1V25_VOLT_PEX_0 0x44
#define SENSOR_NUM_P1V25_IOUT_PEX_0 0x45
#define SENSOR_NUM_P1V25_POUT_PEX_0 0x46

#define SENSOR_NUM_TEMP_PEX_1 0x47
#define SENSOR_NUM_P0V8_VOLT_PEX_1 0x48
#define SENSOR_NUM_P0V8_IOUT_PEX_1 0x49
#define SENSOR_NUM_P0V8_POUT_PEX_1 0x4A
#define SENSOR_NUM_P1V25_VOLT_PEX_1 0x4B
#define SENSOR_NUM_P1V25_IOUT_PEX_1 0x4C
#define SENSOR_NUM_P1V25_POUT_PEX_1 0x4D

#define SENSOR_NUM_TEMP_PEX_2 0x50
#define SENSOR_NUM_P0V8_VOLT_PEX_2 0x51
#define SENSOR_NUM_P0V8_IOUT_PEX_2 0x52
#define SENSOR_NUM_P0V8_POUT_PEX_2 0x53
#define SENSOR_NUM_P1V25_VOLT_PEX_2 0x54
#define SENSOR_NUM_P1V25_IOUT_PEX_2 0x55
#define SENSOR_NUM_P1V25_POUT_PEX_2 0x56

#define SENSOR_NUM_TEMP_PEX_3 0x57
#define SENSOR_NUM_P0V8_VOLT_PEX_3 0x58
#define SENSOR_NUM_P0V8_IOUT_PEX_3 0x59
#define SENSOR_NUM_P0V8_POUT_PEX_3 0x5A
#define SENSOR_NUM_P1V25_VOLT_PEX_3 0x5B
#define SENSOR_NUM_P1V25_IOUT_PEX_3 0x5C
#define SENSOR_NUM_P1V25_POUT_PEX_3 0x5D

#define SENSOR_NUM_P1V8_VOLT_PEX 0x60
#define SENSOR_NUM_P1V8_IOUT_PEX 0x61
#define SENSOR_NUM_P1V8_POUT_PEX 0x62

#define SENSOR_NUM_BB_TEMP_PEX_0 0x6A
#define SENSOR_NUM_BB_TEMP_PEX_1 0x6B
#define SENSOR_NUM_BB_TEMP_PEX_2 0x6C
#define SENSOR_NUM_BB_TEMP_PEX_3 0x6D

#define SENSOR_NUM_SYSTEM_INLET_TEMP 0x70
#define SENSOR_NUM_OUTLET_TEMP_L1 0x71
#define SENSOR_NUM_OUTLET_TEMP_L2 0x72
#define SENSOR_NUM_OUTLET_TEMP_R1 0x73
#define SENSOR_NUM_OUTLET_TEMP_R2 0x74

#define SENSOR_NUM_TEMP_E1S_0 0x80
#define SENSOR_NUM_VOLT_E1S_0 0x81
#define SENSOR_NUM_CURR_E1S_0 0x82
#define SENSOR_NUM_POUT_E1S_0 0x83

#define SENSOR_NUM_TEMP_E1S_1 0x84
#define SENSOR_NUM_VOLT_E1S_1 0x85
#define SENSOR_NUM_CURR_E1S_1 0x86
#define SENSOR_NUM_POUT_E1S_1 0x87

#define SENSOR_NUM_TEMP_E1S_2 0x88
#define SENSOR_NUM_VOLT_E1S_2 0x89
#define SENSOR_NUM_CURR_E1S_2 0x8A
#define SENSOR_NUM_POUT_E1S_2 0x8B

#define SENSOR_NUM_TEMP_E1S_3 0x8C
#define SENSOR_NUM_VOLT_E1S_3 0x8D
#define SENSOR_NUM_CURR_E1S_3 0x8E
#define SENSOR_NUM_POUT_E1S_3 0x8F

#define SENSOR_NUM_TEMP_E1S_4 0x90
#define SENSOR_NUM_VOLT_E1S_4 0x91
#define SENSOR_NUM_CURR_E1S_4 0x92
#define SENSOR_NUM_POUT_E1S_4 0x93

#define SENSOR_NUM_TEMP_E1S_5 0x94
#define SENSOR_NUM_VOLT_E1S_5 0x95
#define SENSOR_NUM_CURR_E1S_5 0x96
#define SENSOR_NUM_POUT_E1S_5 0x97

#define SENSOR_NUM_TEMP_E1S_6 0x98
#define SENSOR_NUM_VOLT_E1S_6 0x99
#define SENSOR_NUM_CURR_E1S_6 0x9A
#define SENSOR_NUM_POUT_E1S_6 0x9B

#define SENSOR_NUM_TEMP_E1S_7 0x9C
#define SENSOR_NUM_VOLT_E1S_7 0x9D
#define SENSOR_NUM_CURR_E1S_7 0x9E
#define SENSOR_NUM_POUT_E1S_7 0x9F

#define SENSOR_NUM_TEMP_E1S_8 0xA0
#define SENSOR_NUM_VOLT_E1S_8 0xA1
#define SENSOR_NUM_CURR_E1S_8 0xA2
#define SENSOR_NUM_POUT_E1S_8 0xA3

#define SENSOR_NUM_TEMP_E1S_9 0xA4
#define SENSOR_NUM_VOLT_E1S_9 0xA5
#define SENSOR_NUM_CURR_E1S_9 0xA6
#define SENSOR_NUM_POUT_E1S_9 0xA7

#define SENSOR_NUM_TEMP_E1S_10 0xA8
#define SENSOR_NUM_VOLT_E1S_10 0xA9
#define SENSOR_NUM_CURR_E1S_10 0xAA
#define SENSOR_NUM_POUT_E1S_10 0xAB

#define SENSOR_NUM_TEMP_E1S_11 0xAC
#define SENSOR_NUM_VOLT_E1S_11 0xAD
#define SENSOR_NUM_CURR_E1S_11 0xAE
#define SENSOR_NUM_POUT_E1S_11 0xAF

#define SENSOR_NUM_TEMP_E1S_12 0xB0
#define SENSOR_NUM_VOLT_E1S_12 0xB1
#define SENSOR_NUM_CURR_E1S_12 0xB2
#define SENSOR_NUM_POUT_E1S_12 0xB3

#define SENSOR_NUM_TEMP_E1S_13 0xB4
#define SENSOR_NUM_VOLT_E1S_13 0xB5
#define SENSOR_NUM_CURR_E1S_13 0xB6
#define SENSOR_NUM_POUT_E1S_13 0xB7

#define SENSOR_NUM_TEMP_E1S_14 0xB8
#define SENSOR_NUM_VOLT_E1S_14 0xB9
#define SENSOR_NUM_CURR_E1S_14 0xBA
#define SENSOR_NUM_POUT_E1S_14 0xBB

#define SENSOR_NUM_TEMP_E1S_15 0xBC
#define SENSOR_NUM_VOLT_E1S_15 0xBD
#define SENSOR_NUM_CURR_E1S_15 0xBE
#define SENSOR_NUM_POUT_E1S_15 0xBF

uint8_t load_sensor_config(void);

#endif
