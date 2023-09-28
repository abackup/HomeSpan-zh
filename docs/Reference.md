原文：2023.9.16， 翻译时间：2023.9.28

# HomeSpan API 参考

通过在您的 Arduino 草图中包含 *HomeSpan.h* 来调用 HomeSpan 库，如下所示：

```C++
#include "HomeSpan.h"
```

## *homeSpan*

在运行时 HomeSpan 将创建一个名为 `homeSpan` 的全局**对象**，它支持以下方法：

* `void begin(Category catID, const char *displayName, const char *hostNameBase, const char *modelName)`
   * 初始化 HomeSpan
   * **必须**在任何其他 HomeSpan 函数之前在每个草图的开头调用，并且通常放置在 Arduino `setup()` 方法的顶部附近，但位于  `Serial.begin()` **之后**以使初始化诊断可以输出到串行监视器
   * 所有参数都是**可选的**
  
     * *catID* —— HAP 类别 HomeSpan 广播用于与 HomeKit 配对。 默认为 Category::Lighting。 有关完整列表，请参阅 [HomeSpan 附件类别](Categories.md)
     * *displayName* —— HomeSpan 广播的 MDNS 显示名称。 默认为 "HomeSpan Server"
     * *hostNameBase* —— 完整的 MDNS 主机名由 HomeSpan 作为 *hostNameBase-DeviceID*.local 广播，其中 DeviceID 是 HomeSpan 自动生成的唯一的 6 字节代码。 默认为 "HomeSpan"
     * *modelName* —— HAP 模型名称 HomeSpan 广播用于与 HomeKit 配对。 默认为 "HomeSpan-ESP32"
   * 示例：`homeSpan.begin(Category::Fans, "Living Room Ceiling Fan");`
 
* `void poll()`
    * 检查 HAP 请求、本地命令和设备活动
    * **必须**在每个草图中重复调用，通常放置在 Arduino `loop()` 方法的顶部（**除非**使用下文描述的 `autoPoll()` 来代替）
   
---

以下**可选** `homeSpan` 方法会覆盖 `begin()` 中使用的各种 HomeSpan 初始化参数，因此**应该**在 `begin()` 之前调用才能生效。 如果该方法**未被**调用，HomeSpan 则使用如下所示的默认参数：

* `void setControlPin(uint8_t pin)`
   * 设置 ESP32 引脚用于 HomeSpan 控制按钮（按下时引脚接地）。 如果未指定，HomeSpan 将假定没有控制按钮

* `int getControlPin()`
   * 返回由 `setControlPin(pin)` 设置的 HomeSpan 控制按钮的引脚号，如果未设置引脚，则返回 -1

* `void setStatusPin(uint8_t pin)`
   * 设置 ESP32 引脚以用于 HomeSpan 状态指示灯
   * 假设标准 LED 将连接到**引脚**
   * 如果既没有调用此方法也没有调用任何等效方法，HomeSpan 将假定没有状态指示灯

* `void setStatusPixel(uint8_t pin, float h=0, float s=100, float v=100)`
   * 设置 ESP32 引脚以用于 HomeSpan 状态指示灯
   * 此方法是上面使用 `setStatusPin()` 的**替代方法**
   * 假设 RGB NeoPixel（或同等产品）将连接到**引脚**
   * 与具有内置 NeoPixel LED 的 ESP32 板配合良好，但添加外部 NeoPixel 也可以
   * 用户可以通过提供以下 HSV 值来选择指定 HomeSpan 将与 NeoPixel 一起使用的颜色：
     * h = 0-360 之间的色调
     * s = 0-100 之间的饱和度
     * v = 0-100 之间的亮度
   * 如果未指定，颜色默认为**红色**
   * 示例： `homeSpan.setStatusPixel(8,120,100,20)` 使用连接到引脚 8 的 NeoPixel 将状态指示灯设置为浅绿色
   * 如果既没有调用此方法也没有调用任何等效方法，HomeSpan 将假定没有状态指示灯

* `void setStatusDevice(Blinkable *sDev)`
   * 将状态指示灯设置为用户指定的可闪烁设备*sDev*
   * 此方法是使用上面的 `setStatusPin()` 或 `setStatusPixel()` 的**替代方法**
   * 有关如何创建通用可闪烁设备的详细信息，请参阅 [Blinkable](Blinkable.md)
   * 当使用连接到引脚扩展器或其他专用驱动器的 LED 作为状态指示灯时很有用
   * 如果既没有调用此方法也没有调用任何等效方法，HomeSpan 将假定没有状态指示灯

* `void setStatusAutoOff（uint16_t duration）`
   * 将状态指示灯设置为在 *duration* 秒后自动关闭
   * 每当 HomeSpan 激活新的闪烁模式时，状态指示灯将自动打开，持续时间计时器将被重置
   * 如果 *duration* 设置为零，则禁用自动关闭（状态指示灯将无限期保持亮起）
  
* `int getStatusPin()`
   * 返回由 `setStatusPin(pin)` 设置的状态指示灯的引脚号，如果没有设置引脚，则返回 -1

* `void setApSSID(const char *ssid)`
   * 设置 HomeSpan 设置接入点的 SSID（网络名称）（默认 = "HomeSpan-Setup"）
  
* `void setApPassword(const char *pwd)`
   * 设置 HomeSpan 设置接入点的密码 （默认 = "homespan"）
  
* `void setApTimeout(uint16_t nSec)`
   * 设置 HomeSpan 设置接入点一旦激活，在超时之前保持活动的持续时间（以秒为单位）（默认值 = 300 秒）
  
* `void setCommandTimeout(uint16_t nSec)`
   * 设置 HomeSpan 最终用户命令模式一旦激活，在超时之前保持活动的持续时间（以秒为单位）（默认值 = 120 秒）
  
* `void setLogLevel(int level)`
   * 设置诊断消息的日志级别，其中：
  
    * 0 = 顶级 HomeSpan 状态消息，以及用户在草图中指定的任何 `LOG0()` 消息（默认）
     * 1 = 所有 HomeSpan 状态消息以及用户在草图中指定的任何 `LOG1()` 消息
     * 2 = 所有 HomeSpan 状态消息加上所有进出 HomeSpan 设备的 HAP 通信数据包，以及用户在草图中指定的所有 `LOG1()` 和 `LOG2()` 消息
     * -1 = 禁止所有 HomeSpan 状态消息，包括用户在草图中指定的所有 `LOG0()`、`LOG1()` 和 `LOG2()` 消息，从而释放串行端口以供其他用途
   * 日志级别设置对草图中可能使用的任何 `Serial.print()` 或 `Serial.printf()` 语句没有影响。 如果您想通过设置 HomeSpan 日志级别来控制输出，请使用 `LOG()` 宏之一而不是 `Serial.print()` 或 `Serial.printf()`
   * 日志级别设置对 ESP32 操作系统本身输出的任何 ESP32 诊断消息没有影响。 要抑制这些消息，请确保在 Arduino IDE 的 "工具" 菜单中将 "核心调试级别" 设置为 "无" 来编译您的草图
   * 请注意，日志级别也可以在运行时通过 [HomeSpan CLI](CLI.md) 使用 "L" 命令进行更改
   * 请参阅[消息日志记录](Logging.md)了解完整详细信息

