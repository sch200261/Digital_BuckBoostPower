/********************************************************************************
 * @file    led.hpp
 * @brief   This file contains all the function prototypes for
 *          the led.cpp file
 *******************************************************************************/

#pragma once

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
/* Includes End --------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/
/* Variables End -------------------------------------------------------------*/

/* Class ---------------------------------------------------------------------*/

/// @brief 颜色类
class Color
{
public:
    const uint8_t R; // 红色亮度0-255
    const uint8_t G; // 绿色亮度0-255
    const uint8_t B; // 蓝色亮度0-255

    Color(uint8_t R, uint8_t G, uint8_t B)
        : R(R), G(G), B(B){};
};

/// @brief LED类
class Led
{
private:
    uint16_t Red   = 0;          // 红色比较值0-1199
    uint16_t Green = 0;          // 绿色比较值0-1199
    uint16_t Blue  = 0;          // 蓝色比较值0-1199
    uint32_t RedChannel;         // 红色PWM通道
    uint32_t GreenChannel;       // 绿色PWM通道
    uint32_t BlueChannel;        // 蓝色PWM通道
    TIM_HandleTypeDef *Redtim;   // 红色或三色LED定时器编号
    TIM_HandleTypeDef *Greentim; // 绿色LED定时器编号，不填视为与红色一致
    TIM_HandleTypeDef *Bluetim;  // 蓝色LED定时器编号，不填视为与红色一致
    bool LED_State = false;      // LED状态，true为亮

    void EnableLED(void)
    {
        this->LED_State = true;
    }

    void DisableLED(void)
    {
        this->LED_State = false;
    }

public:
    Led(uint32_t RedChannel, uint32_t GreenChannel, uint32_t BlueChannel, TIM_HandleTypeDef *Redtim, TIM_HandleTypeDef *Greentim = nullptr, TIM_HandleTypeDef *Bluetim = nullptr)
        : RedChannel(RedChannel), GreenChannel(GreenChannel), BlueChannel(BlueChannel), Redtim(Redtim)
    {
        if (Greentim == nullptr) {
            this->Greentim = Redtim;
        } else {
            this->Greentim = Greentim;
        }
        if (Bluetim == nullptr) {
            this->Bluetim = Redtim;
        } else {
            this->Bluetim = Bluetim;
        }
    }

    /// @brief 使用RGB数值设置LED颜色
    /// @param R 红色亮度0-255
    /// @param G 绿色亮度0-255
    /// @param B 蓝色亮度0-255
    void SetColor(uint8_t R, uint8_t G, uint8_t B)
    {
        this->Red   = R * 4;
        this->Green = G * 4;
        this->Blue  = B * 4;
        __HAL_TIM_SetCompare(Redtim, RedChannel, Red);
        __HAL_TIM_SetCompare(Greentim, GreenChannel, Green);
        __HAL_TIM_SetCompare(Bluetim, BlueChannel, Blue);
    }

    /// @brief 使用颜色类设置LED颜色
    /// @param RGB 传函为颜色类
    void SetColor(Color RGB)
    {
        this->Red   = RGB.R * 4;
        this->Green = RGB.G * 4;
        this->Blue  = RGB.B * 4;
        __HAL_TIM_SetCompare(Redtim, RedChannel, Red);
        __HAL_TIM_SetCompare(Greentim, GreenChannel, Green);
        __HAL_TIM_SetCompare(Bluetim, BlueChannel, Blue);
    }

    /// @brief 启动LED
    /// @param  void
    void LED_ON(void)
    {
        if (LED_State == false) {
            EnableLED();
            HAL_TIM_PWM_Start(Redtim, RedChannel);
            HAL_TIM_PWM_Start(Greentim, GreenChannel);
            HAL_TIM_PWM_Start(Bluetim, BlueChannel);
        }
    }

    /// @brief 关闭LED
    /// @param  void
    void LED_OFF(void)
    {
        if (LED_State == true) {
            DisableLED();
            HAL_TIM_PWM_Stop(Redtim, RedChannel);
            HAL_TIM_PWM_Stop(Greentim, GreenChannel);
            HAL_TIM_PWM_Stop(Bluetim, BlueChannel);
        }
    }
};

extern Led LedMain;
extern Color ColorError;
extern Color ColorNormal;
extern Color ColorInit;
extern Color ColorWarning;

/* Class End -----------------------------------------------------------------*/

/* Function ------------------------------------------------------------------*/
/* Function End --------------------------------------------------------------*/
