/********************************************************************************
 * @file    userdata.hpp
 * @brief   This file contains all the function prototypes for
 *          the userdata.cpp file
 *******************************************************************************/

#pragma once

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define ISENSOR_REF 32767.5

#define ISENSOR_K   0.0007193538894156885
#define VSENSOR_K   0.0011444077210651

class ADC_data
{
private:
    const uint16_t *ptr_Data;
    const bool isIsensor;

public:
    ADC_data(uint16_t *ptr_Data, bool isIsensor)
        : ptr_Data(ptr_Data), isIsensor(isIsensor){};
    double get_RealValue(void)
    {
        if (isIsensor) {
            return ((double)(*ptr_Data - ISENSOR_REF) * ISENSOR_K);
        } else {
            return ((double)(*ptr_Data) * VSENSOR_K);
        }
    }
};
