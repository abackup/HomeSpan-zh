# HomeSpan入门

本页提供了获取和设置开发HomeSpan设备所需的所有软件和硬件的分步说明。那些有Arduino或ESP32经验的人可能会发现他们可以跳过一些步骤。

#### 第1步：安装Arduino IDE

由于HomeSpan是为Arduino集成开发环境设计的库，因此第一步是从Arduino软件页面下载并安装此IDE的最新版本。如果您有Arduino草图编程经验，您会发现Homespan对标准Arduino setup()和loop()函数的使用，以及一直存在的*\*.ino*文件，非常熟悉。如果您从未编写过Arduino，您可能希望首先查看 Arduino IDE 指南（并可能尝试一些 Arduino 示例 ) 在继续使用 HomeSpan 进行编程之前。

#### 第 2 步：安装Arduino-ESP32内核

Arduino IDE带有内置编译器，并支持各种Arduino板，例如Arduino Uno和Arduino Nano。但是，IDE本身并不支持对ESP32进行编程。幸运的是，IDE允许您为其他微控制器（包括 SP32）下载和安装*cores*，因此它们可以在Arduino环境中进行编程。有关如何将Arduino-ESP32内核安装到使用 [ Arduino IDE Board Manager](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md) 的 Arduino IDE。

#### 第 3 步：安装HomeSpan

HomeSpan打包为标准Arduino库，可以从Arduino IDE自动安装，也可以通过GitHub手动安装。

* 要自动安装，请从 Arduino IDE 中打开 Arduino Library Manager，方法是从Arduino 单栏中选择*Sketch → Include Library → Manage Libraries...*。然后，在搜索框中输入*HomeSpan*，从下拉框中选择最新版本，然后单击“安装”按钮。Arduino Library Manager将自动下载并安装您选择的版本。 HomeSpan 和所有教程示例草图现在都可以使用了。


* 要手动安装，请先将 *Source Code (zip)* 的最新版本下载到您的桌面。如果您的操作系统将包保存为zip格式，或者在保存到您的桌面时自动解压缩，则无关紧要。 接下来，从 Arduino IDE 的顶部菜单栏中，选择 *Sketch → Include Library → Add .ZIP Library...* 并导航到桌面文件夹，您应该在该文件夹中看到刚刚下载的 HomeSpan 包（作为 zip 文件， 或文件夹）。 选择包（不要打开它），然后单击“选择”。 这指示 Arduino IDE 将 HomeSpan 包复制到其库子文件夹中。 HomeSpan 现在可以用作标准 Arduino 库（您可以从桌面删除 HomeSpan 包，因为它不再需要）。

#### 第 4 步：获取 ESP32 开发板