* `int getLogLevel()`
   * 返回由 `setLogLevel(level)` 设置的当前日志级别
   
* `void ReserveSocketConnections(uint8_t nSockets)`
   * 保留 *n* 个网络编程接口用于**除** HomeSpan HAP 服务器用于 HomeKit 控制器连接的用途
     * 对于在 Arduino-ESP32 v2.0.1 或更高版本下编译的草图，HomeSpan 为 HAP 控制器连接保留 14 个网络编程接口
     * 每次调用 `reserveSocketConnections(nSockets)` 都会将此数字减少 *n* 个网络编程接口
     * 如果您的草图需要自己的网络编程接口连接以添加代码（例如，单独的 Web 服务、MQTT 服务器等），请使用此方法
   * 允许多次调用此方法 —— 保留的网络编程接口数量将是所有调用的 *nSockets* 之和
   * 请注意，您无需为内置 HomeSpan 功能单独预留网络编程接口
     * 例如， `enableOTA()` 已经包含对 `reserveSocketConnections(1)` 的嵌入调用，因为 HomeSpan 知道必须保留一个网络编程接口来支持 OTA
  
* `void setPortNum(uint16_t port)`
   * 设置用于 HomeKit 和 HomeSpan 之间通信的 TCP 端口号（默认 = 80）
  
* `void setHostNameSuffix(const char *suffix)`
   * 设置 HomeSpan 后缀附加到 *hostNameBase* 以创建完整的主机名
   * 如果未指定，HomeSpan 默认在 HomeSpan 设备的 6 字节配件 ID 后附加破折号 "——" 
   * 允许将 *suffix* 设置为空字符串 "" 
   * 示例： `homeSpan.begin(Category::Fans, "Living Room Ceiling Fan", "LivingRoomFan");` 将生成 *LivingRoomFan-A1B2C3D4E5F6.local* 形式的默认**主机名**。 在 `homeSpan.begin()` 之前调用 `homeSpan.setHostNameSuffix("v2")` 将生成 *LivingRoomFanv2.local* 的**主机名**
  
* `void setQRID(const char *id)`
   * 将用于设备与 [QR 码](QRCodes.md) 配对的设置 ID 从 HomeSpan 默认值更改为 *id*
   * HomeSpan 默认值为 "HSPN" ，除非使用 "Q" 命令通过 [HomeSpan CLI](CLI.md) 对设备进行永久更改
   * *id* 必须恰好是 4 个字母、数字或者字符（0-9、A-Z 和 a-z）。 如果不是，则更改设置 ID 的请求将被静默忽略，并使用默认值
  
---

以下**可选** `homeSpan` 方法启用附加功能并提供 HomeSpan 环境的进一步自定义。 除非另有说明，调用**应该**在`begin()`之前进行才能生效：

