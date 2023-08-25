时间：2023.8.9 翻译

# 欢迎！

个人复制翻译的[ HomeSpan](https://github.com/HomeSpan/HomeSpan)，喜欢的请去[ 原地址 ](https://github.com/HomeSpan/HomeSpan)查看。

欢迎使用 HomeSpan —— 一个强大且非常易于使用的 Arduino 库，完全使用 ArduinoIDE 创建您自己的基于 ESP32 的 HomeKit 设备。

HomeSpan 提供了一个以微控制器为中心符合 Apple 的 HomeKit 附件协议规范版本 R2(HAP-R2) 协议的实现，专为在 Arduino IDE 中运行的 ESP32 微控制器而设计。HomeSpan 无需任何外部网桥或组件，仅需通过您的家庭 WiFi 直接与 HomeKit 配对。借助 HomeSpan，您可以使用 ESP32 I/O 的全部功能来创建自定义控制软件或硬件，通过 iPhone、iPad 或 Mac 上的 Home App 或使用 Siri 自动操作外部设备。

HomeSpan 需要 Arduino-ESP32 Board Manager 的 2.0.0 或更高版本，并且已经过版本 2.0.9 （推荐）的测试。HomeSpan 可以在原装 ESP32 以及乐鑫 ESP32-S2、ESP32-C3 和 ESP32-S3 芯片上运行。

### HomeSpan 亮点

* 提供自然、直观且**非常**易于使用的框架
* 利用独特的**以服务为中心**的方法来创建 HomeKit 设备
* 充分利用广受欢迎的 Arduino IDE
* 100% 符合 HAP-R2 协议
* 集成 41 个 HomeKit 服务
* 在附件或桥接模式下运行
* 支持与设置码或二维码配对

### 写予 HomeSpan 开发者

* 广泛使用 Arduino 串行监视器
  * 实时、易于理解的诊断
  * 完全透明 HomeKit 的每个底层操作、数据请求和数据响应
  * 带有各种信息、调试和配置命令的命令行界面
* 内置数据库验证，确保您的配置满足所有 HAP 要求
* 利用 ESP32 的 16 通道 PWM 外设轻松控制的专用类：
  * LED 亮度（包括自动淡入淡出效果）
  * 伺服电机
* 集成按钮功能，支持单击、双击和长按
  * 将 ESP32 引脚连接到接地或 VCC 的物理按钮
  * 连接到 ESP32 针脚的触摸板或者传感器（适用于支持触摸板的 ESP32 设备）
* 集成访问 ESP32 的片上远程控制外设，轻松生成 IR 和 RF 信号
* 用于控制单线和两线可寻址 RGB、RGBWLED 和 LED 灯带的专用类
* 用于控制步进电机的专用类，可以在后台平稳运行而不干扰 HomeSpan
* 使用 ESP-NOW 促进 ESP32 设备之间的无缝点对点通信的专用类
* 用于用户定义日志消息的集成网页日志
* 广泛评论的教程草图，带您从 HomeSpan 的基础知识到高级 HomeKit 主题
* 展示 HomeSpan 实际实现的其他示例和项目
* 一套解释 HomeSpan API 的各个方面的完整文档

### 写予 HomeSpan 用户

* 嵌入式 WiFi 接入点和网页界面允许最终用户（非开发人员）用于：
  * 使用自己的家庭 WiFi 凭据设置 HomeSpan
  * 创建自己的 HomeKit 配对设置代码
* 状态 LED 和控制按钮允许最终用户用于：
  * 强制解除设备与 HomeKit 的配对
  * 执行出厂重置
  * 启动 WiFi 接入点
* 一个独立的、详细的最终用户指南

# HomeSpan 资源

HomeSpan 包括以下文档：

* [ HomeSpan入门 ](docs/GettingStarted.md) —— 设置开发 HomeSpan 设备所需的软件和硬件
* [ HomeSpan API 概述 ](docs/Overview.md) —— HomeSpanAPI 概述，包括开发您的第一个 API 的分步指南 HomeSpan 草图
* [ HomeSpan 教程 ](docs/Tutorials.md) —— HomeSpan 教程草图指南
* [ HomeSpan 服务和特性 ](docs/ServiceList.md) —— HomeSpan 支持的所有 HAP 服务和特性的列表
* [ HomeSpan 配件类别 ](docs/Categories.md) —— HomeSpan 定义的所有 HAP 配件类别的列表
* [ HomeSpan 命令行界面(CLI) ](docs/CLI.md) —— 配置 HomeSpan 设备的 WiFi 凭据，修改其 HomeKit 设置代码，监控并更新其状态，并从 Arduino IDE 串行监视器访问详细的实时设备诊断
* [ HomeSpan 用户指南 ](docs/UserGuide.md) —— 关于如何配置已经编程的 HomeSpan 设备的 WiFi 凭据、修改其 HomeKit 设置的统包说明编码，并将设备与 HomeKit 配对。无需电脑！
* [ HomeSpan API 参考 ](docs/Reference.md) —— HomeSpan 库 API 完整指南
* [ HomeSpan 二维码 ](docs/QRCodes.md) —— 创建和使用二维码来配对 HomeSpan 设备
* [ HomeSpan OTA ](docs/OTA.md) —— 直接从 Arduino IDE 无线更新您的草图，无需串行连接
* [ HomeSpan PWM ](docs/PWM.md) —— 使用 ESP32 的片上 PWM 外设集成控制标准 LED 和伺服电机
* [ HomeSpan 射频控制 ](docs/RMT.md) —— 使用 ESP32 的片上 RMT 外设轻松生成 RF 和 IR 远程控制信号
* [ HomeSpan 灯带 ](docs/Pixels.md) —— 可寻址的单线和两线 RGB、RGBWLED 和 LED 灯条的集成控制
* [ HomeSpan 控制步进电机 ](docs/Stepper.md) —— 步进电机的集成控制，包括 PWM 微步进
* [ HomeSpan Span 热点 ](docs/NOW.md) —— 使用 ESP-NOW 促进 ESP32 设备之间的点对点双向通信
* [ HomeSpan 电视服务 ](docs/TVServices.md) —— 如何使用 HomeKit 的未认证电视服务和特性
* [ HomeSpan 消息记录 ](docs/Logging.md) —— 如何生成日志消息以显示在 Arduino 串行监视器上以及可选地发布到集成的网页日志页面
* [ HomeSpan 设备克隆 ](docs/Cloning.md) —— 无缝地将损坏的设备更换为新设备，而无需重新配对并丢失 HomeKit 自动装置
* [ HomeSpan 项目 ](https://github.com/topics/HomeSpan) —— HomeSpan 库的实际应用
* [ HomeSpan FAQ ](docs/FAQ.md) —— 常见问题解答
* [ 常见问题解决方法 ](docs/Solutions.md) —— 使用或者编译 HomeSpan 时一些常见问题的解决方案
* [ HomeSpan 推荐草图 ](https://github.com/HomeSpan/HomeSpanReferenceSketches) —— 一系列独立的参考草图，展示了一些更复杂的 HomeKit 服务，例如恒温器和灌溉系统

请注意，所有文档都是受版本控制的，并且与每个分支相关联。*master* 分支通常指向最新版本。*dev* 分支（如果可用）将包含正在积极开发中的代码。

# 外部资源

除了 HomeSpan 资源之外，不熟悉 HomeKit 编程的开发人员还应下载 Apple 的 HomeKit Accessory Protocol Specification，Release R2(HAP-R2) 下载是免费的（现在 Apple 已不再提供），但 Apple 要求您注册您的 Apple ID 才能访问该文档。

您**不需要**阅读整个文档。HomeSpan 的全部意义在于它在引擎盖下实现了所有必需的 HAP 操作，因此您可以专注于编程任何所需的逻辑，以使用该设备控制您的实际设备（灯、风扇、RF 遥控器等）。但是您会发现 HAP 指南的第 8 章和第 9 章是非常宝贵的参考，因为它列出并描述了 HomeSpan 中实现的所有服务和特征，其中许多您将在自己的 HomeSpan 草图中经常使用。

---

### 反馈或提问？

请考虑添加到 HomeSpan 讨论区或直接发送电子邮件至 HomeSpan@icloud.com

### 关于作者（原文）
HomeSpan was developed and continues to be maintained and supported by Gregg Berman. It was originally conceived to solve the pesky problem of not being able to operate an RF-controlled kitchen vent hood with Siri. I hope you find it useful as well as fun to use.

This is my second large-scale open-source project --- my first was the design of an open-source sytem for operating model railroads using nothing more than an Arduino Uno and Arduino Motor Shield to generate digital command and control (DCC) signals. Though I have not been involved with the model railroading hobby for many years, videos showcasing my original system (dubbed DCC++), along with detailed tutorials of how it works, are still available on the[ DCC++YouTubeChannel ](https://www.youtube.com/@dcc2840/videos).
