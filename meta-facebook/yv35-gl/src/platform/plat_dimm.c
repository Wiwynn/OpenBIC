#include "plat_dimm.h"

#include <stdio.h>
#include <stdlib.h>
#include <zephyr.h>
#include <logging/log.h>
#include <errno.h>
#include "plat_sensor_table.h"
#include "ipmb.h"
#include "ipmi.h"
#include "kcs.h"
#include "sensor.h"
#include "pmic.h"
#include "power_status.h"
#include "plat_i2c.h"
#include "plat_isr.h"
#include "plat_class.h"
#include "libutil.h"
#include "rg3mxxb12.h"
#include "p3h284x.h"

LOG_MODULE_REGISTER(plat_dimm);

K_THREAD_STACK_DEFINE(get_dimm_info_stack, GET_DIMM_INFO_STACK_SIZE);
struct k_thread get_dimm_info_thread;
k_tid_t get_dimm_info_tid;

struct k_mutex i3c_dimm_mutex;

uint8_t pmic_i3c_addr_list[MAX_COUNT_DIMM / 2] = { PMIC_A0_A4_ADDR, PMIC_A1_A5_ADDR, PMIC_A2_A6_ADDR,
						   PMIC_A3_A7_ADDR };

dimm_info dimm_data[MAX_COUNT_DIMM];

static bool dimm_prsnt_inited = false;

const uint8_t sys_sem_head_cmd[11] = { 0x00, 0x03, 0x00, 0x00, 0x00, 0x04,
				       0x00, 0xA8, 0x21, 0xE0, 0x01 };
const uint8_t sys_sem_tail_cmd[11] = { 0x00, 0x03, 0x00, 0x00, 0x00, 0x04,
				       0x00, 0xB8, 0x21, 0xE0, 0x01 };
const uint8_t sys_sem_app_cmd[11] = { 0x00, 0x03, 0x00, 0x00, 0x00, 0x04,
				      0x00, 0x98, 0x21, 0xE0, 0x01 };
const uint8_t bios_rtbus_rdy_cmd[11] = { 0x00, 0x03, 0x00, 0x00, 0x00, 0x04,
					 0x00, 0xA0, 0x81, 0x81, 0x00 };
const uint8_t bios_rtbus_get_cmd[11] = { 0x00, 0x03, 0x00, 0x00, 0x00, 0x04,
					 0x00, 0xCC, 0x81, 0x81, 0x00 };
uint8_t check_cpu_i3c_spd_cmd[13] = { 0x12, 0x05, 0x00, 0x00, 0x00, 0x05, 0xFF,
				      0x00, 0x00, 0x20, 0x00, 0x00, 0x00 };
uint8_t wr_lowqport_cmd[17] = { 0x12, 0x05, 0x00, 0x00, 0x00, 0x05, 0xFF, 0x00, 0x00,
				0xC0, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0xe0 };
uint8_t get_pmic_data_cmd[13] = { 0x12, 0x05, 0x00, 0x00, 0x00, 0x05, 0xFF,
				  0x00, 0x00, 0xC8, 0x00, 0x00, 0x00 };
uint8_t back_normal_cmd[13] = { 0x12, 0x05, 0x00, 0x00, 0x00, 0x05, 0xFF,
				0x00, 0x00, 0x20, 0x00, 0x00, 0x00 };
uint8_t rl_sem_cmd[15] = { 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0xC8,
			   0x21, 0xE0, 0x01, 0x00, 0x00, 0x00, 0x00 };

const uint8_t pmic_err_offset[7] = { 0x05, 0x06, 0x08, 0x09, 0x0A, 0x0B, 0x33 };

const uint8_t pmic_err_index[7] = { 0, 1, 3, 4, 5, 6, 46 };

void start_get_dimm_info_thread()
{
	LOG_INF("Start thread to get dimm information");

	get_dimm_info_tid =
		k_thread_create(&get_dimm_info_thread, get_dimm_info_stack,
				K_THREAD_STACK_SIZEOF(get_dimm_info_stack), get_dimm_info_handler,
				NULL, NULL, NULL, CONFIG_MAIN_THREAD_PRIORITY, 0, K_NO_WAIT);
	k_thread_name_set(&get_dimm_info_thread, "get_dimm_info_thread");
}

