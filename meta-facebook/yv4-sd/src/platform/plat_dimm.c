#include <stdio.h>
#include <stdlib.h>
#include <zephyr.h>
#include <logging/log.h>
#include <errno.h>

#include "sensor.h"
#include "power_status.h"

#include "plat_dimm.h"
#include "plat_i2c.h"
#include "plat_i3c.h"
#include "plat_spi.h"

LOG_MODULE_REGISTER(plat_dimm, LOG_LEVEL_DBG);

K_THREAD_STACK_DEFINE(get_dimm_info_stack, GET_DIMM_INFO_STACK_SIZE);
struct k_thread get_dimm_info_thread;
struct k_mutex i3c_dimm_mutex;
k_tid_t get_dimm_info_tid;

dimm_info dimm_data[DIMM_ID_MAX];

uint8_t pmic_i3c_addr_list[] = { DIMM_PMIC_A_G_ADDR, DIMM_PMIC_B_H_ADDR, DIMM_PMIC_C_I_ADDR,
				 DIMM_PMIC_D_J_ADDR, DIMM_PMIC_E_K_ADDR, DIMM_PMIC_F_L_ADDR };
uint8_t spd_i3c_addr_list[] = { DIMM_SPD_A_G_ADDR, DIMM_SPD_B_H_ADDR, DIMM_SPD_C_I_ADDR,
				DIMM_SPD_D_J_ADDR, DIMM_SPD_E_K_ADDR, DIMM_SPD_F_L_ADDR };
/*
static bool dimm_prsnt_inited = false;
*/
void start_get_dimm_info_thread()
{
	LOG_INF("Start thread to get dimm information");

	get_dimm_info_tid =
		k_thread_create(&get_dimm_info_thread, get_dimm_info_stack,
				K_THREAD_STACK_SIZEOF(get_dimm_info_stack), get_dimm_info_handler,
				NULL, NULL, NULL, CONFIG_MAIN_THREAD_PRIORITY, 0, K_NO_WAIT);
	k_thread_name_set(&get_dimm_info_thread, "get_dimm_info_thread");
}

