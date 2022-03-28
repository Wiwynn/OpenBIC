#include <stdio.h>
#include <string.h>
#include "pmic.h"
#include "ipmi.h"
#include "sensor.h"
#include "plat_i2c.h"
#include "plat_gpio.h"
#include "plat_hook.h"
#include "plat_sensor_table.h"

#include "i2c-mux-tca9548.h"

#define ADJUST_ADM1278_POWER(x) (x * 0.98)
#define ADJUST_ADM1278_CURRENT(x) ((x * 0.98) + 0.1)

/**************************************************************************************************
 * INIT ARGS
**************************************************************************************************/
adc_asd_init_arg adc_asd_init_args[] = { [0] = { .is_init = false } };

adm1278_init_arg adm1278_init_args[] = {
	[0] = { .is_init = false, .config = { 0x3F1C }, .r_sense = 0.25 }
};
mp5990_init_arg mp5990_init_args[] = {
	[0] = { .is_init = false, .iout_cal_gain = 0x0104, .iout_oc_fault_limit = 0x0028 },
	[1] = { .is_init = false, .iout_cal_gain = 0x01BF, .iout_oc_fault_limit = 0x0046 }
};
ltc4286_init_arg ltc4286_init_args[] = {
	[0] = { .is_init = false, .r_sense = 0.25, .mfr_config_1 = 0x5570},
	[1] = { .is_init = false, .r_sense = 0.25, .mfr_config_1 = 0x7570}
};

pmic_init_arg pmic_init_args[] = {
	[0] = { .is_init = false, .smbus_bus_identifier = 0x00, .smbus_addr = 0x90 },
	[1] = { .is_init = false, .smbus_bus_identifier = 0x00, .smbus_addr = 0x9C },
	[2] = { .is_init = false, .smbus_bus_identifier = 0x00, .smbus_addr = 0x98 },
	[3] = { .is_init = false, .smbus_bus_identifier = 0x01, .smbus_addr = 0x90 },
	[4] = { .is_init = false, .smbus_bus_identifier = 0x01, .smbus_addr = 0x9C },
	[5] = { .is_init = false, .smbus_bus_identifier = 0x01, .smbus_addr = 0x98 }
};

/**************************************************************************************************
 *  PRE-HOOK/POST-HOOK ARGS
 **************************************************************************************************/
struct tca9548 mux_conf_addr_0xe2[8] = {
	[0] = { .addr = 0xe2, .chan = 0 }, [1] = { .addr = 0xe2, .chan = 1 },
	[2] = { .addr = 0xe2, .chan = 2 }, [3] = { .addr = 0xe2, .chan = 3 },
	[4] = { .addr = 0xe2, .chan = 4 }, [5] = { .addr = 0xe2, .chan = 5 },
	[6] = { .addr = 0xe2, .chan = 6 }, [7] = { .addr = 0xe2, .chan = 7 },
};

isl69259_pre_proc_arg isl69259_pre_read_args[] = {
	[0] = { 0x0 },
	[1] = { 0x1 },
};

/**************************************************************************************************
 *  PRE-HOOK/POST-HOOK FUNC
 **************************************************************************************************/
/* ISL6925 pre read function
 *
 * set mux and VR page
 *
 * @param sensor_num sensor number
 * @param args pointer to isl69259_pre_proc_arg
 * @param reading pointer to reading from previous step
 * @retval true if setting mux and page is successful.
 * @retval false if setting mux or page fails.
 */
bool pre_isl69259_read(uint8_t sensor_num, void *args)
{
	if (args == NULL) {
		return false;
	}

	isl69259_pre_proc_arg *pre_proc_args = (isl69259_pre_proc_arg *)args;
	uint8_t retry = 5;
	I2C_MSG msg;

	/* set page */
	msg.bus = sensor_config[sensor_config_index_map[sensor_num]].port;
	msg.target_addr = sensor_config[sensor_config_index_map[sensor_num]].target_addr;
	msg.tx_len = 2;
	msg.data[0] = 0x00;
	msg.data[1] = pre_proc_args->vr_page;
	if (i2c_master_write(&msg, retry)) {
		printf("pre_isl69259_read, set page fail\n");
		return false;
	}
	return true;
}

/* NVME pre read function
 *
 * set mux
 *
 * @param sensor_num sensor number
 * @param args pointer to struct tca9548
 * @param reading pointer to reading from previous step
 * @retval true if setting mux is successful.
 * @retval false if setting mux fails.
 */
bool pre_nvme_read(uint8_t sensor_num, void *args)
{
	if (!args)
		return false;
	if (!tca9548_select_chan(sensor_num, (struct tca9548 *)args))
		return false;

	return true;
}

/* AST ADC pre read function
 *
 * set gpio high if sensor is "SENSOR_NUM_VOL_BAT3V"
 *
 * @param sensor_num sensor number
 * @param args pointer to NULL
 * @param reading pointer to reading from previous step
 * @retval true always.
 * @retval false NULL
 */
bool pre_vol_bat3v_read(uint8_t sensor_num, void *args)
{
	ARG_UNUSED(args);

	if (sensor_num == SENSOR_NUM_VOL_BAT3V) {
		gpio_set(A_P3V_BAT_SCALED_EN_R, GPIO_HIGH);
		k_msleep(1);
	}

	return true;
}

bool pre_pmic_read(uint8_t sensor_num, void *args)
{
	ARG_UNUSED(args);

	pmic_init_arg *pmic_arg = sensor_config[sensor_config_index_map[sensor_num]].init_args;
	if (pmic_arg->is_init == false) {
		static bool is_ME_reset = false;
		int ret = 0;
		uint8_t seq_source = 0xFF, write_data = 0x0;
		uint8_t *compose_memory_write_read_msg = NULL;

		// ME reset to let ME regain bus setting
		if (is_ME_reset != true) {
			ret = pmic_ipmb_transfer(NULL, seq_source, NETFN_APP_REQ,
						 CMD_APP_COLD_RESET, SELF, ME_IPMB, 0x0, NULL);
			if (ret != 0) {
				goto PMIC_IPMB_TRANSFER_ERR;
			}
			is_ME_reset = true;
			k_msleep(ME_COLD_RESET_DELAY_MSEC);
		}

		// Enable PMIC ADC
		write_data = PMIC_ENABLE_ADC_BIT;
		compose_memory_write_read_msg =
			compose_memory_write_read_req(pmic_arg->smbus_bus_identifier,
						      pmic_arg->smbus_addr, PMIC_ADC_ADDR_VAL,
						      &write_data, 0x1);
		if (compose_memory_write_read_msg == NULL) {
			goto COMPOSE_MSG_ERR;
		}

		ret = pmic_ipmb_transfer(NULL, seq_source, NETFN_NM_REQ, CMD_SMBUS_WRITE_MEMORY,
					 SELF, ME_IPMB, PMIC_WRITE_DATA_LEN,
					 compose_memory_write_read_msg);
		if (ret != 0) {
			goto PMIC_IPMB_TRANSFER_ERR;
		}
		k_msleep(PMIC_COMMAND_DELAY_MSEC);

		// Initialize PMIC to report total mode (could be total power, total current, etc.)
		write_data = SET_DEV_REPORT_TOTAL;
		compose_memory_write_read_msg =
			compose_memory_write_read_req(pmic_arg->smbus_bus_identifier,
						      pmic_arg->smbus_addr,
						      PMIC_TOTAL_INDIV_ADDR_VAL, &write_data, 0x1);
		if (compose_memory_write_read_msg == NULL) {
			goto COMPOSE_MSG_ERR;
		}

		ret = pmic_ipmb_transfer(NULL, seq_source, NETFN_NM_REQ, CMD_SMBUS_WRITE_MEMORY,
					 SELF, ME_IPMB, PMIC_WRITE_DATA_LEN,
					 compose_memory_write_read_msg);
		if (ret != 0) {
			goto PMIC_IPMB_TRANSFER_ERR;
		}
		k_msleep(PMIC_COMMAND_DELAY_MSEC);

		// Initialize PMIC to report power mode
		write_data = SET_DEV_REPORT_POWER;
		compose_memory_write_read_msg =
			compose_memory_write_read_req(pmic_arg->smbus_bus_identifier,
						      pmic_arg->smbus_addr, PMIC_PWR_CURR_ADDR_VAL,
						      &write_data, 0x1);
		if (compose_memory_write_read_msg == NULL) {
			goto COMPOSE_MSG_ERR;
		}

		ret = pmic_ipmb_transfer(NULL, seq_source, NETFN_NM_REQ, CMD_SMBUS_WRITE_MEMORY,
					 SELF, ME_IPMB, PMIC_WRITE_DATA_LEN,
					 compose_memory_write_read_msg);
		if (ret != 0) {
			goto PMIC_IPMB_TRANSFER_ERR;
		}
		k_msleep(PMIC_COMMAND_DELAY_MSEC);

		pmic_arg->is_init = true;
		return true;

	PMIC_IPMB_TRANSFER_ERR:
		if (write_data == 0x0) {
			printf("[%s] PMIC ipmb transfer me reset command error\n", __func__);
		} else {
			printf("[%s] PMIC ipmb transfer command error write_data: 0x%x\n", __func__,
			       write_data);
		}
		return false;

	COMPOSE_MSG_ERR:
		printf("[%s] compose msg error write_data: 0x%x\n", __func__, write_data);
		return false;
	}
	return true;
}

