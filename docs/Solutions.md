<!--  原文时间：2024.3.9，翻译时间：2024.5.7，校对时间：2024.5.31  -->

# 常见问题和可能的解决方案

### *My HomeSpan device does not appear in the Home App when I try to pair it*

* There are a few reasons this may occur:

  * **You have not yet entered your WiFi credentials**.  HomeSpan can't connect to your WiFi network until you provide it with your WiFi&nbsp;SSID and password. If HomeSpan can't find these Credentials it outputs a warning message to the Serial Monitor during start-up.  You can enter your WiFi Credentials into HomeSpan either directly from the Serial Monitor by using the 'W' CLI command, or via the HomeSpan Access Point Setup Page, or by hardcoding it into your sketch with the `homeSpan.setWifiCredentials()` function, though this last method is not recommended for security reasons.

  * **You are out of range of your WiFi network, or entered the wrong WiFi Credentials**.  When HomeSpan first boots, if you've previously entered your WiFi Credentials (see above) it will use them to connect to your WiFi network.  Check the Serial Monitor for status on whether a connection has been successfully made.  If not, make sure your device is in the range of your WiFi network, and re-enter your WiFi Credentials in case you entered them incorrectly the first time.  To double-check that your HomeSpan device is indeed connected to your network after HomeSpan reports a successful connection, open up a terminal window on your computer and use the `ping` command to confirm you can reach the device. 
 
  * **Your iPhone and ESP32 device are not connected to the same WiFi network**.  Make sure your HomeSpan device is connected to the same SSID as your iPhone and any HomeKit Hubs (e.g. HomePods or Apple TV).  Some routers provide a separate SSID to use for IoT ("Internet of Things") devices. If you decide to use a separate SSID, make sure to configure your router so that message traffic flows unimpeded between your main SSID and your dedicated IoT SSID with absolutely no filtering of any messages. Also note that like most commercial HomeKit devices, ESP32 devices operate only on the 2.4 GHz WiFi band.  Most iPhones can operate on either the 2.4 GHz or the 5.0 GHz WiFi bands, so if your router provides multi-band access, you need to make sure it is configured to allow unimpeded cross-traffic between the bands.
    
  * **Your device thinks it is already paired (this is the most common reason)**.  Check the Serial Monitor when HomeSpan first boots - it will let you know if the device is currently *paired* or *unpaired*.  If its already *paired* you must unpair it before it can be paired again with the Home App.  Normally you would unpair the device from the Home App itself, but if for whatever reason you can't (perhaps the device is no longer showing up in the Home App) you can force HomeSpan to forget all its pairing data and reset its state to *unpaired* by typing either the 'U' or 'H' CLI command into the Serial Monitor.  The 'U' command instructs HomeSpan to simply erase all its *Controller* pairing data and reset its state to *unpaired*.  The 'H' command instructs HomeSpan to  erase all its *Controller* pairing data **and** its *HomeKit Device ID*, after which it reboots into the *unpaired* state and generates a new *HomeKit Device ID*.  Typing 'H' is recommended to get the cleanest refresh.  Note that your WiFi Credentials and Pairing Setup Code are not changed by either of these commands.

#### *当我的 ESP32 插入电脑或通过 USB 端口单独供电时，HomeSpan 可以正常工作，但在没有任何 USB 连接的情况下，直接通过 ESP32 5V 引脚供电时，它无法正常工作*

* 在某些 ESP32 板上，USB-UART 芯片仅在通过 USB 端口供电时才接收电源，因此，如果 ESP32 仅通过 ESP32 5V 引脚供电，则保持不供电。因此，与 ESP32 上的 UART0 相关的串口 RX 引脚（通常由 USB-UART 芯片驱动）在任何电压下都可以自由浮动。如果此引脚浮空为低电平，则 ESP32 认为有数据要从串口监视器读取，而 HomeSpan 则陷入无限循环，试图读取此不存在的数据。

