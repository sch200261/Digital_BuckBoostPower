/**
 * @file signal_generator.hpp
 * @author X. Y.
 * @brief 信号生成器
 * @version 0.1
 * @date 2023-07-12
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

#include <cstdint>
#include <cmath>

namespace control_system
{

template <typename T, T (*sin_func)(T) = std::sin>
class SineGenerator
{
private:
    double omega_, Ts_;
    T initial_phase_;
    T k;
    uint32_t counter_;        // 计数值
    uint32_t reload_num_ = 0; // 重装载值

    void UpdateCoefficient()
    {
        if (omega_ != 0) {
            k           = omega_ * Ts_;
            T temp      = static_cast<T>(counter_) / reload_num_;
            reload_num_ = std::abs(std::lround(2 * PI_ / (Ts_ * omega_)));
            counter_    = std::lround(temp * reload_num_); // 用于防止修改参数后相位突变
        } else {
            k           = 0;
            reload_num_ = 0;
        }
    }

public:
    constexpr static T PI_ = M_PI;

    SineGenerator(T omega, T Ts, T initial_phase = 0)
    {
        ResetState();
        SetParam(omega, Ts, initial_phase);
    }

    void SetOmega(T omega)
    {
        omega_ = omega;
        UpdateCoefficient();
    }

    void SetInitialPhase(T initial_phase)
    {
        initial_phase_ = initial_phase;
    }

    void SetTs(T Ts)
    {
        Ts_ = Ts;
        UpdateCoefficient();
    }

    void SetParam(T omega, T Ts, T initial_phase = 0)
    {
        omega_         = omega;
        Ts_            = Ts;
        initial_phase_ = initial_phase;
        UpdateCoefficient();
    }

    /**
     * @brief 走一个采样周期
     *
     * @return  输出
     */
    T Step(T delta_phase = 0)
    {
        T result = sin_func(k * counter_ + initial_phase_ + delta_phase);
        counter_++;
        if (counter_ >= reload_num_) {
            counter_ = 0;
        }
        return result;
    }

    T GetPhase() const
    {
        return k * counter_ + initial_phase_;
    }

    /**
     * @brief 获取在当前相角下增加 delta_phase 后的值
     *
     * @param delta_phase
     * @return T
     */
    T GetOutputDeltaPhase(T delta_phase) const
    {
        return sin_func(k * counter_ + initial_phase_ + delta_phase);
    }

    /**
     * @brief 回到 0 时刻
     *
     */
    void ResetState()
    {
        counter_ = 0;
    }
};

} // namespace control_system
