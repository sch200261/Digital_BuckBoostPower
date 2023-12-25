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
        vTaskDelay(1000);
    }

    vTaskDelete(nullptr);
}
