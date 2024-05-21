/********************************************************************************
 * @file    user_irq.cpp
 * @brief   This file provides code for the configuration
 *          of all used callback function.
 *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <main.h>
#include <cstdio>
#include "tim.h"
#include <adc.h>
#include <userdata.hpp>
#include <usermain.hpp>
#include <button.hpp>
#include <mospwm.hpp>
#include <led.hpp>
/* Includes End --------------------------------------------------------------*/

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc == &hadc1) {
        Iin.Convert_RealValue();
        Iout.Convert_RealValue();
    }
    if (hadc == &hadc2) {
        Vin.Convert_RealValue();
        Vout.Convert_RealValue();
        Powermain();
    }
    if (hadc == &hadc3) {
        IL.Convert_RealValue();
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    /* Prevent unused argument(s) compilation warning */
    if (htim == &htim7) {
        Key1_state = Btn1.IsButtonDown();
        Key2_state = Btn2.IsButtonDown();
        Key3_state = Btn3.IsButtonDown();
        if (Key1_state) {
            LedMain.SetColor(ColorError);
            PWMA.SetDuty(0.000);
            PWMB.SetDuty(0.000);
            PWMA.PWM_OFF();
            PWMB.PWM_OFF();
        }
    }

    if (htim == &htim2) {
        if (Vin.RealValue > 70.0 || Vout.RealValue > 70.0 || abs(Iin.RealValue) > 5.0 || abs(IL.RealValue) > 5.0 || abs(Iout.RealValue) > 5.0) {
            LedMain.SetColor(ColorError);
            PWMA.SetDuty(0.000);
            PWMB.SetDuty(0.000);
            PWMA.PWM_OFF();
            PWMB.PWM_OFF();
        }
    }

    /* NOTE : This function should not be modified, when the callback is needed,
              the HAL_TIM_PeriodElapsedCallback could be implemented in the user file
     */
}