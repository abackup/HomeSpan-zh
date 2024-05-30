<!-- 原文时间：2023.3.19，翻译时间：2024.5.6，校对时间：2024.5.29 -->

# HomeSpan 配件类别

每个 HomeSpan 设备都必须分配一个 HomeKit 配件类别。HomeSpan 将这些类别实现为 C++ 类，其名称与苹果公司在 [HAP-R2](https://developer.apple.com/homekit/specification/) 的第 13 节中指定的拼写和大小写完全匹配，但没有任何空格。HomeSpan 附件类别在 HomeSpan 的 `Category` 命名空间中定义。例如，HomeSpan 将**车库门开启器**类别（HAP 类别 4）定义为 `Category::GarageDoorOpeners`，可以在初始化 HomeSpan 时使用，如下所示：

```C++
homeSpan.begin(Category::GarageDoorOpeners,"Acme Garage Door Lifts");
```

下表提供了所有 HomeSpan 类别的列表。

### 配件类别
|类别|中文|
| :---------------------------: | :------------------------------: |
| AirConditioners | 空调 |
| AirPurifiers | 空气净化器 |
| Bridges |桥接|
| Dehumidifiers |除湿机|
| Doors |门|
| Fans |风扇|
| Faucets |水龙头|
| Lighting |灯|
| Locks| 锁|
| GarageDoorOpeners |车库门开启器|
| Heaters |加热器|
| Humidifiers |加湿器|
| IPCameras |网络摄像机|
| Other |其他|
| Outlets |插座|
| ProgrammableSwitches |可编程开关|
| SecuritySystems |安全系统|
| Sensors |传感器|
| ShowerSystems| 淋浴系统|
| Sprinklers |洒水器|
| Switches |开关|
| Thermostats |恒温器|
| VideoDoorbells| 可视门铃|
| Windows |窗户|
| WindowCoverings |窗帘|
| Television |电视|

请注意，HomeKit 主要使用设备的附件类别来确定在设备配对时在“家庭”应用中显示的图标。除了这个纯粹的装饰功能外，分配给设备的类别不会以任何方式限制可以在该设备上实现的服务或特性。

---

[↩️](../README.md) 返回欢迎页面
