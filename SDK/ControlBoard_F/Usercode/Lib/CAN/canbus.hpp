/********************************************************************************
 * @file    canbus.hpp
 * @brief   This file contains all the function prototypes for
 *          the canbus.cpp file.
 *******************************************************************************/

#pragma once

#include "main.h"
#include <fdcan.h>
#include <cstdio>

void txHeader_init(void);
void rxFilter_init(void);
uint8_t FDCAN_Send_Msg(void);
uint8_t FDCAN_Get_Msg(void);
void set_exp_vol(void);
