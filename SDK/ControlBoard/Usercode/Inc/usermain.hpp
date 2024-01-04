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
#include <userdata.hpp>

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cstdio"
#include "adc.h"
/* Includes End --------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/
/* Variables End -------------------------------------------------------------*/

/* Class ---------------------------------------------------------------------*/
/* Class End -----------------------------------------------------------------*/

/* Function ------------------------------------------------------------------*/

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc == &hadc1) {
        Iin.Convert_RealValue();
        Iout.Convert_RealValue();
    }
    if (hadc == &hadc2) {
        Vin.Convert_RealValue();
        Vout.Convert_RealValue();
    }
    if (hadc == &hadc3) {
        IL.Convert_RealValue();
    }
}

/// @brief FREERTOS线程入口函数
/// @param argument 传入函数
void StartDefaultTask(void const *argument);

/* Function End --------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif
