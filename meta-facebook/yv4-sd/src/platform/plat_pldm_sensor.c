/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <logging/log.h>
#include "pmbus.h"
#include "ast_adc.h"
#include "pldm_sensor.h"
#include "sensor.h"
#include "plat_pdr_table.h"
#include "plat_hook.h"
#include "plat_pldm_sensor.h"

LOG_MODULE_REGISTER(plat_pldm_sensor);

static struct pldm_sensor_thread pal_pldm_sensor_thread[] = {
	// thread id, thread name
	{ ADC_SENSOR_THREAD_ID, "ADC_PLDM_SENSOR_THREAD" },
	//{ VR_SENSOR_THREAD_ID, "VR_PLDM_SENSOR_THREAD" },
};

static struct pldm_sensor_info adc_sensor[] = {
	{
		.pdr_numeric_sensor = &pdr_numeric_adc_table[0],
		.update_time = 0,
		.pldm_sensor_cfg.num = 0,
		.pldm_sensor_cfg.type = sensor_dev_ast_adc,
		.pldm_sensor_cfg.port = ADC_PORT0,
		.pldm_sensor_cfg.access_checker = stby_access,
		.pldm_sensor_cfg.sample_count = SAMPLE_COUNT_DEFAULT,
		.pldm_sensor_cfg.arg0 = 66,
		.pldm_sensor_cfg.arg1 = 10,
		.pldm_sensor_cfg.init_args = &adc_asd_init_args[0],
		.pldm_sensor_cfg.cache = 0,
		.pldm_sensor_cfg.cache_status = PLDM_SENSOR_INITIALIZING,
	},
};

/*static struct pldm_sensor_info vr_sensor[] = {
	{
		.pdr_numeric_sensor = &pdr_numeric_vr_table[0],
		.update_time = 0,
		.pldm_sensor_cfg.num = 0,
		.pldm_sensor_cfg.type = sensor_dev_tps53689,
		.pldm_sensor_cfg.port = 0x04,
		.pldm_sensor_cfg.target_addr = (0xC4 >> 1),
		.pldm_sensor_cfg.offset = PMBUS_READ_VOUT,
		.pldm_sensor_cfg.access_checker = vr_access,
		.pldm_sensor_cfg.sample_count = SAMPLE_COUNT_DEFAULT,
		.pldm_sensor_cfg.pre_sensor_read_hook = pre_isl69259_read,
		.pldm_sensor_cfg.pre_sensor_read_args = &isl69259_pre_read_args[0],
		.pldm_sensor_cfg.cache = 0,
		.pldm_sensor_cfg.cache_status = PLDM_SENSOR_INITIALIZING,
	},
};*/

pldm_sensor_thread * plat_load_pldm_sensor_thread()
{
	return pal_pldm_sensor_thread;
}

int plat_load_pldm_sensor(int thread_id, pldm_sensor_info *pldm_sensor_list)
{
	int ret = 0;

	CHECK_NULL_ARG_WITH_RETURN(pldm_sensor_list, -1);

	switch (thread_id) {
		case ADC_SENSOR_THREAD_ID:
			memcpy(pldm_sensor_list, &adc_sensor, sizeof(adc_sensor));
			break;
		/*case VR_SENSOR_THREAD_ID:
			memcpy(pldm_sensor_list, &vr_sensor, sizeof(vr_sensor));
			break;*/
		default:
			ret = -1;
			LOG_ERR("Unknow pldm sensor thread id %d", thread_id);
			break;
	}

	return ret;
}

int plat_get_pldm_sensor_count(int thread_id)
{
	int count = 0;

	switch (thread_id) {
		case ADC_SENSOR_THREAD_ID:
			count = ARRAY_SIZE(adc_sensor);
			break;
		/*case VR_SENSOR_THREAD_ID:
			count = ARRAY_SIZE(vr_sensor);
			break;*/
		default:
			count = -1;
			LOG_ERR("Unknow pldm sensor thread id %d", thread_id);
			break;
	}

	return count;
}

