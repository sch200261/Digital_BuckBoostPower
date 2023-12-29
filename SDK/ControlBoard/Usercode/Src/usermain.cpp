#include <usermain.h>
#include <led.hpp>
#include <mospwm.hpp>
#include <button.hpp>
#include <sensor.h>
#include <lcd.h>

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cstdio"
#include <adc.h>

using namespace std;
void StartDefaultTask(void const *argument)
{
    // double DutyA = 0.400;
    // double DutyB = 0.700;
    // PWMA.SetDuty(DutyA);
    // PWMA.PWM_ON();
    // PWMB.SetDuty(DutyB);
    // PWMB.PWM_ON();

    // ADC_Calibration();
    // Isense_Start();
    // Vsense_Start();
    // IL_Start();
    LCD_Test();

    while (true) {

        // printf("%d %d\n", Isense_data[0], Isense_data[1]);
        // printf("%d %d\n", Vsense_data[0], Vsense_data[1]);
        // printf("%d %d\n", IL_data[0], IL_data[1]);
        // printf("Temp: %d °C\n", __HAL_ADC_CALC_TEMPERATURE(3300, IL_data[1], ADC_RESOLUTION_16B));
        // printf("%d\n", cnt);
        // printf("1\n");

        vTaskDelay(500);
    }

    vTaskDelete(nullptr);
}