* `int enableOTA(boolean auth=true, boolean safeLoad=true)`
   * 启用 HomeSpan 设备的 [无线 (OTA) 更新](OTA.md)，否则该功能将被禁用
   * HomeSpan OTA 需要授权密码，除非指定 *auth* 并将其设置为 *false*
   * 新 HomeSpan 设备的默认 OTA 密码是 "homespan-ota" 
   * 这可以通过 [HomeSpan CLI](CLI.md) 使用 "O" 命令进行更改
   * 注意启用 OTA 会使 HAP 控制器连接数减少 1
   * 除非指定第二个参数并将其设置为 *false*，否则默认情况下将启用 OTA 安全加载。 HomeSpan OTA 安全加载检查以确保上传到现有 HomeSpan 设备的草图本身就是 HomeSpan 草图，并且它们也启用了 OTA。 详情请参见 [HomeSpan OTA 安全加载](OTA.md#ota-safe-load)
   * 如果启用 OTA 成功，则返回 0，否则返回 -1 ；并向串行监视器报告错误

* `int enableOTA(const char *pwd, boolean safeLoad=true)`
* * `enableOTA()` 的替代形式，允许您以编程方式将 OTA 密码更改为指定的 *pwd*
   * *pwd* 必须包含 1 至 32 个字符
   * 此命令使 HomeSpan 忽略但不更改使用 "O" 命令存储的任何密码
   * 如果启用 OTA 成功，则返回 0，否则返回 -1 ；并向串行监视器报告错误

* `void enableAutoStartAP()`
   * 如果在启动时**未**找到 WiFi 凭证，则启用 WiFi 接入点的自动启动
   * 改变 HomeSpan 接入点行为的方法，例如 `setApTimeout()` ，必须在 `enableAutoStartAP()` 之前调用才能生效
* `void setApFunction(void (*func)())`
   * 调用用户定义的函数 *func* 取代 HomeSpan 的内置 WiFi 接入点
   * *func* 必须是 *void* 类型并且没有参数
   * *func* 将在每次启动接入点时调用，而不是 HomeSpan 的内置 WiFi 接入点：
     * 通过 CLI 输入 "A" ，或者
     * 通过使用命令模式选项 3 的控制按钮，或
     * 如果设置了 `enableAutoStartAP()` 并且没有存储 WiFi 凭证，则启动时自动启动
   * 识别所需网络的 SSID 和密码后，*func* 必须调用 `setWifiCredentials()` 来保存并使用这些值
   * 建议 *func* 通过使用 `ESP.restart()` 重新启动设备来终止。 重新启动后，HomeSpan 将使用刚刚保存的 SSID 和密码
  
* `void setWifiCredentials(const char *ssid, const char *pwd)`
   * 设置 HomeSpan 将连接的 WiFi 网络名 (*ssid*) 和密码 (*pwd*)
   * *ssid* 和 *pwd* 自动保存在 HomeSpan 的非易失性存储 (NVS) 中，以便在设备重新启动时检索
   * 请注意，如果保存的值超过允许的最大字符数 (ssid=32；pwd=64)，则会被截断
   * :warning: 安全警告：此函数的目的是允许高级用户使用 `setApFunction(func)` 指定的自定义接入点函数“动态”设置设备的 WiFi 凭证。 不建议使用此功能将您的 WiFi 名称和密码直接硬编码到您的草图中。 相反，请使用 HomeSpan 提供的更安全的方法之一（例如从 CLI 中键入 "W" 或启动 HomeSpan 的接入点）来设置您的 WiFi 凭据，而无需将其硬编码到您的草图中

* `void setWifiCallback(void (*func)())`
   * 设置一个可选的用户定义回调函数 *func*，由 HomeSpan 在建立 WiFi 连接后启动时调用。 对 *func* 的一次性调用是为正在实现其他网络相关服务作为其草图一部分的用户提供的，但在建立 WiFi 连接之前无法启动。 函数 *func* 必须是 *void* 类型并且没有参数

* `void setPairCallback(void (*func)(boolean status))`
   * 设置可选的用户定义回调函数 *func*，在完成与控制器的配对 (*status=true*) 或与控制器取消配对 (*status=false*) 时由 HomeSpan 调用
   * 对 *func* 的一次性调用是为希望在设备首次配对或设备稍后取消配对时触发其他操作的用户提供的
   * 请注意，此 *func* 在启动时**不会**调用，并且不应用于简单地检查设备是否已配对或未配对。 仅当配对状态发生变化时才会调用
   * 函数 *func* 必须为 *void* 类型并接受一个 *boolean* 参数

* `void setStatusCallback(void (*func)(HS_STATUS status))`
   * 设置一个可选的用户定义回调函数 *func*，每当其运行状态（例如 WiFi 连接、需要配对...）发生变化时由 HomeSpan 调用，从而改变（可选）状态指示灯的闪烁模式
   * 如果设置了 *func*，则无论是否实际定义了状态指示灯，都会调用它
   * 这允许用户使用替代方法反映 HomeSpan 当前状态的更改，例如将消息输出到嵌入式 LCD 或电子墨水显示器
   * 函数 *func* 必须为 *void* 类型并接受一个枚举类型 [HS_STATUS](HS_STATUS.md) 的参数

* `char* statusString(HS_STATUS s)`
   * 返回代表*s*的预定义字符串消息，必须是枚举类型 [HS_STATUS](HS_STATUS.md)
   * 通常与上面的 `setStatusCallback()` 结合使用

* `void setPairingCode(const char *s)`
   * 将设置配对代码设置为 *s*，**必须**恰好是八位数字（无破折号）
   * 示例： `homeSpan.setPairingCode("46637726");`
   * 配对代码的哈希版本将保存到设备的非易失性存储中，覆盖任何当前存储的配对代码
   * 如果 *s* 包含 void 代码，将报告错误并且代码将**不**被保存。 相反，当前存储的配对代码（如果未存储代码，则为 HomeSpan 默认配对代码）
   * :warning:  安全警告：将设备的配对代码硬编码到您的草图中被视为存在安全风险，**不**推荐。 相反，请使用 HomeSpan 提供的更安全的方法之一，例如从 CLI 中键入 "S \<code\>" ，或启动 HomeSpan 的接入点，来设置您的配对代码，而无需将其硬编码到草图中

* `void setSketchVersion(const char *sVer)`
   * 将 HomeSpan 草图的版本设置为 *sVer*，可以是任意字符串
   * 如果未指定，HomeSpan 使用 "n/a" 作为默认版本文本
   * HomeSpan 在启动时在 Arduino IDE 串行监视器中显示草图的版本
   * HomeSpan 还包括草图的版本以及用于编译草图的 HomeSpan 库的版本，作为其 HAP MDNS 广播的一部分。 HAP **不**使用此数据。 相反，它仅供参考，允许您识别通过 [OTA](OTA.md) 更新的设备的草图版本，而不是连接到计算机
  
* `const char *getSketchVersion()`
   * 返回 HomeSpan 草图的版本，使用 `void setSketchVersion(const char *sVer)` 设置，如果未设置则返回 "n/a" 
   * 可以从草图中的任何地方调用

* `void enableWebLog(uint16_t maxEntries, const char *timeServerURL, const char *timeZone, const char *logURL)`
   * 启用滚动网络日志，显示用户使用 `WEBLOG()` 宏创建的最新 *maxEntries* 条目。 参数及其默认值（如果未指定）如下：
     * *maxEntries* —— 要保存的（最新）条目的最大数量。 如果未指定，则默认为 0，在这种情况下，网络日志将仅显示状态，而不显示任何日志条目
     * *timeServerURL* —— 时间服务器的 URL，HomeSpan 在建立 WiFi 连接后启动时将使用它来设置时钟。 如果未指定，则默认为空，在这种情况下 HomeSpan 会跳过设置设备时钟
     * *timeZone* —— 指定用于设置时钟的时区。 使用由 Espressif IDF 解释的标准 Unix 时区格式。 请注意，IDF 使用了一种有点不直观的约定，即时区 "UTC+5:00" 从 UTC 时间**减去**5 小时，而 "UTC-5:00" 向 UTC 时间**添加**5 小时。 如果 *serverURL=NULL* 该字段被忽略； 如果 *serverURL!=NULL* 此字段是必需的
     * *logURL* —— 该设备的网络日志页面的 URL。 如果未指定，则默认为 "状态" 
   * 示例： `homeSpan.enableWebLog(50,"pool.ntp.org","UTC-1:00","myLog");` 在 URL *http<nolink>://HomeSpan-\ [DEVICE-ID\].local:\[TCP-PORT\]/myLog* 将显示 WEBLOG() 宏生成的 50 条最新日志消息。 启动时（建立 WiFi 连接后）HomeSpan 将尝试通过调用服务器 "pool.ntp.org" 并将时间调整为比 UTC 早 1 小时来设置设备时钟。
   * 当尝试连接到 *timeServerURL* 时，HomeSpan 会等待 120 秒以获得响应。 这是在后台完成的，在尝试设置时间时不会阻止 HomeSpan 正常运行。 如果在 120 秒超时期限后未收到响应，HomeSpan 会假定服务器无法访问并跳过时钟设置过程。 使用 `setTimeServerTimeout()` 将 120 秒超时时间重新配置为另一个值
   * 请参阅 [消息日志记录](Logging.md) 了解完整详细信息

* `void setTimeServerTimeout(uint32_t tSec)`
   * 更改 HomeSpan 在 `enableWebLog()` 尝试将来自互联网时间服务器的设备时钟设置为 *tSec* 秒时使用的默认 120 秒超时期限
 
* `void setWebLogCSS(const char *css)`
   * 将 HomeSpan 网络日志的格式设置为 *css* 指定的自定义样式表
   * 有关如何构造 *css* 的详细信息，请参阅 [消息日志记录](Logging.md)
 
* `void processSerialCommand(const char *CLIcommand)`
   * 处理 *CLI* 命令就像在串行监视器中输入一样
   * 允许以编程方式访问所有 CLI 命令，包括用户定义的任何自定义命令
   * 无论设备是否连接到计算机都可以工作
   * 示例： `homeSpan.processSerialCommand("A");` 启动 HomeSpan 设置接入点
   * 示例： `homeSpan.processSerialCommand("Q HUB3");` 将 QR 码的 HomeKit 设置 ID 更改为 "HUB3" 
 
* `void setSerialInputDisable(boolean val)`
    * 如果 *val* 为 true，则禁用 HomeSpan 从串行端口读取输入
    * 如果 *val* 为 false，则重新启用 HomeSpan 从串行端口读取输入
    * 当需要主 USB 串行端口从外部串行外设读取数据而不是用于从 Arduino 串行监视器读取输入时很有用

* `boolean getSerialInputDisable()`
    * 如果 HomeSpan 从串行端口读取当前已禁用，则返回 *true*
    * 如果 HomeSpan 正常运行，则返回 *false* 并将读取输入到 Arduino 串行监视器的任何 CLI 命令
 
---

以下**可选** `homeSpan` 方法为更高级的用例提供了额外的运行时功能：
 
* `void deleteStoredValues()`
   * 从 NVS 中删除所有存储的特性的值设置
   * 执行与在 CLI 中键入 "V" 相同的功能
 
* `boolean deleteAccessory(uint32_t help)`
   * 删除配件 ID 为 *aid* 的配件（如果找到）
   * 如果成功（找到匹配）则返回 true，如果指定的 *aid* 与任何当前附件都不匹配，则返回 false
   * 允许在运行时动态更改附件数据库（即在 Arduino `setup()` 完成**后**更改配置）
   * 删除附件会自动删除所有服务、特性及其包含的任何其他资源
   * 输出列出所有已删除组件的 1 级日志消息
   * 注意：虽然删除会立即生效，但 HomeKit 控制器（例如 Home App）将不会意识到这些更改，直到数据库配置号更新并重新广播 —— 请参阅下面的 updateDatabase()
 
* `boolean updateDatabase()`
   * 重新计算数据库配置编号，如果发生更改，则通过 MDNS 重新广播新编号，以便所有连接的 HomeKit 控制器（例如 Home App）可以请求完全刷新以准确反映新配置
   * 如果配置编号已更改，则返回 true，否则返回 false
   * *仅*如果您想在运行时（即在 Arduino `setup()` 函数完成后）更改设备的配件数据库，则需要
   * 在动态添加一个或多个附件（使用 `new SpanAccessory(aid)` ）或删除一个或多个附件（使用 `homeSpan.deleteAccessory(aid)`）后随时使用
   * **重要**：删除配件后，您在添加新配件（在同一设备上）时将无法重复使用相同的 *aid*，除非新配件配置了与删除的配件完全相同的服务和特征配饰
   * 注意：如果您有一个在草图的 Arduino `setup()` 函数中完全定义的静态配件数据库，则**不需要**此方法
 
---

以下 `homeSpan` 方法被认为是实验性的，因为并非所有用例都已被探索或调试。 谨慎使用：
 
* `void autoPoll(uint32_t stackSize, uint32_t priority, uint32_t cpu)`
 
   * 一个**可选**方法来创建一个单独的任务，在后台重复调用`poll()`。 这释放了 Arduino `loop()` 方法，以便任何用户定义的代码可以并行运行，否则这些代码将被阻塞，或者被在 `loop()` 方法中调用 `poll()` 所阻塞。 参数及其默认值（如果未指定）如下：
 
     * *stackSize* —— 轮询任务使用的堆栈大小（以字节为单位）。 如果未指定，则默认 = 8192
     * *priority* —— 任务运行的优先级。 最小值为 1。最大值通常为 24，但这取决于 ESP32 操作系统的配置方式。 如果将其设置为任意高的值（例如 999），它将被设置为允许的最大优先级。 如果未指定，则默认=1
     * *cpu* —— 指定轮询任务将在其上运行的CPU。 有效值为 0 和 1。该参数在单 CPU 板上被忽略。 如果未指定，则默认=0
   * 如果使用，**必须**放置在草图中作为 Arduino `setup()` 方法的最后一行
   * 如果在同一个程序中同时使用了 `poll()` 和 `autoPoll()`，HomeSpan 将抛出错误并停止 —— 或者将 `poll()` 放置在 Arduino `loop()` 方法中**或**放置 Arduino `setup()` 方法末尾的 `autoPoll()`
   * 如果使用此方法，并且您无需将自己的代码添加到主 Arduino `loop()` 中，则可以安全地跳过在草图中定义空白 `void Loop(){}` 函数
   * 警告: 如果您添加到 Arduino `loop()` 方法的任何代码尝试更改后台 `poll()` 任务中运行的任何 HomeSpan 设置或函数，竞争条件可能会产生未定义的结果
 
## *SpanAccessory（uint32_t aid）*

创建此**类**的实例会将新的 HAP 附件添加到 HomeSpan HAP 数据库中。

   * 每个HomeSpan 草图都需要至少一个配件
   * 每个草图最多可以包含 41 个附件（如果超过，将引发运行时错误并且草图将停止）
   * 没有关联方法
   * 参数 *aid* 是可选的。
  
     * 如果指定且**不**为零，则附件 ID 将设置为 *aid*。
     * 如果未指定或等于 0，则配件 ID 将设置为比先前实例化的配件的 ID 大 1，如果这是第一个配件，则设置为 1。
     * 第一个实例化的 Accessory 必须始终具有 ID=1（如果未指定 *aid*，则这是默认值）。
     * 将第一个Accessory 的 *aid* 设置为除 1 之外的任何值都会在初始化期间引发错误。
    
   * 在实例化任何 Accessories 之前，您必须调用 `homeSpan.begin()`
   * 示例：`new SpanAccessory();`
  
## *SpanService()*

这是一个**基类**，所有 HomeSpan 服务均从中派生，并且**不**直接实例化。 相反，要创建新服务，请实例化 [HomeSpan 服务和特点](ServiceList.md) 命名空间中定义的 HomeSpan 服务之一。 不需要任何参数。

* 实例化的服务被添加到 HomeSpan HAP 数据库并与最后实例化的配件相关联
* 没有先实例化配件就实例化服务会在初始化期间抛出错误
* 示例：`new Service::MotionSensor();`

支持以下方法：

* `SpanService *setPrimary()`
   * 指定这是配件的主要服务。 返回指向服务本身的指针，以便在实例化期间可以链接该方法
   * 示例：`(new Service::Fan)->setPrimary();`
   * 请注意，虽然此功能是由 Apple 在 HAP-R2 中定义的，但它似乎已被弃用，不再有任何用途或对 Home 应用程序有任何影响
  
* `SpanService *setHidden()`
   * 指定这是附件的隐藏服务。 返回指向服务本身的指针，以便可以在实例化期间链接该方法。
   * 示例：`(new Service::Fan)->setHidden();`
   * 请注意，虽然此功能是由 Apple 在 HAP-R2 中定义的，但它似乎已被弃用，不再有任何用途或对 Home 应用程序有任何影响
  
* `SpanService *addLink(SpanService *svc)`
   * 添加 *svc* 作为链接服务。 返回指向调用服务本身的指针，以便在实例化期间可以链接该方法
   * 请注意，链接服务仅适用于选定的 HAP 服务。 有关完整详细信息，请参阅 Apple 的 HAP-R2 文档
   * 示例：`(new Service::Faucet)->addLink(new Service::Valve)->addLink(new Service::Valve);`（将两个阀门链接到一个水龙头）

* `vector<SpanService *> getLinks()`
   * 返回指向使用 `addLink()` 添加的服务的指针向量
   * 对于创建迭代所有链接服务的循环很有用
   * 请注意，返回的向量指向通用的 SpanServices，应根据需要重新转换
   * 示例： `for(auto myValve : faucet->getLinks()) { if((MyValve *)myValve)->active->getVal()) ... }` 检查链接到水龙头的所有阀门
  
* `virtual boolean update()`
   * HomeSpan 在收到来自 HomeKit 控制器的请求后调用此方法，以更新与服务关联的一个或多个特征。 用户应使用使用下面的一个或多个SpanCharacteristic 方法实现请求更新的代码来重写此方法。 如果更新成功，方法**必须**返回 *true*，否则返回 *false*。
  
* `virtual void loop()`
   * 每次执行 `homeSpan.poll()` 时，HomeSpan 都会调用此方法。 用户应使用监视特性状态变化的代码覆盖此方法，这些特性需要使用下面的一个或多个 SpanCharacteristic 方法通知 HomeKit 控制器。
  
* `virtual void button(int pin, int pressType)`
   * 每当触发与 Service 关联的 SpanButton() 对象时，HomeSpan 都会调用此方法。 用户应使用以下代码重写此方法，该代码使用下面的一个或多个 SpanCharacteristic 方法实现响应 SpanButton() 触发器而采取的任何操作。
     * **引脚** —— 与 SpanButton() 对象关联的 ESP32 引脚
     * *按下类型* -
       * 0 = 单击一次 (SpanButton::SINGLE)
       * 1 = 按两次 (SpanButton::DOUBLE)
       * 2 = 长按 (SpanButton::LONG)
    
## *SpanCharacteristic（value[,boolean nvsStore]）*
  
这是一个**基类**，所有 HomeSpan 特性均从中派生，并且**不**直接实例化。 相反，要创建新的特性，请实例化 [HomeSpan 服务和特点](ServiceList.md) 命名空间中定义的 HomeSpan 特性之一。

* 实例化的特征被添加到 HomeSpan HAP 数据库并与最后实例化的服务相关联
* 没有首先实例化服务就实例化一个特性，会在初始化期间抛出错误
* 第一个参数允许您在启动时设置特性的初始**值**。 如果未指定**值**，HomeSpan 将为特性提供合理的默认值
* 如果 *value* 超出特性的最小/最大范围，则抛出运行时警告，其中最小/最大是 HAP 默认值，或者是通过调用 `setRange()` 设置的任何新值
* 第二个可选参数，如果设置为 "true" ，则指示 HomeSpan 在设备的非易失性存储 (NVS) 中保存对此特性值的更新，以便在设备断电时在启动时恢复。 如果未指定，*nvsStore* 将默认为 "false"（无存储）
* 例子：
   * `new Characteristic::Brightness();` 亮度初始化为默认值
   * `new Characteristic::Brightness(50);` 亮度初始化为 50
   * `new Characteristic::Brightness(50,true);` 亮度初始化为50, 更新保存在 NVS 中

#### 基于数字的特征支持以下方法（例如 *int*、*float*...）：

* `type T getVal<T>()`
   * 一个模板方法，在转换为指定的 *T* 类型（例如 *int*、*double* 等）后，返回基于数字的特性的**当前**值。 如果模板参数被排除，值将被转换为 *int*。
   * 指定模板的示例：`double temp = Characteristic::CurrentTemperature->getVal<double>();`
   * 排除模板的示例：`inttilt = Characteristic::CurrentTiltAngle->getVal();`

* `type T getVal<T><T>()`
   * 一个模板方法，返回 HomeKit 控制器请求更新特性所需的**新**值。 与 `getVal<>()` 相同的转换规则
    
* `void setVal(value [,boolean notify])`
   * 将基于数字的特性的值设置为 *value*，并且如果 *notify* 设置为 true，则通知所有 HomeKit 控制器有关更改。 *notify* 标志是可选的，如果未指定，则将设置为 true。 将 *notify* 标志设置为 false 允许您在不通知任何 HomeKit 控制器的情况下更新特性，这对于 HomeKit 自动调整的特性（例如倒计时器）很有用，但如果 Home 应用程序关闭并且正在运行，则会向附件请求。 然后重新打开
   * 适用于任何整数、boolean 值或基于浮点的数值 *value*，尽管 HomeSpan 会将 *value* 转换为每个特性的适当类型（例如，在基于整数的特性上调用 `setValue(5.5)` 会产生 *value*=5 ）
   * 如果 *value* 超出特性的最小/最大范围，则抛出运行时警告，其中最小/最大是 HAP 默认值，或者是通过之前调用 `setRange()` 设置的任何新的最小/最大范围
   * **值不**限制为步长的增量；例如，在基于浮动的特征上调用 `setRange(0,100,5)` 后调用 `setVal(43.5)` 是完全有效的，即使 43.5 与指定的步长不对齐。 Home App 会正确地将值保留为 43.5，但在滑块图形中使用时（例如设置恒温器的温度），它会四舍五入到最接近的步长增量（在本例中为 45）

* `SpanCharacteristic *setRange(min, max, step)`
   * 使用指定的 *min*、*max* 和 *step* 参数覆盖特性的默认 HAP 范围
   * *步骤*是可选的； 如果未指定（或设置为非正数），则默认 HAP 步长保持不变
   * 适用于任何整数或基于浮点的参数，尽管 HomeSpan 会将参数重新转换为每个特征的适当类型（例如，在基于整数的特征上调用 `setRange(50.5,70.3,0.5)` 会导致 *min*=50 ，*max*=70，并且*step*=0)
   * 如果出现以下情况，则会抛出错误：
     * 调用不支持范围更改的特性，或者
     * 对同一特征多次调用
   * 返回一个指向 Characteristic 本身的指针，以便在实例化期间可以链接该方法
   * 示例：`(new Characteristic::Brightness(50))->setRange(10,100,5);`
  
