/********************************************************************************
 * @file    usermain.cpp
 * @brief   This file provides code for the configuration
 *          of usermain.
 *******************************************************************************/
using namespace std;
/* Includes ------------------------------------------------------------------*/
#include <usermain.hpp>
#include <userdata.hpp>
#include <cstdio>
#include <mospwm.hpp>
#include <samping.h>
#include <led.hpp>
#include <lcd.h>
/* Includes End --------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/
/* Variables End -------------------------------------------------------------*/

/* Class ---------------------------------------------------------------------*/
/* Class End -----------------------------------------------------------------*/

/* Function ------------------------------------------------------------------*/

void Usermain()
{
    HAL_TIM_Base_Start(&htim3);
    HAL_TIM_Base_Start(&htim4);
    HAL_TIM_Base_Start_IT(&htim2);
    HAL_TIM_Base_Start_IT(&htim7);

    // LED测试
    LedMain.SetColor(ColorInit);
    LedMain.LED_ON();

    // LCD测试
    LCD_Start();
    HAL_Delay(1);

    // PWM测试
    double DutyA = 0.500;
    double DutyB = 0.900;
    PWMA.SetDuty(DutyA);
    PWMB.SetDuty(DutyB);
    PWMA.PWM_ON();
    PWMB.PWM_ON();

    // ADC测试
    ADC_Trigger_TIM_Base_Start();
    ADC_Calibration(Cail_ADCALL);
    HAL_Delay(10);
    Current_samping_Start();
    Voltage_samping_Start();
    IL_samping_Start();

    while (1) {
        // printf("Vin:%d  Vout:%d  Iin:%d  Iout:%d  IL: %d\n", Voltage_data[0], Voltage_data[1], Current_data[0], Current_data[1], IL_data[0]);
        printf("Vin:%lfV  Vout:%lfV  Iin:%lfA  Iout:%lfA  IL: %lfA\n", Vin.RealValue, Vout.RealValue, Iin.RealValue, Iout.RealValue, IL.RealValue);
        HAL_Delay(10);
    }
}

void Powermain()
{
}

/* Function End --------------------------------------------------------------*/