bool is_dimm_prsnt_inited()
{
	return dimm_prsnt_inited;
}

bool is_dimm_ready_monitor(uint8_t dimm_id)
{
	return dimm_data[dimm_id].is_ready_monitor;
}

void get_dimm_info_handler()
{
	uint8_t pmic_addr, bdf;
	uint8_t read_len = 0x05;
	uint8_t write_len = 0x0C;
	uint16_t sem_head, sem_tail, sem_app;
	uint8_t bios_rtbusu0_val;
	uint8_t pmic_offset;

	while (1) {
		int dimm_id, step;
		for (dimm_id = 0; dimm_id < MAX_COUNT_DIMM; dimm_id++) {
			if (!dimm_data[dimm_id].is_present) {
				continue;
			}

			// Double check before read each DIMM info
			if (!get_post_status()) {
				dimm_data[dimm_id].is_ready_monitor = false;
				break;
			}

			bdf = (dimm_id < (MAX_COUNT_DIMM / 2)) ? 0xF2 : 0xF5;

			pmic_addr = pmic_i3c_addr_list[dimm_id % (MAX_COUNT_DIMM / 2)];

			// Check semaphore head and tail number
			while (1) {
				if (peci_write(PECI_CMD_RD_END_PT_CFG0, addr, read_len, read_buf,
					       write_len, sys_sem_head_cmd) != 0) {
					LOG_ERR("PECI read system semaphore head number error");
				}
				if (read_buf[0] != PECI_CC_RSP_SUCCESS) {
					if (read_buf[0] == PECI_CC_ILLEGAL_REQUEST) {
						LOG_ERR("Read system semaphore head number unknown request");
					} else {
						LOG_ERR("Read system semaphore head number peci control hardware, firmware or associated logic error");
					}
				}
				sem_head = (read_buf[1] << 8) | read_buf[2];

				memset(read_buf, 0, read_len);

				if (peci_write(PECI_CMD_RD_END_PT_CFG0, addr, read_len, read_buf,
					       write_len, sys_sem_tail_cmd) != 0) {
					LOG_ERR("PECI read system semaphore tail number error");
				}
				if (read_buf[0] != PECI_CC_RSP_SUCCESS) {
					if (read_buf[0] == PECI_CC_ILLEGAL_REQUEST) {
						LOG_ERR("Read system semaphore tail number unknown request");
					} else {
						LOG_ERR("Read system semaphore tail number peci control hardware, firmware or associated logic error");
					}
				}
				sem_tail = (read_buf[1] << 8) | read_buf[2];

				if (sem_head == sem_tail) {
					break;
				} else {
					read_len = 0x01;
					write_len = 0x11;
					read_buf = (uint8_t *)realloc(read_buf, read_len);
					rl_sem_cmd[11] = (sem_head >> 8) & 0xFF;
					rl_sem_cmd[12] = sem_head & 0xFF;
					if (peci_write(PECI_CMD_WR_END_PT_CFG0, addr, read_len,
						       read_buf, write_len, rl_sem_cmd) != 0) {
						LOG_ERR("PECI relase the semaphore error");
					}
					if (read_buf[0] != PECI_CC_RSP_SUCCESS) {
						if (read_buf[0] == PECI_CC_ILLEGAL_REQUEST) {
							LOG_ERR("Relase the semaphore unknown request");
						} else {
							LOG_ERR("Relase the semaphore peci control hardware, firmware or associated logic error");
						}
					}
				}
			}

			// Apply semaphore
			read_len = 0x05;
			write_len = 0x0C;
			read_buf = (uint8_t *)realloc(read_buf, read_len);
			if (peci_write(PECI_CMD_RD_END_PT_CFG0, addr, read_len, read_buf, write_len,
				       sys_sem_app_cmd) != 0) {
				LOG_ERR("PECI apply system semaphore error");
				goto cleanup;
			}
			if (read_buf[0] != PECI_CC_RSP_SUCCESS) {
				if (read_buf[0] == PECI_CC_ILLEGAL_REQUEST) {
					LOG_ERR("Apply system semaphore unknown request");
				} else {
					LOG_ERR("Apply system semaphore peci control hardware, firmware or associated logic error");
				}
				goto cleanup;
			}
			sem_app = (read_buf[1] << 8) | read_buf[2];
			if ((sem_app != sem_head) || (read_buf[4] != PECI_CC_RSP_SUCCESS)) {
				LOG_ERR("Apply system semaphore error");
				goto cleanup;
			}

			// Check BIOS assign RootBus_U0 ready
			memset(read_buf, 0, read_len);
			if (peci_write(PECI_CMD_RD_END_PT_CFG0, addr, read_len, read_buf, write_len,
				       bios_rtbus_rdy_cmd) != 0) {
				LOG_ERR("PECI check BIOS assign RootBus_U0 ready error");
				goto cleanup;
			}
			if (read_buf[0] != PECI_CC_RSP_SUCCESS) {
				if (read_buf[0] == PECI_CC_ILLEGAL_REQUEST) {
					LOG_ERR("Check BIOS assign RootBus_U0 ready unknown request");
				} else {
					LOG_ERR("Check BIOS assign RootBus_U0 ready peci control hardware, firmware or associated logic error");
				}
				goto cleanup;
			}
			// Bit 30 == 1 means ready
			if (GETBIT(read_buf[4], 6) != 1) {
				LOG_ERR("BIOS assign RootBus_U0 is not ready");
				goto cleanup;
			}

			// Get RootBus_U0 value
			memset(read_buf, 0, read_len);
			if (peci_write(PECI_CMD_RD_END_PT_CFG0, addr, read_len, read_buf, write_len,
				       bios_rtbus_get_cmd) != 0) {
				LOG_ERR("PECI get BIOS RootBus_U0 value error");
				goto cleanup;
			}
			if (read_buf[0] != PECI_CC_RSP_SUCCESS) {
				if (read_buf[0] == PECI_CC_ILLEGAL_REQUEST) {
					LOG_ERR("Get BIOS RootBus_U0 value unknown request");
				} else {
					LOG_ERR("Get BIOS RootBus_U0 value peci control hardware, firmware or associated logic error");
				}
				goto cleanup;
			}
			bios_rtbusu0_val = read_buf[3];

			for (step = 0; step < PECI_GET_PMIC_ERR_STEP; step++) {
				// Check CPU I3C_SPD controller INTR_STATUS
				read_len = 0x05;
				write_len = 0x0E;
				read_buf = (uint8_t *)realloc(read_buf, read_len);
				check_cpu_i3c_spd_cmd[7] = bdf;
				check_cpu_i3c_spd_cmd[8] = bios_rtbusu0_val;
				if (peci_write(PECI_CMD_RD_END_PT_CFG0, addr, read_len, read_buf,
					       write_len, check_cpu_i3c_spd_cmd) != 0) {
					LOG_ERR("PECI check CPU I3C_SPD controller INTR_STATUS error");
					goto cleanup;
				}
				if (read_buf[0] != PECI_CC_RSP_SUCCESS) {
					if (read_buf[0] == PECI_CC_ILLEGAL_REQUEST) {
						LOG_ERR("Check CPU I3C_SPD controller INTR_STATUS unknown request");
					} else {
						LOG_ERR("Check CPU I3C_SPD controller INTR_STATUS peci control hardware, firmware or associated logic error");
					}
					goto cleanup;
				}
				if (read_buf[1] != 0x09) {
					LOG_ERR("Check CPU I3C_SPD controller INTR_STATUS error");
					goto cleanup;
				}

				// Write REGULAR_COMMAND_LOW to COMMAND_QUEUE_PORT
				read_len = 0x01;
				write_len = 0x13;
				read_buf = (uint8_t *)realloc(read_buf, read_len);
				wr_lowqport_cmd[7] = bdf;
				wr_lowqport_cmd[8] = bios_rtbusu0_val;
				wr_lowqport_cmd[15] = pmic_addr;
				if (peci_write(PECI_CMD_WR_END_PT_CFG0, addr, read_len, read_buf,
					       write_len, wr_lowqport_cmd) != 0) {
					LOG_ERR("PECI write REGULAR_COMMAND_LOW to COMMAND_QUEUE_PORT error");
					goto cleanup;
				}
				if (read_buf[0] != PECI_CC_RSP_SUCCESS) {
					if (read_buf[0] == PECI_CC_ILLEGAL_REQUEST) {
						LOG_ERR("Write REGULAR_COMMAND_LOW to COMMAND_QUEUE_PORT unknown request");
					} else {
						LOG_ERR("Write REGULAR_COMMAND_LOW to COMMAND_QUEUE_PORT peci control hardware, firmware or associated logic error");
					}
					goto cleanup;
				}

				// Make sure user can write next commands
				read_len = 0x05;
				write_len = 0x0E;
				read_buf = (uint8_t *)realloc(read_buf, read_len);
				uint8_t wr_next_cmd[13] = { 0x12, 0x05, 0x00,
							    0x00, 0x00, 0x05,
							    0xFF, bdf,	bios_rtbusu0_val,
							    0x20, 0x00, 0x00,
							    0x00 };
				if (peci_write(PECI_CMD_RD_END_PT_CFG0, addr, read_len, read_buf,
					       write_len, wr_next_cmd) != 0) {
					LOG_ERR("PECI make sure user can write next commands error");
					goto cleanup;
				}
				if (read_buf[0] != PECI_CC_RSP_SUCCESS) {
					if (read_buf[0] == PECI_CC_ILLEGAL_REQUEST) {
						LOG_ERR("Make sure user can write next commands unknown request");
					} else {
						LOG_ERR("Make sure user can write next commands peci control hardware, firmware or associated logic error");
					}
					goto cleanup;
				}
				if (read_buf[1] != 0x09) {
					LOG_ERR("Make sure user can write next commands error");
					goto cleanup;
				}

				// Write REGULAR_COMMAND_High to COMMAND_QUEUE_PORT
				read_len = 0x01;
				write_len = 0x13;
				read_buf = (uint8_t *)realloc(read_buf, read_len);
				uint8_t wr_highqport_cmd[17] = { 0x12,
								 0x05,
								 0x00,
								 0x00,
								 0x00,
								 0x05,
								 0xFF,
								 bdf,
								 bios_rtbusu0_val,
								 0xC0,
								 0x00,
								 0x00,
								 0x00,
								 pmic_err_offset[offset],
								 0x00,
								 0x01,
								 0x00 };
				if (peci_write(PECI_CMD_WR_END_PT_CFG0, addr, read_len, read_buf,
					       write_len, wr_highqport_cmd) != 0) {
					LOG_ERR("PECI write REGULAR_COMMAND_LOW to COMMAND_QUEUE_PORT error");
					goto cleanup;
				}
				if (read_buf[0] != PECI_CC_RSP_SUCCESS) {
					if (read_buf[0] == PECI_CC_ILLEGAL_REQUEST) {
						LOG_ERR("Write REGULAR_COMMAND_LOW to COMMAND_QUEUE_PORT unknown request");
					} else {
						LOG_ERR("Write REGULAR_COMMAND_LOW to COMMAND_QUEUE_PORT peci control hardware, firmware or associated logic error");
					}
					goto cleanup;
				}

				// Make sure getting PMIC respond data back without I3C transfer error happen
				read_len = 0x05;
				write_len = 0x0E;
				read_buf = (uint8_t *)realloc(read_buf, read_len);
				uint8_t check_error_cmd[13] = { 0x12, 0x05, 0x00,
								0x00, 0x00, 0x05,
								0xFF, bdf,  bios_rtbusu0_val,
								0x20, 0x00, 0x00,
								0x00 };
				if (peci_write(PECI_CMD_RD_END_PT_CFG0, addr, read_len, read_buf,
					       write_len, check_error_cmd) != 0) {
					LOG_ERR("PECI check I3C transfer error happen error");
					goto cleanup;
				}
				if (read_buf[0] != PECI_CC_RSP_SUCCESS) {
					if (read_buf[0] == PECI_CC_ILLEGAL_REQUEST) {
						LOG_ERR("Check I3C transfer error happen unknown request");
					} else {
						LOG_ERR("Check I3C transfer error happen peci control hardware, firmware or associated logic error");
					}
					goto cleanup;
				}
				if ((read_buf[1] != 0x1B) || (read_buf[2] != 0x00)) {
					LOG_ERR("I3C transfer error happen");
					goto cleanup;
				}

				// See how many data byte be read back, and make sure without I3C trandfer error happen
				memset(read_buf, 0, read_len);
				uint8_t error_cnt_cmd[13] = { 0x12, 0x05, 0x00,
							      0x00, 0x00, 0x05,
							      0xFF, bdf,  bios_rtbusu0_val,
							      0xC4, 0x00, 0x00,
							      0x00 };
				if (peci_write(PECI_CMD_RD_END_PT_CFG0, addr, read_len, read_buf,
					       write_len, error_cnt_cmd) != 0) {
					LOG_ERR("PECI make sure without I3C trandfer error happen error");
					goto cleanup;
				}
				if (read_buf[0] != PECI_CC_RSP_SUCCESS) {
					if (read_buf[0] == PECI_CC_ILLEGAL_REQUEST) {
						LOG_ERR("Make sure without I3C trandfer error happen unknown request");
					} else {
						LOG_ERR("Make sure without I3C trandfer error happen peci control hardware, firmware or associated logic error");
					}
					goto cleanup;
				}
				if (read_buf[1] != 0x01) {
					LOG_ERR("Data byte be read back is not correct");
					goto cleanup;
				}
				if (read_buf[4] != 0x00) {
					LOG_ERR("I3C trandfer error happen");
					goto cleanup;
				}

				// Read CPU I3C_SPD Controller DATA_PORT to receive PMIC data
				memset(read_buf, 0, read_len);
				uint8_t get_pmic_data_cmd[13] = { 0x12, 0x05, 0x00,
								  0x00, 0x00, 0x05,
								  0xFF, bdf,  bios_rtbusu0_val,
								  0xC8, 0x00, 0x00,
								  0x00 };
				if (peci_write(PECI_CMD_RD_END_PT_CFG0, addr, read_len, read_buf,
					       write_len, get_pmic_data_cmd) != 0) {
					LOG_ERR("PECI get pmic data error");
					goto cleanup;
				}
				if (read_buf[0] != PECI_CC_RSP_SUCCESS) {
					if (read_buf[0] == PECI_CC_ILLEGAL_REQUEST) {
						LOG_ERR("Get pmic data unknown request");
					} else {
						LOG_ERR("Get pmic data peci control hardware, firmware or associated logic error");
					}
					goto cleanup;
				}

				dimm_data[dimm_id].pmic_error_data[pmic_err_index[offset]] =
					read_buf[1];
			}

			// Check CPU I3C_SPD Controller INTR_STATUS, make sure CPU I3C SPD Controller back to normal state
			memset(read_buf, 0, read_len);
			back_normal_cmd[7] = bdf;
			back_normal_cmd[8] = bios_rtbusu0_val;
			if (peci_write(PECI_CMD_RD_END_PT_CFG0, addr, read_len, read_buf, write_len,
				       back_normal_cmd) != 0) {
				LOG_ERR("PECI back to normal state error");
				goto cleanup;
			}
			if (read_buf[0] != PECI_CC_RSP_SUCCESS) {
				if (read_buf[0] == PECI_CC_ILLEGAL_REQUEST) {
					LOG_ERR("Back to normal state unknown request");
				} else {
					LOG_ERR("Back to normal state peci control hardware, firmware or associated logic error");
				}
				goto cleanup;
			}
			if (read_buf[1] != 0x09) {
				LOG_ERR("Back to normal state fail");
				goto cleanup;
			}

			// Relase the semaphore
			read_len = 0x01;
			write_len = 0x11;
			read_buf = (uint8_t *)realloc(read_buf, read_len);
			rl_sem_cmd[11] = (sem_head >> 8) & 0xFF;
			rl_sem_cmd[12] = sem_head & 0xFF;
			if (peci_write(PECI_CMD_WR_END_PT_CFG0, addr, read_len, read_buf, write_len,
				       rl_sem_cmd) != 0) {
				LOG_ERR("PECI relase the semaphore error");
				goto cleanup;
			}
			if (read_buf[0] != PECI_CC_RSP_SUCCESS) {
				if (read_buf[0] == PECI_CC_ILLEGAL_REQUEST) {
					LOG_ERR("Relase the semaphore unknown request");
				} else {
					LOG_ERR("Relase the semaphore peci control hardware, firmware or associated logic error");
				}
				goto cleanup;
			}

			// If the DIMM is ready for monitoring, BIC can send its temperature to CPU by PECI.
			dimm_data[dimm_id].is_ready_monitor = true;
		}

		k_msleep(GET_DIMM_INFO_TIME_MS);
	}
cleanup:
	SAFE_FREE(read_buf);
	return false;
}

void init_i3c_dimm_prsnt_status()
{
	int index;
	for (index = DIMM_ID_A0; index < MAX_COUNT_DIMM; index++) {
		ipmi_msg msg = { 0 };

		msg.InF_source = SELF;
		msg.InF_target = BMC_IPMB;
		msg.netfn = NETFN_OEM_Q_REQ;
		msg.cmd = CMD_OEM_Q_GET_DIMM_INFO;
		msg.data_len = 5;
		msg.data[0] = IANA_ID & 0xFF;
		msg.data[1] = (IANA_ID >> 8) & 0xFF;
		msg.data[2] = (IANA_ID >> 16) & 0xFF;
		msg.data[3] = (uint8_t)index;
		msg.data[4] = CMD_DIMM_LOCATION;

		ipmb_error ret = ipmb_read(&msg, IPMB_inf_index_map[msg.InF_target]);
		if (ret != IPMB_ERROR_SUCCESS) {
			LOG_ERR("Failed to get DIMM status, ret= %d", ret);
			return;
		}

		uint8_t status = msg.data[0];
		if (status == DIMM_PRESENT) {
			dimm_data[index].is_present = true;
		} else {
			dimm_data[index].is_present = false;
		}
	}

	dimm_prsnt_inited = true;
}

bool get_dimm_presence_status(uint8_t dimm_id)
{
	return dimm_data[dimm_id].is_present;
}

