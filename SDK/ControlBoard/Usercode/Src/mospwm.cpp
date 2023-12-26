/********************************************************************************
 * @file    mospwm.cpp
 * @brief   This file provides code for the configuration
 *          of mospwm.
 *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <mospwm.hpp>

CoPWM PWMA(&htim1, TIM_CHANNEL_1, 600);
CoPWM PWMB(&htim1, TIM_CHANNEL_2, 600);
