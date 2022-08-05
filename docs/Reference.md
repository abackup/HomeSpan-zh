# HomeSpan API 参考

通过在您的 Arduino 草图中包含 *HomeSpan.h* 来调用 HomeSpan 库，如下所示：

```C++
#include "HomeSpan.h"
```

## *homeSpan*

在运行时 HomeSpan 将创建一个名为 `homeSpan` 的全局**对象**，它支持以下方法：

* `void begin(Category catID, const char *displayName, const char *hostNameBase, const char *modelName)`
   * 初始化 HomeSpan
   * **必须**在任何其他 HomeSpan 函数之前在每个草图的开头调用，并且通常放置在 Arduino `setup()` 方法的顶部附近，但位于  `Serial.begin()`**之后** 所以 初始化诊断可以输出到串行监视器
   * 所有参数都是**可选的**
  
     * *catID* - HAP 类别 HomeSpan 广播用于与 HomeKit 配对。 默认为Category::Lighting。 有关完整列表，请参阅 [HomeSpan 附件类别](Categories.md)
     * *displayName* - HomeSpan 广播的 MDNS 显示名称。 默认为“HomeSpan Server”
     * *hostNameBase* - 完整的 MDNS 主机名由 HomeSpan 作为 *hostNameBase-DeviceID*.local 广播，其中 DeviceID 是 HomeSpan 自动生成的唯一 6 字节代码。 默认为“HomeSpan”
     * *modelName* - HAP 模型名称 HomeSpan 广播用于与 HomeKit 配对。 默认为“HomeSpan-ESP32”
   * 示例：`homeSpan.begin(Category::Fans, "Living Room Ceiling Fan");`
 
* `void poll()`
    * 检查 HAP 请求、本地命令和设备活动
    * **必须**在每个草图中重复调用，通常放置在 Arduino `loop()` 方法的顶部
   
---

以下**可选** `homeSpan` 方法会覆盖 `begin()` 中使用的各种 HomeSpan 初始化参数，因此**应该**在 `begin()` 之前调用才能生效。 如果一个方法*不*调用，HomeSpan 使用如下所示的默认参数：

* `void setControlPin(uint8_t pin)`
   * 设置 ESP32 引脚用于 HomeSpan 控制按钮。 如果未指定，HomeSpan 将假定没有控制按钮
  
* `void setStatusPin(uint8_t pin)`
   * 设置 ESP32 引脚用于 HomeSpan 状态 LED。 如果未指定，HomeSpan 将假定没有状态 LED

*`void setStatusAutoOff（uint16_t 持续时间）`
   * 将状态 LED 设置为在 *duration* 秒后自动关闭
   * 每当 HomeSpan 激活新的闪烁模式时，状态 LED 将自动打开，持续时间计时器将被重置
   * 如果 *duration* 设置为零，则禁用自动关闭（状态 LED 将无限期保持亮起）
  
* `int getStatusPin()`
* 返回由 `setStatusPin(pin)` 设置的状态 LED 的引脚号，如果没有设置引脚，则返回 -1

* `void setApSSID(const char *ssid)`
   * 设置 HomeSpan 设置接入点的 SSID（网络名称）（默认 =“HomeSpan-Setup”）
  
* `void setApPassword(const char *pwd)`
   * 设置 HomeSpan 设置接入点的密码 (default="homespan")
  
* `void setApTimeout(uint16_t nSec)`
   * 设置 HomeSpan 设置接入点一旦激活，在超时之前保持活动的持续时间（以秒为单位）（默认值 = 300 秒）
  
* `void setCommandTimeout(uint16_t nSec)`
   * 设置 HomeSpan 最终用户命令模式一旦激活，在超时之前保持活动的持续时间（以秒为单位）（默认值 = 120 秒）
  
* `void setLogLevel(uint8_t level)`
   * 设置诊断消息的日志级别，其中：
  
      * 0 = 顶级 HomeSpan 状态消息，以及用户使用 `Serial.print()` 或 `Serial.printf()` 输出的任何消息（默认）
      * 1 = 所有 HomeSpan 状态消息，以及用户在草图中指定的任何“LOG1()”消息
      * 2 = 所有 HomeSpan 状态消息加上所有进出 HomeSpan 设备的 HAP 通信数据包，以及用户在草图中指定的所有“LOG1()”和“LOG2()”消息
   * 请注意，日志级别也可以在运行时通过 [HomeSpan CLI](CLI.md) 使用“L”命令更改
   * 完整的细节参见 [消息记录](Logging.md)
   
