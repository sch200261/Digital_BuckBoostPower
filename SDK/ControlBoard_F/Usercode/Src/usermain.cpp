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
#include <pid_controller.hpp>
#include <butterworth.hpp>
#include <canbus.hpp>
/* Includes End --------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/
double Cur_Bias;
double Vol_Bias;
double Duty;
/* Variables End -------------------------------------------------------------*/

/* Class ---------------------------------------------------------------------*/
control_system::PIController<double> ILoopCtrl{0.005, 150, 0.00002};
control_system::PIController<double> VLoopCtrl{0.01, 1.5, 0.00002};
control_system::Saturation ILoopSaturation{0.1, 0.9};
control_system::Saturation VLoopSaturation{0.0, 5.0};

/* Class End -----------------------------------------------------------------*/

/* Function ------------------------------------------------------------------*/

void Usermain()
{
    HAL_TIM_Base_Start(&htim3);
    HAL_TIM_Base_Start(&htim4);
    HAL_TIM_Base_Start_IT(&htim2);
    HAL_TIM_Base_Start_IT(&htim7);

    Control_Enable = false;

    // LED测试
    LedMain.SetColor(ColorInit);
    LedMain.LED_ON();

    // LCD测试
    LCD_Start();
    HAL_Delay(1);

    // PWM测试
    double DutyA = 0.100;
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

    txHeader_init();
    rxFilter_init();
    HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
    HAL_Delay(10);
    HAL_FDCAN_Start(&hfdcan1);
    HAL_Delay(10);

    LedMain.SetColor(ColorWarning);

    while (1) {
        // printf("Vin:%d  Vout:%d  Iin:%d  Iout:%d  IL: %d\n", Voltage_data[0], Voltage_data[1], Current_data[0], Current_data[1], IL_data[0]);
        printf("%lf,%lf,%lf,%lf,%lf\n", Vin.RealValue, Vout.RealValue, IL.RealValue, Duty, exp_voltage);

        // FDCAN_Send_Msg();
        HAL_Delay(5);
    }
}

void Powermain()
{
    Vol_Bias    = exp_voltage - Vout.RealValue;
    exp_current = VLoopSaturation(VLoopCtrl.Step(Vol_Bias));
    Cur_Bias    = exp_current - IL.RealValue;
    Duty        = ILoopSaturation(ILoopCtrl.Step(Cur_Bias));
    PWMA.SetDuty(Duty);
    PWMB.SetDuty(0.9);

    // Cur_Bias    = exp_current - IL.RealValue;
    // Duty        = ILoopSaturation(ILoopCtrl.Step(Cur_Bias));
    // PWMA.SetDuty(Duty);
    // PWMB.SetDuty(0.9);
}

/* Function End --------------------------------------------------------------*/
