/********************************************************************************
 * @file    samping.c
 * @brief   This file provides code for the configuration
 *          of ADC.
 *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <samping.h>
/* Includes End --------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/

/// @brief 电流采样数据
uint16_t Current_data[2];

/// @brief 电压采样数据
uint16_t Voltage_data[2];

/// @brief 电感电流数据:0为电感电流 1为Core温度数据
uint16_t IL_data[2];

/* Variables End -------------------------------------------------------------*/

/* Function ------------------------------------------------------------------*/

void ADC_Trigger_TIM_Base_Start(void)
{
    HAL_TIM_Base_Start(&htim1);
}

void Current_samping_Start(void)
{
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)Current_data, 2);
}

void Voltage_samping_Start(void)
{
    HAL_ADC_Start_DMA(&hadc2, (uint32_t *)Voltage_data, 2);
}

void IL_samping_Start(void)
{
    HAL_ADC_Start_DMA(&hadc3, (uint32_t *)IL_data, 2);
}

void ADC_Calibration(enum Calibration_Type Type)
{
    switch (Type) {
        case Cail_ADC1:
            HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
            break;
        case Cail_ADC2:
            HAL_ADCEx_Calibration_Start(&hadc2, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
            break;
        case Cail_ADC3:
            HAL_ADCEx_Calibration_Start(&hadc3, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
            break;
        case Cail_ADCALL:
            HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
            HAL_ADCEx_Calibration_Start(&hadc2, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
            HAL_ADCEx_Calibration_Start(&hadc3, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
            break;
    }
}

/* Function End --------------------------------------------------------------*/
