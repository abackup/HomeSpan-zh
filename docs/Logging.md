原文时间：2024.2.18 ，翻译时间：2024.5.6

# 消息日志记录

HomeSpan 包括各种具有不同详细级别的消息日志，以及用于创建您自己的日志消息和 Web 日志的内置方法。

## HomeSpan 日志消息

HomeSpan 日志消息通常以三种可能的详细级别直接输出到 Arduino 串行监视器：

|Log Level|Output|
|---------|------|
|Level 0|HomeSpan 配置数据和一些基本状态信息|
|Level 1|0 级中的所有内容以及其他更详细的状态消息|
|Level 2|1 级的所有内容以及发送到 HomeSpan 设备和从 HomeSpan 设备发送的所有 HAP 通信包|

您可以使用方法 `homeSpan.setLogLevel(uint8_t level)` 在草图中设置 *Log Level*，如 [HomeSpan API Reference](API.md) 中所述。 始终输出 0 级消息； 仅当 *Log Level* 设置为 1 或更高时才输出级别 1 消息； 和级别 2 消息仅在 *Log Level* 设置为 2 时输出。*Log Level* 也可以随时通过串行监视器动态更改，方法是键入“L0”、“L1”或“ L2' 如 [HomeSpan CLI](CLI.md) 中所述。

您还可以通过在 HomeSpan CLI 中键入“L-1”或在草图中调用 `homeSpan.setLogLevel(-1)` 将日志级别设置为-1，完全抑制 HomeSpan 生成的所有日志消息（以及所有用户定义的日志消息-参见下文）。在 ESP 32 控制单独的串行外设的情况下，禁止将所有日志消息输出到串行监视器可能很有用。在这种情况下，您可能希望在设备上实现一个物理开关，自动将日志级别设置为0或-1，这样您就不必在每次要启用/禁用 HomeSpan 日志消息时重新编译草图。

请注意，“日志级别”设置对草图中使用的任何 `Serial.print()` 或 `Serial.printf()` 语句输出的消息没有影响。要确保您可以通过日志级别设置控制此类消息，请使用下面的` LOG() `宏。另请注意，日志级别设置对 ESP32 操作系统本身生成的任何 ESP32 诊断消息没有影响。这些消息根据 Arduino IDE 的工具菜单下编译时指定的核心编译级别进行控制。

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

### Custom Style Sheets (CSS)
 
HomeSpan's Web Log normally consists of black text on a light blue background.  However, you can set a Custom Style Sheet (CSS) to change the format by calling `homeSpan.setWebLogCSS(const char *css)`, where *css* is constructed using [HTML classes](https://www.w3schools.com/html/html_classes.asp) containing one or more custom style elements.  HomeSpan implements the following three class names for the different parts of the Web Log:
 
 * *bod1* - this class specifies style elements for the main body of the Web Log page, including the background color and the header text at the top (which itself is formatted as \<h2\>)
 * *tab1* - this class specifies style elements for the status table at the top of the Web Log page
 * *tab2* - this class specifies style elements for the log entry table at the botom of the Web Log page
 
For example, the following CSS changes the background color of the Web Log page to light yellow, the color of the header text to blue, the color of the cells in the top table to light green, and the color of the cells in the botom table to light blue.  It also changes the color of the text in the header row (\<th\>) of the second table to red, the color of the data rows (\<td\>) in the second table to dark blue, and the alignment of the text in the data rows to be centered within each table cell:
 
 ```C++
 homeSpan.setWebLogCSS(".bod1 {background-color:lightyellow;}"
                       ".bod1 h2 {color:blue;}"
                       ".tab1 {background-color:lightgreen;}"
                       ".tab2 {background-color:lightblue;} .tab2 th {color:red;} .tab2 td {color:darkblue; text-align:center;}"
                       );
 ```
 
Note that HomeSpan outputs the full content of the Web Log HTML, including whatever CSS you may have specified above, to the Serial Monitor whenever the Log Level is set to 1 or greater.  Reviewing this output can be helpful when creating your own CSS.

### Adding User-Defined Data and/or Custom HTML

