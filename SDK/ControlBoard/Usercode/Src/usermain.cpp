#include <usermain.h>
#include "main.h"
#include <led.hpp>
#include <mospwm.hpp>
#include <button.hpp>
#include "FreeRTOS.h"
#include "task.h"

using namespace std;
void StartDefaultTask(void const *argument)
{
    double DutyA = 0.500;
    double DutyB = 0.500;
    PWMA.SetDuty(DutyA);
    PWMA.PWM_ON();
    PWMB.SetDuty(DutyB);
    PWMB.PWM_ON();

    while (true) {

        vTaskDelay(1000);
    }

    vTaskDelete(nullptr);
}
