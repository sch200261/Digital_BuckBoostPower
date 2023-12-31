/********************************************************************************
 * @file    button.hpp
 * @brief   This file contains all the function prototypes for
 *          the button.cpp file
 *******************************************************************************/

#pragma once

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/// @brief 按钮类声明
class Button
{

public:
    const GPIO_TypeDef *GPIOx;             // GPIO组
    const uint16_t GPIO_Pin;               // GPIO引脚
    const GPIO_PinState button_down_level; // 默认有效电平

    Button(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState button_down_level = GPIO_PIN_RESET)
        : GPIOx(GPIOx), GPIO_Pin(GPIO_Pin), button_down_level(button_down_level)
    {
    }

    /// @brief 判断按钮是否按下，返回bool变量
    /// @return bool true为按下，false为未按下
    bool IsButtonDown() const
    {
        if (button_down_level == GPIO_PIN_RESET) {
            return GetLevel() == GPIO_PIN_RESET;
        } else {
            return GetLevel() == GPIO_PIN_SET;
        }
    }

    /// @brief 获取引脚电平，返回电平状态
    /// @return GPIO_PinState 电平状态 GPIO_PIN_RESET为低，GPIO_PIN_SET为高
    GPIO_PinState GetLevel() const
    {
        return HAL_GPIO_ReadPin((GPIO_TypeDef *)GPIOx, GPIO_Pin);
    }
};

extern Button Btn1;
extern Button Btn2;
extern Button Btn3;
