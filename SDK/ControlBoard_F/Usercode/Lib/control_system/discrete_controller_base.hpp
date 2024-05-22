/**
 * @file discrete_controller_base.hpp
 * @author X. Y.  
 * @brief 离散控制器基类
 * @version 0.2
 * @date 2023-07-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

namespace control_system
{

/**
 * @brief 离散控制器基类
 *
 * @tparam T 数据类型，例如 float 或 double
 */
template <typename T>
class DiscreteControllerBase
{
public:
    /**
     * @brief 走一个周期
     *
     * @param input 输入
     * @return  输出
     */
    virtual T Step(T input) = 0;

    /**
     * @brief 重置控制器内部状态
     *
     */
    virtual void ResetState() = 0;
};

} // namespace control_system
