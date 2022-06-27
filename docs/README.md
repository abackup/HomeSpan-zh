# 欢迎！

个人复制翻译的[HomeSpan](https://github.com/HomeSpan/HomeSpan)，喜欢的请去原地址查看。

欢迎使用HomeSpan-一个强大且非常易于使用的Arduino库，完全使用Arduino IDE（https://www.arduino.cc） 创建您自己的基于ESP32 (https://www.espressif.com/en/products/modules/esp32) 的HomeKit设备。

HomeSpan 供了一个以微控制器为中心符合[Apple 的 HomeKit附件协议规范版本R2 (HAP-R2)](https://developer.apple.com/homekit/specification/)协议的实现，专为在Arduino IDE中运行的Espressif ESP32微控制器而设计. HomeSpan无需任何外部网桥或组件，仅需通过您的家庭WiFi网络直接与HomeKit配对。借助HomeSpan，您可以使用ESP32 I/O的全部功能来创建自定义控制软件或硬件，以通过iPhone、iPad或Mac上的Home App或使用Siri自动操作外部设备。

HomeSpan与[Arduino-ESP32 Board Manager](https://github.com/espressif/arduino-esp32)版本1和版本2完全兼容 。在版本1下，HomeSpan只能在ESP32上运行；在版本2下，HomeSpan 可以在ESP32以及Espressif的ESP32-S2和ESP32-C3芯片上运行。

### HomeSpan强调

* 提供自然、直观且**非常**易于使用的框架
* 利用独特的*以服务为中心*的方法来创建HomeKit设备
* 充分利用广受欢迎的Arduino IDE
* 100%符合HAP-R2协议
* 集成38个HomeKit服务
* 在附件或桥接模式下运行
* 支持与设置码或二维码配对

### 写予HomeSpan开发者

* 广泛使用Arduino串行监视器
  * 实时，易于理解的诊断
  * 对每个底层 HomeKit操作、数据请求和数据响应完全透明
  * 带有各种信息、调试和配置命令的命令行界面
* 内置数据库验证，确保您的配置满足所有 HAP 要求
* 利用ESP32的16通道PWM外设轻松控制的专用类：
  * LED 亮度
  * 伺服电机
* 集成按钮功能，支持单击、双击和长按
* 集成访问ESP32的片上远程控制外设，轻松生成IR和RF信号
* 用于控制单线和两线可寻址RGB、RGBW LED和LED灯带的专用类
* 用于用户定义日志消息的集成Web日志
* 广泛评论的教程草图，带您从HomeSpan的基础知识到高级HomeKit主题
* 展示 HomeSpan实际实现的其他示例和项目
* 一套解释HomeSpan API的各个方面的完整文档

### 写予HomeSpan用户

* 嵌入式WiFi接入点和Web界面允许最终用户（非开发人员）：
  * 使用自己的家庭WiFi凭据设置Homespan
  * 创建自己的HomeKit 配对设置代码
* 状态 LED 和控制按钮允许最终用户：
  * 强制解除设备与HomeKit的配对
  * 执行出厂重置
  * 启动WiFi接入点
* 一个独立的、详细的最终用户指南

## ❗最新更新-HomeSpan 1.5.1 (4/17/2022)

* **新的网络日志功能**
  * HomeSpan 现在可以托管用于消息记录的Web日志页面
  * 新的 WEBLOG() 宏使创建用户定义的日志消息变得容易
  * 提供可选使用 NTP 时间服务器来设置设备时钟，以便所有消息都可以正确加时间戳
  * 有关完整详细信息，请参阅 [HomeSpan 消息记录](https://github.com/HomeSpan/HomeSpan/blob/master/docs/Logging.md)

* **LOG() 宏的新 *printf* 样式格式**
   * 添加 LOG0()、LOG1() 和 LOG2() 宏的可变参数形式，以便它们可以以与标准 C printf 函数相同的方式使用
   * 大大简化了日志消息的创建
   * 请参阅 [HomeSpan 消息记录](https://github.com/HomeSpan/HomeSpan/blob/master/docs/Logging.md) 了解完整详情

* **新的 CUSTOM_SERV() 宏**
   * 允许创建自定义服务
   * 可以与现有的 CUSTOM_CHAR() 宏结合使用，以产生超出 HAP-R2 提供的服务
   * 包括一个完整的自定义 [压力传感器附件](https://github.com/HomeSpan/HomeSpan/blob/master/Other%20Examples/CustomService) 示例，该示例已被 *Eve for HomeKit* 识别
   * 详见【HomeSpan API 参考】(https://github.com/HomeSpan/HomeSpan/blob/master/docs/Reference.md)

* **用于 OTA 更新的新“安全加载”模式**
   * HomeSpan 可以检查以确保通过 OTA 上传的新草图是另一个 HomeSpan 草图。 如果不是，则上传失败
   * 在 OTA 更新后重新启动时，HomeSpan 会检查以确保在更新的草图中启用了 OTA。 如果没有，HomeSpan 会回滚到之前版本的草图
   * 详情请参阅 [HomeSpan OTA](https://github.com/HomeSpan/HomeSpan/blob/master/docs/OTA.md)
  
* **其他更新包括：**
   * `SpanUserCommand()` 的新（可选）参数，允许将指针传递给任意数据结构
   * 一个新的 SPAN_ACCESSORY() 宏，它扩展为创建配件时经常使用的通用代码片段
   * 更新和简化示例教程，并完全重做示例 7 和 11，以最好地符合 iOS 15.4 下的 Home App 行为

有关此更新中包含的所有更改和错误修复的详细信息，请参阅 [Releases](https://github.com/HomeSpan/HomeSpan/releases)。

# HomeSpan资源

HomeSpan 包括以下文档：

* [HomeSpan入门](https://github.com/abackup/HomeSpan-zh/blob/master/docs/GettingStarted.md) -设置开发HomeSpan设备所需的软件和硬件
* [HomeSpan API 概述](https://github.com/abackup/HomeSpan-zh/blob/master/docs/Overview.md) - HomeSpan API 概述，包括开发您的第一个 API 的分步指南 HomeSpan草图
* [HomeSpan 教程](https://github.com/abackup/HomeSpan-zh/blob/master/docs/Tutorials.md) - HomeSpan 教程草图指南
* [HomeSpan 服务和特性](https://github.com/abackup/HomeSpan-zh/blob/master/docs/ServiceList.md) - HomeSpan 支持的所有 HAP 服务和特性的列表
* [HomeSpan 配件类别](https://github.com/abackup/HomeSpan-zh/blob/master/docs/Categories.md) - HomeSpan 定义的所有 HAP 配件类别的列表
* [HomeSpan 命令行界面 (CLI)](https://github.com/abackup/HomeSpan-zh/blob/master/docs/CLI.md) - 配置 HomeSpan 设备的 WiFi 凭据，修改其 HomeKit 设置代码，监控并更新其状态，并从 Arduino IDE 串行监视器访问详细的实时设备诊断
* [HomeSpan 用户指南](https://github.com/abackup/HomeSpan-zh/blob/master/docs/UserGuide.md) - 关于如何配置已经编程的 HomeSpan 设备的 WiFi 凭据、修改其 HomeKit 设置的统包说明 编码，并将设备与 HomeKit 配对。 无需电脑！
* [HomeSpan API 参考](https://github.com/abackup/HomeSpan-zh/blob/master/docs/Reference.md) - HomeSpan 库 API 完整指南
* [HomeSpan 二维码](https://github.com/abackup/HomeSpan-zh/blob/master/docs/QRCodes.md) - 创建和使用二维码来配对 HomeSpan 设备
* [HomeSpan OTA](https://github.com/abackup/HomeSpan-zh/blob/master/docs/OTA.md) - 直接从 Arduino IDE 无线更新您的草图，无需串行连接
* [HomeSpan PWM](https://github.com/abackup/HomeSpan-zh/blob/master/docs/PWM.md) - 使用 ESP32 的片上 PWM 外设集成控制标准 LED 和伺服电机
* [HomeSpan 射频控制](https://github.com/abackup/HomeSpan-zh/blob/master/docs/RMT.md) - 使用 ESP32 的片上 RMT 外设轻松生成 RF 和 IR 远程控制信号
* [HomeSpan 灯带](https://github.com/abackup/HomeSpan-zh/blob/master/docs/Pixels.md) - 可寻址的单线和两线 RGB 和 RGBW LED 和 LED 灯条的集成控制
* [HomeSpan 电视服务](https://github.com/abackup/HomeSpan-zh/blob/master/docs/TVServices.md) - 如何使用 HomeKit 的无证电视服务和特性
* [HomeSpan 消息记录](https://github.com/abackup/HomeSpan-zh/blob/master/docs/Logging.md) - 如何生成日志消息以显示在 Arduino 串行监视器上以及可选地发布到 集成的 Web 日志页面
* [HomeSpan 项目](https://github.com/topics/homespan) - HomeSpan 库的实际应用
* [HomeSpan FAQ](https://github.com/abackup/HomeSpan-zh/blob/master/docs/FAQ.md) - 常见问题解答

请注意，所有文档都是受版本控制的，并且与每个分支相关联。 *master* 分支通常指向最新版本。 *dev* 分支（如果可用）将包含正在积极开发中的代码。

# 外部资源

除了 HomeSpan 资源之外，不熟悉 HomeKit 编程的开发人员还应下载 Apple 的 [HomeKit Accessory Protocol Specification, Release R2 (HAP-R2)](https://developer.apple.com/homekit/specification/)。 下载是免费的，但 Apple 要求您注册您的 Apple ID 才能访问该文档。

您***不需要***阅读整个文档。 HomeSpan 的全部意义在于它在引擎盖下实现了所有必需的 HAP 操作，因此您可以专注于编程任何所需的逻辑，以使用该设备控制您的实际设备（灯、风扇、RF 遥控器等） . 但是，您会发现 HAP 指南的第 8 章和第 9 章是非常宝贵的参考，因为它列出并描述了 HomeSpan 中实现的所有服务和特征，其中许多您将在自己的 HomeSpan 草图中经常使用。

---

### 反馈或问题？

请考虑添加到 [HomeSpan 讨论区](https://github.com/HomeSpan/HomeSpan/discussions)，或直接发送电子邮件至 [homespan@icloud.com](mailto:homespan@icloud.com)。
