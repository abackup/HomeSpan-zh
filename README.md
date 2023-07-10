# 欢迎！

个人复制翻译的[HomeSpan](https://github.com/HomeSpan/HomeSpan)，喜欢的请去[原地址](https://github.com/HomeSpan/HomeSpan)查看。

欢迎使用HomeSpan-一个强大且非常易于使用的Arduino库，完全使用Arduino IDE创建您自己的基于ESP32的HomeKit设备。

HomeSpan提供了一个以微控制器为中心符合Apple的HomeKit附件协议规范版本R2 (HAP-R2)协议的实现，专为在Arduino IDE中运行的ESP32微控制器而设计。HomeSpan无需任何外部网桥或组件，仅需通过您的家庭WiFi网络直接与HomeKit配对。借助HomeSpan，您可以使用ESP32 I/O的全部功能来创建自定义控制软件或硬件，通过iPhone、iPad或Mac上的Home App或使用Siri自动操作外部设备。

HomeSpan需要 Arduino-ESP2 Board Manager的2.0.0或更高版本，并且已经过版本2.0.7（推荐）的测试。HomeSpan可以在原装ESP32以及乐鑫的 ESP32-S2、ESP32-C3 和 ESP32-S3 芯片上运行。

### HomeSpan强调

* 提供自然、直观且**非常**易于使用的框架
* 利用独特的*以服务为中心*的方法来创建HomeKit设备
* 充分利用广受欢迎的Arduino IDE
* 100%符合HAP-R2协议
* 集成41个HomeKit服务
* 在附件或桥接模式下运行
* 支持与设置码或二维码配对

### 写予HomeSpan开发者

* 广泛使用Arduino串行监视器
  * 实时、易于理解的诊断
  * 完全透明HomeKit的每个底层操作、数据请求和数据响应
  * 带有各种信息、调试和配置命令的命令行界面
* 内置数据库验证，确保您的配置满足所有HAP要求
* 利用ESP32的16通道PWM外设轻松控制的专用类：
  * LED亮度（包括自动淡入淡出效果）
  * 伺服电机
* 集成按钮功能，支持单击、双击和长按
  * 将 ESP32 引脚连接到接地或 VCC 的物理按钮
  * 连接到 ESP32 针脚的触摸板/传感器（适用于支持触摸板的 ESP32 设备）
* 集成访问ESP32的片上远程控制外设，轻松生成IR和RF信号
* 用于控制单线和两线可寻址RGB、RGBW LED和LED灯带的专用类
* 使用ESP-NOW促进ESP32设备之间的无缝点对点通信的专用类
* 用于用户定义日志消息的集成Web日志
* 广泛评论的教程草图，带您从HomeSpan的基础知识到高级HomeKit主题
* 展示HomeSpan实际实现的其他示例和项目
* 一套解释HomeSpan API的各个方面的完整文档

### 写予HomeSpan用户

* 嵌入式WiFi接入点和Web界面允许最终用户（非开发人员）用于：
  * 使用自己的家庭WiFi凭据设置Homespan
  * 创建自己的HomeKit配对设置代码
* 状态LED和控制按钮允许最终用户用于：
  * 强制解除设备与HomeKit的配对
  * 执行出厂重置
  * 启动WiFi接入点
* 一个独立的、详细的最终用户指南

# HomeSpan资源

HomeSpan包括以下文档：

* [HomeSpan入门](https://github.com/abackup/HomeSpan-zh/blob/master/docs/GettingStarted.md) - 设置开发HomeSpan设备所需的软件和硬件
* [HomeSpan API概述](https://github.com/abackup/HomeSpan-zh/blob/master/docs/Overview.md) - HomeSpan API概述，包括开发您的第一个API的分步指南HomeSpan草图
* [HomeSpan教程](https://github.com/abackup/HomeSpan-zh/blob/master/docs/Tutorials.md) - HomeSpan教程草图指南
* [HomeSpan服务和特性](https://github.com/abackup/HomeSpan-zh/blob/master/docs/ServiceList.md) - HomeSpan支持的所有HAP服务和特性的列表
* [HomeSpan配件类别](https://github.com/abackup/HomeSpan-zh/blob/master/docs/Categories.md) - HomeSpan定义的所有HAP配件类别的列表
* [HomeSpan命令行界面(CLI)](https://github.com/abackup/HomeSpan-zh/blob/master/docs/CLI.md) - 配置HomeSpan设备的WiFi凭据，修改其HomeKit设置代码，监控并更新其状态，并从Arduino IDE串行监视器访问详细的实时设备诊断
* [HomeSpan用户指南](https://github.com/abackup/HomeSpan-zh/blob/master/docs/UserGuide.md) - 关于如何配置已经编程的HomeSpan设备的WiFi凭据、修改其HomeKit设置的统包说明编码，并将设备与HomeKit配对。无需电脑！
* [HomeSpan API参考](https://github.com/abackup/HomeSpan-zh/blob/master/docs/Reference.md) - HomeSpan库API完整指南
* [HomeSpan二维码](https://github.com/abackup/HomeSpan-zh/blob/master/docs/QRCodes.md) - 创建和使用二维码来配对HomeSpan设备
* [HomeSpan OTA](https://github.com/abackup/HomeSpan-zh/blob/master/docs/OTA.md) - 直接从Arduino IDE无线更新您的草图，无需串行连接
* [HomeSpan PWM](https://github.com/abackup/HomeSpan-zh/blob/master/docs/PWM.md) - 使用 ESP32的片上PWM外设集成控制标准LED和伺服电机
* [HomeSpan射频控制](https://github.com/abackup/HomeSpan-zh/blob/master/docs/RMT.md) - 使用 ESP32的片上RMT外设轻松生成RF和IR远程控制信号
* [HomeSpan灯带](https://github.com/abackup/HomeSpan-zh/blob/master/docs/Pixels.md) - 可寻址的单线和两线RGB、RGBW LED和LED灯条的集成控制
* [HomeSpan SpanPoint](https://github.com/abackup/HomeSpan-zh/blob/master/docs/NOW.md) - 使用ESP-NOW促进ESP32设备之间的点对点双向通信
* [HomeSpan电视服务](https://github.com/abackup/HomeSpan-zh/blob/master/docs/TVServices.md) - 如何使用HomeKit的无证电视服务和特性
* [HomeSpan消息记录](https://github.com/abackup/HomeSpan-zh/blob/master/docs/Logging.md) - 如何生成日志消息以显示在Arduino串行监视器上以及可选地发布到集成的Web日志页面
* [HomeSpan Device Cloning](https://github.com/abackup/HomeSpan-zh/blob/master/docs/Cloning.md) - 无缝地将损坏的设备更换为新设备，而无需重新配对并丢失HomeKit自动装置
* [HomeSpan项目](https://github.com/topics/homespan) - HomeSpan库的实际应用
* [HomeSpan FAQ](https://github.com/abackup/HomeSpan-zh/blob/master/docs/FAQ.md) - 常见问题解答

请注意，所有文档都是受版本控制的，并且与每个分支相关联。 *master* 分支通常指向最新版本。 *dev* 分支（如果可用）将包含正在积极开发中的代码。

# 外部资源

除了HomeSpan资源之外，不熟悉HomeKit编程的开发人员还应下载Apple的HomeKit Accessory Protocol Specification, Release R2 (HAP-R2) 下载是免费的（现在Apple已不再提供），但Apple要求您注册您的Apple ID才能访问该文档。

您***不需要***阅读整个文档。 HomeSpan的全部意义在于它在引擎盖下实现了所有必需的HAP操作，因此您可以专注于编程任何所需的逻辑，以使用该设备控制您的实际设备（灯、风扇、RF遥控器等）。但是您会发现HAP指南的第8章和第9章是非常宝贵的参考，因为它列出并描述了HomeSpan中实现的所有服务和特征，其中许多您将在自己的HomeSpan草图中经常使用。

---

### 反馈或提问？

请考虑添加到HomeSpan讨论区或直接发送电子邮件至homespan@icloud.com
