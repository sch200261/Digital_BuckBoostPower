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
#include <fdcan.h>
#include <canbus.hpp>
/* Includes End --------------------------------------------------------------*/

bool Control_Enable = false;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc == &hadc1) {
        Iin.Convert_RealValue();
        Iout.Convert_RealValue();
    }
    if (hadc == &hadc2) {
        Vin.Convert_RealValue_Line_cali(1.0068, 0.1355);
        Vout.Convert_RealValue_Line_cali(1.0535, -0.5445);
        if (Control_Enable == true)
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
        if (Key2_state) {
            Control_Enable = true;
            LedMain.SetColor(ColorNormal);
        }
        if (Key3_state) {
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

    /* NOTE : This function should not be modified, when the callback is needed,
              the HAL_TIM_IC_CaptureCallback could be implemented in the user file
     */
}

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hfdcan);
    if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET) {
        FDCAN_Get_Msg();
        set_exp_vol();
        FDCAN_Send_Msg();
    }
    // UNUSED(RxFifo0ITs);

    /* NOTE: This function Should not be modified, when the callback is needed,
              the HAL_FDCAN_RxFifo0Callback could be implemented in the user file
     */
}
