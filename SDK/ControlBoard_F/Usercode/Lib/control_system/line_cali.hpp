/**
 * @file line_cali.hpp
 * @author X. Y.
 * @brief 线性校正
 * @version 0.1
 * @date 2023-08-02
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

namespace control_system
{
template <typename T>
class LineCali
{
public:
    T k_, b_;

    LineCali(T k = 1, T b = 0)
        : k_(k), b_(b){};

    T Calc(T x) const
    {
        return k_ * x + b_;
    }
};

} // namespace control_system