* `void reserveSocketConnections(uint8_t nSockets)`
   * 保留 *nSockets* 网络套接字用于 **HomeSpan HAP 服务器用于 HomeKit 控制器连接的**除外
      * 对于在 Arduino-ESP32 v2.0.1 或更高版本下编译的草图，HomeSpan 为 HAP 控制器连接保留 14 个插槽
      * 每次调用 `reserveSocketConnections(nSockets)` 都会将这个数字减少 *nSockets*
      * 如果您将代码添加到需要其自己的套接字连接的草图（例如，单独的 Web 服务、MQTT 服务器等），请使用此方法
  * 允许多次调用此方法 - 保留的套接字数量将是所有调用中 *nSockets* 的总和
  * 请注意，您不需要为内置 HomeSpan 功能单独保留套接字
    * 例如，`enableOTA()` 已经包含对`reserveSocketConnections(1)` 的嵌入式调用，因为 HomeSpan 知道必须保留一个套接字才能支持 OTA
  
*`void setPortNum（uint16_t 端口）`
   * 设置用于 HomeKit 和 HomeSpan 之间通信的 TCP 端口号（默认 = 80）
  
* `void setHostNameSuffix(const char *suffix)`
   * 设置后缀 HomeSpan 附加到 *hostNameBase* 以创建完整的主机名
   * 如果未指定，默认情况下 HomeSpan 会在 HomeSpan 设备的 6 字节附件 ID 后附加破折号“-”
   * 允许将 *suffix* 设置为空字符串 ""
   * 示例：`homeSpan.begin(Category::Fans, "Living Room Ceiling Fan", "LivingRoomFan");` 将生成 *LivingRoomFan-A1B2C3D4E5F6.local* 形式的默认 *hostName*。 在 `homeSpan.begin()` 之前调用 `homeSpan.setHostNameSuffix("v2")` 将产生 *LivingRoomFanv2.local* 的 *hostName*
  
* `void setQRID(const char *id)`
   * 将用于将设备与 [QR 码](QRCodes.md) 配对的设置 ID 从 HomeSpan 默认更改为 *id*
   * HomeSpan 默认为“HSPN”，除非使用“Q”命令通过 [HomeSpan CLI](CLI.md) 为设备永久更改
   * *id* 必须正好是 4 个字母数字字符（0-9、A-Z 和 a-z）。 如果没有，更改设置 ID 的请求将被忽略，并使用默认值代替
  
---

以下 **可选** `homeSpan` 方法启用附加功能并提供 HomeSpan 环境的进一步定制。 除非另有说明，否则调用**应该**在 `begin()` 之前进行才能生效：

