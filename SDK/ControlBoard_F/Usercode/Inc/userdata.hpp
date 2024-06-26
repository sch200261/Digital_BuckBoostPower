/********************************************************************************
 * @file    userdata.hpp
 * @brief   This file contains all the function prototypes for
 *          the userdata.cpp file
 *******************************************************************************/

#pragma once

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <samping.h>
#include <butterworth.hpp>
/* Includes End --------------------------------------------------------------*/

/* Typedef -------------------------------------------------------------------*/
/* Typedef End ---------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/
#define CURRENT_SENSOR_R 0.003
#define VOLTAGE_SENSOR_R 75.00
/* Define End ----------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/
/* Macro End -----------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/

/* Variables End -------------------------------------------------------------*/

/* Class ---------------------------------------------------------------------*/

/// @brief 浮点电压数据类
class Voltage_RealValue
{
private:
    const uint16_t *ptrData;
    Butter_LP_5_20_40dB_5000Hz<double> filter;

public:
    double RealValue;
    Voltage_RealValue(uint16_t *ptrData)
        : ptrData(ptrData){};

    /// @brief 将ADC原始数据转换为浮点值，应在ADC转换回调函数中使用
    /// @param  void
    void Convert_RealValue(void)
    {
        RealValue = filter.Step(*ptrData * VOLTAGE_SENSOR_R / 65535.000);
    }

    /// @brief 将ADC原始数据转换为浮点值（带线性校准），应在ADC转换回调函数中使用
    /// @param _k 线性校准的斜率
    /// @param _b 线性校准的截距
    void Convert_RealValue_Line_cali(double _k, double _b)
    {
        RealValue = filter.Step(*ptrData * VOLTAGE_SENSOR_R / 65535.000 * _k + _b);
    }
};

/// @brief 浮点电流数据类
class Current_RealValue
{
private:
    const uint16_t *ptrData;
    Butter_LP_5_50_20dB_1000Hz<double> filter;

public:
    double RealValue;
    Current_RealValue(uint16_t *ptrData)
        : ptrData(ptrData){};

    /// @brief 将ADC原始数据转换为浮点值，应在ADC转换回调函数中使用
    /// @param  void
    void Convert_RealValue(void)
    {
        RealValue = filter.Step((*ptrData / 65535.0 - 0.5000) * 0.165 / CURRENT_SENSOR_R);
    }

    /// @brief 将ADC原始数据转换为浮点值（带线性校准），应在ADC转换回调函数中使用
    /// @param _k 线性校准的斜率
    /// @param _b 线性校准的截距
    void Convert_RealValue_Line_cali(double _k, double _b)
    {
        RealValue = filter.Step(((*ptrData / 65535.0 - 0.5000) * 0.165 / CURRENT_SENSOR_R) * _k + _b);
    }
};

/// @brief 温度数据类
class Temperture_RealValue
{
private:
    const uint16_t *ptrData;

public:
    double RealValue;
    Temperture_RealValue(uint16_t *ptrData)
        : ptrData(ptrData){};

    /// @brief 将ADC原始数据转换为温度，单位Celsius
    /// @param  void
    void Convert_RealValue(void)
    {
        RealValue = __HAL_ADC_CALC_TEMPERATURE(3300, *ptrData, ADC_RESOLUTION_16B);
    }
};

/// @brief 输入电压
extern Voltage_RealValue Vin;
/// @brief 输出电压
extern Voltage_RealValue Vout;
/// @brief 输入电流
extern Current_RealValue Iin;
/// @brief 输出电流
extern Current_RealValue Iout;
/// @brief 电感电流
extern Current_RealValue IL;

extern bool Key1_state;
extern bool Key2_state;
extern bool Key3_state;

extern double exp_voltage;
extern double exp_current;

extern bool Control_Enable;

/* Class End -----------------------------------------------------------------*/
