/********************************************************************************
 * @file    samping.h
 * @brief   This file contains all the function prototypes for
 *          the samping.c file
 *******************************************************************************/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "adc.h"
/* Includes End --------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/

/// @brief ADC偏差校准模式枚举
enum Calibration_Type {
    Cail_ADC1,
    Cail_ADC2,
    Cail_ADC3,
    Cail_ADCALL
};

extern uint16_t Current_data[];
extern uint16_t Voltage_data[];
extern uint16_t IL_data[];

/* Variables End -------------------------------------------------------------*/

/* Function ------------------------------------------------------------------*/

/// @brief 启动PWM触发定时器
/// @param  void 无
void ADC_Trigger_TIM_Base_Start(void);

/// @brief 启动电流采样通道
/// @param  void 无
void Current_samping_Start(void);

/// @brief 启动电压采样通道
/// @param  void 无
void Voltage_samping_Start(void);

/// @brief 启动电感电流采样通道
/// @param  void 无
void IL_samping_Start(void);

/// @brief 启动ADC偏差线性校准
/// @param @ref Cail_ADC1   校准ADC1
/// @param @ref Cail_ADC2   校准ADC2
/// @param @ref Cail_ADC3   校准ADC3
/// @param @ref Cail_ADCALL 校准ADCALL
void ADC_Calibration(enum Calibration_Type Type);

/* Function End --------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif
