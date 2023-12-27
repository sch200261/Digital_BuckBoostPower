#pragma once

#include "high_precision_time.h"
#include <stdio.h>

/**
 * @brief 测试 HPT_GetUs() 是否单调递增
 * @note 建议在新平台使用时都先测试一下
 * @note 如果测试通过，函数会返回，否则会卡在函数内部
 * @param duration 测试时长 (ms)，建议不少于 5000
 */
static inline void HPT_TestGetUs(uint32_t duration)
{
    uint32_t last_value = HPT_GetUs();
    uint32_t until_tick = HAL_GetTick() + duration;
    while (1) {
        uint32_t now_value = HPT_GetUs();
        if (now_value < last_value) {
            fprintf(stderr, "now_value < last_value! now_value:%lu, last_value:%lu\n", now_value, last_value);
            while (1) {}
        }

        if (HAL_GetTick() >= until_tick) {
            break;
        }
        last_value = now_value;
    }
}

/**
 * @brief 测试 HPT_GetTotalSysTick() 是否单调递增
 * @note 由于这个函数溢出时间较短（大概 10~20 秒，取决于 cpu 速度），
 * @note 请在系统启动后立即测试，并且测试时长不要超过溢出时间。
 * @note 建议在新平台使用时都先测试一下
 * @note 如果测试通过，函数会返回，否则会卡在函数内部
 * @param duration 测试时长 (ms)，建议不少于 5000
 */
static inline void HPT_TestGetTotalSysTick(uint32_t duration)
{
    uint32_t last_value = HPT_GetTotalSysTick();
    uint32_t until_tick = HAL_GetTick() + duration;
    while (1) {
        uint32_t now_value = HPT_GetTotalSysTick();
        if (now_value < last_value) {
            fprintf(stderr, "now_value < last_value! now_value:%lu, last_value:%lu\n", now_value, last_value);
            while (1) {}
        }

        if (HAL_GetTick() >= until_tick) {
            break;
        }
        last_value = now_value;
    }
}
