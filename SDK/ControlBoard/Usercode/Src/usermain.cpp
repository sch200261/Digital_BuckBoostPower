#include <usermain.hpp>

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
    // Isamping_Start();
    // Vsamping_Start();
    // IL_Start();

    // LCD_Start();

    while (true) {

        

        vTaskDelay(500);
    }

    vTaskDelete(nullptr);
}
