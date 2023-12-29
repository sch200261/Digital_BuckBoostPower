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

    ADC_Calibration();
    Isense_Start();
    Vsense_Start();
    IL_Start();

    LCD_Start();

    while (true) {

        

        vTaskDelay(500);
    }

    vTaskDelete(nullptr);
}
