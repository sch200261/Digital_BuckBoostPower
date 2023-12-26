# Digital Buck Boost Converter软件设计书

## 开发环境

工程配置软件：STM32 cubeMX

工程文件类型：cubeIDE工程文件

代码编辑软件：VScode

集成开发环境：embedded IDE（EIDE）

编译器：GCC

使用语言：C和C++混合

C/C++语言标准：gnu11 / gnu++17

STM32库：HAL库

链接库选项：-lm -lstdc++

烧录配置：STLink SWD speed:4000kHz

## 工程结构

**\.eide .vscode文件夹**

用于存放EIDE / VScode配置文件

**build文件夹**

存放输出文件

**Core文件夹**

存放cubeMX调用HAL库或直接修改寄存器配置的函数与数据

**Drivers文件夹**

存放原生STM32  HAL库

**Middlewares文件夹**

存放FREERTOS库与代码

**Usercode文件夹**

存放用户代码

**.cproject文件**

cmake文件，保存包含目录与预处理宏定义等重要文件

**ControlBoard.code-workspace文件**

EIDE项目文件

**ControlBoard.ioc文件**

cubeMX工程文件

**STM32H743VITX_FLASH.ld文件**

flash烧写脚本

## Usercode外设库函数介绍

### 按钮库

#### 设计思路与注意事项

读取按钮GPIO电平，判断按钮状态；

注意事项：在使用中需设置消抖时间，因不确定用户需要使用HAL_Delay还是vTaskDelay()，故未在库中编写消抖代码。

#### button.hpp

按钮类

class button

成员变量

const GPIO_TypeDef *GPIOx;                    	 // GPIO组
const uint16_t GPIO_Pin;              			       // GPIO引脚
const GPIO_PinState button_down_level; 	// 默认有效电平

构造函数

Button(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState button_down_level = GPIO_PIN_RESET)

成员函数

bool IsButtonDown() const							   //判断按钮是否按下

GPIO_PinState GetLevel() const					    //返回引脚电平状态

### RGB发光二极管库

#### 设计思路与注意事项

使用三组PWM控制RGB LED的通断程度，RGB各通道亮度由占空比决定；无注意事项

#### led.hpp

颜色类

class Color

成员变量

const uint8_t R; // 红色亮度0-255
const uint8_t G; // 绿色亮度0-255
const uint8_t B; // 蓝色亮度0-255

构造函数

Color(uint8_t R, uint8_t G, uint8_t B)

成员函数

无



LED类

class Led

成员变量

uint16_t Red   = 0;          						// 红色比较值0-1199
uint16_t Green = 0;          					  // 绿色比较值0-1199
uint16_t Blue  = 0;          					    // 蓝色比较值0-1199
uint32_t RedChannel;         				   // 红色PWM通道
uint32_t GreenChannel;       			     // 绿色PWM通道
uint32_t BlueChannel;        				   // 蓝色PWM通道
TIM_HandleTypeDef *Redtim;   		  // 红色或三色LED定时器编号
TIM_HandleTypeDef *Greentim; 		// 绿色LED定时器编号，不填视为与红色一致
TIM_HandleTypeDef *Bluetim;  		  // 蓝色LED定时器编号，不填视为与红色一致
bool LED_State = false;      					// LED状态，true为亮

构造函数

Led(uint32_t RedChannel, uint32_t GreenChannel, uint32_t BlueChannel, TIM_HandleTypeDef *Redtim, TIM_HandleTypeDef *Greentim = nullptr, TIM_HandleTypeDef *Bluetim = nullptr)

成员函数

void SetColor(uint8_t R, uint8_t G, uint8_t B)		//使用RGB数组设置颜色

void SetColor(Color RGB)										  //使用颜色类设置颜色

void LED_ON(void)													   //启动LED

void LED_OFF(void)													   //关闭LED

### 互补中心对齐PWM库

#### 设计思路与注意事项

使用高级定时器生成200kHz三角波载波的一对互补PWM，配置为fast mode + GPIO very High，测试得到上升沿震荡波谷最低电平2.8V（数字电平容差要求>2V），下降沿波峰最高电平0.4V（数字电平容差要求<0.8V）。信号质量相对较高，如需进一步优化，需修改Sheet在PWM通道上添加端接电阻。

注意事项：电源板使用的半桥驱动SI8233-BD-D-IS具有可编程死区功能，可通过修改DT脚对地电阻Rdt大小进行编程。默认使用3.3k，死区时间Deadtime = 3300 * 0.01（ns），即33ns。需测试电源板mos开关的Rise time和Fall time再按需求修改Rdt或设置软件死区。

#### mospwm.hpp

互补PWM类

class CoPWM

成员变量

uint16_t Pulse = 0;              						   // PWM脉宽 0-ReloadCount
const TIM_HandleTypeDef *PWMtim; 	  // 互补PWM定时器编号
const uint32_t Channel;          					 // PWM通道
const uint16_t ReloadCount;      				// PWM重装载值
bool PWM_State = false;          					// PWM状态，true为开启

构造函数

CoPWM(TIM_HandleTypeDef *PWMtim, uint32_t Channel, uint16_t ReloadCount)

成员函数

void PWM_ON(void)					//开启coPWM

void PWM_OFF(void)					//关闭coPWM

void SetDuty(double Duty)		  //设置占空比，为高有效，P通道占空比