void set_dimm_presence_status(uint8_t index, uint8_t status)
{
	if (status == DIMM_PRESENT) {
		dimm_data[index].is_present = true;
	} else {
		dimm_data[index].is_present = false;
	}
}

uint8_t sensor_num_map_dimm_id(uint8_t sensor_num)
{
	uint8_t dimm_id = DIMM_ID_UNKNOWN;

	switch (sensor_num) {
	case SENSOR_NUM_MB_DIMMA0_TEMP_C:
	case SENSOR_NUM_MB_VR_DIMMA0_PMIC_PWR_W:
		dimm_id = DIMM_ID_A0;
		break;
	case SENSOR_NUM_MB_DIMMA1_TEMP_C:
	case SENSOR_NUM_MB_VR_DIMMA1_PMIC_PWR_W:
		dimm_id = DIMM_ID_A1;
		break;
	case SENSOR_NUM_MB_DIMMA2_TEMP_C:
	case SENSOR_NUM_MB_VR_DIMMA2_PMIC_PWR_W:
		dimm_id = DIMM_ID_A2;
		break;
	case SENSOR_NUM_MB_DIMMA3_TEMP_C:
	case SENSOR_NUM_MB_VR_DIMMA3_PMIC_PWR_W:
		dimm_id = DIMM_ID_A3;
		break;
	case SENSOR_NUM_MB_DIMMA4_TEMP_C:
	case SENSOR_NUM_MB_VR_DIMMA4_PMIC_PWR_W:
		dimm_id = DIMM_ID_A4;
		break;
	case SENSOR_NUM_MB_DIMMA5_TEMP_C:
	case SENSOR_NUM_MB_VR_DIMMA5_PMIC_PWR_W:
		dimm_id = DIMM_ID_A5;
		break;
	case SENSOR_NUM_MB_DIMMA6_TEMP_C:
	case SENSOR_NUM_MB_VR_DIMMA6_PMIC_PWR_W:
		dimm_id = DIMM_ID_A6;
		break;
	case SENSOR_NUM_MB_DIMMA7_TEMP_C:
	case SENSOR_NUM_MB_VR_DIMMA7_PMIC_PWR_W:
		dimm_id = DIMM_ID_A7;
		break;
	default:
		dimm_id = DIMM_ID_UNKNOWN;
		break;
	}

	return dimm_id;
}

