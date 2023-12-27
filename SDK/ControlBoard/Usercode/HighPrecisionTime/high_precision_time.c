#include "high_precision_time.h"
#include "main.h"
#include <assert.h>

/****************
 * 用户设置部分 *
 ****************/

// 注：仅在使用 FreeRTOS 时测试通过，尚未在裸机下测试

#define USE_FREERTOS             // 使用 FreeRTOS 时请打开该宏定义
#define HAL_TIMEBASE_htimx htim7 // HAL Timebase Source

/****************
 * 程序代码部分 *
 ****************/

#define MEM_BARRIER() __DSB() // 内存屏障，防止内存访问指令重排

static uint8_t kIsInited = 0; // 是否初始化了
static uint32_t kUs_uwTick;   // 1 uwTick 对应多少 us
static uint32_t kSysTick_Us;  // 1 us 对应多少 SysTick

#ifdef USE_FREERTOS

#include "FreeRTOS.h"
#include "task.h"

extern TIM_HandleTypeDef HAL_TIMEBASE_htimx;

static uint32_t kSysTick_xTickCount; // 1 xTickCount 对应多少 SysTick

void HPT_Init()
{
    kUs_uwTick          = 1000 * uwTickFreq;
    kSysTick_xTickCount = SysTick->LOAD + 1;
    kSysTick_Us         = SystemCoreClock / 1000000;
    kIsInited           = 1;
}

uint32_t HPT_GetUs()
{
    assert(kIsInited); // 记得调用 HPT_Init()

    uint32_t tick = uwTick;
    MEM_BARRIER();
    uint32_t val = HAL_TIMEBASE_htimx.Instance->CNT;
    MEM_BARRIER();
    uint32_t tick1 = uwTick;

    if (tick == tick1) {
        // 在采样时 uwTick 没发生变化，tick 和 val 有效
        return tick * kUs_uwTick + val;
    } else {
        // 在采样时 uwTick 发生变化，说明在此之间进入了定时器中断，需要使用 tick1 和新的 CNT
        return tick1 * kUs_uwTick + HAL_TIMEBASE_htimx.Instance->CNT;
    }
}

uint32_t HPT_GetTotalSysTick()
{
    // 为加快函数执行速度，不判断初始化了
    // assert(kIsInited); // 记得调用 HPT_Init()

    uint32_t tick = xTaskGetTickCount();
    MEM_BARRIER();
    uint32_t val = SysTick->VAL;
    MEM_BARRIER();
    uint32_t tick1 = xTaskGetTickCount();

    if (tick == tick1) {
        return tick * kSysTick_xTickCount + (SysTick->LOAD - val);
    } else {
        return tick1 * kSysTick_xTickCount + (SysTick->LOAD - SysTick->VAL);
    }
}

#else
static uint32_t kSysTick_uwTick; // 1 uwTick 对应多少 SysTick

void HPT_Init()
{
    kUs_uwTick      = 1000 * uwTickFreq;
    kSysTick_Us     = SystemCoreClock / 1000000;
    kSysTick_uwTick = SysTick->LOAD + 1;
    kIsInited       = 1;
}

uint32_t HPT_GetUs()
{
    assert(kIsInited); // 记得调用 HPT_Init()

    uint32_t tick = uwTick;
    MEM_BARRIER();
    uint32_t val = SysTick->VAL;
    MEM_BARRIER();
    uint32_t tick1 = uwTick;

    if (tick == tick1) {
        return tick * kUs_uwTick + (SysTick->LOAD - val) / kSysTick_Us;
    } else {
        return tick1 * kUs_uwTick + (SysTick->LOAD - SysTick->VAL) / kSysTick_Us;
    }
}

uint32_t HPT_GetTotalSysTick()
{
    // 为加快函数执行速度，不判断初始化了
    // assert(kIsInited); // 记得调用 HPT_Init()

    uint32_t tick = uwTick;
    MEM_BARRIER();
    uint32_t val = SysTick->VAL;
    MEM_BARRIER();
    uint32_t tick1 = uwTick;

    if (tick == tick1) {
        return tick * kSysTick_uwTick + (SysTick->LOAD - val);
    } else {
        return tick1 * kSysTick_uwTick + (SysTick->LOAD - SysTick->VAL);
    }
}

#endif // USE_FREERTOS

void HPT_DelayUs(uint32_t us)
{
    uint32_t startUs = HPT_GetUs();
    while (HPT_GetUs() - startUs < us) {}
}

void HPT_DelayMs(uint32_t ms)
{
    HPT_DelayUs(1000 * ms);
}

uint32_t HPT_GetSysTickClkSource()
{
    return READ_BIT(SysTick->CTRL, SYSTICK_CLKSOURCE_HCLK);
}

uint32_t HPT_SysTickToNs(uint64_t tick)
{
    assert(kIsInited);
    if (HPT_GetSysTickClkSource() == SYSTICK_CLKSOURCE_HCLK) {
        return tick * 1000 / kSysTick_Us;
    } else {
        return tick * 8000 / kSysTick_Us;
    }
}
