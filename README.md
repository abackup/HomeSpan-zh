 <!--原文时间：2024.5.31，翻译时间：2024.6.11，校对时间：2024.6.11；文件版本号：1.9.0 -->

个人翻译的 [HomeSpan](https://github.com/HomeSpan/HomeSpan)，喜欢的请去 [原地址](https://github.com/HomeSpan/HomeSpan) 查看。

# 欢迎！


欢迎使用 HomeSpan - 一个强大且极易使用的 Arduino 库，用于完全在 [Arduino IDE](http://www.arduino.cc) 内创建你自己的基于 [ESP32](https://www.espressif.com/en/products/modules/esp32) 的 HomeKit 设备。

HomeSpan 提供以微控制器为中心的苹果 HomeKit 配件协议规范版本 R2 (HAP-R2) 的实现，专门为在 Arduino IDE 中运行的乐鑫 ESP32 微控制器而设计。HomeSpan 通过家庭 WiFi 直接与 HomeKit 配对，无需任何外部网桥或组件。通过 HomeSpan，你可以使用 ESP32 I/O 的全部功能来创建自定义控制软件和/或硬件，以通过 iPhone、iPad 或 Mac 上的“家庭”应用或 Siri 自动操作外部设备。

HomeSpan 需要 2.0.0 或更高版本，并已通过 2.0.14 版本的 [Arduino-ESP32 开发板管理](https://github.com/espressif/arduino-esp32) 测试（推荐使用）。HomeSpan 可以在原版的乐鑫 ESP32 以及 ESP32-S2、ESP32-C3 和 ESP32-S3 芯片上运行。

HomeSpan 目前与 Arduino-ESP32 开发板管理的 3.X 版本不兼容，因为版本 3 包含许多重大更改，并且不向后兼容 Arduino-ESP32开发板管理的版本 2.X。目前 HomeSpan 只能在开发板管理的 2.X 版本下编译。

> [!NOTE] 
苹果公司的新 HomeKit 架构 [需要使用家庭中心](https://support.apple.com/en-us/HT207057)（HomePod 或 Apple TV）才可用于任何 HomeKit 设备的完整地和正确地操作，包括基于 HomeSpan 的设备。如果没有家庭中心，HomeSpan 将无法向“家庭”应用发送通知——按钮和温度传感器等将无法向“家庭”应用发送更新。

### HomeSpan 亮点

* 提供自然、直观且**非常**易于使用的框架
* 利用独特*以服务为中心*的方法创建 HomeKit 设备
* 充分利用广受欢迎的 Arduino IDE
* 100% 符合 HAP-R2 标准
* 集成 38 个 HomeKit 服务
* 在附件模式或桥接模式下运行
* 支持与设置码或二维码配对

### 对于 HomeSpan 开发人员

* Arduino 串口监视器的广泛使用
  * 实时、易于理解的诊断
  * 对每个底层 HomeKit 操作、数据请求和数据响应完全透明
  * 具有各种信息、调试和配置命令的命令行界面
* 内置数据库验证，确保你的配置满足所有 HAP 要求
* 利用 ESP32 的 16 通道 PWM 外设的专用类，可轻松控制：
  * LED 亮度（包括自动淡化）
  * 伺服电机
* 集成按钮和拨动开关功能，支持单击、双击和长按：
  * 将 ESP32 引脚连接到地或 VCC 的物理按钮
  * 连接到 ESP32 引脚的触摸板/传感器（用于支持触摸板的 ESP32 设备）
* 集成访问 ESP32 的片上远程控制外设，可轻松生成红外和射频信号
* 控制单线和双线可寻址 RGB 和 RGBW LED 和 LED 灯带的专用类
* 专门用于控制步进电机的类，可以在后台平稳运行，而不会干扰 HomeSpan 设备
* 使用 ESP-NOW 在 ESP32 设备之间实现无缝点对点通信的专用类
* 用于用户定义的日志消息的集成网络日志
* 大量注释的教程草图将带你从 HomeSpan 的基础知识到高级 HomeKit 主题
* 展示 HomeSpan 实际实现的其他示例和项目
* 一套完整的文档，全面解释了 HomeSpan 的各种 API 

### 对于 HomeSpan 最终用户

* 嵌入式 WiFi 接入点和网络界面，允许最终用户（非开发人员）：
  * 使用自己的家庭 WiFi 凭据设置 HomeSpan
  * 创建自己的 HomeKit 配对设置代码
* 状态指示灯和控制按钮，允许最终用户：
  * 强制解除设备与 HomeKit 的配对
  * 执行恢复出厂设置
  * 启动 WiFi 接入点
* 独立、详细的最终用户指南

# HomeSpan 资源<a name="resources"></a>

HomeSpan 包括以下文档：

* [HomeSpan 入门](docs/GettingStarted.md) - 设置开发 HomeSpan 设备所需的软件和硬件
* [HomeSpan API 概述](docs/Overview.md) - HomeSpan API 概述，包括开发第一个 HomeSpan 草图的分步指南
* [HomeSpan 教程](docs/Tutorials.md) - HomeSpan 的草图指南
* [HomeSpan 服务和特征](docs/ServiceList.md) - HomeSpan 支持的所有 HAP 服务和特征的列表
* [HomeSpan 配件类别](docs/Categories.md) - HomeSpan 定义的所有 HAP 配件类别的列表
* [HomeSpan 命令行界面（CLI）](docs/CLI.md) - 配置 HomeSpan 设备的 WiFi 凭据，修改其 HomeKit 设置代码，监控和更新其状态，并从 Arduino IDE 串口监视器访问详细的实时设备诊断
* [HomeSpan 用户指南](docs/UserGuide.md) - 有关如何配置已编程的 HomeSpan 设备的 WiFi 凭据、修改其 HomeKit 设置代码以及将设备与 HomeKit 配对的交钥匙式说明。不需要电脑！
* [HomeSpan API 参考](docs/Reference.md) - HomeSpan 库 API 的完整指南
* [HomeSpan 二维码](docs/QRCodes.md) - 创建并使用二维码来配对 HomeSpan 设备
* [HomeSpan OTA](docs/OTA.md) - 直接从 Arduino IDE 无线更新草图，无需串口连接
* [HomeSpan PWM](docs/PWM.md) - 使用 ESP32 的片载 PWM 外设集成控制标准 LED 和伺服电机
* [HomeSpan 射频控制](docs/RMT.md) - 使用 ESP32 的片载 RMT 外设，轻松生成射频和红外遥控信号
* [HomeSpan 灯带](docs/Pixels.md) - 可寻址的单线和双线 RGB 和 RGBW LED 和 LED 灯带的集成控制
* [HomeSpan 控制步进电机](docs/Stepper.md) - 步进电机集成控制，包括 PWM 微步进
* [HomeSpan Span 热点](docs/NOW.md) - 使用 ESP-NOW 促进 ESP32 设备之间的点对点双向通信
* [HomeSpan 电视服务](docs/TVServices.md) - 如何使用 HomeKit 未记录的电视服务和特征
* [HomeSpan 消息记录](docs/Logging.md) - 如何生成在 Arduino 串口监视器上显示的日志消息，以及可选地发布到集成的网络日志页面
* [HomeSpan 设备克隆](docs/Cloning.md) - 将损坏的设备无缝更换为新设备，而无需重新配对和丢失 HomeKit 自动化
* [HomeSpan 项目](https://github.com/topics/homespan) - HomePan 库的实际应用
* [HomeSpan 常见问题解答](docs/FAQ.md) - 常见问题解答
* [常见问题的解决方案](docs/Solutions.md) - 解决使用/编译 HomeSpan 时的一些常见问题
* [HomeSpan 推荐草图](https://github.com/HomeSpan/HomeSpanReferenceSketches) - 一系列独立的参考草图，展示了一些更复杂的 HomeKit 服务，如恒温器和灌溉系统

请注意，所有文档都是受版本控制的，并与每个分支相关联。*master* 分支通常指向最新版本。当可用时，该 *dev* 分支将包含正在开发的代码。

# 外部资源

除了 HomeSpan 资源之外，刚接触 HomeKit 编程的开发人员可能会发现苹果公司的 HomeKit 配件协议规范非商业版本 R2 (HAP-R2) 的第 8 章和第 9 章非常有用。不幸的是，苹果公司不再提供这份文件（也许是因为它最后一次更新是在 2019 年 7 月，现在已经有些过时了）。但是，你可以在网络上的其他地方找到此文档的副本。请注意，苹果并未将 HAP-R2 文档替换为用于非商业用途的任何其他版本，并且苹果公司的开源 [HomeKit ADK](https://github.com/apple/HomeKitADK) 仅反映了原始的 HAP-R2 规格（而不是用于商业设备的 HomeKit 中提供的所有最新服务和特征）。

 --- 

### 反馈或问题？

请将 HomeSpan 的错误报告或其他问题发布到 [Issues](https://github.com/HomeSpan/HomeSpan/issues) 页面。请将有关 HomeSpan 的所有其他问题（使用、功能、规格、示例等）或你对新功能的任何想法、建议或有关 HomeSpan 或 HomeKit 的任何反馈发布到 [Discussion](https://github.com/HomeSpan/HomeSpan/discussions) 页面。对于与特定 HomeSpan 问题或与功能无关的更一般的问题或反馈，你可以直接 [homespan@icloud.com](mailto:homespan@icloud.com) 给我发电子邮件。

### 关于作者

HomeSpan 由 Gregg Berman 开发并继续维护和支持。它最初是为了解决无法用 Siri 操作射频控制的厨房通风罩的麻烦问题。我希望你会发现它很有用，而且使用起来很有趣。

这是我的第二个大型开源项目——我的第一个项目是设计一个开源系统，用于操作模型铁路，仅使用 Arduino Uno 和 Arduino Motor Shield 来生成数字命令和控制 (DCC) 信号。虽然我已经多年没有参与模型铁路爱好的建设，但展示我的原始系统（称为 DCC++）的视频，以及它如何工作的详细教程，仍然可以在 [DCC++ YouTube 频道](https://www.youtube.com/@dcc2840/videos) 上找到。


<!--  原文时间：2023.7.11, 翻译时间：2024.5.10，校对时间：2024.5.29   -->

# HomeSpan 入门

本页提供了获取和设置开发 HomeSpan 设备所需的所有软件和硬件的分步说明。那些有 Arduino 或 ESP32 经验的人可能会发现你们可以跳过一些步骤。

#### 第 1 步：安装 Arduino IDE

由于 HomeSpan 是为 Arduino 集成开发环境设计的库，因此第一步是从 [Arduino 官网](https://www.arduino.cc/en/software) 下载并安装此 IDE 的最新版本。如果你有 Arduino 草图编程经验，你会发现 Homespan 对标准 Arduino `setup( )` 和 `loop( )` 函数的使用，以及非常熟悉一直存在的 *\*.ino* 文件。如果你从未编写过 Arduino，你可能希望首先查看 [Arduino's IDE 指南](https://www.arduino.cc/en/Guide/Environment)（并尝试一些 Arduino 示例）再继续使用 HomeSpan 进行编程。

#### 第 2 步：安装 Arduino-ESP32 内核

Arduino IDE 带有内置编译器，并支持各种 Arduino 板，例如 Arduino Uno 和 Arduino Nano。但是 IDE 本身并不支持对 ESP32 进行编程。幸运的是，IDE 允许你为其他微控制器（包括 ESP32 ）下载和安装**内核**，以使它们可以在 Arduino 环境中进行编程。有关如何将 Arduino-ESP32 内核安装到使用 [Arduino IDE 开发板管理](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md) 的 Arduino IDE 中，请参阅 [ESP32 开发板管理](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md)。

#### 第 3 步：安装 HomeSpan

HomeSpan 打包为标准 Arduino 库，可以从 Arduino IDE 自动安装，也可以通过 GitHub 手动安装。

* 自动安装，请从 Arduino IDE 中打开 Arduino 库管理，方法是从 Arduino 单栏中选择 *草图→包含库→管理库...*。然后，在搜索框中输入 *HomeSpan*，从下拉框中选择最新版本，然后单击`安装`按钮。Arduino 库管理将自动下载并安装你选择的版本。HomeSpan 和所有教程示例草图也都可以使用了。


* 手动安装，请先将 *Source Code(zip)* 的 [最新版本](https://github.com/HomeSpan/HomeSpan/releases/latest) 下载到你的桌面。如果你的操作系统将包保存为 zip 格式或者在保存到你的桌面时自动解压缩，无关紧要。接下来，从 Arduino IDE 的顶部菜单栏中，选择 *草图→包含库→添加 .ZIP 库...* 并导航到桌面文件夹，你应该在该文件夹中看到刚刚下载的 HomeSpan 包（ zip 文件，或文件夹）。选择包（不要打开它），然后单击`选择`。这表示 Arduino IDE 要已将 HomeSpan 包复制到其库子文件夹中。HomeSpan 现在可以用作标准 Arduino 库（你现在可以从桌面删除 HomeSpan 包，因为它不再需要）。

#### 第 4 步：获取 ESP32 开发板

ESP32 开发板在大多数电子爱好网站上提都供不同配置的 ESP32 开发板，例如 [Adafruit](https://www.adafruit.com) 和 [Sparkfun](https://www.sparkfun.com)。HomeSpan 可与 [Arduino-ESP32 内核](https://docs.espressif.com/projects/arduino-esp32/en/latest/getting_started.html#supported-soc-s) 支持的任何 ESP32 配合使用，包括原版的 ESP32、ESP32-S2、ESP32-S3 以及 ESP32-C3。


#### 第 5 步：安装所需的 USB 驱动程序


对 ESP32 板进行编程通常通过 USB 串口完成。大多数 ESP32 开发板都包含一个专用芯片，该 ESP32 使用的串口 UART 信号转换为可以在电脑之间传输的 USB 信号，通常通过标准 USB 数据线传输。根据 ESP32 上使用的他不同的 USB-UART 芯片，你可能需要安装单独的驱动程序。你的主板制造商可能会提供有关如何下载和安装操作系统所需的驱动程序的说明。

#### 第 6 步：编程你的第一个 HomeSpan 设备

在继续之前，你可能需要先通读 [HomeSpan 概述](Overview.md)。或者你可以直接进入并使用 HomeSpan 的内置教程草图之一对你的设备进行编程：

* 将 ESP32 连接到电脑上的空闲 USB 端口

* 启动 Arduino IDE

* 加载 HomeSpan 教程草图之一（例如，*文件→示例→HomeSpan→01-SimpleLightBulb*）

* 设置开发板参数以匹配你的 ESP32（例如，*工具→开发板→ESP32 Arduino→Adafruit ESP32 Feather* ）

* 打开 Arduino 串口监视器（*工具→串口监视器*）

* 编译并上传 HomeSpan 草图（*草图→上传*）

编译和上传完成后，HomeSpan 将向 Arduino 串口监视器报告各种初始诊断消息，之后报告已准备就绪。那么恭喜！你刚刚成功对你的第一个 HomeSpan 设备进行了编程。

#### 第 7 步：配置和配对 HomeSpan 设备

尽管该设备现在已编程并完全可操作，但需要先配置 WiFi 凭据和 HomeKit 设置代码，然后才能与你的 HomeKit 账户配对。有关如何通过 Arduino 串口监视器配置 HomeSpan 的详细信息，请参阅 [HomeSpan 命令行界面 (CLI)](CLI.md)。一旦设备连接到你的家庭 WiFi，HomeSpan 现在就可以通过 iPhone 上的“家庭”应用进行配对了！


## 添加控制按钮和状态指示灯（*可选*）

除了能够通过 Arduino 串口监视器使用 [HomeSpan 命令行界面 (CLI)](CLI.md) 配置 HomeSpan 设备外，HomeSpan 还为最终用户提供了一种替代方法来配置未连接到电脑的独立 HomeSpan 设备。此方法需要安装两个外部组件：

1. 一个常开按钮，用作 HomeSpan 的控制按钮，以及
1. 一个 LED（带有限流电阻）用作表示 HomeSpan 状态的 LED。

控制按钮应安装在接地和 ESP32 上任何可用作输入的引脚之间。要告知 HomeSpan 你选择了哪个引脚，你必须在你的草图顶部附近调用方法 `homeSpan.setControlPin(pin)`，有关详细信息，请参阅 [HomeSpan API 参考](Reference.md)，否则 HomeSpan 将默认**未**安装控制按钮。

同样，状态指示灯可以连接到 ESP32 上任何可用作输出的引脚（并通过适当大小的限流电阻接地）。要告知 HomeSpan 你选择了哪个引脚，你必须在草图顶部附近调用方法 `homeSpan.setStatusPin(pin)`，否则 HomeSpan 将默认**未**安装状态指示灯。请注意，一些 ESP32 板有一个内置 LED - 如果它**不是**需要特殊驱动器的可寻址全彩 LED，而是一个简单的开关 LED，则可以将其用于状态指示灯。


使用控制按钮和状态指示灯来配置独立的 HomeSpan 设备，包括启动 HomeSpan 的临时 WiFi 网络以配置设备的 WiFi 凭据和 HomeKit 设置代码，在 [HomeSpan 用户指南](UserGuide.md) 中有详细说明。


## 接下来是什么？

如果你还没有通读 [HomeSpan API 概述](Overview.md)，你现在应该阅读，以便你对开发 HomeSpan 草图的框架有一个很好的理解。

接下来，探索教程草图，上传几个试试，看看它们是如何工作的。这些示例从简单开始逐渐复杂化，带你了解 HomeSpan 的所有功能和特征。在此过程中，你还将学习很多 HomeKit 提示和技巧。有关所有包含示例的摘要，请参阅 [HomeSpan 教程](Tutorials.md)。在草图中找到你不理解的东西？ 有关所有 HomeSpan 对象、函数和方法的详细信息，请访问 [HomeSpan API 参考](Reference.md)。有更一般的问题吗？ 查看是否已出现在 [HomeSpan 常见问题解答](FAQ.md) 页面或任何 [Disussion](https://github.com/HomeSpan/HomeSpan/discussions) 或 [Issues](https://github.com/HomeSpan/HomeSpan/issues) 页面。如果没有，请随时通过添加新问题来加入讨论。

准备好开始创建自己的 HomeSpan 草图了吗？ 查看 [HomeSpan 服务和特征](ServiceList.md) 以获取 HomeSpan 支持的所有 HomeKit 服务和特征的完整列表，以及 [HomeSpan 配件类别](Categories.md) 以获取所有支持的 HomeKit 类别列表。并且不要忘记使用 [苹果 (HAP-R2)](https://developer.apple.com/homekit/specification/) 作为你对每项服务和详细信息的参考特征。

在开发你的草图时，请记住使用 Arduino 串口监视器。HomeSpan 生成广泛的调试信息，可帮助你调试草图并监控 HomeSpan 设备的各个方面。你还可以使用 [HomeSpan 命令行界面 (CLI)](CLI.md) 从串口监视器控制 HomeSpan 的各个方面，包括配置设备的 WiFi 凭据和 HomeKit 设置代码。

要访问更高级的功能，请查看 [HomeSpan PWM](PWM.md)、 [HomeSpan 射频控制](RMT.md) 和 [HomeSpan 灯带](Pixels.md) 以获取关于如何使用 HomeSpan 通过 PWM 信号控制 LED、灯和步进电机；生成射频和红外遥控代码来操作电器和电视；甚至控制全彩 LED 灯带的教程和详细信息。

最后，断开 HomeSpan 设备与电脑的连接，并直接从电源适配器为其供电。毕竟 HomeSpan 设备旨在独立运行连接到现实世界的设备，如灯、风扇、门锁和窗帘。有关如何**无需将设备连接到电脑**就可操作和配置独立 HomeSpan 设备的 WiFi 凭据和 HomeKit 设置代码，请参阅 [HomeSpan 用户指南](UserGuide.md)。

---

[↩️](../README.md#resources) 返回欢迎页面