int get_pmic_error_raw_data(int dimm_index, uint8_t *data)
{
	CHECK_NULL_ARG_WITH_RETURN(data, -1);

	int i = 0, fail_count = 0;

	for (i = 0; i < sizeof(dimm_data[dimm_index].pmic_error_data); i++) {
		if (dimm_data[dimm_index].pmic_error_data[i] == SENSOR_FAIL) {
			fail_count++;
		}
	}

	// PMIC error data read failed
	if (fail_count == sizeof(dimm_data[dimm_index].pmic_error_data)) {
		return -1;
	}

	memcpy(data, &dimm_data[dimm_index].pmic_error_data,
	       sizeof(dimm_data[dimm_index].pmic_error_data));

	return 0;
}

void get_pmic_power_raw_data(int dimm_index, uint8_t *data)
{
	CHECK_NULL_ARG(data);

	memcpy(data, &dimm_data[dimm_index].pmic_pwr_data,
	       sizeof(dimm_data[dimm_index].pmic_pwr_data));
}

void get_spd_temp_raw_data(int dimm_index, uint8_t *data)
{
	CHECK_NULL_ARG(data);

	memcpy(data, &dimm_data[dimm_index].spd_temp_data,
	       sizeof(dimm_data[dimm_index].spd_temp_data));
}

