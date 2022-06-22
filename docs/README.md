# Welcome!
# 欢迎！

个人复制翻译的[HomeSpan](https://github.com/HomeSpan/HomeSpan)，喜欢的请去原地址查看。

Welcome to HomeSpan - a robust and extremely easy-to-use Arduino library for creating your own [ESP32-based](https://www.espressif.com/en/products/modules/esp32) HomeKit devices entirely within the [Arduino IDE](https://www.arduino.cc).

欢迎使用HomeSpan-一个强大且非常易于使用的Arduino库，完全使用Arduino IDE（https://www.arduino.cc） 创建您自己的基于ESP32 (https://www.espressif.com/en/products/modules/esp32) 的HomeKit设备。

HomeSpan provides a microcontroller-focused implementation of [Apple's HomeKit Accessory Protocol Specification Release R2 (HAP-R2)](https://developer.apple.com/homekit/specification/) designed specifically for the Espressif ESP32 microcontroller running within the Arduino IDE.  HomeSpan pairs directly to HomeKit via your home WiFi network without the need for any external bridges or components.  With HomeSpan you can use the full power of the ESP32's I/O functionality to create custom control software and/or hardware to automatically operate external devices from the Home App on your iPhone, iPad, or Mac, or with Siri.

HomeSpan 供了一个以微控制器为中心符合[Apple 的 HomeKit附件协议规范版本R2 (HAP-R2)](https://developer.apple.com/homekit/specification/)协议的实现，专为在Arduino IDE中运行的Espressif ESP32微控制器而设计. HomeSpan无需任何外部网桥或组件，仅需通过您的家庭WiFi网络直接与HomeKit配对。借助HomeSpan，您可以使用ESP32 I/O的全部功能来创建自定义控制软件或硬件，以通过iPhone、iPad或Mac上的Home App或使用Siri自动操作外部设备。

HomeSpan is fully compatible with both Versions 1 and 2 of the [Arduino-ESP32 Board Manager](https://github.com/espressif/arduino-esp32).  Under Version 1, HomeSpan can be run only on the original ESP32.  Under Version 2, HomeSpan can be run on the original ESP32 as well as Espressif's ESP32-S2 and ESP32-C3 chips.

HomeSpan与[Arduino-ESP32 Board Manager](https://github.com/espressif/arduino-esp32)版本1和版本2完全兼容 。在版本1下，HomeSpan只能在ESP32上运行；在版本2下，HomeSpan 可以在ESP32以及Espressif的ESP32-S2和ESP32-C3芯片上运行。

### HomeSpan Highlights
### HomeSpan强调

* Provides a natural, intuitive, and **very** easy-to-use framework
* 提供自然、直观且**非常**易于使用的框架
* Utilizes a unique *Service-Centric* approach to creating HomeKit devices
* 利用独特的*以服务为中心*的方法来创建HomeKit设备
* Takes full advantage of the widely-popular Arduino IDE
* 充分利用广受欢迎的Arduino IDE
* 100% HAP-R2 compliance
* 100%符合HAP-R2协议
* 38 integrated HomeKit Services
* 集成38个HomeKit服务
* Operates in either Accessory or Bridge mode
* 在附件或桥接模式下运行
* Supports pairing with Setup Codes or QR Codes
* 支持与设置码或二维码配对

### For the HomeSpan Developer
### 写予HomeSpan开发者

* Extensive use of the Arduino Serial Monitor
* 广泛使用 Arduino 串行监视器
  * Real-time, easy-to-understand diagnostics
  * 实时，易于理解的诊断
  * Complete transparency to every underlying HomeKit action, data request, and data response
  * 对每个底层 HomeKit 操作、数据请求和数据响应完全透明
  * Command-line interface with a variety of info, debugging, and configuration commands
  * 带有各种信息、调试和配置命令的命令行界面
* Built-in database validation to ensure your configuration meets all HAP requirements
* 内置数据库验证，确保您的配置满足所有 HAP 要求
* Dedicated classes that utilize the ESP32's 16-channel PWM peripheral for easy control of:
* 利用ESP32的16通道PWM外设轻松控制的专用类：
  * LED Brightness
  * LED 亮度
  * Servo Motors
  * 伺服电机
* Integrated Push Button functionality supporting single, double, and long presses 
* 集成按钮功能，支持单、双和长按
* Integrated access to the ESP32's on-chip Remote Control peripheral for easy generation of IR and RF signals
* 集成访问ESP32的片上远程控制外设，轻松生成IR和RF信号
* Dedicated classes to control one- and two-wire addressable RGB and RGBW LEDs and LED strips
* 用于控制单线和两线可寻址RGB、RGBW LED和LED灯条的专用类
* Integrated Web Log for user-defined log messages
* 用于用户定义日志消息的集成Web日志
* Extensively-commented Tutorial Sketches taking you from the very basics of HomeSpan through advanced HomeKit topics
* 广泛评论的教程草图，带您从HomeSpan的基础知识到高级HomeKit主题
* Additional examples and projects showcasing real-world implementations of HomeSpan
* 展示 HomeSpan 实际实现的其他示例和项目
* A complete set of documentation explaining every aspect of the HomeSpan API
* 一套解释HomeSpan API的各个方面的完整文档

### For the HomeSpan End-User
### 写予HomeSpan终端用户

* Embedded WiFi Access Point and Web Interface to allow end-users (non-developers) to:
* 嵌入式 WiFi 接入点和 Web 界面允许最终用户（非开发人员）：
  * Set up Homespan with their own home WiFi Credentials
  * 使用自己的家庭 WiFi 凭据设置 Homespan
  * Create their own HomeKit Pairing Setup Code
  * 创建自己的 HomeKit 配对设置代码
* Status LED and Control Button to allow end-users to:
* 状态 LED 和控制按钮允许最终用户：
  * Force-unpair the device from HomeKit
  * 强制解除设备与 HomeKit 的配对
  * Perform a Factory Reset
  * 执行出厂重置
  * Launch the WiFi Access Point
  * 启动 WiFi 接入点
* A standalone, detailed End-User Guide
* 一个独立的、详细的最终用户指南

## ❗Latest Update - HomeSpan 1.5.1 (4/17/2022)
## ❗最新更新-HomeSpan 1.5.1 (4/17/2022)

* **New Web Logging functionality**
* **新的网络日志功能**
  * HomeSpan can now host a Web Log page for message logging
  * HomeSpan 现在可以托管用于消息记录的Web日志页面
  * New WEBLOG() macro makes is easy to create user-defined log messages
  * 新的 WEBLOG() 宏使创建用户定义的日志消息变得容易
  * Provides for the optional use of an NTP Time Server to set the device clock so all messages can be properly timestamped
  * 提供可选使用 NTP 时间服务器来设置设备时钟，以便所有消息都可以正确加时间戳
  * See [HomeSpan Message Logging](https://github.com/HomeSpan/HomeSpan/blob/master/docs/Logging.md) for full details
  * 有关完整详细信息，请参阅 [HomeSpan 消息记录](https://github.com/HomeSpan/HomeSpan/blob/master/docs/Logging.md)

* **New *printf*-style formatting for LOG() macros**
  * Adds variadic forms of the LOG0(), LOG1(), and LOG2() macros so they can be used in the same manner as a standard C printf function
  * Greatly simplifies the creation of log messages 
  * See [HomeSpan Message Logging](https://github.com/HomeSpan/HomeSpan/blob/master/docs/Logging.md) for full details

* **New CUSTOM_SERV() macro**
  * Allows for the creation of Custom Services
  * Can be used in conjunction with the existing CUSTOM_CHAR() macro to produce Services beyond those provided in HAP-R2
  * Includes a fully worked example of a custom [Pressure Sensor Accessory](https://github.com/HomeSpan/HomeSpan/blob/master/Other%20Examples/CustomService) that is recognized by *Eve for HomeKit*
  * See [HomeSpan API Reference](https://github.com/HomeSpan/HomeSpan/blob/master/docs/Reference.md) for details

* **New "Safe-Load" mode for OTA updates**
  * HomeSpan can check to make sure the new sketch being uploaded via OTA is another HomeSpan sketch.  If not, the upload fails
  * Upon rebooting after an OTA update, HomeSpan checks to ensure that OTA is enabled in the updated sketch.  If not, HomeSpan rolls back to the previous version of the sketch
  * See [HomeSpan OTA](https://github.com/HomeSpan/HomeSpan/blob/master/docs/OTA.md) for full details
  
* **Additional updates include:**
  * a new (optional) argument to `SpanUserCommand()` that allows for passing a pointer to any arbitrary data structure
  * a new SPAN_ACCESSORY() macro that expands to a common snippet of code often used when creating Accessories 
  * refreshed and streamlined example Tutorials, and fully reworked Examples 7 and 11, to best conform with Home App behavior under iOS 15.4

See [Releases](https://github.com/HomeSpan/HomeSpan/releases) for details on all changes and bug fixes included in this update.

# HomeSpan Resources
# HomeSpan资源

HomeSpan includes the following documentation:

HomeSpan 包括以下文档：

* [Getting Started with HomeSpan] - setting up the software and the hardware needed to develop HomeSpan devices
* [HomeSpan入门](https://github.com/abackup/HomeSpan-zh/blob/master/docs/GettingStarted.md) -设置开发HomeSpan设备所需的软件和硬件
 
* [HomeSpan API Overview] - an overview of the HomeSpan API, including a step-by-step guide to developing your first HomeSpan Sketch
* [HomeSpan API 概述](https://github.com/abackup/HomeSpan-zh/blob/master/docs/Overview.md) - HomeSpan API 概述，包括开发您的第一个 API 的分步指南 HomeSpan草图

* [HomeSpan Tutorials] - a guide to HomeSpan's tutorial-sketches
* [HomeSpan 教程](https://github.com/abackup/HomeSpan-zh/blob/master/docs/Tutorials.md) - HomeSpan 教程草图指南

* [HomeSpan Services and Characteristics] - a list of all HAP Services and Characterstics supported by HomeSpan
* [HomeSpan 服务和特性](https://github.com/abackup/HomeSpan-zh/blob/master/docs/ServiceList.md) - HomeSpan 支持的所有 HAP 服务和特性的列表

* [HomeSpan Accessory Categories] - a list of all HAP Accessory Categories defined by HomeSpan
* [HomeSpan Accessory Categories](https://github.com/abackup/HomeSpan-zh/blob/master/docs/Categories.md) - HomeSpan 定义的所有 HAP Accessory Categories 的列表

* [HomeSpan Command-Line Interface (CLI)] - configure a HomeSpan device's WiFi Credentials, modify its HomeKit Setup Code, monitor and update its status, and access detailed, real-time device diagnostics from the Arduino IDE Serial Monitor
* [HomeSpan 命令行界面 (CLI)](https://github.com/abackup/HomeSpan-zh/blob/master/docs/CLI.md) - 配置 HomeSpan 设备的 WiFi 凭据，修改其 HomeKit 设置代码，监控 并更新其状态，并从 Arduino IDE 串行监视器访问详细的实时设备诊断

* [HomeSpan User Guide] - turnkey instructions on how to configure an already-programmed HomeSpan device's WiFi Credentials, modify its HomeKit Setup Code, and pair the device to HomeKit.  No computer needed!
* [HomeSpan 用户指南](https://github.com/abackup/HomeSpan-zh/blob/master/docs/UserGuide.md) - 关于如何配置已经编程的 HomeSpan 设备的 WiFi 凭据、修改其 HomeKit 设置的统包说明 编码，并将设备与 HomeKit 配对。 无需电脑！

* [HomeSpan API Reference] - a complete guide to the HomeSpan Library API
* [HomeSpan API 参考](https://github.com/abackup/HomeSpan-zh/blob/master/docs/Reference.md) - HomeSpan 库 API 完整指南

* [HomeSpan QR Codes] - create and use QR Codes for pairing HomeSpan devices
* [HomeSpan 二维码](https://github.com/abackup/HomeSpan-zh/blob/master/docs/QRCodes.md) - 创建和使用二维码来配对 HomeSpan 设备

* [HomeSpan OTA] - update your sketches Over-the-Air directly from the Arduino IDE without a serial connection
* [HomeSpan OTA](https://github.com/abackup/HomeSpan-zh/blob/master/docs/OTA.md) - 直接从 Arduino IDE 无线更新您的草图，无需串行连接

* [HomeSpan PWM] - integrated control of standard LEDs and Servo Motors using the ESP32's on-chip PWM peripheral
* [HomeSpan PWM](https://github.com/abackup/HomeSpan-zh/blob/master/docs/PWM.md) - 使用 ESP32 的片上 PWM 外设集成控制标准 LED 和伺服电机

* [HomeSpan RFControl] - easy generation of RF and IR Remote Control signals using the ESP32's on-chip RMT peripheral
* [HomeSpan RFControl](https://github.com/abackup/HomeSpan-zh/blob/master/docs/RMT.md) - 使用 ESP32 的片上 RMT 外设轻松生成 RF 和 IR 远程控制信号

* [HomeSpan Pixels] - integrated control of addressable one- and two-wire RGB and RGBW LEDs and LED strips
* [HomeSpan Pixels](https://github.com/abackup/HomeSpan-zh/blob/master/docs/Pixels.md) - 可寻址的单线和两线 RGB 和 RGBW LED 和 LED 灯条的集成控制

* [HomeSpan Television Services] - how to use HomeKit's undocumented Television Services and Characteristics
* [HomeSpan 电视服务](https://github.com/abackup/HomeSpan-zh/blob/master/docs/TVServices.md) - 如何使用 HomeKit 的无证电视服务和特性

* [HomeSpan Message Logging](https://github.com/abackup/HomeSpan-zh/blob/master/docs/Logging.md) - how to generate log messages for display on the Arduino Serial Monitor as well as optionally posted to an integrated Web Log page
* [HomeSpan 消息记录](https://github.com/abackup/HomeSpan-zh/blob/master/docs/Logging.md) - 如何生成日志消息以显示在 Arduino 串行监视器上以及可选地发布到 集成的 Web 日志页面

* [HomeSpan Projects] - real-world applications of the HomeSpan Library
* [HomeSpan Projects](https://github.com/topics/homespan) - HomeSpan 库的实际应用

* [HomeSpan FAQ] - answers to frequently-asked questions
* [HomeSpan FAQ](https://github.com/abackup/HomeSpan-zh/blob/master/docs/FAQ.md) - 常见问题解答

Note that all documentation is version-controlled and tied to each branch.  The *master* branch generally points to the latest release.  The *dev* branch, when available, will contain code under active development.

# External Resources

In addition to HomeSpan resources, developers who are new to HomeKit programming should download Apple's [HomeKit Accessory Protocol Specification, Release R2 (HAP-R2)](https://developer.apple.com/homekit/specification/). The download is free, but Apple requires you to register your Apple ID for access to the document.

You ***do not*** need to read the entire document.  The whole point of HomeSpan is that it implements all the required HAP operations under the hood so you can focus on just programming whatever logic is needed to control your real-world appliances (lights, fans, RF remote controls, etc.) with the device.  However, you will find Chapters 8 and 9 of the HAP guide to be an invaluable reference as it lists and describes all of the Services and Characteristics implemented in HomeSpan, many of which you will routinely utilize in your own HomeSpan sketches.

---

### Feedback or Questions?

Please consider adding to the [HomeSpan Discussion Board](https://github.com/HomeSpan/HomeSpan/discussions), or email me directly at [homespan@icloud.com](mailto:homespan@icloud.com).