* `void enableOTA(boolean auth=true, boolean safeLoad=true)`
   * 启用 HomeSpan 设备的 [无线 (OTA) 更新](OTA.md)，否则会被禁用
   * HomeSpan OTA 需要授权密码，除非指定 *auth* 并设置为 *false*
   * 新 HomeSpan 设备的默认 OTA 密码为“homespan-ota”
   * 这可以通过 [HomeSpan CLI](CLI.md) 使用“O”命令进行更改
   * 注意启用 OTA 将 HAP 控制器连接数减少 1
   * OTA 安全加载将默认启用，除非指定第二个参数并将其设置为 *false*。 HomeSpan OTA 安全加载检查以确保上传到现有 HomeSpan 设备的草图本身就是 HomeSpan 草图，并且它们也启用了 OTA。 详见[HomeSpan OTA 安全加载](OTA.md#ota-safe-load)

* `void enableAutoStartAP()`
   * 如果在启动时**未**找到 WiFi 凭据，则启用 WiFi 接入点的自动启动
   * 改变 HomeSpan 接入点行为的方法，例如 `setApTimeout()`，必须在 `enableAutoStartAP()` 之前调用才能生效
  
* `void setApFunction(void (*func)())`
   * 将 HomeSpan 的内置 WiFi 接入点替换为用户定义的函数 *func*
   * *func* 必须是 *void* 类型并且没有参数
   * 每次启动接入点时都会调用 *func* 而不是 HomeSpan 的内置 WiFi 接入点：
      * 通过 CLI 键入“A”，或
      * 通过使用命令模式选项 3 的控制按钮，或
      * 如果设置了 `enableAutoStartAP()` 并且没有存储 WiFi 凭据，则在启动时自动
   * 在识别出所需网络的 SSID 和密码后，*func* 必须调用 `setWifiCredentials()` 来保存和使用这些值
   * 建议 *func* 通过使用 `ESP.restart()` 重新启动设备来终止。 重启后 HomeSpan 将使用刚刚保存的 SSID 和密码
  
* `void setWifiCredentials(const char *ssid, const char *pwd)`
   * 设置 HomeSpan 将连接的 WiFi 网络的 SSID (*ssid*) 和密码 (*pwd*)
   * *ssid* 和 *pwd* 会自动保存在 HomeSpan 的非易失性存储 (NVS) 中，以便在设备重启时进行检索
   * 请注意，如果保存的值超过允许的最大字符数（ssid=32; pwd=64），则会截断
  
> :警告：安全警告：此功能的目的是允许高级用户使用“setApFunction(func)”指定的自定义接入点功能*动态*设置设备的 WiFi 凭据。 不建议使用此功能将您的 WiFi SSID 和密码直接硬编码到您的草图中。 相反，请使用 HomeSpan 提供的更安全的方法之一，例如从 CLI 键入“W”，或启动 HomeSpan 的接入点，以设置您的 WiFi 凭据，而无需将它们硬编码到您的草图中

* `void setWifiCallback(void (*func)())`
  * 设置一个可选的用户定义回调函数 *func*，在 WiFi 连接建立后由 HomeSpan 在启动时调用。这种对 *func* 的一次性调用是为正在实施其他网络相关服务作为其草图的一部分的用户提供的，但在建立 WiFi 连接之前无法启动。函数 *func* 必须是 *void* 类型并且没有参数

* `void setPairCallback(void (*func)(boolean status))`
  * 设置可选的用户定义回调函数 *func*，在完成与控制器的配对 (*status=true*) 或与控制器取消配对 (*status=false*) 时由 HomeSpan 调用
  * 此一次性调用 *func* 是为希望在设备首次配对时触发其他操作的用户提供的，或者设备稍后取消配对
  * 请注意，此 *func* **not** 在启动时调用，不应用于简单地检查设备是否已配对或未配对。仅在配对状态改变时调用
  * 函数 *func* 必须是 *void* 类型并且有一个 *boolean* 参数

* `void setPairingCode(const char *s)`
  * 将设置配对代码设置为 *s*，其中 **必须** 正好是八位数字（无破折号）
  * 示例：`homeSpan.setPairingCode("46637726");`
  * 配对代码的散列版本将保存到设备的非易失性存储器中，覆盖当前存储的任何配对代码
  * 如果 *s* 包含无效代码，则会报告错误并且代码不会*保存。相反，将使用当前存储的配对代码（或 HomeSpan 默认配对代码，如果没有存储代码）
  * :exclamation: 安全警告：将设备的配对代码硬编码到您的草图中被认为存在安全风险，并且**不**推荐。相反，请使用 HomeSpan 提供的更安全的方法之一，例如从 CLI 键入“S \<code\>”，或启动 HomeSpan 的接入点，以设置您的配对代码，而无需将其硬编码到您的草图中

*`无效删除存储值（）`
  * 从 NVS 中删除所有存储特性的值设置
  * 执行与在 CLI 中键入“V”相同的功能
  * 可以从草图中的任何位置调用

* `void setSketchVersion(const char *sVer)`
  * 将 HomeSpan 草图的版本设置为 *sVer*，可以是任意字符串
  * 如果未指定，HomeSpan 使用“n/a”作为默认版本文本
  * HomeSpan 在启动时在 Arduino IDE 串行监视器中显示草图的版本
  * HomeSpan 还包括草图版本以及用于编译草图的 HomeSpan 库版本，作为其 HAP MDNS 广播的一部分。 HAP *不*使用此数据。相反，它仅用于提供信息，并允许您识别通过 [OTA](OTA.md) 更新的设备的草图版本，而不是连接到计算机
  
*`const char *getSketchVersion()`
   * 返回 HomeSpan 草图的版本，使用 `void setSketchVersion(const char *sVer)` 设置，如果未设置，则返回“n/a”
   * 可以从草图中的任何位置调用

* `void enableWebLog(uint16_t maxEntries, const char *timeServerURL, const char *timeZone, const char *logURL)`
   * 启用滚动网络日志，显示用户使用 `WEBLOG()` 宏创建的最新 *maxEntries* 条目。 参数及其默认值（如果未指定）如下：
      * *maxEntries* - 要保存的（最新）条目的最大数量。 如果未指定，则默认为 0，在这种情况下，Web 日志将仅显示状态而没有任何日志条目
      * *timeServerURL* - 建立 WiFi 连接后 HomeSpan 将用于在启动时设置其时钟的时间服务器的 URL。 如果未指定，则默认为 NULL，在这种情况下 HomeSpan 会跳过设置设备时钟
      * *timeZone* - 指定用于设置时钟的时区。 使用由 Espressif IDF 解释的标准 Unix 时区格式。 请注意，IDF 使用了一种有点不直观的约定，例如“UTC+5:00”时区*从 UTC 时间减去* 5 小时，而“UTC-5:00”*在 UTC 时间后*增加* 5 小时。 如果 *serverURL=NULL* 该字段被忽略； 如果 *serverURL!=NULL* 此字段是必需的
      * *logURL* - 此设备的日志页面的 URL。 如果未指定，则默认为“状态” 
  * 示例：`homeSpan.enableWebLog(50,"pool.ntp.org","UTC-1:00","myLog");` 在 URL *http<nolink>://HomeSpan-\ 创建网络日志 [DEVICE-ID\].local:\[TCP-PORT\]/myLog* 将显示使用 WEBLOG() 宏生成的 50 条最新日志消息。 启动时（建立 WiFi 连接后）HomeSpan 将尝试通过调用服务器“pool.ntp.org”来设置设备时钟，并将时间调整为比 UTC 提前 1 小时。
   * 当尝试连接到 *timeServerURL* 时，HomeSpan 等待 10 秒以等待响应。 如果在 10 秒超时期限后没有收到响应，HomeSpan 会假定服务器不可达并跳过时钟设置过程。 使用 `setTimeServerTimeout()` 将 10 秒超时时间重新配置为另一个值
   * 完整的细节参见 [消息记录](Logging.md)

* `void setTimeServerTimeout(uint32_t tSec)`
  * 更改 HomeSpan 在 `enableWebLog()` 尝试将设备时钟从互联网时间服务器设置为 *tSec* 秒时使用的默认 10 秒超时时间
 
## *SpanAccessory(uint32_t 辅助)*

创建此**类**的实例会将新的 HAP 附件添加到 HomeSpan HAP 数据库。

  * 每个 HomeSpan 草图都需要至少一个附件
  * 每个草图最多可以包含 41 个配件（如果超过，将引发运行时错误并且草图将停止）
  * 没有关联的方法
  * 参数 *aid* 是可选的。
  
    * 如果指定且 *不* 为零，则附件 ID 设置为 *aid*。
    * 如果未指定或等于零，则附件 ID 将设置为比先前实例化附件的 ID 多一个，如果这是第一个附件，则设置为 1。
    * 实例化的第一个附件必须始终具有 ID=1（如果未指定 *aid* 则为默认值）。
    * 将第一个附件的 *aid* 设置为除 1 以外的任何值都会在初始化期间引发错误。
    
  * 在实例化任何附件之前，您必须调用 `homeSpan.begin()`
  * 示例：`new SpanAccessory();`
  
## *跨度服务（）*

这是一个**基类**，所有 HomeSpan 服务都从该类派生，并且**不应该**直接实例化。相反，要创建一个新服务，实例化 [Service](ServiceList.md) 命名空间中定义的 HomeSpan 服务之一。不需要任何论据。

* 实例化服务被添加到 HomeSpan HAP 数据库并与最后实例化的附件相关联
* 在没有先实例化附件的情况下实例化服务会在初始化期间引发错误
* 示例：`new Service::MotionSensor();`

支持以下方法：

* `SpanService *setPrimary()`
  * 指定这是附件的主要服务。返回指向服务本身的指针，以便可以在实例化期间链接方法
  * 示例：`(new Service::Fan)->setPrimary();`
  * 请注意，虽然此功能是由 Apple 在 HAP-R2 中定义的，但它似乎已被弃用，不再用于任何目的或对 Home 应用程序有任何影响
  
* `SpanService *setHidden()`
  * 指定这是附件的隐藏服务。返回指向服务本身的指针，以便可以在实例化期间链接方法。
  * 示例：`(new Service::Fan)->setHidden();`
  * 请注意，虽然此功能是由 Apple 在 HAP-R2 中定义的，但它似乎已被弃用，不再用于任何目的或对 Home 应用程序有任何影响
  
* `SpanService *addLink(SpanService *svc)`
  * 添加 *svc* 作为链接服务。返回指向调用服务本身的指针，以便可以在实例化期间链接方法。
  * 请注意，链接服务仅适用于部分 HAP 服务。有关完整详细信息，请参阅 Apple 的 [HAP-R2](https://developer.apple.com/support/homekit-accessory-protocol/) 文档。
  * 示例：`(new Service::Faucet)->addLink(new Service::Valve)->addLink(new Service::Valve);`（将两个阀门链接到一个水龙头）

* `vector<SpanService *> getLinks()`
  * 返回一个指向使用 `addLink()` 添加的服务的指针向量
  * 对于创建遍历所有链接服务的循环很有用
  * 请注意，返回的向量指向通用 SpanServices，应根据需要重新转换
  * 示例：`for(auto myValve : faucet::getLinks()) { if((MyValve *)myValve)->active->getVal()) ... }` 检查链接到水龙头的所有阀门
  
* `虚拟布尔更新（）`
  * HomeSpan 在收到来自 HomeKit 控制器的请求以更新与服务关联的一个或多个特征时调用此方法。用户应使用以下一种或多种 SpanCharacteristic 方法实现请求更新的代码覆盖此方法。如果更新成功，方法**必须**返回 *true*，否则返回 *false*。
  
*`虚拟无效循环（）`
  * HomeSpan 每次执行 `homeSpan.poll()` 时都会调用此方法。用户应使用以下代码覆盖此方法，该代码监视特性中的状态变化，这些特性需要使用以下一种或多种 SpanCharacteristic 方法通知 HomeKit 控制器。
  
*`虚拟无效按钮（int pin，int pressType）`
  * 每当触发与服务关联的 SpanButton() 对象时，HomeSpan 都会调用此方法。用户应使用以下一种或多种 SpanCharacteristic 方法，使用实现响应 SpanButton() 触发器的任何操作的代码覆盖此方法。
    * *pin* - 与 SpanButton() 对象关联的 ESP32 引脚
    * *pressType* -
      * 0=单按 (SpanButton::SINGLE)
      * 1=双击 (SpanButton::DOUBLE)
      * 2=长按 (SpanButton::LONG)
    
## *SpanCharacteristic(value [,boolean nvsStore])*
  
这是一个**基类**，所有 HomeSpan 特性都是从该类派生的，不应该**直接实例化。相反，要创建一个新的特性，实例化 [Characteristic](ServiceList.md) 命名空间中定义的 HomeSpan 特性之一。

* 实例化特征被添加到 HomeSpan HAP 数据库并与最后实例化的服务相关联
* 在没有先实例化一个服务的情况下实例化一个特性会在初始化过程中抛出一个错误
* 第一个参数可选地允许您在启动时设置特性的初始*值*。如果没有指定 *value*，HomeSpan 将为 Characteristic 提供一个合理的默认值
* 如果 *value* 超出特性的最小/最大范围，则抛出运行时警告，其中 min/max 是 HAP 默认值，或通过调用 `setRange()` 设置的任何新值
* 第二个可选参数，如果设置为 `true`，则指示 HomeSpan 将此特性值的更新保存在设备的非易失性存储 (NVS) 中，以便在设备断电时在启动时恢复。如果未指定，*nvsStore* 将默认为 `false`（无存储）
* 例子：
  * `new Characteristic::Brightness();` 亮度初始化为默认值
  * `new Characteristic::Brightness(50);` 亮度初始化为 50
  * `new Characteristic::Brightness(50,true);` 亮度初始化为50；保存在 NVS 中的更新

#### 基于数值的特征（例如 *int*、*float*...）支持以下方法：

* `type T getVal<T>()`
  * 一个模板方法，它在转换为指定的 *T* 类型（例如 *int*、*double* 等）之后返回基于数字的特性的**当前**值。如果模板参数被排除，值将被转换为 *int*。
  * 指定模板的示例：`double temp = Characteristic::CurrentTemperature->getVal<double>();`
  * 排除模板的示例：`inttilt = Characteristic::CurrentTiltAngle->getVal();`

* `type T getNewVal<T>()`
  * 一个模板方法，它返回 HomeKit 控制器请求更新特性的所需 **new** 值。与 `getVal<>()` 相同的转换规则。仅适用于基于数值的特征
    
* `void setVal(value [,boolean notify])`
  * 将基于数值的 Characteristic 的值设置为 *value*，并且，如果 *notify* 设置为 true，则通知所有 HomeKit 控制器更改。 *notify* 标志是可选的，如果未指定，将设置为 true。将 *notify* 标志设置为 false 允许您在不通知任何 HomeKit 控制器的情况下更新特性，这对于 HomeKit 自动调整的特性（例如倒数计时器）很有用，但如果 Home 应用程序关闭并且是然后重新打开
  * 适用于任何整数、布尔值或基于浮点的数字 *value*，尽管 HomeSpan 会将 *value* 转换为每个 Characteristic 的适当类型（例如，在基于整数的 Characteristic 上调用 `setValue(5.5)` 会产生 *value *=5)
  * 如果 *value* 超出特性的最小/最大范围，则引发运行时警告，其中 min/max 是 HAP 默认值，或者是通过先前调用 `setRange()` 设置的任何新的最小/最大范围
  * *value* **不**限制为步长的增量；例如，在基于浮点的特性上调用 `setRange(0,100,5)` 后调用 `setVal(43.5)` 是完全有效的，即使 43.5 与指定的步长不对齐。家庭应用程序将正确保留该值作为 43.5，但在滑块图形中使用时（例如设置恒温器的温度），它会四舍五入到最接近的步长增量（在本例中为 45）

* `SpanCharacteristic *setRange(min, max, step)`
  * 使用指定的 *min*、*max* 和 *step* 参数覆盖特性的默认 HAP 范围
  * *步骤*是可选的；如果未指定（或设置为非正数），则默认 HAP 步长保持不变
  * 适用于任何整数或基于浮点的参数，尽管 HomeSpan 会将参数重新转换为每个特征的适当类型（例如，在基于整数的特征上调用 `setRange(50.5,70.3,0.5)` 会导致 *min*=50 , *max*=70 和 *step*=0)
  * 如果出现以下情况，将引发错误：
    * 调用不支持范围更改的特性，或
    * 在同一个特征上多次调用
  * 返回指向特性本身的指针，以便在实例化期间可以链接方法
  * 示例：`(new Characteristic::Brightness(50))->setRange(10,100,5);`
  
