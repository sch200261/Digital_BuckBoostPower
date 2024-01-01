/********************************************************************************
 * @file    usermain.hpp
 * @brief   This file contains all the function prototypes for
 *          the usermain.cpp file
 *******************************************************************************/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <led.hpp>
#include <mospwm.hpp>
#include <button.hpp>
#include <samping.h>
#include <lcd.h>

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cstdio"
#include <adc.h>
/* Includes End --------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/
/* Variables End -------------------------------------------------------------*/

/* Class ---------------------------------------------------------------------*/
/* Class End -----------------------------------------------------------------*/

/* Function ------------------------------------------------------------------*/

/// @brief FREERTOS线程入口函数
/// @param argument 传入函数
void StartDefaultTask(void const *argument);

/* Function End --------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif
