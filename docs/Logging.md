# 消息记录

HomeSpan 包括各种具有不同详细级别的消息日志，以及用于创建您自己的日志消息和 Web 日志的内置方法。

## HomeSpan 日志消息

HomeSpan 日志消息通常以三种可能的详细级别直接输出到 Arduino 串行监视器：

|Log Level|Output|
|---------|------|
|Level 0|HomeSpan 配置数据和一些基本状态信息|
|Level 1|0 级中的所有内容以及其他更详细的状态消息|
|Level 2|1 级的所有内容以及发送到 HomeSpan 设备和从 HomeSpan 设备发送的所有 HAP 通信包|

您可以使用方法 `homeSpan.setLogLevel(uint8_t level)` 在草图中设置 *Log Level*，如 [HomeSpan API Reference](API.md) 中所述。 始终输出 0 级消息； 仅当 *Log Level* 设置为 1 或更高时才输出级别 1 消息； 和级别 2 消息仅在 *Log Level* 设置为 2 时输出。*Log Level* 也可以随时通过串行监视器动态更改，方法是键入“L0”、“L1”或“ L2' 如 [HomeSpan CLI](CLI.md) 中所述。

## 用户定义的日志消息

您可以使用 HomeSpan 的 **LOG0()**、**LOG1()** 和 **LOG2()** 宏将自己的日志消息添加到任何草图。 使用这些宏创建的消息将根据上述 *Log Level* 设置输出到 Arduino 串行监视器。 每个 **LOGn()** 宏（其中 n=\[0,2\]）根据指定的参数数量有两种形式：

* `LOGn(val)` - 当只指定一个参数时，HomeSpan 使用标准的 Arduino `Serial.print(val)` 方法输出 *val*，这意味着 *val* 几乎可以是任何 timvariable 类型。 缺点是您无法控制格式。 例如，`int n=255; LOG1(n);` 向 Arduino 串行监视器输出数字“255”，前提是 *Log Level* 设置为 1 或更大。

* `LOGn(const char *fmt, ...)` - 当指定多个参数时，HomeSpan 使用 ESP32 `Serial.printf(fmt, ...)` 方法输出消息，该方法允许您格式化消息使用标准 C++ *printf* 约定具有可变数量的参数。例如，`int n=255; LOG2("The value is 0x%X",n);` 向 Arduino 串行监视器输出消息“The value is 0xFF”，前提是 *Log Level* 设置为 2。

有关演示这些宏的教程草图，请参阅 [示例 9 - MessageLogging](Tutorials.md#example-9---messagelogging)。
 
## 网络日志

除了将消息记录到 Arduino 串行监视器之外，HomeSpan 还可以选择在您选择的任何页面地址提供 Web 日志页面。由于 Web 日志作为 HomeSpan 的 HAP 服务器的一部分托管，因此其基地址和端口将与您的设备相同。例如，如果您的设备名称是 *http<nolink>://homespan-4e8eb8504e59.local*（假设端口为 80）并且您选择“myLog”作为 Web 日志页面地址，它将托管在 *http<nolink> ://homespan-4e8eb8504e59.local/myLog*。

HomeSpan 的 Web 日志功能还嵌入了调用 NTP 时间服务器来设置设备时钟的能力。此可选功能允许 HomeSpan 创建基于时钟的时间戳（例如 *Sat Apr 16 19:48:41 2022*）。

HomeSpan Web 日志页面本身包含两个部分：
 
  * 页面顶部提供 HomeSpan 生成的状态信息，例如设备名称、自上次重启以来的总正常运行时间以及各种软件组件的版本号
 
  * 页面底部发布您使用 **WEBLOG()** 宏创建的消息。此宏仅以 *printf* 样式的形式 `WEBLOG(const char *fmt, ...)` 出现，类似于上述 LOG() 宏的第二个版本。
 
使用 WEBLOG() 生成的消息*也*以与 LOG1() 消息相同的优先级回显到 Arduino 串行监视器，这意味着如果 *Log Level* 设置为 1 或更高，它们将输出到串行监视器。 Web 日志页面按时间倒序显示消息，并补充了以下附加项目：
* *Entry Number* - HomeSpan 为每条消息编号，从 1 开始表示重启后的第一条消息
* *Up Time* - 相对消息时间，格式为 DDD:HH:MM:SS，从重启后的 000:00:00:00 开始
* *日志时间* - 标准 UNIX 格式的绝对消息时间，前提是 Web 日志已通过 NTP 时间服务器启用（见下文）
* *Client* - 创建 WEBLOG() 消息时连接到 HomeSpan 的客户端的 IP 地址。仅适用于在 Service 的 `update()` 方法中产生的消息。客户端在所有其他实例中设置为“0.0.0.0”
* *Message* - 格式化消息的文本。例如，`int ledNumber=5; WEBLOG("Request to turn LED %d OFF\n",ledNumber);` 会产生消息“Request to turn LED 5 OFF”

要启用 Web 日志记录（默认情况下关闭），请调用方法 `homeSpan.enableWebLog()`，如在草图顶部附近的 [HomeSpan API 参考](Reference.md) 中更全面地描述。此方法允许您设置：

* 要存储的 WEBLOG() 消息的总数 - 一旦达到您设置的限制，旧消息将被丢弃以支持新消息
* NTP 时间服务器的 URL - 这是可选的，仅当您想在启动时设置设备的时钟时才需要
* 设备的时区 - 仅在指定 NTP 时间服务器时才需要
* Web 日志页面的 URL - 如果未指定，HomeSpan 将在名为“status”的页面上提供 Web 日志
 
补充说明：
 
  * 可以在你的草图中包含 WEBLOG() 消息，即使 Web 日志 * 未* 启用。在这种情况下，HomeSpan 不会提供 Web 日志页面，但如果 *Log Level* 设置为 1 或更高，WEBLOG() 消息仍将输出到 Arduino 串行监视器
  * 消息**不**存储在 NVS 中，因此在重新启动之间**不**保存
 
请参阅 [示例 19 - WebLog](Tutorials.md#example-19---weblog) 以获得演示使用 `homeSpan.enableWebLog()` 和 WEBLOG() 宏的教程草图。
 
---

[↩️](README.md) 返回欢迎页面


