# Getting Started with HomeSpan
# HomeSpan 入门

This page provides step-by-step instructions for acquiring and setting up all the software and hardware needed to develop HomeSpan devices.  Those with Arduino and/or ESP32 experience may find they can skip some of the steps.
本页提供了获取和设置开发 HomeSpan 设备所需的所有软件和硬件的分步说明。 那些有 Arduino 和/或 ESP32 经验的人可能会发现他们可以跳过一些步骤。

#### Step 1: Install the Arduino IDE
#### 第 1 步：安装 Arduino IDE

Since HomeSpan is a library designed for Arduino's Integrated Development Environment, the first step is to download and install the latest version of this IDE from the [Arduino Software page](https://www.arduino.cc/en/software).  If you have experience with programming Arduino sketches, you'll find Homespan's use of the standard Arduino setup() and loop() functions, as well as the ever-present *\*.ino* file, very familiar.  If you've never programmed an Arduino, you may want to begin by first reviewing [Arduino's Guide to the IDE](https://www.arduino.cc/en/Guide/Environment) (and maybe try out a few Arduino examples) before proceeding to program with HomeSpan.

由于 HomeSpan 是为 Arduino 的集成开发环境设计的库，因此第一步是从 [Arduino 软件页面](https://www.arduino.cc/en/software) 下载并安装此 IDE 的最新版本。 如果您有 Arduino 草图编程经验，您会发现 Homespan 对标准 Arduino setup() 和 loop() 函数的使用，以及一直存在的 *\*.ino* 文件，非常熟悉。 如果您从未编写过 Arduino，您可能希望首先查看 [Arduino 的 IDE 指南](https://www.arduino.cc/en/Guide/Environment)（并可能尝试一些 Arduino 示例 ) 在继续使用 HomeSpan 进行编程之前。

#### Step 2: Install the Arduino-ESP32 Core
#### 第 2 步：安装 Arduino-ESP32 内核

The Arduino IDE comes with built-in compilers and support for a variety of Arduino boards, such as the Arduino Uno and Arduino Nano.  However, the IDE does not natively support programming for the ESP32.  Fortunately, the IDE allows you to download and install *cores* for other micro-controllers, including the ESP32, so  they can be programming from within the Arduino environment.  See the [Espressif Arduino-ESP32 GitHub page](https://github.com/espressif/arduino-esp32#arduino-core-for-esp32-wifi-chip) for complete instructions on how to install the Arduino-ESP32 core into the Arduino IDE using the [Arduino IDE Board Manager](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md).

Arduino IDE 带有内置编译器，并支持各种 Arduino 板，例如 Arduino Uno 和 Arduino Nano。 但是，IDE 本身并不支持对 ESP32 进行编程。 幸运的是，IDE 允许您为其他微控制器（包括 ESP32）下载和安装 *cores*，因此它们可以在 Arduino 环境中进行编程。 有关如何将 Arduino-ESP32 内核安装到 使用 [Arduino IDE Board Manager]（https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md）的 Arduino IDE。

#### Step 3: Install HomeSpan
#### 第 3 步：安装 HomeSpan

HomeSpan is packaged as a standard Arduino library and can be installed either automatically from the Arduino IDE, or manually via GitHub.
HomeSpan 打包为标准 Arduino 库，可以从 Arduino IDE 自动安装，也可以通过 GitHub 手动安装。

* To install automatically, open the Arduino Library Manager from within the Arduino IDE by selecting *Sketch → Include Library → Manage Libraries...* from the Arduino menu bar.  Then, type *HomeSpan* into the search box, choose the latest version from the drop-down box, and click the `Install` button.  The Arduino Library Manager will automatically download and install the version you selected. HomeSpan and all of the tutorial example sketches are now ready for use.
* 要自动安装，请从 Arduino IDE 中打开 Arduino Library Manager，方法是从 Arduino 菜单栏中选择 *Sketch → Include Library → Manage Libraries...*。 然后，在搜索框中输入 *HomeSpan*，从下拉框中选择最新版本，然后单击“安装”按钮。 Arduino Library Manager 将自动下载并安装您选择的版本。 HomeSpan 和所有教程示例草图现在都可以使用了。

* To install manually, first download the [latest version](https://github.com/HomeSpan/HomeSpan/releases/latest) of *Source Code (zip)* to your desktop. It does not matter if your operating system keeps the package in zip form, or automatically unzips it when saving to you desktop.  Next, from the top menu bar within the Arduino IDE, select *Sketch → Include Library → Add .ZIP Library...* and navigtate to the Desktop folder where you should see the HomeSpan package you just downloaded (either as a zip file, or a folder).  Select the package (don't open it) and click `Choose`.  This directs the Arduino IDE to copy the HomeSpan package into its library sub-folder.  HomeSpan is now ready for use as a standard Arduino library (you may delete the HomeSpan package from your desktop as it is no longer needed).
* 要手动安装，请先将 *Source Code (zip)* 的 [最新版本](https://github.com/HomeSpan/HomeSpan/releases/latest) 下载到您的桌面。 如果您的操作系统将包保存为 zip 格式，或者在保存到您的桌面时自动解压缩，则无关紧要。 接下来，从 Arduino IDE 的顶部菜单栏中，选择 *Sketch → Include Library → Add .ZIP Library...* 并导航到桌面文件夹，您应该在该文件夹中看到刚刚下载的 HomeSpan 包（作为 zip 文件， 或文件夹）。 选择包（不要打开它），然后单击“选择”。 这指示 Arduino IDE 将 HomeSpan 包复制到其库子文件夹中。 HomeSpan 现在可以用作标准 Arduino 库（您可以从桌面删除 HomeSpan 包，因为它不再需要）。

#### Step 4: Acquire an ESP32 Board
#### 第 4 步：获取 ESP32 开发板

ESP32 development boards are widely available in different configurations from most electronics hobby sites, such as [Adafruit](https://www.adafruit.com) and [Sparkfun](https://www.sparkfun.com).  HomeSpan was developed using a dual-core ESP32-WROOM-32 (the [Huzzah32 from Adafruit](https://www.adafruit.com/product/3619)) but should work equally well on dual-core ESP32-WROVER chips.  HomeSpan has *not* been tested on any single-core ESP32 chips, such as the ESP32-S2.
ESP32 开发板在大多数电子爱好网站上都有不同的配置，例如 [Adafruit](https://www.adafruit.com) 和 [Sparkfun](https://www.sparkfun.com)。 HomeSpan 是使用双核 ESP32-WROOM-32（来自 Adafruit 的 [Huzzah32](https://www.adafruit.com/product/3619)）开发的，但在双核 ESP32-WROVER 芯片上也同样适用。 HomeSpan *未*在任何单核 ESP32 芯片上进行过测试，例如 ESP32-S2。

#### Step 5: Install any required USB Drivers
#### 第 5 步：安装任何所需的 USB 驱动程序

Programming an ESP32 board is generally done serially via USB.  Most ESP32 development boards contain a specialized chip that converts the serial UART signals used by the ESP32 to USB signals that can be transmitted to and from your computer, usually over a standard USB cable.  Depending on the specific USB-UART chip used on your ESP32 board, you may need to install a separate driver.  The manufacturer of your board should provides instructions on how to download and install whatever drivers are required for your operating system.
对 ESP32 板进行编程通常通过 USB 串行完成。 大多数 ESP32 开发板都包含一个专用芯片，该芯片将 ESP32 使用的串行 UART 信号转换为可以在计算机之间传输的 USB 信号，通常通过标准 USB 电缆传输。 根据 ESP32 板上使用的特定 USB-UART 芯片，您可能需要安装单独的驱动程序。 您的主板制造商应提供有关如何下载和安装操作系统所需的任何驱动程序的说明。

#### Step 6: Program your First HomeSpan Device
#### 第 6 步：对您的第一个 HomeSpan 设备进行编程

Before proceeding, you may want to first read through the [HomeSpan Overview](Overview.md) page.  Alternatively, you can jump right in and program your device using one of HomeSpan's built-in tutorial sketches:
在继续之前，您可能需要先通读 [HomeSpan Overview](Overview.md) 页面。 或者，您可以直接进入并使用 HomeSpan 的内置教程草图之一对您的设备进行编程：

* Plug your ESP32 board into a free USB port on your computer
* 将 ESP32 板插入计算机上的空闲 USB 端口

* Launch the Arduino IDE
* 启动 Arduino IDE

* Load one of the HomeSpan tutorial sketches (for example, *File → Examples → HomeSpan → 01-SimpleLightBulb*)
* 加载 HomeSpan 教程草图之一（例如，*File → Examples → HomeSpan → 01-SimpleLightBulb*）

* Set the Board to match your ESP32 board (for example, *Tools → Board → ESP32 Arduino → Adafruit ESP32 Feather*)
* 设置开发板以匹配您的 ESP32 开发板（例如，*Tools → Board → ESP32 Arduino → Adafruit ESP32 Feather*）

* Open the Arduino Serial Monitor (*Tools → Serial Monitor*)
* 打开 Arduino 串行监视器（*工具 → 串行监视器*）

* Compile and upload the HomeSpan sketch (*Sketch → Upload*)
* 编译并上传 HomeSpan 草图（*草图→上传*）

After compilation and uploading completes, HomeSpan will report a variety of initial diagnostics messages to the Arduino Serial Monitor and report that it is ready.  Congratulations!  You've just programmed your first HomeSpan device.
编译和上传完成后，HomeSpan 将向 Arduino 串行监视器报告各种初始诊断消息，并报告它已准备就绪。 恭喜！ 您刚刚对您的第一个 HomeSpan 设备进行了编程。

#### Step 7: Configure and Pair your HomeSpan Device
#### 第 7 步：配置和配对 HomeSpan 设备


Though the device is now programmed and fully operational, it needs to be configured with WiFi Credentials and a HomeKit Setup Code before it can be paired to your HomeKit account.  See HomeSpan's [Command-Line Interface (CLI)](CLI.md) page for details on how to configure HomeSpan via the Arduino Serial Monitor.  Once the device is connected to your WiFi network, HomeSpan is now ready to be paired from the Home App on your iPhone!
尽管该设备现在已编程并完全可操作，但需要先配置 WiFi 凭据和 HomeKit 设置代码，然后才能与您的 HomeKit 帐户配对。 有关如何通过 Arduino 串行监视器配置 HomeSpan 的详细信息，请参阅 HomeSpan 的 [命令行界面 (CLI)](CLI.md) 页面。 一旦设备连接到您的 WiFi 网络，HomeSpan 现在就可以通过 iPhone 上的 Home 应用程序进行配对了！

## Adding a Control Button and Status LED (*optional*)
## 添加控制按钮和状态 LED（*可选*）

In addition to being able to configure a HomeSpan device using the [HomeSpan CLI](CLI.md) via the Arduino Serial Monitor, HomeSpan provides an alternative method for end-users to configure a standalone HomeSpan device that is not connected to a computer.  This method requires the installation of two external components:
除了能够通过 Arduino 串行监视器使用 [HomeSpan CLI](CLI.md) 配置 HomeSpan 设备外，HomeSpan 还为最终用户提供了一种替代方法来配置未连接到计算机的独立 HomeSpan 设备。 此方法需要安装两个外部组件：

1. a normally-open single-pole pushbutton to function as the HomeSpan Control Button, and
1. 一个常开单刀按钮，用作 HomeSpan 控制按钮，以及
1. an LED (with a current-limiting resistor) to function as the HomeSpan Status LED.
1. 一个 LED（带有限流电阻）用作 HomeSpan 状态 LED。

The Control Button should be installed between ground and any pin on the ESP32 that can serve as an input.  To inform HomeSpan of which pin you chose, you must call the method `homeSpan.setControlPin(pin)` near the top of your sketch (see the [HomeSpan API Reference](Reference.md) for details), else HomeSpan will assume a Control Button has **not** be installed.
控制按钮应安装在接地和 ESP32 上任何可用作输入的引脚之间。 要通知 HomeSpan 您选择了哪个引脚，您必须在您的草图顶部附近调用方法 `homeSpan.setControlPin(pin)`（有关详细信息，请参阅 [HomeSpan API 参考]（Reference.md）），否则 HomeSpan 将假定 控制按钮**未**安装。

Similarly, the Status LED can be connected to any pin on the ESP32 that can serve as an output (and grounded through an appropriately-sized current-limiting resistor).  To inform HomeSpan of which pin you chose, you must call the method `homeSpan.setStatusPin(pin)` near the top of your sketch, else HomeSpan will assume a Status LED has **not** been installed.  Note some ESP32 boards have a built-in LED --- it is fine to use this for the Status LED if it is a simple on/off LED, *not* an addressable color LED that requires a special driver.
同样，状态 LED 可以连接到 ESP32 上任何可用作输出的引脚（并通过适当大小的限流电阻接地）。 要通知 HomeSpan 您选择了哪个引脚，您必须在草图顶部附近调用方法 `homeSpan.setStatusPin(pin)`，否则 HomeSpan 将假定状态 LED **未**安装。 请注意，一些 ESP32 板有一个内置 LED --- 如果它是一个简单的开/关 LED，则可以将其用于状态 LED，*不是*需要特殊驱动器的可寻址彩色 LED。

Using the Control Button and Status LED to configure a standalone HomeSpan device, including starting HomeSpan's temporary WiFi network to configure the device's WiFi Credentials and HomeKit Setup Code, is fully explained in the [HomeSpan User Guide](UserGuide.md).
使用控制按钮和状态 LED 来配置独立的 HomeSpan 设备，包括启动 HomeSpan 的临时 WiFi 网络以配置设备的 WiFi 凭据和 HomeKit 设置代码，在 [HomeSpan 用户指南](UserGuide.md) 中有详细说明。

## What Next?
## 接下来是什么？

If you've not yet read through the [HomeSpan API Overview](Overview.md) page, you should do so now so you'll have a good understanding of the framework for developing HomeSpan sketches.
如果您还没有通读 [HomeSpan API 概述](Overview.md) 页面，您现在应该阅读，以便您对开发 HomeSpan 草图的框架有一个很好的理解。

Next, explore the tutorial sketches, upload a few, and see how they work. The examples start simple and grow in complexity, taking you through all the functions and features of HomeSpan.  Along the way you'll also learn a lot of HomeKit tips and tricks.  See [HomeSpan Tutorials](Tutorials.md) for a summary of all the included examples.  Find something in a sketch you don't understand?  Visit the [HomeSpan API Reference](Reference.md) for details on all HomeSpan objects, functions, and methods.  Have a more general question?  See if it's been answered on the [HomeSpan FAQ](FAQ.md) page or any of the [Disussion](https://github.com/HomeSpan/HomeSpan/discussions) or [Issues](https://github.com/HomeSpan/HomeSpan/issues) pages.  If not, feel free to join the Discusion by adding a new question.
接下来，探索教程草图，上传一些，看看它们是如何工作的。 这些示例从简单开始逐渐复杂化，带您了解 HomeSpan 的所有功能和特性。 在此过程中，您还将学习很多 HomeKit 提示和技巧。 有关所有包含示例的摘要，请参阅 [HomeSpan 教程](Tutorials.md)。 在草图中找到你不理解的东西？ 有关所有 HomeSpan 对象、函数和方法的详细信息，请访问 [HomeSpan API 参考](Reference.md)。 有更一般的问题吗？ 查看是否已在 [HomeSpan FAQ](FAQ.md) 页面或任何 [Disussion](https://github.com/HomeSpan/HomeSpan/discussions) 或 [Issues](https://github. com/HomeSpan/HomeSpan/issues）页面。 如果没有，请随时通过添加新问题来加入讨论。

Ready to start creating your own HomeSpan sketches?  Check out the [HomeSpan Services and Characteristics](ServiceList.md) page for a full list of all the HomeKit Services and Characteristics supported by HomeSpan, as well as the [HomeSpan Categories](Categories.md) page for a list of all supported HomeKit Categories.  And don't forget to use Apple's [HomeKit Accessory Protocol Specification, Release R2 (HAP-R2)](https://developer.apple.com/homekit/specification/) as your go-to reference for details on every Service and Characteristic.
准备好开始创建自己的 HomeSpan 草图了吗？ 查看 [HomeSpan 服务和特性](ServiceList.md) 页面以获取 HomeSpan 支持的所有 HomeKit 服务和特性的完整列表，以及 [HomeSpan 类别](Categories.md) 页面以获取所有支持的列表 HomeKit 类别。 并且不要忘记使用 Apple 的 [HomeKit Accessory Protocol Specification, Release R2 (HAP-R2)](https://developer.apple.com/homekit/specification/) 作为您对每项服务和详细信息的参考 特征。

While developing your sketch remember to utilize the Arduino Serial Monitor.  HomeSpan produces extensive diagnostics that will help you debug your sketches as well as monitor all aspects of the HomeSpan device.  You'll also be able to control various aspects of HomeSpan from the Serial Monitor using the [HomeSpan Command-Line Interface (CLI)](CLI.md), including configuring the device's WiFi Credentials and HomeKit Setup Code.
在开发您的草图时，请记住使用 Arduino 串行监视器。 HomeSpan 生成广泛的诊断程序，可帮助您调试草图并监控 HomeSpan 设备的各个方面。 您还可以使用 [HomeSpan 命令行界面 (CLI)](CLI.md) 从串行监视器控制 HomeSpan 的各个方面，包括配置设备的 WiFi 凭据和 HomeKit 设置代码。

For access to even more advanced features, check out the [HomeSpan PWM](https://github.com/HomeSpan/HomeSpan/blob/master/docs/PWM.md), [HomeSpan RFControl](https://github.com/HomeSpan/HomeSpan/blob/master/docs/RMT.md), and [HomeSpan Pixels](https://github.com/HomeSpan/HomeSpan/blob/master/docs/Pixels.md) pages for tutorials and details on how HomeSpan can be used to control LEDs, lights, and Servo Motors with PWM signals; generate RF and IR Remote Control codes to operate appliances and TVs; and even control multicolor RGB LED strips.

Finally, disconnect your HomeSpan device from the computer and power it directly from a wall adapter.  After all, HomeSpan devices are designed to run on a standalone basis connected to real-world applicances like lights, fans, door locks, and window shades.  See the [HomeSpan User Guide](UserGuide.md) for end-user instructions on how to operate and configure a standlone HomeSpan device's WiFi Credentials and HomeKit Setup Code *without the need to connect the device to a computer*.

---

[↩️](README.md) Back to the Welcome page
