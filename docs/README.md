# Welcome!
# 欢迎！

个人复制翻译的[HomeSpan](https://github.com/HomeSpan/HomeSpan)，喜欢的请去原地址查看。

Welcome to HomeSpan - a robust and extremely easy-to-use Arduino library for creating your own [ESP32-based](https://www.espressif.com/en/products/modules/esp32) HomeKit devices entirely within the [Arduino IDE](https://www.arduino.cc).

欢迎使用HomeSpan-一个强大且非常易于使用的Arduino库，完全使用Arduino IDE（https://www.arduino.cc） 创建您自己的基于ESP32 (https://www.espressif.com/en/products/modules/esp32) 的HomeKit设备。

HomeSpan provides a microcontroller-focused implementation of [Apple's HomeKit Accessory Protocol Specification Release R2 (HAP-R2)](https://developer.apple.com/homekit/specification/) designed specifically for the Espressif ESP32 microcontroller running within the Arduino IDE.  HomeSpan pairs directly to HomeKit via your home WiFi network without the need for any external bridges or components.  With HomeSpan you can use the full power of the ESP32's I/O functionality to create custom control software and/or hardware to automatically operate external devices from the Home App on your iPhone, iPad, or Mac, or with Siri.

HomeSpan 供了一个以微控制器为中心符合[Apple 的 HomeKit附件协议规范版本R2 (HAP-R2)](https://developer.apple.com/homekit/specification/)协议的实现，专为在Arduino IDE中运行的Espressif ESP32微控制器而设计. HomeSpan无需任何外部网桥或组件，仅需通过您的家庭WiFi网络直接与HomeKit配对。借助HomeSpan，您可以使用ESP32的I/O的全部功能来创建自定义控制软件或硬件，以通过iPhone、iPad或Mac上的Home App或使用Siri自动操作外部设备。

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

* **New Web Logging functionality**
  * HomeSpan can now host a Web Log page for message logging
  * New WEBLOG() macro makes is easy to create user-defined log messages
  * Provides for the optional use of an NTP Time Server to set the device clock so all messages can be properly timestamped
  * See [HomeSpan Message Logging](https://github.com/HomeSpan/HomeSpan/blob/master/docs/Logging.md) for full details

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

HomeSpan includes the following documentation:

* [Getting Started with HomeSpan](https://github.com/HomeSpan/HomeSpan/blob/master/docs/GettingStarted.md) - setting up the software and the hardware needed to develop HomeSpan devices
* [HomeSpan API Overview](https://github.com/HomeSpan/HomeSpan/blob/master/docs/Overview.md) - an overview of the HomeSpan API, including a step-by-step guide to developing your first HomeSpan Sketch
* [HomeSpan Tutorials](https://github.com/HomeSpan/HomeSpan/blob/master/docs/Tutorials.md) - a guide to HomeSpan's tutorial-sketches
* [HomeSpan Services and Characteristics](https://github.com/HomeSpan/HomeSpan/blob/master/docs/ServiceList.md) - a list of all HAP Services and Characterstics supported by HomeSpan
* [HomeSpan Accessory Categories](https://github.com/HomeSpan/HomeSpan/blob/master/docs/Categories.md) - a list of all HAP Accessory Categories defined by HomeSpan
* [HomeSpan Command-Line Interface (CLI)](https://github.com/HomeSpan/HomeSpan/blob/master/docs/CLI.md) - configure a HomeSpan device's WiFi Credentials, modify its HomeKit Setup Code, monitor and update its status, and access detailed, real-time device diagnostics from the Arduino IDE Serial Monitor
* [HomeSpan User Guide](https://github.com/HomeSpan/HomeSpan/blob/master/docs/UserGuide.md) - turnkey instructions on how to configure an already-programmed HomeSpan device's WiFi Credentials, modify its HomeKit Setup Code, and pair the device to HomeKit.  No computer needed!
* [HomeSpan API Reference](https://github.com/HomeSpan/HomeSpan/blob/master/docs/Reference.md) - a complete guide to the HomeSpan Library API
* [HomeSpan QR Codes](https://github.com/HomeSpan/HomeSpan/blob/master/docs/QRCodes.md) - create and use QR Codes for pairing HomeSpan devices
* [HomeSpan OTA](https://github.com/HomeSpan/HomeSpan/blob/master/docs/OTA.md) - update your sketches Over-the-Air directly from the Arduino IDE without a serial connection
* [HomeSpan PWM](https://github.com/HomeSpan/HomeSpan/blob/master/docs/PWM.md) - integrated control of standard LEDs and Servo Motors using the ESP32's on-chip PWM peripheral
* [HomeSpan RFControl](https://github.com/HomeSpan/HomeSpan/blob/master/docs/RMT.md) - easy generation of RF and IR Remote Control signals using the ESP32's on-chip RMT peripheral
* [HomeSpan Pixels](https://github.com/HomeSpan/HomeSpan/blob/master/docs/Pixels.md) - integrated control of addressable one- and two-wire RGB and RGBW LEDs and LED strips
* [HomeSpan Television Services](https://github.com/HomeSpan/HomeSpan/blob/master/docs/TVServices.md) - how to use HomeKit's undocumented Television Services and Characteristics
* [HomeSpan Message Logging](https://github.com/HomeSpan/HomeSpan/blob/master/docs/Logging.md) - how to generate log messages for display on the Arduino Serial Monitor as well as optionally posted to an integrated Web Log page
* [HomeSpan Projects](https://github.com/topics/homespan) - real-world applications of the HomeSpan Library
* [HomeSpan FAQ](https://github.com/HomeSpan/HomeSpan/blob/master/docs/FAQ.md) - answers to frequently-asked questions

Note that all documentation is version-controlled and tied to each branch.  The *master* branch generally points to the latest release.  The *dev* branch, when available, will contain code under active development.

# External Resources

In addition to HomeSpan resources, developers who are new to HomeKit programming should download Apple's [HomeKit Accessory Protocol Specification, Release R2 (HAP-R2)](https://developer.apple.com/homekit/specification/). The download is free, but Apple requires you to register your Apple ID for access to the document.

You ***do not*** need to read the entire document.  The whole point of HomeSpan is that it implements all the required HAP operations under the hood so you can focus on just programming whatever logic is needed to control your real-world appliances (lights, fans, RF remote controls, etc.) with the device.  However, you will find Chapters 8 and 9 of the HAP guide to be an invaluable reference as it lists and describes all of the Services and Characteristics implemented in HomeSpan, many of which you will routinely utilize in your own HomeSpan sketches.

---

### Feedback or Questions?

Please consider adding to the [HomeSpan Discussion Board](https://github.com/HomeSpan/HomeSpan/discussions), or email me directly at [homespan@icloud.com](mailto:homespan@icloud.com).
