/**
 * @file discrete_integrator.hpp
 * @author X. Y.
 * @brief 离散时间积分器
 * @version 0.2
 * @date 2023-07-06
 *
 * @copyright Copyright (c) 2023
 *
 * 按照 Simulink 中的 Discrete-Time Integrator 模块设计
 *
 * 使用示例：
 * control_system::DiscreteIntegrator<float> integrator{2, 0.01}; // 定义一个积分增益为 2 采样周期为 0.01s 的积分器
 * control_system::DiscreteIntegratorSaturation<float> i_controller{{2, 0.01}, {-10, 10}}; // 定义一个带有积分限幅的积分器
 *
 */

#pragma once
#include "discrete_controller_base.hpp"
#include "saturation.hpp"

namespace control_system
{

template <typename T>
class DiscreteIntegrator : public DiscreteControllerBase<T>
{
protected:
    T Ki, Ts;
    T input_coefficient_; // 系数，见 UpdateCoefficient()
    T x_;                 // 内部状态变量

    void UpdateCoefficient()
    {
        input_coefficient_ = Ki * Ts / 2;
    }

public:
    /**
     * @brief 积分器
     *
     * @param Ki 积分器系数
     * @param Ts 采样周期
     *
     */
    DiscreteIntegrator(T Ki, T Ts)
    {
        ResetState();
        SetParam(Ki, Ts);
    }

    /**
     * @brief 走一个采样周期
     *
     * @param input 输入
     * @return T 输出
     */
    T Step(T input) override
    {
        auto temp = input_coefficient_ * input;
        auto y_   = x_ + temp; // y_ 是输出

        x_ = y_ + temp;

        return y_;
    }

    T GetStateOutput() const
    {
        return x_;
    }

    /**
     * @brief 设置积分初值
     *
     */
    void SetStateValue(T x)
    {
        x_ = x;
    }

    void SetParam(T Ki, T Ts)
    {
        this->Ki = Ki;
        this->Ts = Ts;
        UpdateCoefficient();
    }

    void SetParam(T Ki)
    {
        this->Ki = Ki;
        UpdateCoefficient();
    }

    T GetKi() const
    {
        return Ki;
    }

    T GetTs() const
    {
        return Ts;
    }

    /**
     * @brief 重置控制器状态
     *
     */
    void ResetState()
    {
        x_ = 0;
    }
};

template <typename T>
class DiscreteIntegratorSaturation : public DiscreteIntegrator<T>
{
protected:
    using DiscreteIntegrator<T>::x_;
    using DiscreteIntegrator<T>::input_coefficient_;

public:
    using DiscreteIntegrator<T>::DiscreteIntegrator;
    Saturation<T, T> saturation; // 限幅器，可以对这个类操作，调整限幅幅值

    DiscreteIntegratorSaturation(const DiscreteIntegrator<T> &discrete_integrator,
                                 const Saturation<T, T> &saturation)
        : DiscreteIntegrator<T>{discrete_integrator}, saturation{saturation} {};

    /**
     * @brief 走一个采样周期
     *
     * @param input 输入
     * @return T 输出
     */
    T Step(T input) override
    {
        auto temp = input_coefficient_ * input;
        auto y_   = saturation(x_ + temp); // y_ 是输出

        x_ = y_ + temp;

        return y_;
    }
};

} // namespace control_system
