#ifndef PDR_H
#define PDR_H

#include <stdbool.h>
#include <stdint.h>

extern uint32_t pdr_count;
extern uint16_t pdr_config_size;
uint8_t pdr_init(void);

typedef struct _PDR_numeric_sensor_ {
	/*** PDR common header***/
	uint32_t recordHandle;
	uint8_t PDRHeaderVersion;
	uint8_t PDRType;
	uint16_t recordChangeNumber;
	uint16_t dataLength;

	/***numeric sensor format***/
	uint16_t PLDMTerminusHandle;
	uint16_t sensorId;
	uint16_t entityType;
	uint16_t entityInstanceNumber;
	uint16_t containerId;
	uint8_t sensorInit;
	uint8_t sensorAuxiliaryNamesPDR;
	uint8_t baseUnit;
	int8_t unitModifier;
	uint8_t rateUnit;
	uint8_t baseOEMUnitHandle;
	uint8_t auxUnit;
	int8_t auxUnitModifier;
	uint8_t auxrateUnit;
	uint8_t rel;
	uint8_t auxOEMUnitHandle;
	uint8_t isLinear;
	uint8_t sensorDataSize;
	int32_t resolution;
	int32_t offset;
	uint16_t accuracy;
	uint8_t plusTolerance;
	uint8_t minusTolerance;
	uint8_t hysteresis;
	uint8_t supportedThresholds;
	uint8_t thresholdAndHysteresisVolatility;
	int32_t stateTransitionInterval;
	int32_t updateInterval;
	uint32_t maxReadable;
	uint32_t minReadable;
	uint8_t rangeFieldFormat;
	uint8_t rangeFieldSupport;
	uint32_t nominalValue;
	uint32_t normalMax;
	uint32_t normalMin;
	uint32_t warningHigh;
	uint32_t warningLow;
	uint32_t criticalHigh;
	uint32_t criticalLow;
	uint32_t fatalHigh;
	uint32_t fatalLow;
} PDR_numeric_sensor;

extern PDR_numeric_sensor *numeric_sensor_table;
uint8_t plat_get_pdr_size();

#endif