Homespan provides a hook into the text used to generate the Web Log that you can extend to add your own data to the initial table as well as more generally add any custom HTML.

To access this text, set a Web Log callback using `homeSpan.setWebLogCallback(void (*func)(String &htmlText))` where

  * *func* is a function of type *void* that takes a single argument of type *String*, and
  * *htmlText* will be set by HomeSpan to a String reference containing all the HTML text that the Web Log has already generated to produce the initial table.

To add your own data to the table, simply extend the String *htmlText* by adding as many `<tr>` and `<td>` HTML tags as needed.  If you wish to end the table and add any other HTML, simple include the `</table>` tag in *htmlText*, and then add any other custom HTML.  For example, the following function could be used to extend the initial Web Log table to show free DRAM, end the table, and provide a hot link to the HomeSpan Repo:

```C++
void extraData(String &r){
  r+="<tr><td>Free DRAM:</td><td>" + String(esp_get_free_internal_heap_size()) + " bytes</td></tr>\n"; 
  r+="</table><p><a href=\"https://github.com/HomeSpan/HomeSpan\">Click Here to Access HomeSpan Repo</a></p>";
}
```

To embed this custom HTML text in the Web Log, call `homeSpan.setWebLogCallback(extraData)` in your sketch.

### Accessing Web Log HTML from within your sketch

In addition to (or as an alternative to) having HomeSpan serve HTML Web Log pages in response to HTTP requests, users can directly access the HTML text for a Web Log page from within their sketch for customized processing and handling.  Since the HTML for a Web Log page can be very large, HomeSpan only generates the HTML for a Web Log page when the page has been requested, and streams the HTML in sequential chunks of 1024 bytes in response to a Web Log HTTP request.  It is therefore not possible for HomeSpan to simply provide the user with a `char *` pointer to the HTML text for a complete Web Log.  Instead, HomeSpan provides the user with the following *homeSpan* method to trigger the production of a Web Log page and access the resulting HTML text whenever needed:

`getWebLog(void (*f)(const char *htmlText, void *data), void *userData)`

 * *f()* - a user-defined function that returns `void` and takes two arguments:
   * *htmlText* - a null-terminated `const char *` pointer to a chunk of HTML text (max 1024 bytes) provided by HomeSpan
   * *data* - a `void *` pointer to any user-provided data, *userData*
 * *userData* - a `void *` pointer to any optional user-provided data that is passed to *f()* as its second argument, *data*

When the above method is called from a sketch, HomeSpan will repeatedly call the user-defined function *f()* and provide sequential chunks of HTML text for the Web Log page as the first argument, *htmlText*.  Once all HTML chunks have been sent to the function *f()*, HomeSpan calls *f()* one final time with *htmlText* set to NULL to indicate there are no more HTML chunks to be sent.

The primary purpose of this function is for the user to provide their own method of serving an HTML Web Log page, such as through a secure HTTPS channel.  Note this channel can be in addition to, or instead of, HomeSpan's normal serving of Web Log pages through HTTP requests depending on whether or not the URL argument used in the `homeSpan.enableWebLog()` method was set to NULL (disabling HomeSpan from serving Web Log pages in response to HTTP requests).

The following psuedo-code snippet shows how `getWebLog()` can be used:

```C++
...
homeSpan.enableWebLog(50,"pool.ntp.org","UTC",NULL);      // this enables the Web Log for 50 entries and sets the clock, but prevents HomeSpan from responding to any HTTP requests for a Web Log page
...
IF WEBLOG NEEDED THEN{
  homeSpan.getWebLog(myWebLogHandler,NULL);               // this triggers HomeSpan to produce the HTML text for a Web Log page and stream the data to myWebLogHandler without any extra user data
}
...
void myWebLogHandler(const char *htmlText, void *args){   // this is the user-defined Web Log handler (note the optional *arg parameter is not used in this example)
  if(htmlText!=NULL){
    DO SOMETHING WITH htmlText (e.g. transmit it to the user via an HTTPS connection)
  }
  else
    PERFORM ANY CLEAN-UP PROCESSING (e.g. close the HTTPS connection)
  }
}
```
 
---

[↩️](../README.md) 返回欢迎页面