* `SpanCharacteristic *setValidValues(int n, [int v1, int v2 ...])`
   * 使用 *n* 个值 *v1*、*v2* 等的可变长度列表覆盖具有特定枚举有效值的特性的默认 HAP 有效值。
   * 仅适用于 UINT8、UINT16、UINT32 和 INT 格式的特性
     * 如果对具有任何其他格式的特征调用此方法，则会引发警告消息，并且请求将被忽略
   * 返回一个指向 Characteristic 本身的指针，以便在实例化期间可以链接该方法
   * 示例： `(new Characteristic::SecuritySystemTargetState())->setValidValues(3,0,1,3);` 创建一个长度等于 3 的新有效值列表，其中包含值 0、1 和 3。 通知 HomeKit SecuritySystemTargetState 值 2（Night Arm）无效且不应在 Home App 中显示为选项的效果







#### 基于字符串的特性支持以下方法（即以 null 结尾的 C 样式字符数组）：

* `char *getString()`
   * 相当于 `getVal()`，但专门用于字符串特征（即以 null 结尾的字符数组）
  
* `char *getNewString()`
   * 相当于 `getNewVal()`，但专门用于字符串特征（即以 null 结尾的字符数组）

* `void setString(const char *value)`
   * 相当于 `setVal(value)`，但专门用于字符串特征（即以 null 结尾的字符数组）
 
