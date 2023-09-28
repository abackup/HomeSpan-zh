<!---
<p>时间：2023.7.26翻译</p>
-->

# 脉宽调制 (PWM)

ESP32 拥有多达 16 个 PWM 通道，可用于驱动各种设备。 HomeSpan 包含一个集成的 PWM 库，其中包含专门用于控制**可调光 LED** 和**伺服电机**的类。这两个类都在一个独立的头文件中提供，可以通过将以下内容放在草图顶部附近来访问：

`#include "extras/PwmPin.h"`

## *LedPin(uint8_t pin [,float level [,uint16_t frequency [,boolean invert]]])*

创建此**类**的实例配置指定的 *pin* 以输出适用于控制可调光 LED 的 PWM 信号。参数及其默认值（如果未指定）如下：

  * *pin* —— 输出 PWM 控制信号的引脚
  * *level* —— 将 PWM 的初始占空比百分比设置为从 0（LED 完全关闭）到 100（LED 完全打开）。默认值 = 0（LED 最初关闭）
  * *频率* —— 设置 PWM 频率，单位为 Hz，范围为 1-65535（仅限 ESP32）或 5-65535（ESP32-S2 和 ESP32-C3）。如果未指定或设置为 0，则默认为 5000 Hz
 * *boolean* —— 如果为 true，PWM 信号的输出将反转。默认值 = 假
  
 支持以下方法：

* `void set(float level)`

   * 将PWM占空比百分比设置为 *level*，其中 *level* 范围从 0（LED 完全关闭）到 100（LED 完全打开）
  
* `int fade(float level, uint32_t fadeTime, int fadeType=LedPin::ABSOLUTE)`

  * 使用 ESP32 的 PWM 硬件，在最大 *fadeTime* 毫秒内将 LED 平滑淡入淡出到 *level*（从 0到100）
  * 如果*淡入淡出类型*设置为**LedPin::ABSOLUTE**（默认值），淡入淡出将占用*淡入淡出时间*指定的全部时间
  * 如果*淡入淡出类型*设置为**LedPin::PROPORTIONAL**，则淡入淡出时间将根据当前电平与指定电平之间的差异按比例缩小。例如，如果当前级别设置为 30，则
    * `fade(20, 1000, LedPin::ABSOLUTE)` 在 20 秒内将电平设置为 1，而
    * `fade(20, 1000, LedPin::PROPORTIONAL)` 在 20 毫秒内将级别设置为 100（因为级别只需要在 10 个单位中更改 100 个）
  * 这是一种**非阻塞**方法，将立即返回。淡入淡出发生在 ESP32 硬件控制的后台
  * 注意：淡入淡出一旦开始，在完成之前无法停止或更改（这是 ESP32 硬件的限制）
  * 如果淡入淡出已成功启动，则此方法返回 0，如果淡入淡出已在进行且尚未更改，则此方法返回 1（对于特定 LedPin 的淡入淡出，则直接忽略新的淡入淡出请求）
  * 使用*淡入淡出状态*方法（如下）确定任何给定 LedPin 的当前淡入淡出状态

* `int fadeStatus()`

  * 返回 LedPin 的淡入淡出状态。返回值如下所示：
    * **LedPin::NOT_FADING** - LedPin目前没有淡入淡出
    * **LedPin::FADING** - 淡入淡出 - LedPin上的淡入淡出当前正在进行中，无法更改/停止f
    * **LedPin::COMPLETED** - 淡入淡出刚刚完成
      * 返回此值后，后续调用`fadeStatus()`将返回**LedPin::NOT_FADING**（除非您再次调用`fade()`）
      * 通过`loop()`检查方法，您可以在淡入淡出`fadeStatus()==LedPin::COMPLETED`完成后触发新操作（如果需要）
    
* `int getPin()`

   * 返回引脚号（如果 LedPin 未成功初始化，则返回 -1）
  
LedPin 还包括一个静态类函数，可将色调/饱和度/亮度值（通常由 HomeKit 使用）转换为红/绿/蓝值（通常用于控制多色 LED）。

*`静态无效HSVtoRGB（float h，float s，float v，float *r，float *g，float *b）`

   * *h* - 输入色调值，范围 0-360
   * *s* - 输入饱和度值，范围 0-1
   * *v* - 输入亮度值，范围 0-1
   * *r* - 输出红色值，范围 0-1
   * *g* - 输出绿色值，范围 0-1
   * *b* - 输出蓝色值，范围 0-1

有关使用 LedPin 控制 RGB LED 的示例，请参阅教程草图 [#10 (RGB_LED)](../examples/10-RGB_LED)。

## *ServoPin(uint8_t pin [,double initDegrees [,uint16_t minMicros, uint16_t maxMicros, double minDegrees, double maxDegrees]])*

创建这个 **class** 的实例将指定的 *pin* 配置为输出 50 Hz PWM 信号，适用于控制大多数伺服电机。构造函数有三种形式：一种只有一个参数；另一种只有一个参数。一个有两个参数；一个包含所有六个参数。参数及其默认值（如果未指定）如下：

  * *pin* - 输出 PWM 控制信号的引脚。伺服电机的控制线应连接此引脚
  * *initDegrees* - 伺服电机应设置的初始位置（以度为单位）（默认 = 0°）
  * *minMicros* - 将伺服电机移动到 *minDegrees* 的“最小”位置的脉冲宽度（以微秒为单位）（默认 = 1000𝛍s）
  * *maxMicros* - 将伺服电机移动到 *maxDegrees* 的“最大”位置的脉冲宽度（以微秒为单位）（默认 = 2000𝛍s）
  * *minDegrees* - 伺服电机在接收到 *minMicros* 脉冲宽度时移动的位置（以度为单位）（默认值=-90°）
  * *maxDegrees* - 伺服电机在接收到 *maxMicros* 脉冲宽度时移动的位置（以度为单位）（默认值 = 90°）

*minMicros* 参数必须小于 *maxMicros* 参数，但允许将 *minDegrees* 设置为大于 *maxDegrees* 的值，并可用于反转伺服电机的最小和最大位置。支持以下方法：

* `void set（double position）`

  * 将伺服电机的位置设置为 *position*（以度为单位）。为了保护伺服电机，*position* 的值小于 *minDegrees* 会自动重置为 *minDegrees*，而大于 *maxDegrees* 的值会自动重置为 *maxDegrees*。
  
* `int getPin()`

  * 返回引脚号（如果 ServoPin 未成功初始化，则返回 -1）

可以在 Arduino IDE 的 *文件 → 示例 → HomeSpan → Other Examples →* [ServoControl](../Other%20Examples/ServoControl) 下找到一个展示如何使用 ServoPin 控制电动窗帘的水平倾斜的工作示例 ）。

### PWM 资源分配和限制

以下 PWM 资源可用：

* ESP32： 16个通道/8个定时器（分为两组不同的 8 个通道和 4 个定时器）
* ESP32-S2：8个通道 / 4个定时器
* ESP32-C3：6个通道 / 4个定时器
* ESP32-S3：8个通道 / 4个定时器

HomeSpan *自动* 在实例化时将通道和计时器分配给 LedPin 和 ServoPin 对象。 分配的每个引脚都消耗一个通道； 在所有通道中指定的每个*唯一*频率（对于 ESP32，在同一组内）消耗一个计时器。 HomeSpan 将通过为以相同频率运行的所有通道重复使用相同的计时器来节省资源。 *HomeSpan 还自动配置每个定时器，以支持指定频率的最大占空比。*

#### 诊断信息

**LedPin** 和 **ServoPin**类根据使用 Arduino IDE 编译草图时选择的*核心调试级别*向串行监视器输出*信息\[I\]* 和*警告\[W\]* 消息。当通道或定时器资源不足阻止创建新的 LedPin 或 ServoPin 对象时，将生成非致命警告消息。对未能正确创建的对象的方法的调用`set()`将被静默忽略。

---

[↩️](../README.md) 返回欢迎页面
