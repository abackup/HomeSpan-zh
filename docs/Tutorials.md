# HomeSpan 教程

HomeSpan 库包括 16 个越来越复杂的教程草图，带您了解 HomeSpan 的所有功能和特性。这些草图带有大量注释，您甚至可以通过阅读所有示例来了解很多关于 HomeKit 本身的知识。如果您已经将 HomeSpan 加载到 Arduino IDE 中，则可以在 *File → Examples → HomeSpan* 下找到教程。每个草图都可以编译并上传到您的 ESP32 设备，这样您就可以看到它们的运行情况。或者，您可以通过单击下面的任何标题来探索 GitHub 中的代码。注意：在浏览教程之前，您可能需要先通读 [HomeSpan API 概述](Overview.md)。如果你这样做，它们可能会更有意义！

> :heavy_check_mark: 每个示例都设计为在将 ESP32 与 HomeKit 配对后进行操作，以便您可以从 iPhone、iPad 或 Mac 上的 Home App 控制 HomeSpan。原则上，一旦您配置设备并将其与 HomeKit 配对，您的 Home App 应该会在您上传不同的教程时自动反映配置中的所有更改。然而，实际上情况并非总是如此，因为 HomeKit 有时会缓存有关设备的信息，这意味着您在 Home App 中看到的内容可能与您的草图不完全同步。如果发生这种情况，取消配对然后重新配对 ESP32 设备通常可以解决问题。如果没有，您可能需要重置 ESP32 设备上的 ID，以便 HomeKit 认为它是新设备并且不会使用任何缓存数据。这很容易做到 - 请参阅 [HomeSpan 命令行界面 (CLI)](CLI.md) 页面了解详细信息。

### [示例 1 - SimpleLightBulb](../examples/01-SimpleLightBulb)
第一个示例介绍了 HomeSpan 库，并演示了如何使用 HomeSpan 附件、服务和特性对象的组合来实现简单的开/关灯控制。将此草图上传到您的 HomeSpan 设备并且设备与您的家配对后，您的 iPhone、iPad 或 Mac 的家庭应用程序中将出现一个新的“灯泡”图块。虽然瓷砖将完全可操作（即您可以将灯泡的状态从“开”或“关”更改），但我们尚未将实际的灯或 LED 连接到 HomeSpan 设备，因此不会亮起任何真实的东西。相反，在这个和接下来的几个示例中，我们将专注于了解配置 HomeKit 控件的不同方式。从示例 5 开始，我们将把 LED 连接到设备，并介绍在 Home App 中实际打开和关闭 LED 的方法。此示例中涵盖的 HomeSpan API 主题包括：

* `homeSpan` 全局对象，它是 `begin()` 和 `poll()` 方法
* 引用在 `Categories::` 命名空间中定义的 HomeSpan 类别
* 实例化一个新的 `SpanAccessory`
* 实例化在 `Service::` 和 `Characteristic::` 命名空间中定义的 HomeSpan 服务和特征

### [示例 2 - TwoSimpleLightBulbs](../examples/02-TwoSimpleLightBulbs)
示例 2 通过实现两个灯泡来扩展示例 1，每个灯泡都作为自己的附件。

### [示例 3 - CeilingFanWithLight](../examples/03-CeilingFanWithLight)
示例 3 展示了如何将多个服务添加到单个配件中，从而使我们能够创建多功能配件，例如带吸顶灯的吊扇。

### [示例 4 - AdvancedCeilingFan](../examples/04-AdvancedCeilingFan)
示例 4 通过添加特性来设置风扇速度、风扇旋转方向和灯光亮度，从而扩展了示例 3。 此示例中涵盖的新 HomeSpan API 主题包括：

* 使用 `setRange()` 设置特征的允许范围和增量值

### [示例 5 - WorkingLED](../examples/05-WorkingLED)
示例 5 通过添加实际控制从 HomeKit 连接到 ESP32 的 LED 所需的代码来扩展示例 2。在示例 2 中，我们构建了所有功能，以在 HomeKit 中创建一个显示开/关灯的“Tile”Acessories，但这些控件实际上并未对 ESP32 进行任何操作。要操作实际设备，需要对 HomeSpan 进行编程，以通过执行某种形式的操作来响应来自 HomeKit 的“更新”请求。此示例中涵盖的新 HomeSpan API 主题包括：

