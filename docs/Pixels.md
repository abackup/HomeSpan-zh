# 可寻址 RGB LED

HomeSpan 包括两个专用类，可轻松控制“可寻址”RGB LED。 **Pixel()** 类用于只需要一根“数据”控制线的 RGB 和 RGBW LED，例如这个 8 像素 [NeoPixel RGB Stick](https://www.adafruit.com/product /1426) 或此单像素 [NeoPixel RGBW LED](https://www.adafruit.com/product/2759)。 **Dot()** 类用于需要两条控制线（“数据”和“时钟”）的 RGB LED，例如这个 144 像素 [DotStar RGB Strip](https://www.adafruit.com /product/2241) 或这个 60 像素 [RGB LED 灯条](https://www.sparkfun.com/products/14015)。

这两个类都允许您将多像素 LED 灯条中的每个“像素”单独设置为不同的 24 位 RGB 颜色（或 32 位颜色，如果使用 RGBW LED）。或者，这些类允许您简单地指定单个 24 位（或 32 位）颜色以在所有像素上复制。

这两个类的方法几乎相同，只需稍作修改，您就可以轻松地将为单线设备编写的代码与两线设备（反之亦然）互换。

这两个类都在一个独立的头文件中提供，可以通过将以下内容放在草图顶部附近来访问：

`#include "extras/Pixel.h"`

## *Pixel(uint8_t pin, [boolean isRGBW])*

创建此 **class** 的实例将指定的 *pin* 配置为输出适用于控制具有任意像素数的单线、可寻址 RGB 或 RGBW LED 设备的波形信号。 此类设备通常包含 SK6812 或 WS2812 LED。 参数及其默认值（如果未指定）如下：

   * *pin* - 将输出 RGB 控制信号的引脚； 通常连接到可寻址 LED 设备的“数据”输入
   * *isRGBW* - 对于包含 4 色（红/绿/蓝/白）LED 的 RGBW 设备，设置为 *true*； 对于更典型的 3 色 RGB 设备，设置为 *false*。 如果未指定，则默认为 *false*。 请注意，如果您使用的是 RGBW 设备，则必须将 *isRGBW* 标志设置为 *true*，即使您不打算使用白色 LED

设置像素颜色的两种主要方法是：

* `void set(Color color, int nPixels=1)`

  * 将单像素设备中像素的颜色，或等效地，将多像素设备中第一个 *nPixels* 的颜色设置为 *color*，其中 *color* 是 **Color** 类型的对象 定义如下。 如果未指定，*nPixels* 默认为 1（即单个像素）。 如果为 *nPixels* 指定的值与设备中实际 RGB（或 RGBW）像素的总数不匹配，这不是问题； 如果 *nPixels* 小于设备像素的总数，则只有第一个 *nPixels* 将设置为 *color*； 如果 *nPixels* 大于设备像素的总数，设备将简单地忽略附加输入
  
* `void set(Color *color, int nPixels)`

  * 将多像素设备中每个像素的颜色分别设置为 *nPixels* 大小的 **Color** 数组 *\*color* 中指定的颜色值，其中设备的第一个像素设置为该值 在 *color\[0\]* 中，第二个像素设置为 *color\[1\]* 中的值 ... 最后一个像素设置为 *color\[nPixels-1\]* 中的值 . 与上述类似，如果为 *nPixels* 指定的值与设备中实际 RGB（或 RGBW）像素的总数不匹配，则不是问题

在上述两种方法中，颜色都存储在一个 32 位 **Color** 对象中，该对象配置为保存四个 8 位 RGBW 值。 **Color** 对象可以实例化为单个变量（例如 `Pixel::Color myColor;`）或数组（例如`Pixel::Color myColors\[8\];`）。 请注意，**Pixel** 类使用的 **Color** 对象的范围仅限于 **Pixel** 类本身，因此您需要使用完全限定的类名“Pixel::Color”。 创建 **Color** 对象后，可以使用以下两种方法之一设置它存储的颜色：
  
  * `Color RGB(uint8_t r, uint8_t g, uint8_t b, uint8_t w=0)`

    * 其中 *r*、*g* 和 *b* 表示 0-255 范围内的 8 位红色、绿色和蓝色值，*w* 表示白色的 8 位值 [0-255] 引领。 白色值可以未指定，在这种情况下默认为 0。此外，*set()* 将忽略白色值，除非在构造函数中将 *isRGBW* 标志指定为 *true*
    * example: `myColor.RGB(255,255,0)` 将 myColor 设置为亮黄色
      
  * `Color HSV(float h, float s, float v, double w=0)`
    
    * 其中 *h*=Hue，范围为 0-360； *s*=0-100 的饱和度百分比； *v*=0-100 的亮度百分比。 这些值被转换为等效的 8 位 RGB 值 (0-255) 以存储在 *Color* 对象中。 请注意，*w* 值是单独处理的，它表示白色 LED 的亮度百分比（从 0-100），它也转换为 0-255 的 8 位值以存储在 **Color** 对象中。 与上面类似，可以不指定白色值，在这种情况下，它默认为 0
    * example: `myColor.HSV(120,100,50)` 将 myColor 设置为具有 50% 亮度的完全饱和绿色
      
请注意，上述两种方法都返回完整的 **Color** 对象本身，因此可以在需要 **Color** 对象的任何地方使用：例如：`Pixel p(5); 像素::颜色 myColor; p.set(myColor.RGB(255,215,0))` 将连接到引脚 5 的单个像素设备的颜色设置为亮金色。

**Pixel** 类还支持以下类级方法作为创建颜色的便捷替代方法：
  
*`静态颜色RGB（uint8_t r，uint8_t g，uint8_t b，uint8_t w = 0）`
   * 相当于`return(Color().RGB(r,g,b,w));`
   * 示例：`像素 p(8); p.set(Pixel::RGB(0,0,255),8);` 将 8 像素设备中每个像素的颜色设置为蓝色

*`静态颜色HSV（float h，float s，float v，double w=0）`
   * 相当于`return(Color().HSV(h,s,v,w));`
   * 示例：`Pixel::Color c[]={Pixel::HSV(120,100,100),Pixel::HSV(60,100,100),Pixel::HSV(0,100,100)};` 创建红黄绿红绿灯图案

最后，**Pixel** 类支持这两个额外但很少需要的方法：

* `int getPin()`

  * 返回引脚号，如果实例化由于资源不足而失败，则返回 -1

*`void setTiming（float high0，float low0，float high1，float low1，uint32_t lowReset）`

   * **Pixel** 类用于生成设置 RGB LED 设备颜色所需的“数据”信号的默认时序参数应该适用于大多数基于 SK6812 或 WS2812 驱动芯片的商业产品。 如果您需要覆盖类默认值并将其替换为您自己的计时参数，请使用此方法**仅**，其中
  
          * *high0* 和 *low0* 指定编码零位的脉冲的高相位和低相位的持续时间（以微秒为单位）；
          * *high1* 和 *low1* 指定脉冲编码一位的高相位和低相位的持续时间（以微秒为单位）； 和
        * *lowReset* 指定代表脉冲流结束的延迟（以微秒为单位）
    * 作为参考，**Pixel** 类使用以下默认值：*high0=0.32𝛍s、low0=0.88𝛍s、high1=0.64𝛍s、low1=0.56𝛍s、lowReset=80.0𝛍s*
    
### 资源使用和资源冲突

**Pixel** 类依靠 ESP32 的 RMT 外设来创建控制单线可寻址 RGB LED 所需的精确脉冲序列。 由于 **Pixel** 的每个实例化都会消耗一个 RMT 通道，因此您可以实例化的 **Pixel** 对象的数量（每个控制连接到特定引脚的单独的多像素 RGB LED 设备）受限于 RMT 的数量 可用如下：ESP32 - 8 个实例； ESP32-S2 - 4 个实例； ESP32-C3 - 2 个实例。

此外，**Pixel** 类经过优化，可处理包含数百个 RGB 或 RGBW 像素的任意长度的 LED 灯带。 为了有效地完成此任务，**Pixel** 类实现了自己的 RMT 驱动程序，这与 HomeSpan 的 **RFControl** 库使用的默认 RMT 驱动程序冲突。 不幸的是，这意味着您不能在同一个 HomeSpan 草图中同时使用 **Pixel** 类库和 **RFControl** 类库。

## *Dot(uint8_t dataPin, uint8_t clockPin)*

创建此**类**的实例将指定的引脚配置为输出波形信号，适用于控制具有任意像素数的两线、可寻址 RGB LED 设备。 此类设备通常包含 SK9822 或 APA102 LED，或嵌入式 WS2801 驱动芯片。 参数及其默认值（如果未指定）如下：

   * *dataPin* - 将输出 RGB 数据信号的引脚； 通常连接到可寻址 LED 设备的“数据”输入
   * *clockPin* - 将输出 RGB 时钟信号的引脚； 通常连接到可寻址 LED 设备的“时钟”输入

设置像素颜色的两种主要方法是：

* `void set(Color color, int nPixels=1)`

  * 将单像素设备中像素的颜色，或等效地，将多像素设备中第一个 *nPixels* 的颜色设置为 *color*，其中 *color* 是 **Color** 类型的对象 定义如下。 如果未指定，*nPixels* 默认为 1（即单个像素）。 如果为 *nPixels* 指定的值与设备中实际 RGB 像素的总数不匹配，这不是问题； 如果 *nPixels* 小于设备像素的总数，则只有第一个 *nPixels* 将设置为 *color*； 如果 *nPixels* 大于设备像素的总数，设备将简单地忽略附加输入
  
* `void set(Color *color, int nPixels)`

  * 将多像素设备中每个像素的颜色分别设置为 *nPixels* 大小的 **Color** 数组 *\*color* 中指定的颜色值，其中设备的第一个像素设置为该值 在 *color\[0\]* 中，第二个像素设置为 *color\[1\]* 中的值 ... 最后一个像素设置为 *color\[nPixels-1\]* 中的值 . 与上面类似，如果为 *nPixels* 指定的值与设备中实际 RGB 像素的总数不匹配，这不是问题

在上述两种方法中，颜色都存储在一个 32 位 **Color** 对象中，该对象配置为保存三个 8 位 RGB 值和一个可用于限制 LED 电流的 5 位值。 **Color** 对象可以实例化为单个变量（例如 `Dot::Color myColor;`）或数组（例如`Dot::Color myColors\[8\];`）。 请注意，**Dot** 类使用的 **Color** 对象的作用域为 **Dot** 类本身，因此您需要使用完全限定的类名“Dot::Color”。 创建 **Color** 对象后，可以使用以下两种方法之一设置它存储的颜色：
  
  * `Color RGB(uint8_t r, uint8_t g, uint8_t b, uint8_t driveLevel=31)`

    * 其中 *r*、*g* 和 *b* 表示 0-255 范围内的 8 位红色、绿色和蓝色值，*driveLevel* 表示用于限制的 5 位值 [0-31] LED 电流从 0（无电流）到 31（最大电流，这是默认值）。 通过将 *driveLevel* 设置为小于 31 的值来限制 LED 电流提供了一种无闪烁的方式来控制每个像素的 RGB LED 的亮度。
     * 示例：`myColor.RGB(128,128,0)` 使用红色和绿色 LED 的 50% 占空比（即 128/256）将 myColor 设置为半亮度黄色
     * 示例：`myColor.RGB(255,255,0,16)` 通过将像素的 LED 电流限制为其最大值的 50%（即 16/32），将 myColor 设置为黄色半亮度
      
  * `Color HSV(float h, float s, float v, double drivePercent=100)`
    
    * 其中 *h*=Hue，范围为 0-360； *s*=0-100 的饱和度百分比； *v*=0-100 的亮度百分比。这些值被转换为等效的 8 位 RGB 值 (0-255) 以存储在 *Color* 对象中。 *drivePercent* 参数以与上面的 *driveLevel* 相同的方式控制电流，不同之处在于它不是指定为 0-31 的绝对值，而是指定为 0 到 100 的百分比（默认值）
    * 示例：`myColor.HSV(120,100,50)` 使用 50% 占空比将 myColor 设置为半亮度的完全饱和绿色
    * 示例：`myColor.HSV(120,100,100,50)` 通过将像素的 LED 电流限制为其最大值的 50%，将 myColor 设置为在半亮度下完全饱和的绿色
      
请注意，上述两种方法都返回完整的 **Color** 对象本身，因此可以在需要 **Color** 对象的任何地方使用：例如：`Dot p(5,6);点::颜色 myColor; p.set(myColor.RGB(255,215,0))` 将连接到引脚 5 和 6 的单个像素设备的颜色设置为亮金色。

**Pixel** 类还支持以下类级方法作为创建颜色的便捷替代方法：
  
* `static Color RGB(uint8_t r, uint8_t g, uint8_t b, uint8_t driveLevel=31)`
  * equivalent to `return(Color().RGB(r,g,b,driveLevel));`
  * example: `Dot p(8,11);  p.set(Dot::RGB(0,0,255),8);` 将 8 像素设备中每个像素的颜色设置为蓝色

* `static Color HSV(float h, float s, float v, double drivePercent=100)`
  * equivalent to `return(Color().HSV(h,s,v,drivePercent));`
  * example: `Dot::Color c[]={Dot::HSV(120,100,100),Dot::HSV(60,100,100),Dot::HSV(0,100,100)};` to create a red-yellow-green traffic light pattern

与 **Pixel** 类不同，**Dot** 类*不*使用 ESP32 的 RMT 外围设备，因此您可以实例化的 **Dot** 对象的数量没有限制，也没有任何冲突 在同一个草图中同时使用 **Dot** 类和 **RFControl** 库。 此外，由于时钟信号是由 **Dot** 类本身生成的，因此无需设置时序参数，也不需要 *setTiming()* 方法。

### 示例草图

一个完整的示例展示了如何在 HomeSpan 草图中使用 Pixel 库来控制 RGB 像素设备、RGBW 像素设备和 RGB DotStar 设备，所有这些都来自 iPhone 上的 Home 应用程序，可以在 Arduino IDE 下找到 [*文件 → 示例 → HomeSpan → 其他示例 → 像素*](../Other%20Examples/Pixel)。

有关 Pixel 库的更完整展示，请查看 [HomeSpan 项目页面](https://github.com/topics/homespan) 上的 [Holiday Lights](https://github.com/HomeSpan/HolidayLights)。 此草图演示如何使用 Pixel 库通过 60 像素 RGBW 条生成各种特殊效果。 该草图还展示了使用 HomeSpan 的 [自定义特征宏](https://github.com/HomeSpan/HomeSpan/blob/master/docs/Reference.md#define-custom_charnameuuidpermsformatdefaultvalueminvaluemaxvaluestaticrange) 来实现特殊效果的“选择器”按钮 在 Eve for HomeKit 应用程序中使用。

---

[↩️](../README.md) 返回欢迎页面
