/**
 * @file saturation.hpp
 * @author X. Y.
 * @brief 限幅函数
 * @version 0.1
 * @date 2023-07-05
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <limits>

namespace control_system
{

/**
 * @brief 限幅函数（默认 is_enable_ = true）
 *
 * @tparam T 数据类型
 */
template <typename Tmin, typename Tmax>
class Saturation
{
private:
    Tmin min_;
    Tmax max_;
    bool is_enable_ = true;

public:
    Saturation(Tmin min = std::numeric_limits<Tmin>::lowest(),
               Tmax max = std::numeric_limits<Tmin>::max())
        : min_{min}, max_{max} {};

    void SetMinMax(Tmin min, Tmax max)
    {
        this->min_ = min;
        this->max_ = max;
    }

    void SetMin(Tmin min)
    {
        this->min_ = min;
    }

    Tmin GetMin() const
    {
        return min_;
    }

    void SetMax(Tmax max)
    {
        this->max_ = max;
    }

    Tmax GetMax() const
    {
        return max_;
    }

    /**
     * @brief 设置是否使能限幅，如果不使能，则没有限幅作用
     *
     * @param is_enable
     */
    void SetEnable(bool is_enable)
    {
        is_enable_ = is_enable;
    }

    bool IsEnable() const
    {
        return is_enable_;
    }

    template <typename T>
    T operator()(T value) const
    {
        if (is_enable_) {
            if (value > max_) return max_;
            if (value < min_) return min_;
        }

        return value;
    }
};

} // namespace control_system