void get_dimm_info_handler()
{
	I3C_MSG i3c_msg = { 0 };
	int i;

	i3c_msg.bus = I3C_BUS3;

	// Attach PMIC addr
	for (i = 0; i < sizeof(pmic_i3c_addr_list); i++) {
		i3c_msg.target_addr = pmic_i3c_addr_list[i];
		i3c_attach(&i3c_msg);
	}
	// Init mutex
	if (k_mutex_init(&i3c_dimm_mutex)) {
		LOG_ERR("i3c_dimm_mux_mutex mutex init fail");
	}

	while (1) {
		int ret = 0;
		uint8_t dimm_id;

		// Avoid to get wrong thus only monitor after post complete
		if (!get_post_status()) {
			k_msleep(GET_DIMM_INFO_TIME_MS);
			continue;
		}

		// TODO: check DIMM present init

		/*if (!is_dimm_prsnt_inited()) {
			init_i3c_dimm_prsnt_status();
		}*/

		if (k_mutex_lock(&i3c_dimm_mutex, K_MSEC(I3C_DIMM_MUTEX_TIMEOUT_MS))) {
			LOG_ERR("Failed to lock I3C dimm MUX");
			k_msleep(GET_DIMM_INFO_TIME_MS);
			continue;
		}

		for (dimm_id = 0; dimm_id < DIMM_ID_MAX; dimm_id++) {
			// TODO: check DIMM present

			/*if (!dimm_data[dimm_id].is_present) {
				continue;
			}*/

			uint8_t i3c_ctrl_mux_data = (dimm_id / (DIMM_ID_MAX / 2)) ?
							    I3C_MUX_TO_DIMMG_TO_L :
							    I3C_MUX_TO_DIMMA_TO_F;

			ret = switch_i3c_dimm_mux(i3c_ctrl_mux_data);
			if (ret != 0) {
				clear_unaccessible_dimm_data(dimm_id);
				continue;
			}

			memset(&i3c_msg, 0, sizeof(I3C_MSG));
			i3c_msg.bus = I3C_BUS3;
			i3c_msg.target_addr = spd_i3c_addr_list[dimm_id % (DIMM_ID_MAX / 2)];
			i3c_attach(&i3c_msg);

			// I3C_CCC_RSTDAA: Reset dynamic address assignment
			// I3C_CCC_SETAASA: Set all addresses to static address
			ret = all_brocast_ccc(&i3c_msg);
			if (ret != 0) {
				clear_unaccessible_dimm_data(dimm_id);
				i3c_detach(&i3c_msg);
				continue;
			}

			if (!get_post_status()) {
				i3c_detach(&i3c_msg);
				break;
			}

			i3c_msg.tx_len = 1;
			i3c_msg.rx_len = MAX_LEN_I3C_GET_SPD_TEMP;
			i3c_msg.data[0] = DIMM_SPD_TEMP;

			ret = i3c_spd_reg_read(&i3c_msg, false);
			if (ret != 0) {
				clear_unaccessible_dimm_data(dimm_id);
				i3c_detach(&i3c_msg);
				LOG_ERR("Failed to read DIMM %d SPD temperature via I3C, ret= %d",
					dimm_id, ret);
			} else {
				memcpy(&dimm_data[dimm_id].spd_temp_data, &i3c_msg.data,
				       sizeof(dimm_data[dimm_id].spd_temp_data));
			}
			i3c_detach(&i3c_msg);

			// Double check before read each DIMM info
			if (!get_post_status()) {
				dimm_data[dimm_id].is_ready_monitor = false;
				break;
			}

			// Read DIMM PMIC power
			memset(&i3c_msg, 0, sizeof(I3C_MSG));
			i3c_msg.bus = I3C_BUS3;
			i3c_msg.target_addr = pmic_i3c_addr_list[dimm_id % (DIMM_ID_MAX / 2)];
			i3c_msg.tx_len = 1;
			i3c_msg.rx_len = MAX_LEN_I3C_GET_PMIC_PWR;
			i3c_msg.data[0] = DIMM_PMIC_SWA_PWR;

			ret = i3c_transfer(&i3c_msg);
			if (ret != 0) {
				clear_unaccessible_dimm_data(dimm_id);
				LOG_ERR("Failed to read DIMM %d PMIC power via I3C, ret= %d",
					dimm_id, ret);
				continue;
			} else {
				memcpy(&dimm_data[dimm_id].pmic_pwr_data, &i3c_msg.data,
				       sizeof(dimm_data[dimm_id].pmic_pwr_data));
			}
		}

		if (k_mutex_unlock(&i3c_dimm_mutex)) {
			LOG_ERR("Failed to unlock I3C dimm MUX");
		}

		k_msleep(GET_DIMM_INFO_TIME_MS);
	}
}

uint8_t sensor_num_map_dimm_id(uint8_t sensor_num)
{
	uint8_t dimm_id = DIMM_ID_UNKNOWN;

	switch (sensor_num) {
	case NUM_DIMM_A_TEMP:
	case NUM_DIMM_A_PMIC_PWR:
		dimm_id = DIMM_ID_A;
		break;
	case NUM_DIMM_B_TEMP:
	case NUM_DIMM_B_PMIC_PWR:
		dimm_id = DIMM_ID_B;
		break;
	case NUM_DIMM_C_TEMP:
	case NUM_DIMM_C_PMIC_PWR:
		dimm_id = DIMM_ID_C;
		break;
	case NUM_DIMM_D_TEMP:
	case NUM_DIMM_D_PMIC_PWR:
		dimm_id = DIMM_ID_D;
		break;
	case NUM_DIMM_E_TEMP:
	case NUM_DIMM_E_PMIC_PWR:
		dimm_id = DIMM_ID_E;
		break;
	case NUM_DIMM_F_TEMP:
	case NUM_DIMM_F_PMIC_PWR:
		dimm_id = DIMM_ID_F;
		break;
	case NUM_DIMM_G_TEMP:
	case NUM_DIMM_G_PMIC_PWR:
		dimm_id = DIMM_ID_G;
		break;
	case NUM_DIMM_H_TEMP:
	case NUM_DIMM_H_PMIC_PWR:
		dimm_id = DIMM_ID_H;
		break;
	case NUM_DIMM_I_TEMP:
	case NUM_DIMM_I_PMIC_PWR:
		dimm_id = DIMM_ID_I;
		break;
	case NUM_DIMM_J_TEMP:
	case NUM_DIMM_J_PMIC_PWR:
		dimm_id = DIMM_ID_J;
		break;
	case NUM_DIMM_K_TEMP:
	case NUM_DIMM_K_PMIC_PWR:
		dimm_id = DIMM_ID_K;
		break;
	case NUM_DIMM_L_TEMP:
	case NUM_DIMM_L_PMIC_PWR:
		dimm_id = DIMM_ID_L;
		break;
	default:
		dimm_id = DIMM_ID_UNKNOWN;
		break;
	}

	return dimm_id;
}

