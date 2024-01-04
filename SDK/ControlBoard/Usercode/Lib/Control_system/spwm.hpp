/**
 * @file svpwm.hpp
 * @author X. Y.
 * @brief
 * @version 0.1
 * @date 2023-07-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <cmath>
#include <array>

namespace control_system
{

/**
 * @brief SPWM
 *
 * @tparam T 数据类型，如 float, double
 * @tparam cos_func 用于计算三角函数的方法。默认为 std::cos，可以指定为 std::sin 或其他快速三角函数
 *
 * @example control_system::Sypwm<float>
 * @example control_system::Sypwm<float, std::sin>
 * @example control_system::Sypwm<float, arm_cos_f32>
 */
template <typename T, T (*cos_func)(T) = std::cos>
class Spwm3Phase
{
private:
    constexpr static T PI_ = M_PI;

public:
    std::array<T, 3> duty_; // 占空比

    /**
     * @brief 计算，结果存放在 duty_ 中
     *
     * @param phase 相位 (rad)
     * @param max_duty 最大占空比
     */
    void Calc(T phase, T max_duty = 1)
    {
        // 检查 T 的类型，必须是浮点类型
        static_assert(std::is_floating_point<T>::value, "'T' must be floating point type. ");

        duty_[0] = max_duty * cos_func(phase);
        duty_[1] = max_duty * cos_func(phase + 2 * PI_ / 3);
        duty_[2] = max_duty * cos_func(phase - 2 * PI_ / 3);
    }
};

} // namespace control_system