*`SpanCharacteristic *setValidValues(int n, [int v1, int v2 ...])`
  * 使用*n* 值*v1*、*v2* 等的可变长度列表覆盖具有特定枚举有效值的特征的默认 HAP 有效值。
  * 如果出现以下情况，将引发错误：
    * 调用没有特定枚举有效值的特征，或
    * 在同一个特征上多次调用
  * 返回指向特性本身的指针，以便在实例化期间可以链接方法
  * 示例：`(new Characteristic::SecuritySystemTargetState())->setValidValues(3,0,1,3);` 创建一个长度为 3 的新有效值列表，其中包含值 0、1 和 3。这具有通知 HomeKit SecuritySystemTargetState 值为 2（夜间武装）无效且不应在 Home 应用程序中显示为选项的效果

#### 基于字符串的特征（即以空字符结尾的 C 样式字符数组）支持以下方法：

* `char *getString()`
  * 等效于 `getVal()`，但仅用于字符串特征（即以 null 结尾的字符数组）
  
* `char *getNewString()`
  * 等效于 `getNewVal()`，但专门用于字符串特征（即以 null 结尾的字符数组）

* `void setString(const char *value)`
  * 等价于 `setVal(value)`，但仅用于字符串特征（即以 null 结尾的字符数组）

#### 所有特征都支持以下方法：

