/**
 * @file pid_controller.hpp
 * @author X. Y.
 * @brief PID 控制器
 * @version 0.5
 * @date 2023-07-05
 *
 * @copyright Copyright (c) 2023
 *
 * 这些控制器按照 Simulink 中的 Discrete PID Controller 模块设计，其中积分器方法和滤波器方法均为梯形（也就是双线性变换）
 * 你可以直接把 Discrete PID Controller 中的参数填入这些控制器中
 *
 * PID 控制器采用的公式为：
 *   Kp + Ki/s + Kd * Kn / (1 + Kn/s)
 *
 *   其中,
 *   s = 2/Ts * (z-1)/(z+1)
 *   Kp 为比例系数
 *   Ki 为积分系数
 *   Kd 为微分系数
 *   Kn 为滤波器系数
 *   Ts 为采样周期
 *
 * 参数说明：
 *   Kn 可以减弱微分器对高频噪声的敏感性。Kn 越小减弱效果越好，但微分器的响应更慢
 *   Kn 的值超过 2/Ts 时，微分器的阶跃响应会震荡
 *
 *   Ts 为采样周期，单位为秒。如 1000 Hz 的采样率，对应的 Ts 为 0.001.
 *   请使得调用控制器 Step() 的周期为 Ts
 *
 * 使用示例:
 *   定义 PID 控制器:
 *     PIDController<float> pid_controller{1.23, 0.54, 0, 1000, 0.01};
 *
 *   使用 PID 控制器:
 *     while(1) {
 *         output_data = controller.Step(input_data);
 *         sleep_ms(10); // 因为 Ts = 0.01, 等待 10 ms
 *     }
 *
 */

#pragma once

#include "discrete_controller_base.hpp"
#include "z_tf.hpp"
#include "discrete_integrator.hpp"
#include "saturation.hpp"
#include <array>

namespace control_system
{

template <typename T>
class PController : public DiscreteControllerBase<T>
{
private:
    T Kp = 0;

public:
    PController(T Kp)
    {
        SetParam(Kp);
    }

    /**
     * @brief 走一个采样周期
     *
     * @param input 输入
     * @return T 输出
     */
    T Step(T input) override
    {
        return Kp * input;
    }

    /**
     * @brief 设置参数
     *
     * @param Kp 比例项
     */
    void SetParam(T Kp)
    {
        this->Kp = Kp;
    }

    T GetKp() const
    {
        return Kp;
    }

    void ResetState(){};
};

/**
 * @brief 积分控制器
 * @note 直接使用 DiscreteIntegratorSaturation
 */
template <typename T>
using IController = DiscreteIntegratorSaturation<T>;

template <typename T>
class DController : public DiscreteControllerBase<T>
{
private:
    T Kd, Kn, Ts;
    T input_coefficient_;
    T output_coefficient_;
    T last_input_;
    T last_output_;

    void UpdateCoefficient()
    {
        auto den            = 2 + Kn * Ts;
        input_coefficient_  = (2 * Kd * Kn) / den;
        output_coefficient_ = (2 - Kn * Ts) / den;
    }

public:
    DController(T Kd, T Kn, T Ts)
    {
        ResetState();
        SetParam(Kd, Kn, Ts);
    }

    /**
     * @brief 走一个采样周期
     *
     * @param input 输入
     * @return T 输出
     */
    T Step(T input) override
    {
        last_output_ = input_coefficient_ * (input - last_input_) + output_coefficient_ * last_output_;
        last_input_  = input;
        return last_output_;
    }

    void SetParam(T Kd, T Kn, T Ts)
    {
        this->Kd = Kd;
        this->Kn = Kn;
        this->Ts = Ts;
        UpdateCoefficient();
    }

    void SetParam(T Kd, T Kn)
    {
        this->Kd = Kd;
        this->Kn = Kn;
        UpdateCoefficient();
    }

    T GetKd() const
    {
        return Kd;
    }

    T GetKn() const
    {
        return Kn;
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
        last_input_  = 0;
        last_output_ = 0;
    }
};

/**
 * @brief PID 控制器
 *
 * @tparam T 运算数据类型
 * @tparam IntegratorType 积分器类型，默认为带限幅的 DiscreteIntegratorSaturation<T>. 如果不需要限幅，可以指定为 DiscreteIntegrator<T>
 * @note   例如：PIDController<float, DiscreteIntegrator<float>> pid_controller{1.23, 0.54, 0.5, 100, 0.01};
 */
template <typename T, typename IntegratorType = IController<T>>
class PIDController : public DiscreteControllerBase<T>
{
public:
    T Kp; // 比例系数，可以直接修改
    IntegratorType i_controller;
    DController<T> d_controller;

    PIDController(T Kp, T Ki, T Kd, T Kn, T Ts)
        : Kp{Kp}, i_controller{Ki, Ts}, d_controller{Kd, Kn, Ts} {};

    /**
     * @brief 走一个采样周期
     *
     * @param input 输入
     * @return T 输出
     */
    T Step(T input) override
    {
        return Kp * input + i_controller.Step(input) + d_controller.Step(input);
    }

    void SetParam(T Kp, T Ki, T Kd, T Kn, T Ts)
    {
        this->Kp = Kp;
        i_controller.SetParam(Ki, Ts);
        d_controller.SetParam(Kd, Kn, Ts);
    }

    void SetParam(T Kp, T Ki, T Kd, T Kn)
    {
        this->Kp = Kp;
        i_controller.SetParam(Ki);
        d_controller.SetParam(Kd, Kn);
    }