void get_spd_temp_raw_data(int dimm_index, uint8_t *data)
{
	CHECK_NULL_ARG(data);

	memcpy(data, &dimm_data[dimm_index].spd_temp_data,
	       sizeof(dimm_data[dimm_index].spd_temp_data));
}

int pal_get_spd_temp(uint8_t sensor_num, uint8_t *data)
{
	CHECK_NULL_ARG_WITH_RETURN(data, -1);

	uint8_t dimm_id = DIMM_ID_UNKNOWN;

	dimm_id = sensor_num_map_dimm_id(sensor_num);
	if (dimm_id == DIMM_ID_UNKNOWN) {
		LOG_DBG("dimm_id is DIMM_ID_UNKNOWN");
		return -1;
	}

	get_spd_temp_raw_data(dimm_id, (uint8_t *)data);

	// If sensor data is SENSOR_FAIL, return failed
	if (data[0] == SENSOR_FAIL) {
		LOG_DBG("dimm data[0] is SENSOR_FAIL");
		return -1;
	}
	return 0;
}

void clear_unaccessible_dimm_data(uint8_t dimm_id)
{
	/*
	memset(dimm_data[dimm_id].pmic_error_data, SENSOR_FAIL,
	       sizeof(dimm_data[dimm_id].pmic_error_data));
	*/
	memset(dimm_data[dimm_id].pmic_pwr_data, SENSOR_FAIL,
	       sizeof(dimm_data[dimm_id].pmic_pwr_data));
	memset(dimm_data[dimm_id].spd_temp_data, SENSOR_FAIL,
	       sizeof(dimm_data[dimm_id].spd_temp_data));
}

int switch_i3c_dimm_mux(uint8_t i3c_ctrl_mux_data)
{
	I2C_MSG i2c_msg = { 0 };
	int ret = 0, retry = 3;

	i2c_msg.bus = I2C_BUS5;
	i2c_msg.target_addr = CPLD_ADDR;
	i2c_msg.tx_len = 2;
	i2c_msg.rx_len = 0;
	i2c_msg.data[0] = DIMM_I3C_MUX_CONTROL_OFFSET;

	i2c_msg.data[1] = i3c_ctrl_mux_data;

	ret = i2c_master_write(&i2c_msg, retry);
	if (ret != 0) {
		LOG_ERR("Failed to switch I3C MUX: 0x%x, ret= %d", i3c_ctrl_mux_data, ret);
	}

	return ret;
}

int all_brocast_ccc(I3C_MSG *i3c_msg)
{
	CHECK_NULL_ARG_WITH_RETURN(i3c_msg, -1);

	int ret = 0;

	ret = i3c_brocast_ccc(i3c_msg, I3C_CCC_RSTDAA, I3C_BROADCAST_ADDR);
	if (ret != 0) {
		return ret;
	}

	ret = i3c_brocast_ccc(i3c_msg, I3C_CCC_SETAASA, I3C_BROADCAST_ADDR);
	if (ret != 0) {
		return ret;
	}

	return ret;
}