*`布尔更新（）`
  * 如果 HomeKit 控制器请求更新 Characteristic 的值，则返回 *true*，否则返回 *false*。可以使用 `getNewVal<>()` 或 `getNewString()` 检索请求的值本身

* `int timeVal()`
  * 返回自上次更新特性值以来经过的时间（以毫秒为单位）（无论是通过 `setVal()`、`setString()` 还是来自 HomeKit 控制器的成功更新请求的结果）

* `SpanCharacteristic *setPerms(uint8_t perms)`
  * 将特性的默认权限更改为 *perms*，其中 *perms* 是附加的权限列表，如 HAP-R2 表 6-4 中所述。有效值为 PR、PW、EV、AA、TW、HD 和 WR
  * 返回指向特性本身的指针，以便在实例化期间可以链接方法
  * 示例：`(new Characteristic::IsConfigured(1))->setPerms(PW+PR+EV);`
   
*`SpanCharacteristic *addPerms(uint8_t perms)`
  * 将新权限 *perms* 添加到特性的默认权限，其中 *perms* 是 HAP-R2 表 6-4 中所述的附加权限列表。有效值为 PR、PW、EV、AA、TW、HD 和 WR
  * 返回指向特性本身的指针，以便在实例化期间可以链接方法
  * 示例：`(new Characteristic::IsConfigured(1))->addPerms(PW);`

