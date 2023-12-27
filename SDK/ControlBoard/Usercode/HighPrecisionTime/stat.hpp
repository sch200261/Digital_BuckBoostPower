#pragma once

#include "high_precision_time.h"
#include <cstdint>

class TimeMeter
{
private:
    uint32_t *duration_;
    bool end_measure_ = false;

public:
    uint32_t start_time_ = 0;

    /**
     * @brief 创建时是否开始测量
     */
    TimeMeter(uint32_t *duration, bool start_measure = true)
        : duration_(duration)
    {
        if (start_measure) {
            start_time_ = HPT_GetUs();
        }
    }

    /**
     * @brief 开始测量
     * @note 这会重新开始记录时间
     *
     */
    void StartMeasure()
    {
        start_time_ = HPT_GetUs();
    }

    void EndMeasure()
    {
        *duration_ = HPT_GetUs() - start_time_;
    }

    ~TimeMeter()
    {
        if (end_measure_ == false) {
            *duration_ = HPT_GetUs() - start_time_;
        }
    }
};

template <typename T>
class CounterFreqMeter
{
private:
    const T *const counter_;
    T last_count_ = 0;
    uint32_t last_ms_;

public:
    CounterFreqMeter(const T *const counter)
        : counter_(counter)
    {
        last_count_ = *counter_;
        last_ms_    = HAL_GetTick();
    }

    uint32_t MeasureFreq()
    {
        T now_count     = *counter_;
        uint32_t now_ms = HAL_GetTick();

        uint32_t result = (now_count - last_count_) * 1000 / (now_ms - last_ms_);

        last_ms_    = now_ms;
        last_count_ = now_count;
        return result;
    }
};