* **解决方法:** 添加一个上拉电阻（10 kΩ 即可），将电路板上的 UART0 RX 引脚连接到 +3.3V 对于大多数板，默认的 UART0 RX 引脚如下：

  * ESP32 的针脚 3
  * ESP32-S2 和 ESP32-S3 的针脚 44
  * ESP32-C3 的针脚 20

* 请注意，添加此上拉电阻会**不**干扰电路板的正常串口操作，例如使用串口监视器或上传草图。

* *作为替代方案*，而不是添加上拉电阻，你可以简单地排除（或注释掉）草图中的 `Serial.begin()` 线。当你通过 5V 引脚为其供电时，这可以防止 HomeSpan 挂起的问题，但不幸的是，这意味着当你将主板连接到电脑时，串口显示器将无法正常工作，并且每当你想要使用串口显示器时，你都需要重新添加 `Serial.begin()`。

### *HomeSpan crashes when I enable PSRAM, but works fine if I disable PSRAM*

* If your ESP32 comes with Quad or Octal PSRAM, the chip will likely need to use one or more additional I/O pins so that it can access the PSRAM using an extended SPI bus, as required for these types of PSRAM.  If you happen to use one of those pins for something else (e.g an input button, an LED, etc.) the ESP32 will likely crash whenever PSRAM is enabled.
  
* **解决方法:**  Check the documentation for your board to see what pins are reserved for use when PSRAM is enabled, and *don't use those pins for anything else.*

### *The Serial Monitor is reporting* "gpio: gpio_set_level(226): GPIO output gpio_num error"

* This is an ESP32-generated error message and it occurs if you try to set the output of a pin that either does not exist on your chip, or does exist but it is input-only (i.e. it cannot be used as a output).  This typically occurs when you try to compile code for one chip (such as an ESP32-S2) on another chip (such as an ESP32-C3).  The code will compile fine, but may produce the above error during run-time.
  
* **解决方法:**  Check the documentation for your board and *use only pins that exist for your chip, and are not reserved for internal functions, and are not input-only.*

### *My sketch is too large to be uploaded (error when trying to upload)*

* Though all ESP32 chips have a minimum of 4MB of flash memory, the amount that can be used to store a program depends on the *partition scheme* selected.  By default, the ESP32 uses a parition scheme that reserves 1408 KB for a SPIFFS partition (SPI Flash File Storage) and splits the majority of the remaining flash into two equal OTA partitions of 1280 KB each for program storage.  Most HomeSpan sketches come close to filling up an entire OTA partition, and if you add a lot of other libraries you will likely exceed 1280&nbsp;KB.

* **解决方法:**  Select a different partition table that does not reserve so much flash memory for a SPIFFS partition since SPIFFS is not used at all by HomeSpan and *this partition is just wasting space.*

* From within the Arduino IDE, the easiest way to reduce the SPIFFS partition is to select the *Minimal SPIFFS* partition scheme from under the Tools menu, and then simply recompile and upload your sketch.  This scheme reserves only 128 KB for the SPIFFS partition, which leaves a full 1920 KB of program storage for each OTA partition.  This represents a 50% increase in program size, which should suffice for most applications.
  
* If for some reason you still need more space, and you only have 4MB of flash, you can try selecting the *Huge App* partition scheme, which reserves 896 KB for SPIFFS and leaves a *single* partition of 3072 KB for program storage. OTA will unfortunately *not* be available in this scheme. 

* Note: if you are not using the Arduino IDE to compile and upload HomeSpan sketches, please consult the documentation for your IDE to learn how to change the partition scheme. 

* Note: if none of the built-in partition schemes contain the right balance of partition sizes for your sketch, you can always create a custom partition scheme as demonstrated in HomeSpan's  [CustomNVSParititon Example](../examples/Other%20Examples/CustomNVSPartition).  This technique should work even if not using the Arduino IDE.
 
---

[↩️](../README.md#resources)返回欢迎页面


