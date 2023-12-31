/********************************************************************************
 * @file    led.cpp
 * @brief   This file provides code for the configuration
 *          of 5050 LED.
 *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "led.hpp"

Led LedMain(TIM_CHANNEL_3, TIM_CHANNEL_2, TIM_CHANNEL_4, &htim4);

Color ColorError(255, 0, 0);
Color ColorNormal(0, 50, 0);
Color ColorInit(25, 25, 75);
Color ColorWarning(255, 50, 0);
