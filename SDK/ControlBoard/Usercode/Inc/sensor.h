/********************************************************************************
 * @file    sensor.hpp
 * @brief   This file contains all the function prototypes for
 *          the sensor.cpp file
 *******************************************************************************/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "adc.h"

void Isense_Start(void);
void Vsense_Start(void);
void IL_Start(void);
void ADC_Calibration(void);

extern uint16_t Isense_data[];
extern uint16_t Vsense_data[];
extern uint16_t IL_data;

#ifdef __cplusplus
}
#endif
