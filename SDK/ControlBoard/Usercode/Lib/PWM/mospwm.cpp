/********************************************************************************
 * @file    mospwm.cpp
 * @brief   This file provides code for the configuration
 *          of mospwm.
 *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <mospwm.hpp>
/* Includes End --------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/
/* Variables End -------------------------------------------------------------*/

/* Class ---------------------------------------------------------------------*/
/// @brief 左半桥互补PWM
CoPWM PWMA(&htim1, TIM_CHANNEL_1, 600);
/// @brief 右半桥互补PWM
CoPWM PWMB(&htim1, TIM_CHANNEL_2, 600);
/* Class End -----------------------------------------------------------------*/

/* Function ------------------------------------------------------------------*/
/* Function End --------------------------------------------------------------*/
