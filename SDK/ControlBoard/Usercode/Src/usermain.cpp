#include <usermain.h>
#include "main.h"
#include <led.hpp>
#include <mospwm.hpp>
#include <button.hpp>
#include "FreeRTOS.h"
#include "task.h"
#include <sensor.hpp>
#include <os_printf.h>

using namespace std;
void StartDefaultTask(void const *argument)
{
    // double DutyA = 0.500;
    // double DutyB = 0.500;
    // PWMA.SetDuty(DutyA);
    // PWMA.PWM_ON();
    // PWMB.SetDuty(DutyB);
    // PWMB.PWM_ON();
    ADC_Calibration();
    // Isense_Start();
    // Vsense_Start();
    // IL_Start();

    while (true) {
        // os_printf("%d %d\n", Isense_data[0], Isense_data[1]);
        //  os_printf("%d %d\n", Vsense_data[0], Vsense_data[1]);
        // os_printf("%d\n", cnt);
        //  os_printf("1\n");
        vTaskDelay(500);
    }

    vTaskDelete(nullptr);
}
