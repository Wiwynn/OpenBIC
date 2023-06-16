#include "plat_pdr_table.h"

#include <stdio.h>
#include <string.h>

#include "pdr.h"
#include "sensor.h"
#include "plat_class.h"
#include "plat_ipmb.h"
#include "plat_sensor_table.h"
#include <logging/log.h>

LOG_MODULE_REGISTER(plat_pdr_table);

PDR_numeric_sensor plat_pdr_table[] = {
	{
		// P12V STBY ADC voltage
		/*** PDR common header***/
		0x00000000, //uint32_t recordHandle
		0x01, //uint8_t PDRHeaderVersion
		0x02, //uint8_t PDRType
		0x0000, //uint16_t recordChangeNumber
		0x0000, //uint16_t dataLength

		/***numeric sensor format***/
		0x1000, //uint16_t PLDMTerminusHandle;
		0x0020, //uint16_t sensorId;
		0x8801, //uint16_t entityType;
		0x1000, //uint16_t entityInstanceNumber;
		0x0000, //uint16_t containerId;
		0x00, //uint8_t sensorInit;
		0x00, //uint8_t sensorAuxiliaryNamesPDR;
		0x05, //uint8_t baseUnit;
		0x00, //int8_t unitModifier;
		0x00, //uint8_t rateUnit;
		0x00, //uint8_t baseOEMUnitHandle;
		0x00, //uint8_t auxUnit;
		0x00, //int8_t auxUnitModifier;
		0x00, //uint8_t auxrateUnit;
		0x00, //uint8_t rel;
		0x00, //uint8_t auxOEMUnitHandle;
		0x00, //uint8_t isLinear;
		0x04, //uint8_t sensorDataSize;
		0x00000000, //int32_t resolution;
		0x00000000, //int32_t offset;
		0x0000, //uint16_t accuracy;
		0x00, //uint8_t plusTolerance;
		0x00, //uint8_t minusTolerance;
		0x00, //uint8_t hysteresis;
		0x3F, //uint8_t supportedThresholds;
		0x00, //uint8_t thresholdAndHysteresisVolatility;
		0x00000000, //int32_t stateTransitionInterval;
		0x00000000, //int32_t updateInterval;
		0x00000000, //uint32_t maxReadable;
		0x00000000, //uint32_t minReadable;
		0x04, //uint8_t rangeFieldFormat;
		0x7F, //uint8_t rangeFieldSupport;
		0x00000000, //uint32_t nominalValue;
		0x00000000, //uint32_t normalMax;
		0x00000000, //uint32_t normalMin;
		0x0890000D, //uint32_t warningHigh;
		0x2000000A, //uint32_t warningLow;
		0x0DA0000A, //uint32_t criticalHigh;
		0x1BB0000A, //uint32_t criticalLow;
		0x014D000E, //uint32_t fatalHigh;
		0x005B000A, //uint32_t fatalLow;
	},
	{
		// PVCCFA_EHV VR voltage
		/*** PDR common header***/
		0x00000000, //uint32_t recordHandle
		0x01, //uint8_t PDRHeaderVersion
		0x02, //uint8_t PDRType
		0x0000, //uint16_t recordChangeNumber
		0x0000, //uint16_t dataLength

		/***numeric sensor format***/
		0x1000, //uint16_t PLDMTerminusHandle;
		0x002D, //uint16_t sensorId;
		0x8801, //uint16_t entityType;
		0x1000, //uint16_t entityInstanceNumber;
		0x0000, //uint16_t containerId;
		0x00, //uint8_t sensorInit;
		0x00, //uint8_t sensorAuxiliaryNamesPDR;
		0x05, //uint8_t baseUnit;
		0x00, //int8_t unitModifier;
		0x00, //uint8_t rateUnit;
		0x00, //uint8_t baseOEMUnitHandle;
		0x00, //uint8_t auxUnit;
		0x00, //int8_t auxUnitModifier;
		0x00, //uint8_t auxrateUnit;
		0x00, //uint8_t rel;
		0x00, //uint8_t auxOEMUnitHandle;
		0x00, //uint8_t isLinear;
		0x04, //uint8_t sensorDataSize;
		0x00000000, //int32_t resolution;
		0x00000000, //int32_t offset;
		0x0000, //uint16_t accuracy;
		0x00, //uint8_t plusTolerance;
		0x00, //uint8_t minusTolerance;
		0x00, //uint8_t hysteresis;
		0x06, //uint8_t supportedThresholds;
		0x00, //uint8_t thresholdAndHysteresisVolatility;
		0x00000000, //int32_t stateTransitionInterval;
		0x00000000, //int32_t updateInterval;
		0x00000000, //uint32_t maxReadable;
		0x00000000, //uint32_t minReadable;
		0x04, //uint8_t rangeFieldFormat;
		0x7F, //uint8_t rangeFieldSupport;
		0x00000000, //uint32_t nominalValue;
		0x00000000, //uint32_t normalMax;
		0x00000000, //uint32_t normalMin;
		0x0001036E, //uint32_t warningHigh;
		0x000102CA, //uint32_t warningLow;
		0x00010380, //uint32_t criticalHigh;
		0x00010289, //uint32_t criticalLow;
		0x00020002, //uint32_t fatalHigh;
		0x00000004, //uint32_t fatalLow;
	},
	{
		// TMP75 on board temperature
		/*** PDR common header***/
		0x00000000, //uint32_t recordHandle
		0x01, //uint8_t PDRHeaderVersion
		0x02, //uint8_t PDRType
		0x0000, //uint16_t recordChangeNumber
		0x0000, //uint16_t dataLength

		/***numeric sensor format***/
		0x1000, //uint16_t PLDMTerminusHandle;
		0x0001, //uint16_t sensorId;
		0x8801, //uint16_t entityType;
		0x1000, //uint16_t entityInstanceNumber;
		0x0000, //uint16_t containerId;
		0x00, //uint8_t sensorInit;
		0x00, //uint8_t sensorAuxiliaryNamesPDR;
		0x02, //uint8_t baseUnit;
		0x00, //int8_t unitModifier;
		0x00, //uint8_t rateUnit;
		0x00, //uint8_t baseOEMUnitHandle;
		0x00, //uint8_t auxUnit;
		0x00, //int8_t auxUnitModifier;
		0x00, //uint8_t auxrateUnit;
		0x00, //uint8_t rel;
		0x00, //uint8_t auxOEMUnitHandle;
		0x00, //uint8_t isLinear;
		0x04, //uint8_t sensorDataSize;
		0x00000000, //int32_t resolution;
		0x00000000, //int32_t offset;
		0x0000, //uint16_t accuracy;
		0x00, //uint8_t plusTolerance;
		0x00, //uint8_t minusTolerance;
		0x00, //uint8_t hysteresis;
		0x06, //uint8_t supportedThresholds;
		0x00, //uint8_t thresholdAndHysteresisVolatility;
		0x00000000, //int32_t stateTransitionInterval;
		0x00000000, //int32_t updateInterval;
		0x00000000, //uint32_t maxReadable;
		0x00000000, //uint32_t minReadable;
		0x04, //uint8_t rangeFieldFormat;
		0x29, //uint8_t rangeFieldSupport;
		0x00000000, //uint32_t nominalValue;
		0x00000000, //uint32_t normalMax;
		0x00000000, //uint32_t normalMin;
		0x00000000, //uint32_t warningHigh;
		0x00000000, //uint32_t warningLow;
		0x00000000, //uint32_t criticalHigh;
		0x00340000, //uint32_t criticalLow;
		0x00960000, //uint32_t fatalHigh;
		0x00000000, //uint32_t fatalLow;
    },
};

const int PDR_TABLE_SIZE = ARRAY_SIZE(plat_pdr_table);

void load_pdr_table(void)
{
	memcpy(numeric_sensor_table, plat_pdr_table, sizeof(plat_pdr_table));
	pdr_count = PDR_TABLE_SIZE;
}
