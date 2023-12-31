/********************************************************************************
 * @file    usermain.hpp
 * @brief   This file contains all the function prototypes for
 *          the usermain.cpp file
 *******************************************************************************/

#pragma once

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

void StartDefaultTask(void const *argument);