* 从基础 HomeSpan 服务类创建派生的特定于设备的服务结构（类）
* 将派生的服务类放在它们自己的 \*.h 文件中以提高可读性和可移植性
* 为您的派生服务实现虚拟 `update()` 方法
* 使用 `SpanCharacteristic *` 指针保存对特征对象的引用
* 使用 `getVal()` 和 `getNewVal()` 方法检索新的和更新的特征值

### [示例 6 - DimmableLED](../examples/06-DimmableLED)
示例 6 更改了示例 5，使得 LED #2 现在可以调光，而不仅仅是开/关。此示例中涵盖的新 HomeSpan API 主题包括：

* 实现脉宽调制 (PWM) 以通过实例化“LedPin()”对象来控制连接到任何 ESP32 引脚的 LED
* 使用 LedPin `set()` 方法设置 LED 的亮度
* 将类似的派生服务类存储在同一个 \*.h 文件中以便于使用

### [示例 7 - 附件名称](../examples/07-附件名称)
示例 7 演示了如何将示例 6 中创建的两个 LED 配件的名称从 Home App 生成的默认值更改为更有用和自定义的名称。

### [示例 8 - 桥梁](../examples/08-Bridges)
示例 8 在功能上与示例 7 相同，只是我们没有定义两个附件（一个用于开/关 LED，一个用于可调光 LED），而是定义了三个附件，其中第一个充当 HomeKit 桥接器。

### [示例 9 - MessageLogging](../examples/09-MessageLogging)
示例 9 说明了如何将日志消息添加到 HomeSpan 草图。除了包含新的日志消息外，该代码与示例 8 相同。此示例中涵盖的新 HomeSpan API 主题包括：

* 使用 `LOG0()`、`LOG1()` 和 `LOG2()` 宏来为不同的日志级别创建日志消息
* 使用 `homeSpan.setLogLevel()` 方法设置草图的初始日志级别

### [示例 10 - RGB_LED](../examples/10-RGB_LED)
示例 10 说明了如何控制 RGB LED 来设置任何颜色和亮度。此示例中涵盖的新 HomeSpan API 主题包括：

* 使用 `PwmPin::HSVtoRGB()` 将 HomeKit 色相/饱和度/亮度级别转换为红/绿/蓝级别
* 使用 `getVal()` 的可选模板功能，例如 `getVal<float>()`

### [示例 11 - ServiceNames](../examples/11-ServiceNames)
示例 11 演示了如何将多服务附件中不同服务的名称从 Home App 生成的默认值更改为更有用和自定义的名称。这些示例还探讨了 Home App 显示这些名称的方式和时间，以及当设备配置为 Bridge 时 Home App 如何为 Accessory Tile 选择适当的图标。

### [示例 12 - ServiceLoops](../examples/12-ServiceLoops)
示例 12 引入了 HomeKit *Event Notifications* 来实现两个新附件 - 温度传感器和空气质量传感器。当然，出于本示例的目的，我们实际上不会将这些物理设备连接到 ESP32，但我们将模拟定期“读取”它们的属性，并通知 HomeKit 任何更改的值。此示例中涵盖的新 HomeSpan API 主题包括：

* 在派生服务中实现虚拟 `loop()` 方法
* 使用 `timeVal()` 方法跟踪自上次更新特性以来经过的时间
* 使用 `setVal()` 方法设置特征值并触发事件通知

### [示例 13 - TargetStates](../examples/13-TargetStates)
示例 13 我们通过实现两个新服务来演示同时使用 `update()` 和 `loop()` 方法：车库门开启器和电动窗帘。这两个示例都展示了 HomeKit 的 Target-State/Current-State 框架。

### [示例 14 - EmulatedPushButtons](../examples/14-EmulatedPushButtons)
示例 14 演示了如何使用 Service 的 `loop()` 方法中的 `setVal()` 和 `timeVal()` 方法在 Home App 中创建一个模拟按钮开关的图块。在此示例中，按下 Home App 中的磁贴将使其打开，LED 闪烁 3 次，然后关闭（就像真正的按钮可能会做的那样）。

### [示例 15 - RealPushButtons](../examples/15-RealPushButtons)
此示例介绍了 HomeSpan 功能，可让您轻松地将真正的按钮连接到 ESP32 设备上的任何引脚。然后，这些按钮可用于手动控制连接到设备的任何设备，例如灯或风扇。在此示例中，我们实现了 3 个按钮来控制 LED 的电源、亮度和“收藏夹”设置，使用单次、双次和长按按钮的组合。每次按下按钮后，使用 `setVal()` 方法将事件通知发送回 HomeKit，以便 Home App 磁贴立即反映您对 LED 功率和亮度的手动更改。此示例中涵盖的新 HomeSpan API 主题包括：

