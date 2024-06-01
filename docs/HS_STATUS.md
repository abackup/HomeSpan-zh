原文时间：2022.11.6 ，翻译时间：2024.5.6

# HomeSpan 状态

可选的 ***homeSpan*** 方法`void setStatusCallback(void (*func)(HS_STATUS status))` 可用于创建一个回调函数 func，每当 HomeSpan 的状态发生变化时，它就会调用该函数。HomeSpan 向 func 传递一个参数 status ，类型为 HS_STATUS，定义如下：

```C++
enum HS_STATUS {
  HS_WIFI_NEEDED,                         // WiFi Credentials have not yet been set/stored
  HS_WIFI_CONNECTING,                     // HomeSpan is trying to connect to the network specified in the stored WiFi Credentials
  HS_PAIRING_NEEDED,                      // HomeSpan is connected to central WiFi network, but device has not yet been paired to HomeKit
  HS_PAIRED,                              // HomeSpan is connected to central WiFi network and ther device has been paired to HomeKit
  HS_ENTERING_CONFIG_MODE,                // User has requested the device to enter into Command Mode
  HS_CONFIG_MODE_EXIT,                    // HomeSpan is in Command Mode with "Exit Command Mode" specified as choice
  HS_CONFIG_MODE_REBOOT,                  // HomeSpan is in Command Mode with "Reboot" specified as choice
  HS_CONFIG_MODE_LAUNCH_AP,               // HomeSpan is in Command Mode with "Launch Access Point" specified as choice
  HS_CONFIG_MODE_UNPAIR,                  // HomeSpan is in Command Mode with "Unpair Device" specified as choice
  HS_CONFIG_MODE_ERASE_WIFI,              // HomeSpan is in Command Mode with "Erase WiFi Credentials" specified as choice
  HS_CONFIG_MODE_EXIT_SELECTED,           // User has selected "Exit Command Mode" 
  HS_CONFIG_MODE_REBOOT_SELECTED,         // User has select "Reboot" from the Command Mode
  HS_CONFIG_MODE_LAUNCH_AP_SELECTED,      // User has selected "Launch AP Access" from the Command Mode
  HS_CONFIG_MODE_UNPAIR_SELECTED,         // User has seleected "Unpair Device" from the Command Mode
  HS_CONFIG_MODE_ERASE_WIFI_SELECTED,     // User has selected "Erase WiFi Credentials" from the Command Mode
  HS_REBOOTING,                           // HomeSpan is in the process of rebooting the device
  HS_FACTORY_RESET,                       // HomeSpan is in the process of performing a Factory Reset of device
  HS_AP_STARTED,                          // HomeSpan has started the Access Point but no one has yet connected
  HS_AP_CONNECTED,                        // The Access Point is started and a user device has been connected
  HS_AP_TERMINATED,                       // HomeSpan has terminated the Access Point 
  HS_OTA_STARTED                          // HomeSpan is in the process of recveived an Over-the-Air software update   
};
```

 ***homeSpan*** 方法 `char* statusString(HS_STATUS s)` 是一个方便的函数，用于将上面的任何枚举转换为简短的预定义字符串消息，如下所示：

```C++
const char* Span::statusString(HS_STATUS s){
  switch(s){
    case HS_WIFI_NEEDED: return("WiFi Credentials Needed");
    case HS_WIFI_CONNECTING: return("WiFi Connecting");
    case HS_PAIRING_NEEDED: return("Device not yet Paired");
    case HS_PAIRED: return("Device Paired");
    case HS_ENTERING_CONFIG_MODE: return("Entering Command Mode");
    case HS_CONFIG_MODE_EXIT: return("1. Exit Command Mode"); 
    case HS_CONFIG_MODE_REBOOT: return("2. Reboot Device");
    case HS_CONFIG_MODE_LAUNCH_AP: return("3. Launch Access Point");
    case HS_CONFIG_MODE_UNPAIR: return("4. Unpair Device");
    case HS_CONFIG_MODE_ERASE_WIFI: return("5. Erase WiFi Credentials");
    case HS_CONFIG_MODE_EXIT_SELECTED: return("Exiting Command Mode...");
    case HS_CONFIG_MODE_REBOOT_SELECTED: return("Rebooting Device...");
    case HS_CONFIG_MODE_LAUNCH_AP_SELECTED: return("Launching Access Point...");
    case HS_CONFIG_MODE_UNPAIR_SELECTED: return("Unpairing Device...");
    case HS_CONFIG_MODE_ERASE_WIFI_SELECTED: return("Erasing WiFi Credentials...");
    case HS_REBOOTING: return("REBOOTING!");
    case HS_FACTORY_RESET: return("Performing Factory Reset...");
    case HS_AP_STARTED: return("Access Point Started");
    case HS_AP_CONNECTED: return("Access Point Connected");
    case HS_AP_TERMINATED: return("Access Point Terminated");
    case HS_OTA_STARTED: return("OTA Update Started");
    default: return("Unknown");
  }
}
```

### 例如:

```C++
#include "HomeSpan.h"

void setup(){
  homeSpan.setStatusCallback(statusUpdate);   // set callback function
  ...
  homeSpan.begin();
  ...
}

// create a callback function that simply prints the pre-defined short messages on the Serial Monitor whenever the HomeSpan status changes

void statusUpdate(HS_STATUS status){
  Serial.printf("\n*** HOMESPAN STATUS CHANGE: %s\n",homeSpan.statusString(status));
}
```

当然，你可以在 *func* 中创建任何替代消息，或者采取任何需要的操作，而不需要使用上面预定义的字符串。

---

[↩️](Reference.md) 返回 API 页面
