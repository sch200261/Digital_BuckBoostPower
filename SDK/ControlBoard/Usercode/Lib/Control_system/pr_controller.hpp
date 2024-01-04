#pragma once

#include <cmath>
#include "z_tf.hpp"
#include <vector>
#include <cassert>

namespace control_system
{

template <typename T>
class PRController : public DiscreteControllerBase<T>
{
private:
    ZTf<T> controller_;

public:
    // 这些参数更新后需要调用 UpdateCoefficient()
    T Ts_; // 采样时间
    T Kp_; // 在非谐振处增
    T Kr_; // 在谐振处增益
    T Wc_; // 谐振带宽
    T W0_; // 谐振峰值频率

    /**
     * @brief 初始化比例谐振滤波器
     *
     * @param Ts 采样时间
     * @param Kpc 在非谐振处增益大小
     * @param Kr 在谐振处增益
     * @param Wc 谐振带宽
     * @param W0 谐振峰值频率
     */
    PRController(T Ts, T Kp = 1, T Kr = 100, T Wc = 10, T W0 = 2 * 50 * M_PI)
        : Ts_(Ts), Kp_(Kp), Kr_(Kr), Wc_(Wc), W0_(W0)
    {
        // T 必须是浮点数类型。另外，注意 Ts 是采样周期而不是采样频率
        static_assert(std::is_floating_point<T>::value,
                      "'T' must be floating point type. And note that 'Ts' is sampling period, not frequency.");

        assert(Ts <= 1); // 注意，Ts 是采样周期，不是采样频率

        UpdateCoefficient();
    }

    /**
     * @brief 走一个采样周期
     *
     * @param input 输入
     * @return T 输出
     */
    T Step(T input) override
    {
        return controller_.Step(input);
    }

    void UpdateCoefficient()
    {
        auto W0_2_Ts_2 = W0_ * W0_ * Ts_ * Ts_;

        auto num = {
            (4 + 4 * Ts_ * Wc_ + W0_2_Ts_2) * Kp_ + 4 * Kr_ * Ts_ * Wc_,
            (2 * W0_2_Ts_2 - 8) * Kp_,
            (4 - 4 * Ts_ * Wc_ + W0_2_Ts_2) * Kp_ - 4 * Kr_ * Ts_ * Wc_};

        auto den = {
            4 + 4 * Ts_ * Wc_ + W0_2_Ts_2,
            2 * W0_2_Ts_2 - 8,
            4 - 4 * Ts_ * Wc_ + W0_2_Ts_2};

        controller_.Init(num, den);
    }

    /**
     * @brief 重置控制器状态
     *
     */
    void ResetState()
    {
        controller_.ResetState();
    }
};

} // namespace control_system
