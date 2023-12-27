/**
 * @file high_precision_time.h
 * @author X. Y.
 * @brief 高精度时间库
 * @version 1.2
 * @date 2023-07-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 初始化 HPT
 * @note 需要先初始化，然后才能使用其他函数
 * @note 需要在系统时钟配置完后或修改时钟配置后调用
 */
void HPT_Init();

/**
 * @brief 获取当前微秒值
 *
 * @return uint32_t 微秒值
 */
uint32_t HPT_GetUs();

/**
 * @brief 获取总 SysTick
 *
 * @note SysTick 的时钟可以配置成 HCLK 或 HCLK/8
 * @note CubeMX 可以在时钟树界面配置 To Cortex System timer. 这个值就是 SysTick 的频率 (不是 cpu 频率)
 * @note cpu 的频率是 FCLK Cortex clock, 等于 HCLK
 * @note 这个数字增长得很快，在几十秒内会循环溢出，一般用于测量极短时间。溢出周期取决于 SysTick 速度
 */
uint32_t HPT_GetTotalSysTick();

/**
 * @brief 高精度延时
 * @note 比 vTaskDelay 和 HAL_Delay 精度高
 * @param ms 要延时的毫秒数
 */
void HPT_DelayMs(uint32_t ms);

/**
 * @brief 高精度延时
 * @param us 要延时的微秒数
 */
void HPT_DelayUs(uint32_t us);

/**
 * @brief  Get the SysTick clock source
 * @retval Returned value can be one of the following values:
 *         @arg @ref SYSTICK_CLKSOURCE_HCLK_DIV8
 *         @arg @ref SYSTICK_CLKSOURCE_HCLK
 */
uint32_t HPT_GetSysTickClkSource();

/**
 * @brief 将 SysTick 转换成纳秒
 *
 * @param tick SysTick 值
 * @return uint32_t 纳秒
 *
 */
uint32_t HPT_SysTickToNs(uint64_t tick);

#ifdef __cplusplus
}
#endif