* `SpanCharacteristic *removePerms(uint8_t perms)`
  * 从特性的默认权限中删除权限 *perms*，其中 *perms* 是附加的权限列表，如 HAP-R2 表 6-4 中所述。有效值为 PR、PW、EV、AA、TW、HD 和 WR
  * 返回指向特性本身的指针，以便在实例化期间可以链接方法
  * 示例：`(new Characteristic::ConfiguredName("HDMI 1"))->removePerms(PW);`

* `SpanCharacteristic *setDescription(const char *desc)`
  * 为特性添加可选描述 *desc*，如 HAP-R2 表 6-3 中所述
  * 此字段通常用于提供有关自定义特性的信息，但似乎并未被 Home 应用程序以任何方式使用
  * 返回指向特性本身的指针，以便在实例化期间可以链接方法
  * 示例：`(new Characteristic::MyCustomChar())->setDescription("Tuner Frequency");`

* `SpanCharacteristic *setUnit(const char *unit)`
  * 添加或覆盖特性的 *unit*，如 HAP-R2 表 6-6 中所述
  * 返回指向特性本身的指针，以便在实例化期间可以链接方法
  * 示例：`(new Characteristic::RotationSpeed())->setUnit("percentage");`

## *SpanButton(int pin, uint16_t longTime, uint16_t singleTime, uint16_t doubleTime)*

创建此 **class** 的实例会将按钮处理程序附加到指定的 ESP32 *pin*。

* 实例化的按钮与最后实例化的服务相关联
* 不先实例化Service就实例化Button会在初始化时抛出错误

第一个参数是必需的；其余的都是可选的：
* *pin* - ESP32 引脚，常开按钮的一极将连接到该引脚；另一极接地
* *longTime* - 按住按钮以触发长按所需的最短时间（以毫秒为单位）（默认 = 2000 毫秒）
* *singleTime* - 按下按钮触发单次按下所需的最短时间（以毫秒为单位）（默认值 = 5 毫秒）
* *doubleTime* - 两次单次按下之间允许的最大时间（以毫秒为单位）以符合双次按下的条件（默认值 = 200 毫秒）
  
触发规则：
* 如果按钮被按下并持续按住，每 longTime ms 将触发一次长按，直到按钮被释放
* 如果按钮被按下的时间超过 singleTime ms 但小于 longTime ms 然后松开，将触发 Single Press，除非在 doubleTime ms 内再次按下按钮并再次按住至少 singleTime ms，在这种情况下DoublePress 将被触发；在释放按钮之前不会发生进一步的事件
* 如果singleTime>longTime，则只能发生长按触发
* 如果 doubleTime=0，则不能发生双击
  
HomeSpan 会在与该服务关联的任何 Button 中的触发事件时自动调用该服务的 `button(int pin, int pressType)` 方法，其中 *pin* 是按钮连接到的 ESP32 引脚，而 *pressType* 是一个整数，也可以由指定的枚举常量表示：
  * 0=单按 (SpanButton::SINGLE)
  * 1=双击 (SpanButton::DOUBLE)
  * 2=长按 (SpanButton::LONG)
  