#### DATA（即字节数组）特性支持以下方法：

* `size_t getData(uint8_t *data, size_t len)`
   * 类似于`getVal()`，但专门用于字节数组特性
   * 填充指定大小 *len* 的字节数组 *data*，所有字节“编码”为特征的当前值
   * 返回特征中编码的字节总数
   * 如果 *len* 小于编码的字节总数，则不会提取任何数据（即 *data* 未修改），并抛出一条警告消息，指示 *data* 数组的大小不足以提取所有字节编码在特征中
   * 将 *data* 设置为 NULL 返回编码的字节总数，而不提取任何数据。 这可用于帮助在提取数据之前创建足够大小的 *data* 数组
  
* `size_t getNewData(uint8_t *data, size_t len)`
   * 与 `getData()` 类似，但填充指定大小 *len* 的字节数组 *data*，其字节数基于 HomeKit 控制器请求将特性更新到的所需 **新 ** 值

* `void setData(uint8_t *data, size_t len)`
   * 类似于`setVal()`，但专门用于字节数组特性
   * 通过用字节数组 *data* 中的 *len* 字节“填充”它来更新特性
   * 注意：字节数组特征被编码并作为 base-64 字符串传输。 HomeSpan 自动执行此格式和指定字节数组之间的所有编码和解码。 但是，当输出到串行监视器时，字节数组特征的值以其 base-64 格式显示（而不是显示为字节数组），因为 base-64 是实际传输到 HomeKit 或从 HomeKit 传输的表示形式

