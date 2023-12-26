/********************************************************************************
 * @file    mospwm.hpp
 * @brief   This file contains all the function prototypes for
 *          the mospwm.cpp file
 *******************************************************************************/

#pragma once

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"

class CoPWM
{
private:
    uint16_t Pulse = 0;              // PWM脉宽 0-ReloadCount
    const TIM_HandleTypeDef *PWMtim; // 互补PWM定时器编号
    const uint32_t Channel;          // PWM通道
    const uint16_t ReloadCount;      // PWM重装载值
    bool PWM_State = false;          // PWM状态，true为开启

    void EnablePWM(void)
    {
        this->PWM_State = true;
    }

    void DisablePWM(void)
    {
        this->PWM_State = false;
    }

public:
    CoPWM(TIM_HandleTypeDef *PWMtim, uint32_t Channel, uint16_t ReloadCount)
        : PWMtim(PWMtim), Channel(Channel), ReloadCount(ReloadCount){};

    /// @brief 设置PWM占空比
    /// @param Duty 占空比0-1.000
    void SetDuty(double Duty)
    {
        this->Pulse = (uint16_t)(Duty * ReloadCount);
        __HAL_TIM_SetCompare(PWMtim, Channel, Pulse);
        //__HAL_TIM_SetCompare(PWMtim, NChannel, Pulse);
    }

    /// @brief 启动PWM
    /// @param  void
    void PWM_ON(void)
    {
        if (PWM_State == false) {
            EnablePWM();
            HAL_TIM_PWM_Start((TIM_HandleTypeDef *)PWMtim, Channel);
            HAL_TIMEx_PWMN_Start((TIM_HandleTypeDef *)PWMtim, Channel);
        }
    }

    /// @brief 关闭PWM
    /// @param  void
    void PWM_OFF(void)
    {
        if (PWM_State == true) {
            DisablePWM();
            HAL_TIM_PWM_Stop((TIM_HandleTypeDef *)PWMtim, Channel);
            HAL_TIMEx_PWMN_Stop((TIM_HandleTypeDef *)PWMtim, Channel);
        }
    }
};

extern CoPWM PWMA;
extern CoPWM PWMB;
