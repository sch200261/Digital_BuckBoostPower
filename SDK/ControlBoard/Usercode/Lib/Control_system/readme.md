# control system lib

控制系统的 c++ 模板库

本库按照 Matlab 和 Simulink 对应模块设计，仅需填写 Matlab 和 Simulink 中的参数，即可得到对应的控制器

本库仅依赖 c++ STL，可以用于任何支持 c++ 的地方

注：本库在 c++ 17 标准下开发测试，较低的版本可能需要一点修改才能编译通过

## 有哪些控制器

- 离散时间积分器
- PID 控制器
- 限幅器
- 任意离散传递函数控制器

## 使用示例

### 离散传递函数控制器

头文件: `#include "control_system/z_tf.hpp"`

```cpp
using namespace control_system;

// 定义一个离散传递函数
// 其中内部运算数据类型为 float
// 分子为 66 z^2 - 124 z + 58
// 分母为 z^2 - 0.333 z - 0.667
// 注意，分子阶数不能大于分母，否则为非因果系统，无法实现
ZTf<float> ztf({66, -124, 58}, {1, -0.333, -0.667});

// 输出单位阶跃响应的前 10 个数
for (size_t i = 0; i < 10; i++) {
    std::cout << ztf.Step(1) << std::endl;
}

ztf.ResetState(); // 重置内部状态

// 输出单位斜坡响应的前 10 个数
for (size_t i = 0; i < 10; i++) {
    std::cout << ztf.Step(i) << std::endl;
}
```

### PID 控制器

头文件: `#include "control_system/pid_controller.hpp"`

示例1:

```cpp
using namespace control_system;

// 定义一个 PID 控制器
// 其中内部运算数据类型为 float
// Kp = 2
// Ki = 100
// Kd = 0.76
// Kn = 100 （滤波器系数）
// Ts = 0.01 （采样周期）
// 详细信息见头文件注释
PID<float> pid_controller{2, 100, 0.76, 100, 0.01};

// 设置积分限幅
pid_controller.i_controller.saturation.SetMinMax(-1, 1);

// 重新设置参数
pid_controller.SetParam(1, 2, 0.5, 20, 0.1);

// 单独设置微分器参数
pid_controller.d_controller.SetParam(0.2, 20);

// 重置内部状态（如积分器的积分量等）
pid_controller.ResetState();

// 输出单位阶跃响应的前 10 个数
for (size_t i = 0; i < 10; i++) {
    std::cout << pid_controller.Step(1) << std::endl;
}
```

示例2:

```cpp
using namespace control_system;

// 定义一个抗饱和的 PI 控制器
// 其中内部运算数据类型为 float
// Kp = 2
// Ki = 1
// Ts = 0.1 （采样周期）
// Kb = 1 （反算系数）
// 输出饱和下限: -5
// 输出饱和上限: 5
// 详细信息见头文件注释
PI_AntiWindup<float> pi_antiwindup{2, 1, 0.1, 1, -5, 5};
```

示例3:

```cpp
using namespace control_system;

// 如果不需要限幅，可以指定一个不带限幅的积分器，提高计算速度
// 实测在 STM32F407 上，Og 优化，不带限幅器的为 5587.37 千次/s，默认带限幅器的 PI 控制器计算速度为 2747.85 千次/s
// O3 优化下则分别为 27917.4 千次/s 和 11972.2 千次/s
PI<float, DiscreteIntegrator<float>> pi_controller{1.23, 0.54, 0.01};
```

### 离散时间积分器

头文件: `#include "control_system/discrete_integrator.hpp"`

```cpp
// 定义一个积分增益为 2 采样周期为 0.01s 的积分器
control_system::DiscreteIntegrator<float> integrator{2, 0.01};

// 定义一个带有积分限幅的积分器
control_system::DiscreteIntegratorSaturation<float> i_controller{{2, 0.01}, {-10, 10}};
```
