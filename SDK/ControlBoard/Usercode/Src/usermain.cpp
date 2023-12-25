#include <usermain.h>
#include "main.h"
#include <led.hpp>
#include "FreeRTOS.h"
#include "task.h"

using namespace std;
void StartDefaultTask(void const *argument)
{
    LedMain.LED_ON();
    while (true) {
        LedMain.SetColor(ColorInit);
        vTaskDelay(1000);
        LedMain.SetColor(ColorWarning);
        vTaskDelay(1000);
    }

    vTaskDelete(nullptr);
}