#### 所有特性都支持以下方法：

* `boolean updated()`
   * 如果 HomeKit 控制器请求更新特性值，则返回 *true*，否则返回 *false*。 请求的值本身可以使用 `getNewVal<>()` 或 `getNewString()` 检索

* `int timeVal()`
   * 返回自上次更新特性值以来经过的时间（以毫秒为单位）（无论是通过 `setVal()` 、 `setString()` 还是作为来自 HomeKit 控制器的成功更新请求的结果）

* `SpanCharacteristic *setPerms(uint8_t perms)`
   * 将特性的默认权限更改为 *perms*，其中 *perms* 是权限的附加列表，如 HAP-R2 表 6-4 中所述。 有效值为 PR、PW、EV、AA、TW、HD 和 WR
   * 返回一个指向Characteristic本身的指针，以便在实例化期间可以链接该方法
   * 示例：`(new Characteristic::IsConfigured(1))->setPerms(PW+PR+EV);`
   
* `SpanCharacteristic *addPerms(uint8_t perms)`
   * 将新权限 *perms* 添加到特性的默认权限中，其中 *perms* 是权限的附加列表，如 HAP-R2 表 6-4 中所述。 有效值为 PR、PW、EV、AA、TW、HD 和 WR
   * 返回一个指向 Characteristic 本身的指针，以便在实例化期间可以链接该方法
   * 示例：`(new Characteristic::IsConfigured(1))->addPerms(PW);`

* `SpanCharacteristic *removePerms(uint8_t perms)`
   * 从特性的默认权限中删除权限 *perms*，其中 *perms* 是权限的附加列表，如 HAP-R2 表 6-4 中所述。 有效值为 PR、PW、EV、AA、TW、HD 和 WR
   * 返回一个指向Characteristic本身的指针，以便在实例化期间可以链接该方法
   * 示例： `(new Characteristic::ConfiguredName("HDMI 1"))->removePerms(PW);`

* `SpanCharacteristic *setDescription(const char *desc)`
   * 将可选描述 *desc* 添加到特性中，如 HAP-R2 表 6-3 中所述
   * 该字段通常用于提供有关自定义特征的信息，但 Home App 似乎不会以任何方式使用
   * 返回一个指向 Characteristic 本身的指针，以便在实例化期间可以链接该方法
   * 示例： `(new Characteristic::MyCustomChar())->setDescription("Tuner Frequency");`

* `SpanCharacteristic *setUnit(const char *unit)`
   * 添加或覆盖特性的*单位*，如 HAP-R2 表 6-6 中所述
   * 返回一个指向 Characteristic 本身的指针，以便在实例化期间可以链接该方法
   * 示例： `(new Characteristic::RotationSpeed())->setUnit("percentage");`

### *SpanButton(int pin, uint16_t longTime, uint16_t singleTime, uint16_t doubleTime, boolean (\*triggerType)(int))*

创建此**类**的实例会将按钮处理程序附加到指定的 ESP32 **引脚**。

* 实例化的按钮与最后实例化的服务相关联
* 没有先实例化 Service 就实例化 Button 会在初始化期间抛出错误

第一个参数是必需的； 其余的是可选的：
 
* **引脚** —— 按钮所连接的 ESP32 引脚
* *longTime* —— 按下并按住按钮以触发长按所需的最短时间（以毫秒为单位）（默认 = 2000 毫秒）
* *singleTime* —— 按下按钮触发单次按下所需的最短时间（以毫秒为单位）（默认 = 5 毫秒）
* *doubleTime* —— 两次单击之间允许作为双击的最长时间（以毫秒为单位）（默认 = 200 毫秒）
* *triggerType* —— 指向 boolean 函数的指针，该函数接受单个 *int* 参数并返回 "true" 或 "false" ，具体取决于传递给 *int* 的**引脚**数字是否触发了“按下”争论。 为了方便使用，您可以简单地从以下内置函数中进行选择：
   * `SpanButton::TRIGGER_ON_LOW` —— 当**引脚**驱动为低电平时触发。 适用于将**引脚**连接到 GROUND 的按钮（这是未指定 *triggerType* 时的默认设置）
 
   * `SpanButton::TRIGGER_ON_HIGH` —— 当**引脚**驱动为高电平时触发。 适用于将**引脚**连接到 VCC（通常为 3.3V）的按钮
   * `SpanButton::TRIGGER_ON_TOUCH`- 使用设备的触摸传感器外设在触摸连接到**引脚**的传感器时触发（在 ESP32-C3 设备上不可用）
 
当选择任何这些内置函数时（或未指定 *triggerType* 并使用默认值），SpanButton 将在实例化时根据需要自动配置**引脚**。
 
或者，您可以将 *triggerType* 设置为 `boolean(int arg)` 形式的任何用户定义函数，并提供您自己的逻辑来确定指定**引脚**上是否发生触发，该触发将传递给您的函数 作为 *arg*。 在这种情况下，*arg* 可以代表实际的设备引脚，也可以只是函数使用的任意 *int*，例如多路复用器上的虚拟引脚号。 注意：如果您为 *triggerType* 指定自己的函数，您还必须在草图中包含初始化逻辑或配置 *triggerType* 正在使用的任何资源（例如引脚多路复用器）所需的任何代码。

为了方便起见，还提供了 *SpanButton()* 构造函数的第二种形式：
   * `SpanButton(int pin, boolean (*triggerType)(int), uint16_t longTime=2000, uint16_t singleTime=5, uint16_t doubleTime=200)`
     * 这允许您仅设置**引脚**和 *triggerType*，同时将其余参数保留为默认值
 
#### 触发规则 ###
* 如果按下按钮并持续按住，每隔 longTime ms 就会触发一次长按，直到松开按钮
* 如果按下按钮的时间超过 singleTime 毫秒但少于 longTime 毫秒然后释放，则会触发单次按下，除非在 doubleTime 毫秒内再次按下按钮并再次按住至少 singleTime 毫秒，在这种情况下 DoublePress 将被触发； 在释放按钮之前不会发生进一步的事件
* 如果singleTime>longTime，则只有长按触发才会发生
* 如果 doubleTime=0，则不会发生双击
 
### 用法 ###
当与该服务关联的任何 SpanButton 中发生触发事件时，HomeSpan 会自动调用该服务的 `button(int pin, int pressType)` 方法，其中**引脚**是按钮所连接的 ESP32 引脚，*pressType* 是 也可以由指示的枚举常量表示的整数：
   * 0 = 单击（`SpanButton::SINGLE`）
   * 1 = 双击 (`SpanButton::DOUBLE`)
   * 2 = 长按（`SpanButton::LONG`）
  
