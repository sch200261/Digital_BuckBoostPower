#include <usermain.h>
#include "main.h"
#include <led.hpp>
#include <mospwm.hpp>
#include "FreeRTOS.h"
#include "task.h"

using namespace std;
void StartDefaultTask(void const *argument)
{
    LedMain.LED_ON();
    PWMA.SetDuty(0.5000);
    PWMA.PWM_ON();
    PWMB.SetDuty(0.2000);
    PWMB.PWM_ON();
    while (true) {
        LedMain.SetColor(ColorInit);
        vTaskDelay(1000);
        LedMain.SetColor(ColorWarning);
        vTaskDelay(1000);
    }

    vTaskDelete(nullptr);
}