int pal_get_pmic_pwr(uint8_t sensor_num, uint8_t *data)
{
	CHECK_NULL_ARG_WITH_RETURN(data, -1);

	uint8_t dimm_id = DIMM_ID_UNKNOWN;

	dimm_id = sensor_num_map_dimm_id(sensor_num);
	if (dimm_id == DIMM_ID_UNKNOWN) {
		return -1;
	}

	get_pmic_power_raw_data(dimm_id, (uint8_t *)data);

	// If sensor data is SENSOR_FAIL, return failed
	if (data[0] == SENSOR_FAIL) {
		return -1;
	}

	return 0;
}

int pal_get_spd_temp(uint8_t sensor_num, uint8_t *data)
{
	CHECK_NULL_ARG_WITH_RETURN(data, -1);

	uint8_t dimm_id = DIMM_ID_UNKNOWN;

	dimm_id = sensor_num_map_dimm_id(sensor_num);
	if (dimm_id == DIMM_ID_UNKNOWN) {
		return -1;
	}

	get_spd_temp_raw_data(dimm_id, (uint8_t *)data);

	// If sensor data is SENSOR_FAIL, return failed
	if (data[0] == SENSOR_FAIL) {
		return -1;
	}

	return 0;
}

void clear_unaccessible_dimm_data(uint8_t dimm_id)
{
	memset(dimm_data[dimm_id].pmic_error_data, SENSOR_FAIL,
	       sizeof(dimm_data[dimm_id].pmic_error_data));
	memset(dimm_data[dimm_id].pmic_pwr_data, SENSOR_FAIL,
	       sizeof(dimm_data[dimm_id].pmic_pwr_data));
	memset(dimm_data[dimm_id].spd_temp_data, SENSOR_FAIL,
	       sizeof(dimm_data[dimm_id].spd_temp_data));
}