如果用户没有覆盖包含一个或多个 Button 的 Service 的 virtual Button() 方法，HomeSpan 将在初始化期间报告警告，但不会报告错误； 这些按钮的触发器将被忽略。
 
当使用一个或多个触摸传感器时，HomeSpan 会在实例化第一个 `SpanButton::TRIGGER_ON_TOUCH` 类型的 SpanButton 时轮询基线传感器读数，自动校准触发传感器的阈值。 对于 ESP32 设备，阈值设置为基线值的 50%，因为当传感器值低于阈值水平时就会发生触发。 对于 ESP32-S2 和 ESP32-S3 设备，阈值设置为基线值的 200%，因为当传感器值上升*高于*阈值水平时就会发生触发。 通常，HomeSpan 的自动校准将导致准确检测触摸传感器的单击、双击和长按。 但是，如果需要，您可以使用以下类级别方法覆盖校准并设置您自己的阈值：

  * `void SpanButton::setTouchThreshold(uintXX_t thresh)`
    * 设置高于（对于 ESP32 设备）或低于（对于 ESP32-S2 和 ESP32-S3 设备）触摸传感器被触发的阈值 *thresh*
    * *XX* 为 16（对于 ESP32 设备）或 32（对于 ESP32-S2 和 ESP32-S3 设备）
    * 指定的阈值被视为全局阈值，并用于 `SpanButton::TRIGGER_ON_TOUCH` 类型的**所有** SpanButton 实例
    * 该方法可以在创建 SpanButton 之前或之后调用
 
此外，您还可以使用以下类级方法覆盖 ESP32 的触摸传感器时序参数：

* `void SpanButton::setTouchCycles(uint16_tmeasureTime, uint16_t sleepTime)`
   * 将测量时间和睡眠时间时钟周期分别更改为 *measureTime* 和 *sleepTime*。 这只是对 Arduino-ESP32 库 `touchSetCycles()` 函数的传递调用
   * 除非使用 `setTouchThreshold()` 设置了特定的阈值，否则在实例化 `SpanButton::TRIGGER_ON_TOUCH` 类型的第一个 `SpanButton()` 之前必须调用 `setTouchCycles()`，以便 HomeSpan 将根据指定的新定时参数校准触摸阈值

### *SpanToggle(int pin, boolean (\*triggerType)(int)=PushButton::TRIGGER_ON_LOW, uint16_32toggleTime=5)*
 
创建此**类**的实例会将切换开关处理程序附加到指定的 ESP32 **引脚**。 这是 *SpanButton* 的子类，因此派生出所有相同的功能。 例如，您可以将 *triggerType* 设置为 PushButton::TRIGGER_ON_HIGH，创建自己的触发函数等。但是，当 "按下" 按钮时，HomeSpan 不会调用 `button(int pin, int pressType)` ，而是调用当开关从一个位置“切换”到另一个位置时，使用相同的 `button()` 方法。 在这种情况下，传递给 `button()` 的参数 *pressType* 有一组不同的枚举：
   * 3 = 开关已关闭（`SpanToggle::CLOSED`）
   * 4 = 开关打开（`SpanToggle::OPEN`）
 
请注意，构造函数中没有 *singleTime*、*longTime* 或 *doubleTime* 参数，因为您无法单击、双击或长按切换开关。 相反，构造函数支持单个参数 *toggleTime* （如果未指定，则默认 = 5ms），该参数设置开关需要移动到关闭位置以触发对 `button()` 方法的调用的最短时间。这有效地“消除了”拨动开关的抖动。
 
SpanToggle 还支持以下附加方法：
 
  * `int position()`
    * 返回切换开关的当前位置（即 SpanToggle::CLOSED 或 SpanToggle::OPEN）
    * 相当于传递给 `button()` 方法的 *pressType* 参数，但可以从草图中的任何位置调用
    * 用于在启动时读取接触开关的初始状态，以便可以相应地设置 Characteristic::ContactSensorState 的初始值
    * 示例 `sensorState=new Characteristic::ContactSensorState(toggleSwitch->position()==SpanToggle::OPEN);`
 
### *SpanUserCommand(char c, const char \*desc, void (\*f)(const char \*buf [,void \*obj]) [,void \*userObject])*

创建此**类**的实例会将用户定义的命令添加到 HomeSpan 命令行界面 (CLI)，其中：

   * *c* 是用户定义命令的单字母名称
   * *desc* 是用户定义命令的描述，当用户键入 "?" 时显示 进入 CLI
   * *f* 是指向调用命令时调用的用户定义函数的指针。 *f* 的允许形式为：
     1. `void f(const char *buf)`，或者
     2. `void f(const char *buf, void *obj)`
   * *userObject* 是指向任意对象的指针，当使用 *f* 的第二种形式时，HomeSpan 会作为第二个参数传递给函数 *f*。 请注意，当使用 *f* 的第一种形式时，包含 *userObject* 是一个错误，而当使用 *f* 的第二种形式时，排除 *userObject* 也是一个错误

要从 CLI 调用自定义命令，请在单字母名称 *c* 前面添加 "@" 。 这使得 HomeSpan 能够区分用户定义的命令和内置命令。 例如，

```C++
new SpanUserCommand('s', "save current configuration 保存当前配置", saveConfig);
...
void saveConfig(const char *buf){ ... };
```

将向 CLI 添加一个新命令 "@s" ，其描述为 "保存当前配置" ，在调用时将调用用户定义的函数 `void saveConfig(const char *buf)`。 参数 *buf* 指向在 "@" 之后在 CLI 中键入的所有字符的数组。 这允许用户将参数从 CLI 传递到用户定义的函数。 例如，在调用 saveConfig 时，在 CLI 中键入 "@s123" 会将 *buf* 设置为 "s123" 。

在参数的第二种形式中，HomeSpan 将向您的函数 *f* 传递一个附加对象。 例如，

```C++
struct myConfigurations[10]；
new SpanUserCommand('s', "<n> save current configuration for specified index 保存指定索引的当前配置，n", saveConfig, myConfigurations);
...
void saveConfig(const char *buf, void *obj){ ... do something with myConfigurations ... };
```

当仅使用 "@s" 命令调用时，可以用于保存 *myArray* 中的所有元素，并且可能根据添加到命令的索引仅保存一个元素，例如 "@s34" 将元素 34 保存在**我的数组**。 用户可以在函数 *f* 中创建所有必要的逻辑，以解析和处理 *buf* 中传递的完整命令文本，并对通过 *obj* 传递的任何内容进行操作。

要创建多个用户定义命令，只需创建多个 SpanUserCommand 实例，每个实例都有自己的单字母名称。 请注意，在 SpanUserCommand 实例中重复使用相同的单字母名称会覆盖之前使用该相同字母的任何实例。

## 自定义特征和自定义服务宏

### *CUSTOM_CHAR（name,uuid,perms,format,defaultValue,minValue,maxValue,staticRange）*
### *CUSTOM_CHAR_STRING（name,uuid,perms,defaultValue）*
### *CUSTOM_CHAR_DATA（name,uuid,perms）*

