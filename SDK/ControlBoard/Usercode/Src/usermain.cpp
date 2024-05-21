/********************************************************************************
 * @file    usermain.cpp
 * @brief   This file provides code for the configuration
 *          of usermain.
 *******************************************************************************/
using namespace std;
/* Includes ------------------------------------------------------------------*/
#include <usermain.hpp>
/* Includes End --------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/
/* Variables End -------------------------------------------------------------*/

/* Class ---------------------------------------------------------------------*/
/* Class End -----------------------------------------------------------------*/

/* Function ------------------------------------------------------------------*/

void StartDefaultTask(void const *argument)
{
    // LED测试
    LedMain.SetColor(ColorInit);
    LedMain.LED_ON();

    // PWM测试
    double DutyA = 0.500;
    double DutyB = 0.900;
    PWMA.SetDuty(DutyA);
    PWMB.SetDuty(DutyB);
    PWMA.PWM_ON();
    PWMB.PWM_ON();
    vTaskDelay(1);

    // ADC测试
    ADC_Trigger_TIM_Base_Start();
    ADC_Calibration(Cail_ADCALL);
    vTaskDelay(10);
    Current_samping_Start();
    Voltage_samping_Start();
    IL_samping_Start();
    vTaskDelay(1);

    // LCD测试
    LCD_Start();
    vTaskDelay(1);

    while (true) {
        printf("Vin:%lfV  Vout:%lfV  Iin:%lfA  Iout:%lfA  IL: %lfA\n", Vin.RealValue, Vout.RealValue, Iin.RealValue, Iout.RealValue, IL.RealValue);
        // printf("Vin:%d  Vout:%d  Iin:%d  Iout:%d  IL: %d\n", Voltage_data[0], Voltage_data[1], Current_data[0], Current_data[1], IL_data[0]);
        vTaskDelay(100);
    }

    vTaskDelete(nullptr);
}

/* Function End --------------------------------------------------------------*/