    /**
     * @brief 重置控制器状态
     *
     */
    void ResetState()
    {
        i_controller.ResetState();
        d_controller.ResetState();
    }
};

/**
 * @brief PI 控制器
 *
 * @tparam T 运算数据类型
 * @tparam IntegratorType 积分器类型，默认为带限幅的 DiscreteIntegratorSaturation<T>. 如果不需要限幅，可以指定为 DiscreteIntegrator<T>
 * @note   例如：PIController<float, DiscreteIntegrator<float>> pi_controller{1.23, 0.54, 0.01};
 */
template <typename T, typename IntegratorType = IController<T>>
class PIController : public DiscreteControllerBase<T>
{
public:
    T Kp; // 比例系数，可以直接修改
    IntegratorType i_controller;

    PIController(T Kp, T Ki, T Ts)
        : Kp{Kp}, i_controller{Ki, Ts} {};

    /**
     * @brief 走一个采样周期
     *
     * @param input 输入
     * @return T 输出
     */
    T Step(T input) override
    {
        return Kp * input + i_controller.Step(input);
    }

    /**
     * @brief 重置控制器状态
     *
     */
    void ResetState()
    {
        i_controller.ResetState();
    }
};

template <typename T>
class PDController : public DiscreteControllerBase<T>
{
public:
    T Kp; // 比例系数，可以直接修改
    DController<T> d_controller;

    PDController(T Kp, T Kd, T Kn, T Ts)
        : Kp{Kp}, d_controller{Kd, Kn, Ts} {};

    /**
     * @brief 走一个采样周期
     *
     * @param input 输入
     * @return T 输出
     */
    T Step(T input) override
    {
        return Kp * input + d_controller.Step(input);
    }

    /**
     * @brief 重置控制器状态
     *
     */
    void ResetState()
    {
        d_controller.ResetState();
    }
};

/**
 * @brief 抗饱和 PID 控制器
 * @note 目前只实现了反算抗饱和法
 * @note 详细用法可以参考 Matlab 文档 https://ww2.mathworks.cn/help/simulink/slref/anti-windup-control-using-a-pid-controller.html
 * @tparam T 运算数据类型
 */
template <typename T>
class PID_AntiWindup : public DiscreteControllerBase<T>
{
public:
    T Kp; // 比例系数，可以直接修改
    T Ki; // 积分系数，可以直接修改
    T Kb; // 反算系数，可以直接修改
    DController<T> d_controller;
    Saturation<T, T> output_saturation; // 输出限幅

private:
    DiscreteIntegrator<T> integrator;

public:
    /**
     * @brief 带有抗饱和的 PID 控制器
     *
     * @param Kp 比例系数
     * @param Ki 积分系数
     * @param Kd 微分系数
     * @param Kn 滤波器系数
     * @param Ts 采样周期（秒）
     * @param Kb 反算系数
     * @param output_min 输出饱和下限
     * @param output_max 输出饱和上限
     */
    PID_AntiWindup(T Kp, T Ki, T Kd, T Kn, T Ts, T Kb, T output_min, T output_max)
        : Kp{Kp}, Ki{Ki}, Kb{Kb}, d_controller{Kd, Kn, Ts}, output_saturation{output_min, output_max}, integrator{1, Ts}
    {
        ResetState();
    }

    /**
     * @brief 走一个采样周期
     *
     * @param input 输入
     * @return T 输出
     */
    T Step(T input) override
    {
        auto p = Kp * input;
        auto d = d_controller.Step(input);

        auto preSat  = integrator.GetStateOutput() + p + d;
        auto postSat = output_saturation(preSat);

        auto i_output = integrator.Step(input * Ki + (postSat - preSat) * Kb);
        return output_saturation(i_output + p + d);
    }

    /**
     * @brief 重置控制器状态
     *
     */
    void ResetState()
    {
        integrator.ResetState();
        d_controller.ResetState();
    }
};

/**
 * @brief 抗饱和 PI 控制器
 * @note 目前只实现了反算抗饱和法
 * @note 详细用法可以参考 Matlab 文档 https://ww2.mathworks.cn/help/simulink/slref/anti-windup-control-using-a-pid-controller.html
 * @tparam T 运算数据类型
 */
template <typename T>
class PI_AntiWindup : public DiscreteControllerBase<T>
{
public:
    T Kp;                               // 比例系数，可以直接修改
    T Ki;                               // 积分系数，可以直接修改
    T Kb;                               // 反算系数，可以直接修改
    Saturation<T, T> output_saturation; // 输出限幅

private:
    DiscreteIntegrator<T> integrator;

public:
    /**
     * @brief 带有抗饱和的 PI 控制器
     *
     * @param Kp 比例系数
     * @param Ki 积分系数
     * @param Ts 采样周期（秒）
     * @param Kb 反算系数
     * @param output_min 输出饱和下限
     * @param output_max 输出饱和上限
     */
    PI_AntiWindup(T Kp, T Ki, T Ts, T Kb, T output_min, T output_max)
        : Kp{Kp}, Ki{Ki}, Kb{Kb}, output_saturation{output_min, output_max}, integrator{1, Ts}
    {
        ResetState();
    }

    /**
     * @brief 走一个采样周期
     *
     * @param input 输入
     * @return T 输出
     */
    T Step(T input) override
    {
        auto p = Kp * input;

        auto preSat  = integrator.GetStateOutput() + p;
        auto postSat = output_saturation(preSat);

        auto i_output = integrator.Step(input * Ki + (postSat - preSat) * Kb);
        return output_saturation(i_output + p);
    }

    /**
     * @brief 重置控制器状态
     *
     */
    void ResetState()
    {
        integrator.ResetState();
    }
};

} // namespace control_system