如果用户没有重写包含一个或多个按钮的服务的虚拟按钮（）方法，则 HomeSpan 将在初始化期间报告警告，但不会报告错误；这些按钮的触发器将被忽略。

### *SpanUserCommand(char c, const char \*desc, void (\*f)(const char \*buf [,void \*obj]) [,void \*userObject])*

创建此**类**的实例会将用户定义的命令添加到 HomeSpan 命令行界面 (CLI)，其中：

  * *c* 是用户定义命令的单字母名称
  * *desc* 是用户键入“？”时显示的用户定义命令的描述进入 CLI
  * *f* 是指向在调用命令时调用的用户定义函数的指针。 *f* 的允许形式为：
    1. `void f(const char *buf)`，或
    1. `void f(const char *buf, void *obj)`
  * *userObject* 是指向任意对象的指针 HomeSpan 在使用 *f* 的第二种形式时作为第二个参数传递给函数 *f*。注意当使用*f*的第一种形式时包含*userObject*是错误的，当使用*f*的第二种形式时排除*userObject*同样是错误的

要从 CLI 调用您的自定义命令，请在单字母名称 *c* 前加上“@”。这允许 HomeSpan 将用户定义的命令与其内置命令区分开来。例如，

```C++
new SpanUserCommand('s', "save current configuration", saveConfig);
...
void saveConfig(const char *buf){ ... };
```

将向 CLI 添加一个新命令“@s”，其描述为“保存当前配置”，该命令将在调用时调用用户定义的函数 `void saveConfig(const char *buf)`。 参数 *buf* 指向在“@”之后键入到 CLI 中的所有字符的数组。 这允许用户将参数从 CLI 传递给用户定义的函数。 例如，在调用 saveConfig 时，在 CLI 中键入“@s123”会将 *buf* 设置为“s123”。

在参数的第二种形式中，HomeSpan 将向您的函数 *f* 传递一个附加对象。 例如，

```C++
struct myConfigurations[10];
new SpanUserCommand('s', "<n> save current configuration for specified index, n", saveConfig, myConfigurations);
...
void saveConfig(const char *buf, void *obj){ ... do something with myConfigurations ... };
```

当仅使用 '@s' 命令调用时，可能用于保存 *myArray* 中的所有元素，并且可能仅根据添加到命令中的索引保存一个元素，例如 '@s34' 将元素 34 保存在 * 我的数组*。 用户可以在函数 *f* 中创建所有必要的逻辑来解析和处理 *buf* 中传递的完整命令文本，以及对通过 *obj 传递的任何内容采取行动。

要创建多个用户定义的命令，只需创建多个 SpanUserCommand 实例，每个实例都有自己的单字母名称。 请注意，在 SpanUserCommand 的实例中重新使用相同的单字母名称会覆盖使用相同字母的任何先前实例。

## 自定义特征和自定义服务宏

### *CUSTOM_CHAR(name,uuid,perms,format,defaultValue,minValue,maxValue,staticRange)*
### *CUSTOM_CHAR_STRING(name,uuid,perms,defaultValue)*

创建可以添加到任何服务的自定义特征。 Home App 通常会忽略自定义特性，但可能会被其他第三方应用程序使用（例如 *Eve for HomeKit*）。 应使用第一种形式创建数字 Characterstics（例如，UINT8、BOOL...）。 第二种形式用于基于字符串的特征。 参数如下（请注意，任何宏参数中都不应使用引号，除非 *defaultValue* 应用于基于 STRING 的特性）：

* *name* - 自定义特征的名称。这将被添加到 Characteristic 命名空间，以便像任何 HomeSpan Characteristic 一样访问它
* *uuid* - 制造商定义的特性的 UUID。必须*精确* 36 个字符，格式为 XXXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX，其中*X* 表示有效的十六进制数字。如果需要，需要前导零，如 HAP-R2 第 6.6.1 节所述
* *perms* - 附加的权限列表，如 HAP-R2 表 6-4 中所述。有效值为 PR、PW、EV、AA、TW、HD 和 WR
* *format* - 指定特征值的格式，如 HAP-R2 表 6-5 中所述。有效值为 BOOL、UINT8、UINT16、UNIT32、UINT64、INT 和 FLOAT（请注意，HomeSpan 目前不支持 TLV8 或 DATA 格式）。不适用于基于字符串的特征
* *defaultValue* - 如果在实例化期间未定义，则指定 Characteristic 的默认值
* *minValue* - 指定有效值的默认最小范围，可以通过调用 `setRange()` 覆盖。不适用于基于字符串的特征
* *minValue* - 指定有效值的默认最小范围，可以通过调用 `setRange()` 覆盖。不适用于基于字符串的特征
* *staticRange* - 如果 *minValue* 和 *maxValue* 是静态的并且不能被调用 `setRange()` 覆盖，则设置为 *true*。如果允许调用 `setRange()`，则设置为 *false*。不适用于基于字符串的特征

