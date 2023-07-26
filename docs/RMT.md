<!---
<p>时间：2023.7.26翻译</p>
-->

# 遥控射频/红外线信号产生

ESP32 具有片上信号发生器外设，旨在驱动射频或红外发射器。 HomeSpan 包含一个易于使用的库，可与此外围设备连接，因此您可以通过一些额外的电子组件创建一个 HomeSpan 设备，直接从 iPhone 上的 Home App 或通过 Siri 控制 RF 或 IR 设备。 通过将以下内容放在草图顶部附近可以访问该库：

`#include "extras/RFControl.h"`

## *RFControl(int pin, boolean refClock=true)*

创建此 **类** 的实例会初始化 RF/IR 信号发生器并指定 ESP32 *pin* 以输出信号。 如果驱动多个 RF/IR 发射器（每个都连接到不同的 *pin*），您可以创建多个此类的实例，但受到以下限制：ESP32-8个实例； ESP32-S2-4个实例； ESP32-C3- 2个实例。可选参数 *refClock* 将在下面的 `start()` 方法下更全面地描述。

信号被定义为一系列 HIGH 和 LOW 相位，它们一起形成一个脉冲序列，您可以在其中指定每个 HIGH 和 LOW 相位的持续时间，以 *ticks* 为单位，在下图中分别显示为 H1-H4 和 L1-L4：

![脉冲列车](images/pulseTrain.png)

由于大多数 RF/IR 信号多次重复相同的脉冲序列，因此应延长最后一个 LOW 阶段的持续时间，以考虑脉冲序列重复之间的延迟。脉冲序列被编码为 32 位字的顺序数组，其中每个 32 位字代表使用以下协议的单个脉冲：

  * 位 0-14：要传输的脉冲的第一部分的持续时间，以 *ticks* 为单位，范围为 0-32767
  * 位 15：指示要发送的脉冲的第一部分是 HIGH (1) 还是 LOW (0)
  * 位 16-30：要传输的脉冲的第二部分的持续时间，以 *ticks* 为单位，范围为 0-32767
  * 位 31：指示要发送的脉冲的第二部分是 HIGH (1) 还是 LOW (0)

HomeSpan 提供了两种简单的方法来创建、存储和传输脉冲序列。第一种方法依赖于这样一个事实，即每个 RFControl 实例都维护自己的内部存储器结构来存储任意长度的脉冲序列。下面描述的函数 `clear()`、`add()` 和 `pulse()` 允许您使用此内部存储器结构创建脉冲序列。然后使用`start()`函数开始传输完整的脉冲序列。当需要根据需要动态创建脉冲序列时，通常使用此方法，因为每个 RFControl 实例一次只能存储一个脉冲序列。

在第二种方法中，您使用上述协议在 32 位字的外部数组中创建一个或多个脉冲序列。 要开始传输特定脉冲串，请使用指向包含该脉冲串的外部数组的指针引用调用`start()`函数。 当您想要预先计算许多不同的脉冲序列并让它们根据需要准备好发送时，通常使用此方法。 请注意，此方法需要将数组存储在 RAM 中，而不是 PSRAM 中。

每个功能的详细信息如下：

* `void clear()`

  * 清除 RFControl 特定实例的脉冲序列内存结构

* `void phase(uint32_t numTicks, uint8_t phase)`

  * 将 HIGH 或 LOW 相位附加到 RFControl 特定实例的脉冲序列内存缓冲区

    * *numTicks* - 脉冲阶段的持续时间，以 *ticks* 为单位。 允许大于 32767 个ticks的持续时间（系统自动创建每个最多 32767 个ticks的重复脉冲，直到达到指定的 *numTicks* 持续时间）
    
    * *phase* - 设置为 0 以创建 LOW 阶段； 设置为 1（或任何非零数）以创建 HIGH 阶段
    
  * 相同类型的重复阶段（例如，HIGH 后跟另一个 HIGH）是允许的，并导致单个 HIGH 或 LOW 阶段的持续时间等于为每个重复阶段指定的 *numTicks* 之和（这在生成曼彻斯特编码信号时很有帮助）

* `void add(uint32_t onTime, uint32_t offTime)`

  * 将持续时间为 *onTime* 后跟 *offTime* 的单个 HIGH/LOW 脉冲附加到 RFControl 特定实例的脉冲序列。 这在功能上等同于调用 `phase(onTime,HIGH);` 后跟 `phase(offTime,LOW);` 定义如上
  * 
* `void enableCarrier(uint32_t freq, float duty=0.5)`

  * 能够使用“方”载波调制脉冲序列。 在实践中，这仅用于 IR 信号（不是 RF）
  
    * *freq* - 载波的频率，以 Hz 为单位。 如果freq=0，载波被禁用
    
    * *duty* - 载波的占空比，从 0 到 1。 如果未指定，默认值为 0.5

  * 如果指定的频率和占空比的组合超出支持的配置范围，RFControl 将报告错误

* `void disableCarrier()`

  * 禁用载波。 相当于`enableCarrier(0);`

* `void start(uint8_t _numCycles, uint8_t tickTime)`
* `void start(uint32_t *data, int nData, uint8_t nCycles, uint8_t tickTime)`

 * 在第一个变体中，这将开始传输存储在给定 RFControl 实例的内部存储器结构中的脉冲序列，该实例是使用上面的`clear()`, `add()`和 `phase()`函数创建的 . 在第二个变体中，这将启动存储在包含 *nData* 32 位字的外部阵列 *data* 中的脉冲序列的传输。 信号将在 RFControl 实例化时指定的引脚上输出。 请注意，这是一个阻塞调用——该方法等到传输完成后再返回。 这不应在程序操作中产生明显的延迟，因为大多数 RF/IR 脉冲序列只有几十毫秒长
 
   * *numCycles* - 发送脉冲串的总次数（即值 3 表示脉冲串将被发送一次，然后再重新发送 2 次）。 这是一个可选参数，如果未指定，则默认值为 1。
   
   * *tickTime* - *tick* 的持续时间，以 ***clock units***。 如果未指定，这是一个可选参数，默认值为 1 *clock unit*。 有效范围是 1-255 *时钟单位*，或设置为 0 表示 256 *时钟单位*。 *clock unit* 的持续时间由 *refClock* 参数（第二个可选参数，在上述 RFControl 构造函数中）确定。 如果 *refClock* 设置为 true（默认），RFControl 使用 ESP32 的 1 MHz 参考时钟进行计时，以便每个 *clock unit* 等于 1𝛍s。 如果 *refClock* 设置为 false，RFControl 使用 ESP32 更快的 80 MHz APB 时钟，因此每个 *clock unit* 等于 0.0125𝛍s（1/80 微秒）
   
* 为了帮助创建存储在 32 位字的外部数组中的脉冲序列，RFControl 包含宏 *RF_PULSE(highTicks,lowTicks)*，它返回一个格式正确的 32 位值，代表单个 HIGH/LOW 脉冲 持续时间 *highTicks* 后跟 *lowTicks*。 这基本上类似于`add()` 函数。 例如，下面的代码片段显示了两种创建和传输相同 3 脉冲脉冲序列的方法 --- 唯一的区别是一种使用 RFControl 的内部存储器结构，而第二种使用外部阵列：

```C++

RFControl rf(11);  // 创建一个 RFControl 实例

rf.clear();        // 清除内部存储器结构
rf.add(100,50);    // 创建 100 个高点的脉冲，然后是 50 个低点的脉冲
rf.add(100,50);    // 创建第二个 100 记号 HIGH 后跟 50 记号 LOW 的脉冲
rf.add(25,500);    // 创建第三个 25 记号 HIGH 脉冲，然后是 500 记号 LOW
rf.start(4,1000);  // 开始发送脉冲串； 重复4个周期； 一个ticks声 = 1000𝛍s

uint32_t pulseTrain[] = {RF_PULSE(100,50), RF_PULSE(100,50), RF_PULSE(25,500)};    // 在外部阵列中创建相同的脉冲序列
rf.start(pulseTrain,3,4,1000);  // 使用相同的参数开始传输
```
#### 诊断消息

**RFControl**类根据使用 Arduino IDE 编译草图时选择的核心调试级别将*警告\[W\]* 消息输出到串行监视器。当通道资源不足阻止创建新的 RFControl 对象时，将生成非致命警告消息。对未能正确创建的对象的方法`start()`的调用将被静默忽略。

## 示例 RFControl 草图

下面是一个完整的草图，它产生两个不同的脉冲序列，信号输出链接到 ESP32 设备的内置 LED（而不是 RF 或 IR 发射器）。 出于说明目的，刻度持续时间已设置为非常长的 100 秒，脉冲时间范围为 1000-10,000 Ticks，以便在 LED 上轻松识别各个脉冲。 请注意，此示例草图也可在 Arduino IDE 中的*文件 → 示例 → HomeSpan → Other Examples →*[RemoteControl](../Other%20Examples/RemoteControl) 下找到。

```C++
/* HomeSpan Remote Control Example */

#include "HomeSpan.h"             // 包括 HomeSpan 库
#include "extras/RFControl.h"     // 包括射频控制库

void setup() {     
 
  Serial.begin(115200);           // 启动串行接口
  Serial.flush();
  delay(1000);                    // 等待接口刷新

  Serial.print("\n\nHomeSpan RF Transmitter Example\n\n");

  RFControl rf(13);               // 创建一个 RFControl 实例，将信号输出到 ESP32 上的引脚 13

  rf.clear();                     // 清除脉冲序列内存缓冲区

  rf.add(5000,5000);              // 创建一个具有三个 5000 节拍高/低脉冲的脉冲序列
  rf.add(5000,5000);
  rf.add(5000,10000);             // 最后低点的双倍持续时间

  Serial.print("Starting 4 cycles of three 500 ms on pulses...");
  
  rf.start(4,100);                // 开始传输 4 个周期的脉冲序列，1 个ticks = 100 微秒

  Serial.print("Done!\n");

  delay(2000);

  rf.clear();

  for(int i=1000;i<10000;i+=1000)
    rf.add(i,10000-i);
  rf.add(10000,10000);
  
  Serial.print("Starting 3 cycles of 100-1000 ms pulses...");
  
  rf.start(3,100);                // 以 1 个ticks = 100 微秒开始传输 3 个脉冲序列周期

  Serial.print("Done!\n");
  
  Serial.print("\nEnd Example");
  
} // end of setup()

void loop(){

} //结束循环
```

---

[↩️](../README.md) 返回欢迎页面