ESP32 开发板在大多数电子爱好网站上都有不同的配置，例如Adafruit和Sparkfun。 HomeSpan的使用双核ESP32-WROOM-32（来自 Adafruit 的 [Huzzah32](https://www.adafruit.com/product/3619)）开发的，但在双核 ESP32-WROVER 芯片上也同样适用。 HomeSpan *未*在任何单核 ESP32 芯片上进行过测试，例如 ESP32-S2。


#### 第 5 步：安装任何所需的 USB 驱动程序


对 ESP32 板进行编程通常通过 USB 串行完成。 大多数 ESP32 开发板都包含一个专用芯片，该芯片将 ESP32 使用的串行 UART 信号转换为可以在计算机之间传输的 USB 信号，通常通过标准 USB 电缆传输。 根据 ESP32 板上使用的特定 USB-UART 芯片，您可能需要安装单独的驱动程序。 您的主板制造商应提供有关如何下载和安装操作系统所需的任何驱动程序的说明。

#### 第 6 步：对您的第一个 HomeSpan 设备进行编程

在继续之前，您可能需要先通读 [HomeSpan概述](Overview.md) 页面。 或者您可以直接进入并使用 HomeSpan 的内置教程草图之一对您的设备进行编程：

* 将 ESP32 板插入计算机上的空闲 USB 端口

* 启动 Arduino IDE* 加载 HomeSpan 教程草图之一 (例如，*文件 → 示例 → HomeSpan → 01-SimpleLightBulb*)

* 加载 HomeSpan 教程草图之一（例如，*文件 → 示例 → HomeSpan → 01-SimpleLightBulb*）

* 设置开发板以匹配您的 ESP32 开发板（例如，*工具 → 开发板 → ESP32 Arduino → Adafruit ESP32 Feather*）

* 打开 Arduino 串行监视器（*工具 → 串行监视器*）

* 编译并上传 HomeSpan 草图（*草图→上传*）

编译和上传完成后，HomeSpan 将向 Arduino 串行监视器报告各种初始诊断消息，并报告它已准备就绪。 恭喜！ 您刚刚对您的第一个 HomeSpan 设备进行了编程。

#### 第 7 步：配置和配对 HomeSpan 设备

尽管该设备现在已编程并完全可操作，但需要先配置 WiFi 凭据和 HomeKit 设置代码，然后才能与您的 HomeKit 帐户配对。 有关如何通过 Arduino 串行监视器配置 HomeSpan 的详细信息，请参阅 HomeSpan 的 [命令行界面 (CLI)](CLI.md) 页面。 一旦设备连接到您的 WiFi 网络，HomeSpan 现在就可以通过 iPhone 上的 Home 应用程序进行配对了！


## 添加控制按钮和状态 LED（*可选*）

除了能够通过 Arduino 串行监视器使用 [HomeSpan CLI](CLI.md) 配置 HomeSpan 设备外，HomeSpan 还为最终用户提供了一种替代方法来配置未连接到计算机的独立 HomeSpan 设备。 此方法需要安装两个外部组件：

1. 一个常开单刀按钮，用作 HomeSpan 控制按钮，以及
1. 一个 LED（带有限流电阻）用作 HomeSpan 状态 LED。

控制按钮应安装在接地和 ESP32 上任何可用作输入的引脚之间。 要通知 HomeSpan 您选择了哪个引脚，您必须在您的草图顶部附近调用方法 `homeSpan.setControlPin(pin)`（有关详细信息，请参阅 [HomeSpan API参考]（Reference.md）），否则 HomeSpan 将假定 控制按钮**未**安装。

同样，状态 LED 可以连接到 ESP32 上任何可用作输出的引脚（并通过适当大小的限流电阻接地）。 要通知 HomeSpan 您选择了哪个引脚，您必须在草图顶部附近调用方法 `homeSpan.setStatusPin(pin)`，否则 HomeSpan 将假定状态 LED **未**安装。 请注意，一些 ESP32 板有一个内置 LED --- 如果它是一个简单的开/关 LED，则可以将其用于状态 LED，*不是*需要特殊驱动器的可寻址彩色 LED。


使用控制按钮和状态 LED 来配置独立的 HomeSpan 设备，包括启动 HomeSpan 的临时 WiFi 网络以配置设备的 WiFi 凭据和 HomeKit 设置代码，在 [HomeSpan用户指南](UserGuide.md) 中有详细说明。


## 接下来是什么？

如果您还没有通读 [HomeSpan API概述](Overview.md) 页面，您现在应该阅读，以便您对开发 HomeSpan 草图的框架有一个很好的理解。

接下来，探索教程草图，上传一些，看看它们是如何工作的。 这些示例从简单开始逐渐复杂化，带您了解 HomeSpan 的所有功能和特性。 在此过程中，您还将学习很多 HomeKit 提示和技巧。 有关所有包含示例的摘要，请参阅 [HomeSpan教程](Tutorials.md)。 在草图中找到你不理解的东西？ 有关所有 HomeSpan 对象、函数和方法的详细信息，请访问 [HomeSpan API参考](Reference.md)。 有更一般的问题吗？ 查看是否已在 [HomeSpan FAQ](FAQ.md) 页面或任何 [Disussion](https://github.com/abackup/HomeSpan-zh/discussions) 或 [Issues](https://github. com/abackup/HomeSpan-zh/issues）页面。 如果没有，请随时通过添加新问题来加入讨论。

准备好开始创建自己的 HomeSpan 草图了吗？ 查看 [HomeSpan服务和特性](ServiceList.md) 页面以获取 HomeSpan 支持的所有 HomeKit 服务和特性的完整列表，以及 [HomeSpan 类别](Categories.md) 页面以获取所有支持的列表 HomeKit 类别。 并且不要忘记使用 Apple 的 [(HAP-R2)](https://developer.apple.com/homekit/specification/) 作为您对每项服务和详细信息的参考 特征。

在开发您的草图时，请记住使用 Arduino 串行监视器。 HomeSpan 生成广泛的诊断程序，可帮助您调试草图并监控 HomeSpan 设备的各个方面。 您还可以使用 [HomeSpan 命令行界面 (CLI)](CLI.md) 从串行监视器控制 HomeSpan 的各个方面，包括配置设备的 WiFi 凭据和 HomeKit 设置代码。

要访问更高级的功能，请查看 [HomeSpan PWM](https://github.com/abackup/HomeSpan-zh/blob/master/docs/PWM.md)、[HomeSpan RFControl](https://github. com/abackup/HomeSpan-zh/blob/master/docs/RMT.md)和 [HomeSpan Pixels](https://github.com/abackup/HomeSpan-zh/blob/master/docs/Pixels.md) 页面获取教程和详细信息 关于如何使用 HomeSpan 通过 PWM 信号控制 LED、灯和伺服电机； 生成射频和红外遥控代码来操作电器和电视； 甚至控制多色 RGB LED 灯条。

最后，断开 HomeSpan 设备与计算机的连接，并直接从墙上适配器为其供电。 毕竟，HomeSpan 设备旨在独立运行，连接到现实世界的设备，如灯、风扇、门锁和窗帘。 有关如何操作和配置独立 HomeSpan 设备的 WiFi 凭据和 HomeKit 设置代码*无需将设备连接到计算机*的最终用户说明，请参阅 [HomeSpan 用户指南](UserGuide.md)。

---

[?](README.md) 返回欢迎页面
