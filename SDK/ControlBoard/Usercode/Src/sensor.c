/********************************************************************************
 * @file    sensor.cpp
 * @brief   This file provides code for the configuration
 *          of ADC.
 *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "sensor.h"

uint16_t Isense_data[2];
uint16_t Vsense_data[2];
uint16_t IL_data[2];

void Isense_Start(void)
{
    HAL_TIM_Base_Start(&htim1);
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)Isense_data, 2);
}

void Vsense_Start(void)
{
    HAL_TIM_Base_Start(&htim1);
    HAL_ADC_Start_DMA(&hadc2, (uint32_t *)Vsense_data, 2);
}

void IL_Start(void)
{
    HAL_TIM_Base_Start(&htim1);
    HAL_ADC_Start_DMA(&hadc3, (uint32_t *)IL_data, 2);
}

void ADC_Calibration(void)
{
    HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
    HAL_ADCEx_Calibration_Start(&hadc2, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
    HAL_ADCEx_Calibration_Start(&hadc3, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
}

void ADC_Calibration_working(void);