/* AST ADC post read function
 *
 * set gpio low if sensor is "SENSOR_NUM_VOL_BAT3V"
 *
 * @param sensor_num sensor number
 * @param args pointer to NULL
 * @param reading pointer to reading from previous step
 * @retval true always.
 * @retval false NULL
 */
bool post_vol_bat3v_read(uint8_t sensor_num, void *args, int *reading)
{
	ARG_UNUSED(args);
	ARG_UNUSED(reading);

	if (sensor_num == SENSOR_NUM_VOL_BAT3V)
		gpio_set(A_P3V_BAT_SCALED_EN_R, GPIO_LOW);

	return true;
}

/* INTEL PECI post read function
 *
 * modify certain sensor value after reading
 *
 * @param sensor_num sensor number
 * @param args pointer to NULL
 * @param reading pointer to reading from previous step
 * @retval true if no error
 * @retval false if reading get NULL
 */

bool post_cpu_margin_read(uint8_t sensor_num, void *args, int *reading)
{
	if (!reading)
		return false;
	ARG_UNUSED(args);

	sensor_val *sval = (sensor_val *)reading;
	sval->integer = -sval->integer; /* for BMC minus */
	return true;
}

/* ADM1278 post read function
 *
 * modify ADM1278 power value after reading
 *
 * @param sensor_num sensor number
 * @param args pointer to NULL
 * @param reading pointer to reading from previous step
 * @retval true if no error
 * @retval false if reading get NULL
 */
bool post_adm1278_power_read(uint8_t sensor_num, void *args, int *reading)
{
	if (!reading)
		return false;
	ARG_UNUSED(args);

	sensor_val *sval = (sensor_val *)reading;
	float val = (float)sval->integer + (sval->fraction / 1000.0);

	val = ADJUST_ADM1278_POWER(val);
	sval->integer = (int)val & 0xFFFF;
	sval->fraction = (val - sval->integer) * 1000;
	return true;
}

/* ADM1278 post read function
 *
 * modify ADM1278 current value after reading
 *
 * @param sensor_num sensor number
 * @param args pointer to NULL
 * @param reading pointer to reading from previous step
 * @retval true if no error
 * @retval false if reading get NULL
 */
bool post_adm1278_current_read(uint8_t sensor_num, void *args, int *reading)
{
	if (!reading)
		return false;
	ARG_UNUSED(args);

	sensor_val *sval = (sensor_val *)reading;
	float val = (float)sval->integer + (sval->fraction / 1000.0);

	val = ADJUST_ADM1278_CURRENT(val);
	sval->integer = (int)val & 0xFFFF;
	sval->fraction = (val - sval->integer) * 1000;
	return true;
}