例如，下面的第一行创建了一个名为“Voltage”的自定义特征，其 UUID 代码可由 *Eve for HomeKit* 应用程序识别。参数显示该特性是只读的 (PR) 并且启用了通知 (EV)。允许值的默认范围是 0-240，默认值为 120。该范围*可以*被后续调用 `setRange()` 覆盖。下面的第二行创建了一个自定义的基于字符串的只读只读特性：

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

请注意，必须在调用 `homeSpan.begin()` 之前创建自定义特征
 
> 高级提示：当出现无法识别的自定义特性时，*Eve for HomeKit* 会帮助显示*通用控件*，允许您与在 HomeSpan 中创建的任何自定义特性进行交互。 但是，由于 Eve 无法识别 Characteristic，它只会在 Characteristic 包含 **description** 字段时呈现通用控件，您可以使用上述 `setDescription()` 方法将其添加到任何 Characteristic。 您可能还想使用 `setUnit()` 和 `setRange()` 以便 Eve 应用程序显示具有适合您自定义特征的范围的控件。

### *CUSTOM_SERV(name,uuid)*

创建用于第三方应用程序的自定义服务（例如 *Eve for HomeKit*）。 自定义服务将显示在本机 Apple Home 应用程序中，并带有标记为“不支持”的磁贴，否则 Home 应用程序将安全地忽略该服务。 参数如下（注意在任何一个宏参数中都不能使用引号）：

* *name* - 自定义服务的名称。 这将被添加到服务命名空间，以便与任何 HomeSpan 服务一样访问它。 例如，如果 *name*="Vent"，HomeSpan 会将 `Service::Vent` 识别为新的服务类
* *uuid* - 制造商定义的服务的 UUID。 必须*精确* 36 个字符，格式为 XXXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX，其中*X* 表示有效的十六进制数字。 如果需要，需要前导零，如 HAP-R2 第 6.6.1 节所述

自定义服务可能包含自定义特性和标准 HAP 特性的混合，但由于服务本身是自定义的，因此即使它包含一些标准 HAP 特性，主页应用程序也会忽略整个服务。 请注意，必须在调用 `homeSpan.begin()` 之前创建自定义服务

一个完整的示例展示了如何使用 ***CUSTOM_SERV()*** 和 ***CUSTOM_CHAR()*** 宏来创建 *Eve for HomeKit* 识别的压力传感器附件，可以在 [*File → Examples → HomeSpan → Other Examples → CustomService*](../Other%20Examples/CustomService) 下的 Arduino IDE。
 
## 其他宏

### *SPAN_ACCESSORY()* and *SPAN_ACCESSORY(NAME)*
 
一个“便利”宏，它实现了创建附件时使用的以下非常常见的代码片段。 仅当 *NAME*（C 风格的字符串）已作为参数包含在宏中时才包含最后一行：
 
```C++
new SpanAccessory();
 new Service::AccessoryInformation();
 new Characteristic::Identify();
 new Characteristic::Name(NAME);   // included only in the second form of the macro
```

## 用户可定义的宏
 
### *#define REQUIRED VERSION(major,minor,patch)*

如果在主草图 *prior* 中定义了 REQUIRED 以包含 HomeSpan 库与 `#include "HomeSpan.h"`，则 HomeSpan 将引发编译时错误，除非包含的库版本等于或晚于， 使用 VERSION 宏指定的版本。 例子：

```C++
#define REQUIRED VERSION(1,3,0)   // throws a compile-time error unless HomeSpan library used is version 1.3.0 or later
#include "HomeSpan.h"
```

 ---

#### 不推荐使用的功能（可用于向后兼容旧草图）：

* `SpanRange(int min, int max, int step)`

  * 这个遗留类仅限于基于整数的参数，并且已重新编码以简单地调用更通用的 `setRange(min, max, step)` 方法
  * 最后支持的版本：[v1.2.0](https://github.com/HomeSpan/HomeSpan/blob/release-1.2.0/docs/Reference.md#spanrangeint-min-int-max-int-step)
  * **请使用** `setRange(min, max, step)` **适用于所有新草图**

* `void homeSpan.setMaxConnections(uint8_t nCon)`
  * 此遗留方法用于设置 HomeSpan 在启动时实现的 HAP 控制器连接总数，以确保仍有空闲套接字可用于需要单独网络资源的用户定义代码
  * 最后支持的版本：[v1.4.2](https://github.com/HomeSpan/HomeSpan/blob/release-1.4.2/docs/Reference.md)
  * 此方法已被更灵活的方法 `reserveSocketConnections(uint8_t nSockets)` 取代
    * 允许您根据需要简单地为其他自定义代码保留网络套接字
    * 在调用 `homespan.begin()` 时，HomeSpan 会自动确定剩余多少个套接字可用于 HAP 控制器连接
  * **请使用** `homeSpan.reserveSocketConnections(uint8_t nSockets)` **用于所有新草图**
  
---

[↩️](README.md) 返回欢迎页面
