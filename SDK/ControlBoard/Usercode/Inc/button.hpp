/********************************************************************************
 * @file    button.hpp
 * @brief   This file contains all the function prototypes for
 *          the button.cpp file
 *******************************************************************************/

#pragma once

/* Includes ------------------------------------------------------------------*/
#include "main.h"

class Button // 按钮类声明
{

public:
    const GPIO_TypeDef *GPIOx;             // GPIO组
    const uint16_t GPIO_Pin;               // GPIO引脚
    const GPIO_PinState button_down_level; // 默认有效电平

    Button(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState button_down_level = GPIO_PIN_RESET)
        : GPIOx(GPIOx), GPIO_Pin(GPIO_Pin), button_down_level(button_down_level){};

    bool IsButtonDown() const // 判断按钮是否按下，返回bool变量
    {
        if (button_down_level == GPIO_PIN_RESET) {
            return GetLevel() == GPIO_PIN_RESET;
        } else {
            return GetLevel() == GPIO_PIN_SET;
        }
    }

    GPIO_PinState GetLevel() const // 获取引脚电平，返回电平状态
    {
        return HAL_GPIO_ReadPin((GPIO_TypeDef *)GPIOx, GPIO_Pin);
    }
};

extern Button Btn1;
extern Button Btn2;
extern Button Btn3;
