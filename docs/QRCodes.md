# 与二维码配对

使用 8 位 *Setup Code* 配对 HomeKit 设备需要您：

* 从 Home App 在本地网络上找到的未配对 HomeKit 设备列表中选择要配对的特定 HomeKit 设备
*将该设备的*设置代码*输入到家庭应用程序中。

上述步骤的顺序取决于您是手动键入 *Setup Code*，还是从打印的标签上扫描它。

相比之下，将 HomeKit 设备与 **QR 码** 配对只需要扫描 QR 码。您无需识别要配对的设备。家庭应用程序将改为在您的本地网络上搜索它，如果找到，则会自动与之配对。

这是可能的，因为 QR 码包含一个 4 字符的 *Setup ID*，它对于与 QR 码关联的设备是唯一的。 QR 码还嵌入了有关设备的其他配对信息，例如其类别（例如灯、风扇、门）及其 8 位*设置代码*。

HomeSpan 支持与 QR 码配对，并使用“HSPN”作为其默认 *Setup ID*。但是，如果您打算将多个设备与 QR 码配对，则需要确保每个设备都有一个唯一的*设置 ID*。您可以通过以下两种方式之一更改设备上的 *Setup ID*：

* 通过在 HomeSpan [命令行界面](https://github.com/HomeSpan/HomeSpan/blob/master/docs/CLI.md) 中键入“O \<code\>”将新代码存储在设备 NVS 中;或者
* 使用 `homeSpan.setQRID(const char *ID)` 方法直接在您的草图中指定 QR *Setup ID*。
  
优先顺序如下：如果您的草图包含对 `homeSpan.setQRID(const char *ID)` 的调用，则使用指定的 ID。如果没有，HomeSpan 将改为在 NVS 中搜索存储的 *Setup ID*。如果未找到，HomeSpan 默认使用“HSPN”作为*Setup ID*。
  
请注意，如果您不打算将设备与 QR 码配对，则它们都可以保留默认的“HSPN”*Setup ID*，因为此 ID 仅用于通过 QR 码启动配对过程并提供服务没有其他目的。

### 创建可扫描的二维码

就像您可以根据 HomeSpan 设备的 *Setup Code* 创建自己的可扫描标签一样（请参阅 [HomeSpan 用户指南](https://github.com/abackup/HomeSpan-zh/blob/master/docs/UserGuide.md#创建可扫描的二维码), 您还可以创建自己的可扫描二维码来配对 HomeSpan 设备。也许最简单的方法是使用 Apple 的 HomeKit 二维码生成器，包括其 [HomeKit Accessory Simulator](https://developer. apple.com/documentation/homekit/testing_your_app_with_the_homekit_accessory_simulator) Xcode的附加组件。

![二维码生成器](images/QRCode.png)

如上图，模拟器的二维码生成器需要输入以下字段：

* **版本**。始终将此设置为零，否则家庭应用程序将无法识别 QR 码。
* **预订的**。始终将此设置为零，否则家庭应用程序将无法识别 QR 码。
* **类别**。将此设置为与您的 HomeSpan 设备的类别相匹配（例如灯泡、风扇、门锁）。请注意，家庭应用程序仅在您首次扫描 QR 码时将其用于显示目的。家庭应用程序实际上不会检查 QR 码中列出的类别是否与您正在配对的设备的类别匹配。
* **设置标志**。这些标志提供有关 HomeKit 设备支持哪些配对方法的信息。 HomeSpan 仅支持 IP 配对，因此您选中该框并将其他两个留空。但是，您检查哪个框（如果有）似乎并不重要，因为 Home 应用程序似乎没有将此信息用于任何事情。
* **设置代码**。这是您使用 [HomeSpan 命令行界面 (CLI)](https://github.com/HomeSpan/HomeSpan/blob/master/docs/CLI.md) 为您的设备设置的 8 位 *Setup Code* ) 或 [HomeSpan 的 WiFi 设置网页](https://github.com/HomeSpan/HomeSpan/blob/master/docs/UserGuide.md#setting-homespans-wifi-credentials-and-setup-code)。请注意，上面屏幕截图中显示的代码是 HomeSpan 使用的默认代码，如果您不设置自己的代码。
* **设置 ID**。这是您在草图中使用方法 `homeSpan.setQRID(const char *id)` 为 HomeSpan 设备设置的 4 字符 *Setup ID*。如果您未在草图中指定 QR 设置 ID，HomeSpan 将使用默认值“HSPN”（如上例所示），除非您已通过 [CLI](CLI.md) 更新此设备的默认值使用“Q”命令。注意案例很重要！ HSPN 与“hspn”不同。
* **设置有效负载**。这是由上述输入产生的输出，并且是由显示的 QR 码表示的文本。 HomeKit 设备的 Setup Payload 始终以“X-HM://”开头，后跟 9 个字母数字字符，并以纯文本形式的 *Setup ID* 结尾。如果您没有更改 HomeSpan 的默认 *Setup Code* 或 *Setup ID*，您可以通过使用 Home App 扫描此图形来配对您的设备。更简单的是直接从您的相机扫描它 - 您的 iPhone 会识别出这是一个 HomeKit 二维码并为您打开 Home 应用程序。

您可能注意到 QR 码包含额外的图形，例如左上角的 Apple HomeKit 徽标。这纯粹是装饰性的，家庭应用程序不需要进行配对。同样，在右上角以大数字显示设备的 8 位 *Setup Code* 也是一种装饰，不需要配对，但如果您在扫描 QR 码时遇到问题并想要手动输入 *Setup，它可能会很方便代码* 进入家庭应用程序。

Home App 实际扫描的完整图形的唯一部分是 QR 码本身，这意味着您可以使用任何允许您输入任意文本的通用 QR 码生成器创建与 HomeKit 兼容的 QR 码。您需要输入到此类 QR 码生成器的文本当然是 Setup Payload。您可以遵循一种相对简单的算法来为您的每个 HomeSpan 设备生成正确的设置有效负载文本，但让 HomeSpan 为您执行此操作更容易。

这是因为每当您设置或更改 *Setup Code* 时，HomeSpan 都会在 Arduino 串行监视器上自动显示 HomeSpan 设备所需的 Setup Payload 文本。 **只需将串行监视器上显示的设置有效负载文本复制到通用 QR 码生成器中，viola — 您已经创建了一个可扫描的 QR 码，可用于配对 HomeSpan 设备。**

### 设置有效载荷算法（*可选阅读*）

HomeKit 设备的 Setup Payload 始终以“X-HM://”开头，后跟 9 个 base-36 数字，用于编码设备的所有配对参数，并以纯文本形式的设备的 *Setup ID* 结尾。

> Base-36 数字使用字符 0-9 和 A-Z（仅限大写！）来表示数字 0-35，其方式与十六进制数字 0-9 和 A-F 表示数字 0-15 的方式相同。 例如，十进制数 91 将表示为以 36 为底的 2S (91 = 2 * 36 + 19)

九个 base-36 数字应编码由以下数据元素组成的 45 位字（从最高有效位到最低有效位列出）：

* 位 45-43 - “版本”字段 (0-7)。 始终设置为 0
* 位 42-39 - “保留”字段 (0-15)。 始终设置为 0
* 位 38-31 - 设备的附件类别 (0-255)
* 位 30 - 始终设置为 0
* 位 29 - 如果设备支持 BLTE 配对，则设置为 1，否则设置为 0
* 位 28 - 如果设备支持 IP 配对设置为 1，否则设置为 0
* 位 27 - 如果设备支持 NFC 配对，则设置为 1，否则设置为 0
* 位 26-0 - 设备的 8 位*设置代码*（从 0-99999999）

结果必须是 9 位数字。 如果小于，则用前导零填充。

---

[↩️](README.md) 返回欢迎页面