* 使用 `SpanButton()` 在任何 ESP32 引脚上创建按钮对象
* 在派生服务中实现虚拟 `button()` 方法
* 解析 SINGLE、DOUBLE 和 LONG 按钮按下

### [示例 16 - ProgrammableSwitches](../examples/16-ProgrammableSwitches)
示例 16 没有引入任何新的 HomeSpan 功能，而是展示了 HomeKit 的一个独特功能，您可以使用 HomeSpan 轻松访问该功能。在之前的所有示例中，我们使用 ESP32 来控制本地设备 - 直接连接到 ESP32 设备的设备。然后，我们了解了如何通过 HomeKit 的 iOS 或 MacOS Home App 或通过添加直接连接到 ESP32 设备的本地按钮来控制设备。在这个例子中，我们做相反的事情，并使用连接到 ESP32 的按钮来控制任何类型的其他 HomeKit 设备。为此，我们使用 HomeKit 的 Stateless Programmable Switch Service。

### [示例 17 - LinkedServices](../examples/17-LinkedServices)
示例 17 介绍了链接服务的 HAP 概念，并演示了如何通过实现多头淋浴来使用它们。此示例还说明了一些不同的编码风格，展示了 HomeSpan 的 C++ *基于结构*设计范例的强大功能和灵活性。此示例中涵盖的新 HomeSpan API 主题包括：

* 使用 `addLink()` 方法创建链接服务

### [示例 18 - SavingStatus](../examples/18-SavingStatus)
示例 18 演示了通过两个可调光 LED 的实现，如何将特性值自动保存在设备的非易失性存储器 (NVS) 中，以便在设备断电时在启动时恢复。此示例中涵盖的新 HomeSpan API 主题包括：

* 通过将构造函数的第二个参数设置为 `true` 来指示 HomeSpan 在 NVS 中存储 Characteristic 的值

### [示例 19 - WebLog](../examples/19-WebLog)
示例 19 通过实现两个开/关 LED 说明如何将 Web 日志添加到 HomeSpan 草图中，如何使用 NTP 时间服务器同步设备的内部时钟，以及如何创建自己的 Web 日志消息。此示例中涵盖的新 HomeSpan API 主题包括：
* enabling the HomeSpan Web Log and specifying an optional NTP time server with the `homeSpan.enableWebLog()` method
* using the `WEBLOG()` macro to create Web Log messages

## 其他示例

以下示例展示了 HomeSpan 文档的不同部分中引用的各种 HomeSpan 和 HomeKit 功能。这些草图可以在 Arduino IDE 中的 *File → Examples → HomeSpan → Other Examples* 下找到

### [TableLamp](../Other%20Examples/TableLamp)
台灯配件的基本实现。用作 [HomeSpan API 概述](Overview.md) 中的教程

### [RemoteControl](../Other%20Examples/RemoteControl)
一个独立的示例，展示了如何使用 HomeSpan 的 *RFControl* 类来生成自定义脉冲序列。出于说明目的，脉冲宽度非常长，适合输出到 LED，因此您可以“看到”脉冲序列。请参阅 [RF/IR Generation](RMT.md) 页面了解完整详情

### [ServoControl](../Other%20Examples/ServoControl)
Window Shade 的实现，它使用 HomeSpan 的 *ServoPin* 类来控制板条的水平倾斜。有关完整详细信息，请参阅 [ServoPin](PWM.md#servopinuint8_t-pin-double-initdegrees-uint16_t-minmicros-uint16_t-maxmicros-double-mindegrees-double-maxdegrees)

### [电视](../Other%20Examples/Television)
HomeKit *undocumented* 电视服务的示例，展示了如何使用不同的特性来控制电视的电源、输入源和其他一些功能。请参阅 [电视服务和特征](TVServices.md) 页面了解完整详情

### [像素](../Other%20Examples/Pixel)
演示如何使用 HomeSpan 的 *Pixel* 和 *Dot* 类来控制单线和两线可寻址 RGB 和 RGBW LED。有关完整详细信息，请参阅 [Addressable RGB LED](Pixels.md) 页面

### [CustomService](../Other%20Examples/CustomService)
演示如何在 HomeSpan 中创建自定义服务和自定义特征，以实现 *Eve for HomeKit* 应用程序识别的大气压力传感器。有关完整详细信息，请参阅 [自定义特征和自定义服务宏](Reference.md#custom-characteristics-and-custom-services-macros)
 
---

[↩️](README.md) 返回欢迎页面