创建可以添加到任何服务的自定义特征。 自定义特征通常会被 Home 应用程序忽略，但可能会被其他第三方应用程序使用（例如 *Eve for HomeKit*）。 第一种形式应该用于创建数字字符（例如，UINT8、BOOL...）。 第二种形式用于基于 STRING 的特征。 第三种形式用于基于数据（即字节数组）的特征。 参数如下（请注意，任何宏参数中都不应使用引号，但应用于基于 STRING 的特性时，*defaultValue* 除外）：

* *名称* —— 自定义特征的名称。 这将被添加到特性命名空间中，以便像任何 HomeSpan 特性一样访问它
* *uuid* —— 制造商定义的特性的 UUID。 必须*正好* 36 个字符，格式为 XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX，其中 *X* 表示有效的十六进制数字。 如果需要，则需要前导零，如 HAP-R2 第 6.6.1 节中更详细的描述
* *权限* —— 附加权限列表，如 HAP-R2 表 6-4 中所述。 有效值为 PR、PW、EV、AA、TW、HD 和 WR
* *format* —— 指定特征值的格式，如 HAP-R2 表 6-5 中所述。 有效值为 BOOL、UINT8、UINT16、UNIT32、UINT64、INT 和 FLOAT（请注意，HomeSpan 目前不支持 TLV8 格式）。 不适用于 STRING 或 DATA 特征宏
* *defaultValue* —— 指定特性的默认值（如果在实例化期间未定义）。 不适用于数据特征宏。
* *minValue* —— 指定有效值的默认最小范围，可以通过调用 `setRange()` 来覆盖它。 不适用于 STRING 或 DATA 特征宏
* *minValue* —— 指定有效值的默认最小范围，可以通过调用 `setRange()` 来覆盖它。 不适用于 STRING 或 DATA 特征宏
* *staticRange* —— 如果 *minValue* 和 *maxValue* 是静态的并且不能通过调用 `setRange()` 来覆盖，则设置为 *true*。 如果允许调用 `setRange()` ，则设置为 *false*。 不适用于 STRING 或 DATA 特征宏

例如，下面的第一行创建一个名为 "Voltage" 的自定义特性，其 UUID 代码可被 *Eve for HomeKit* 应用程序识别。 这些参数显示该特性是只读的 (PR) 并且通知已启用 (EV)。 允许值的默认范围是 0-240，默认值为 120。后续调用 `setRange()` 可以覆盖该范围。 下面的第二行创建一个自定义的基于只读字符串的特征：

```C++
CUSTOM_CHAR(Voltage, E863F10A-079E-48FF-8F27-9C2605A29F52, PR+EV, UINT16, 120, 0, 240, false);
CUSTOM_CHAR_STRING(UserTag, AAAAAAAA-BBBB-AAAA-AAAA-AAAAAAAAAAAA, PR, "Tag 123");
...
new Service::LightBulb();
  new Characteristic::Name("Low-Voltage Lamp");
  new Characteristic::On(0);
  new Characteristic::Brightness(50);
  new Characteristic::Voltage(12);      // adds Voltage Characteristic and sets initial value to 12 volts
  new Characteristic::UserTag();        // adds UserTag Characteristic and retains default initial value of "Tag 123"

```

请注意，自定义特征必须在全局级别创建（即不在 `setup()` 内部）且在调用 `homeSpan.begin()` 之前

> 高级提示 1：当遇到无法识别的自定义特征时，*Eve for HomeKit* 会显示一个*通用控件*，允许您与在 HomeSpan 中创建的任何自定义特征进行交互。 但是，由于 Eve 无法识别该特性，因此只有在该特性包含**描述**字段时，它才会呈现通用控件，您可以使用上述 `setDescription()` 方法将其添加到任何特性中。 您可能还想使用 `setUnit()` 和 `setRange()` ，以便 Eve 应用程序显示具有适合您的自定义特征的范围的控件。
 
> 高级提示 2：DATA 格式当前未被任何本机家庭应用程序特性使用，尽管它是 HAP-R2 规范的一部分。 此格式包含在 HomeSpan 中，因为其他应用程序（例如 *Eve for HomeKit*）确实使用这些类型的特征来创建家庭应用程序之外的功能，因此提供给高级用户进行实验。
 
> 高级提示 3：使用多文件草图时，如果您在多个文件中定义相同的自定义特性，编译器将抛出“重定义错误”。 为了避免这一错误并允许在多个文件中使用相同的自定义特征，请在每个包含“重复”定义的文件中添加行 `#define CUSTOM_CHAR_HEADER` **之前* `#include "HomeSpan.h` 先前定义的自定义特征。

### *CUSTOM_SERV（name，uuid）*

创建与第三方应用程序一起使用的自定义服务（例如*HomeKit 的 Eve*)。 自定义服务将显示在本机 Apple Home 应用程序中，并带有标有 "不支持" 的图块，但否则该服务将被 Home 应用程序安全地忽略。 参数如下（请注意，任一宏参数中不应使用引号）：

* *名称* —— 自定义服务的名称。 这将被添加到 Service 命名空间中，以便像任何 HomeSpan 服务一样访问它。 例如，如果 *name*="Vent"，HomeSpan 会将 `Service::Vent` 识别为新的服务类
* *uuid* —— 制造商定义的服务的 UUID。 必须**正好** 36 个字符，格式为 XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX，其中 *X* 表示有效的十六进制数字。 如果需要，则需要前导零，如 HAP-R2 第 6.6.1 节中更详细的描述

自定义服务可能包含自定义特征和标准 HAP 特征的混合，但由于服务本身是自定义的，因此家庭应用程序将忽略整个服务，即使它包含一些标准 HAP 特征。 请注意，必须在调用 `homeSpan.begin()` 之前创建自定义服务

一个完整的示例展示了如何使用 ***CUSTOM_SERV()*** 和 ***CUSTOM_CHAR()*** 宏来创建由 *Eve for HomeKit* 识别的压力传感器配件，可以在 Arduino IDE 位于 [*文件 → 示例 → HomeSpan → 其他示例 → CustomService*](../examples/Other%20Examples/CustomService) 下。

## 其他宏

### *SPAN_ACCESSORY()* 和 *SPAN_ACCESSORY(NAME)*
 
一个“方便”宏，它实现了创建附件时使用的以下非常常见的代码片段。 仅当 *NAME* （C 样式字符串）已作为宏的参数包含时，才包含最后一行：

```C++
new SpanAccessory();
 new Service::AccessoryInformation();
 new Characteristic::Identify();
 new Characteristic::Name(NAME);   // included only in the second form of the macro
```

## 用户可定义宏
 
### *#定义所需版本（主要、次要、补丁）*

如果在使用 `#include "HomeSpan.h"` 包含 HomeSpan 库**之前**在主草图中定义了 REQUIRED，则 HomeSpan 将引发编译时错误，除非包含的库的版本等于或晚于：使用 VERSION 宏指定的版本。 例子：

```C++
#define REQUIRED VERSION(1,3,0) // 抛出编译时错误，除非使用的 HomeSpan 库是 1.3.0 或更高版本
#include "HomeSpan.h" 
```

---

[↩️](../README.md) 返回欢迎页面
