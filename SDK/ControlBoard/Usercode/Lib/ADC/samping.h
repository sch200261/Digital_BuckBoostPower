/********************************************************************************
 * @file    samping.hpp
 * @brief   This file contains all the function prototypes for
 *          the samping.cpp file
 *******************************************************************************/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "adc.h"

void Isamping_Start(void);
void Vsamping_Start(void);
void IL_Start(void);
void ADC_Calibration(void);

extern uint16_t Isamping_data[];
extern uint16_t Vsamping_data[];
extern uint16_t IL_data[];

#ifdef __cplusplus
}
#endif
