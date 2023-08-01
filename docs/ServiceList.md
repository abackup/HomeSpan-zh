时间：2023.8.1 翻译

# HomeSpan 服务和特点

HomeSpan 实现了所有 [HAP-R2](https://developer.apple.com/homekit/specification/) 服务和特性，除了那些涉及视频或音频流、苹果电视盒或高级锁定管理的服务和特性（即所有 HAP 服务，除了那些需要具有 TLV8 数据类型的特性）。

HomeSpan 服务和特性作为 C++ 类实现，其名称与 Apple 在 [HAP-R2](https://developer.apple.com/homekit/specification/) 的第 8 和 9 节中指定的拼写和大小写完全匹配，但是没有任何空格。 HomeSpan 服务在 HomeSpan 的 `Service` 命名空间中定义。 HomeSpan 特征在 HomeSpan 的 `Characteristic` 命名空间中定义。例如，HomeSpan 将 *Carbon Dioxide Sensor* 服务 (HAP Service 8.7) 定义为 `Service::CarbonDioxideSensor`，将 *Carbon Dioxide Detected* Characteristic (HAP Characteristic 9.16) 定义为 `Characteristic::CarbonDioxideDetected`。

HomeSpan 服务和特性使用 C++ `new` 命令实例化。服务不采用任何参数，而特性采用单个可选参数，用于在启动时初始化特性的值。如果未指定此参数，HomeSpan 将根据 Characteristic 的类型和允许的范围应用合理的 [默认值](#特征类型和默认值)。

下表提供了所有 HomeSpan 服务的列表。对于每项服务，该表还指出了哪些特性是必需的，哪些是可选的。例如，可以在 HomeSpan 中配置可调光灯泡，如下所示：

```C++
new Service::LightBulb();                           // 实例化一个灯泡服务e
  new Characteristics:On();                         // 在不设置初始值的情况下实例化所需的On特征值
  new Characteristic::Brightness(50);               // 实例化一个可选的亮度特性并将初始值设置为50%
  new Characteristic::Name("Living Room Lamp");     // 为此服务实例化一个可选的名称特征，并设置为“客厅灯”
```

请参阅 [HAP-R2](https://developer.apple.com/homekit/specification/) 的第 8 节和第 9 节，了解所有 HAP 服务和特征的完整描述。 请注意，HomeSpan 的服务和特征类已经包含所有必需的 HAP 字段，例如 UUID、格式和权限，因此您无需指定任何这些参数。

此外，首次启动时，HomeSpan 首先验证设备的配置，以确保您实例化的每个服务都包含所有必需的特征，但不包括任何既非必需也非可选的特征。 如果发现任何错误，HomeSpan 会将它们报告给 Arduino 串行监视器并停止程序。

### 服务列表

| Service 服务 | Required Characteristics 必需特性 | Optional Characteristics 可选特性 |
| ------- | -------------------- | ------------------- |
| AccessoryInformation 配件信息| Identity 身份| FirmwareRevision 固件版本<br>Manufacturer 制造商<br>Model 型号<br>Name 名称名称<br>SerialNumber 序列号<br>HardwareRevision 硬件版本<br>AccessoryFlags 附件标志 |
| AirPurifier 空气净化器 | Active 活跃<br>CurrentAirPurifierState 当前空气净化器状态<br>TargetAirPurifierState 目标空气净化器状态 | Name 名称<br>RotationSpeed 旋转速度<br>SwingMode 摇摆模式<br>LockPhysicalControls 锁定物理控制 |
| AirQualitySensor 空气质量传感器 | AirQuality 空气质量 | Name 名称<br>OzoneDensity 臭氧密度<br>NitrogenDioxideDensity 二氧化氮密度<br>SulphurDioxideDensity 二氧化硫密度<br>PM25Density PM25 密度<br>PM10Density PM10 密度<br>VOCDensity VOC 密度<br>StatusActive 活跃状态状态<br>StatusFault 状态故障<br>StatusTampered 状态篡改<br>StatusLowBattery 状态低电量 |
| BatteryService 电池服务 | BatteryLevel 电池电量<br>ChargingState 充电状态<br>StatusLowBattery 状态低电量 | Name 名称 |
| CarbonDioxideSensor 二氧化碳传感器 | CarbonDioxideDetected 检测到二氧化碳 | Name 名称<br>StatusActive 活跃状态状态<br>StatusFault 状态故障<br>StatusTampered 状态篡改<br>StatusLowBattery 状态低电量<br>CarbonDioxideLevel 二氧化碳水平<br>CarbonDioxidePeakLevel 二氧化碳峰值水平 |
| CarbonMonoxideSensor一氧化碳传感器 | CarbonMonoxideDetected 检测到一氧化碳 | Name 名称<br>StatusActive 活跃状态状态<br>StatusFault 状态故障<br>StatusTampered 状态篡改<br>StatusLowBattery 状态低电量<br>CarbonMonoxideLevel 一氧化碳水平<br>CarbonMonoxidePeakLevel 一氧化碳峰值水平 |
| ContactSensor 接触传感器 | ContactSensorState 接触传感器状态 | Name 名称<br>StatusActive 活跃状态状态<br>StatusFault 状态故障<br>StatusTampered 状态篡改<br>StatusLowBattery 状态低电量 |
| Door 门 | CurrentPosition 当前位置当前位置<br>TargetPosition 目标位置目标位置<br>PositionState 位置状态 | Name 名称<br>HoldPosition 暂停位置<br>ObstructionDetected 检测到障碍物 |
| Doorbell 门铃 | ProgrammableSwitchEvent 可编程开关事件 | Name 名称<br>Volume 音量<br>Brightness 亮度 |
| Fan 电扇 | Active 活跃 | Name 名称<br>CurrentFanState 当前风扇状态<br>CTargetFanState 目标风扇状态<br>RotationDirection 旋转方向<br>RotationSpeed 旋转速度<br>SwingMode 摇摆模式<br>LockPhysicalControls 锁定物理控制 |
| Faucet 水龙头 | Active 活跃 | StatusFault 状态故障<br>Name 名称 |
| FilterMaintenance 过滤器维护 | FilterChangeIndication 过滤器变化指示 | Name 名称<br>FilterLifeLevel 过滤器生命等级<br>ResetFilterIndication 重置过滤器指示 |
| GarageDoorOpener 车库开门器 | CurrentDoorState 当前门状态<br>TargetDoorState 目标门状态<br>ObstructionDetected 检测到障碍物 | LockCurrentState 锁定当前状态<br>LockTargetState 锁定目标状态<br>Name 名称 |
| HAPProtocolInformation HAP 协议信息 | Version 版本 |  |
| HumidifierDehumidifier 加湿器除湿机 | Active 活跃<br>CurrentRelativeHumidity 当前相对湿度当前相对湿度<br>CurrentHumidifierDehumidifierState 当前加湿器除湿器状态<br>TargetHumidifierDehumidifierState 目标加湿器除湿器状态 | Name 名称<br>RelativeHumidityDehumidifierThreshold 相对湿度除湿阈值<br>RelativeHumidityHumidifierThreshold 相对湿度加湿器阈值<br>RotationSpeed 旋转速度<br>SwingMode 摇摆模式<br>WaterLevel 水位<br>LockPhysicalControls 锁定物理控制 |
| HumiditySensor 湿度传感器 | CurrentRelativeHumidity 当前相对湿度 | Name 名称<br>StatusActive 活跃状态<br>StatusFault 状态故障<br>StatusTampered 状态篡改<br>StatusLowBattery 状态低电量 |
| InputSource 输入源 | Identifier 标识符 | ConfiguredName 配置名称<br>IsConfigured 已配置<br>CurrentVisibilityState 当前可见性状态<br>TargetVisibilityState 目标可见性状态 |
| IrrigationSystem 灌溉系统 | Active 活跃<br>ProgramMode 程序模式<br>InUse 正在使用 | RemainingDuration 剩余时间<br>StatusFault 状态故障 |
| LeakSensor 泄漏传感器 | LeakDetected 泄漏检测 | Name 名称<br>StatusActive 活跃状态<br>StatusFault 状态故障<br>StatusTampered 状态篡改<br>StatusLowBattery 状态低电量 |
| LightBulb 灯泡 | On 开启| Brightness 亮度<br>Hue 色调<br>Name 名称<br>Saturation 饱和度<br>ColorTemperature 色温 |
| LightSensor 光传感器 | CurrentAmbientLightLevel 当前环境光级别 | Name 名称<br>StatusActive 活跃状态<br>StatusFault 状态故障<br>StatusTampered 状态篡改<br>StatusLowBattery 状态低电量 |
| LockMechanism 锁定机制 | LockCurrentState 锁定当前状态<br>LockTargetState 锁定目标状态 | Name 名称 |
| Microphone 麦克风 | Mute 静音 | Name 名称<br>Volume 音量 |
| MotionSensor 运动传感器 | MotionDetected 运动检测 | Name 名称<br>StatusActive 活跃状态<br>StatusFault 状态故障<br>StatusTampered 状态篡改<br>StatusLowBattery 状态低电量 |
| OccupancySensor 占用传感器 | OccupancyDetected 检测到占用 | Name 名称<br>StatusActive 活跃状态<br>StatusFault 状态故障<br>StatusTampered 状态篡改<br>StatusLowBattery 状态低电量 |
| Outlet 插座| On 开关<br>OutletInUse 正在使用 | Name 名称 |
| SecuritySystem 安保系统 | SecuritySystemCurrentState 安保系统当前状态<br>SecuritySystemTargetState 安全系统目标状态 | Name 名称<br>SecuritySystemAlarmType 安全系统警报类型<br>StatusFault 状态故障<br>StatusTampered 状态篡改 |
| ServiceLabel 服务标签 | ServiceLabelNamespace 服务标签命名空间 |  |
| SmokeSensor 烟雾传感器 | SmokeDetected 烟雾检测 | Name 名称<br>StatusActive 活跃状态<br>StatusFault 状态故障<br>StatusTampered 状态篡改<br>StatusLowBattery 状态低电量 |
| Speaker 扬声器 | Mute 静音 | Name 名称<br>Volume 音量 |
| StatelessProgrammableSwitch 无状态可编程开关 | ProgrammableSwitchEvent 可编程开关事件 | Name 名称<br>ServiceLabelIndex 服务标签索引 |
| Switch 开关 | On 开启| Name 名称 |
| Television 电视 | Active 活跃 | ConfiguredName 名称<br>ActiveIdentifier 标识符<br>RemoteKey 遥控钥匙<br>PowerModeSelection 电源模式选择 | 
|TelevisionSpeaker 电视音箱|VolumeControlType 音量控制类型<br>VolumeSelector 音量选择器|
| Thermostat 恒温器 | CurrentHeatingCoolingState 当前加热冷却状态<br>TargetHeatingCoolingState 目标加热冷却状态<br>CurrentTemperature 当前温度<br>TargetTemperature 目标温度<br>TemperatureDisplayUnits 温度显示单位 | CoolingThresholdTemperature 冷却阈值温度<br>CurrentRelativeHumidity 当前相对湿度<br>HeatingThresholdTemperature 加热阈值温度<br>Name 名称<br>TargetRelativeHumidity 目标相对湿度 | 
| Valve 阀门 | Active 活跃<br>InUse 正在使用<br>ValveType 阀门类型 | SetDuration 设置持续时间<br>RemainingDuration 剩余时间<br>IsConfigured 已配置<br>ServiceLabelIndex 服务标签索引<br>StatusFault 状态故障<br>Name 名称 |
| Window 窗 | CurrentPosition 当前位置<br>TargetPosition 目标位置<br>PositionState 位置状态 | Name 名称<br>HoldPosition 暂停位置<br>ObstructionDetected 检测到障碍物 |
| WindowCovering 窗帘 | TargetPosition 目标位置<br>CurrentPosition 当前位置<br>PositionState 位置状态<br> | Name 名称<br>HoldPosition 暂停位置<br>CurrentHorizontalTiltAngle 当前水平倾斜角度<br>TargetHorizontalTiltAngle 目标水平倾斜角度<br>CurrentVerticalTiltAngle 当前垂直倾斜角度<br>TargetVerticalTiltAngle 目标垂直倾斜角度<br>ObstructionDetected 检测到障碍物 |

### 特征类型和默认值

|Characteristic 特征|Type 类型|Default 默认值|Range 范围|
|-|-|-|-|
AccessoryFlags 附件标志|uint32_t|1|[1,1]|
Active 活动|uint8_t|0|[0,1]|
ActiveIdentifier 活动标识符|uint32_t|0|[0,255]|
AirQuality 空气质量|uint8_t|0|[0,5]|
BatteryLevel 电池电量|uint8_t|0|[0,100]|
Brightness 亮度|int|0|[0,100]|
CarbonMonoxideLevel 一氧化碳水平|double|0|[0,100]|
CarbonMonoxidePeakLevel 一氧化碳峰值水平|double|0|[0,100]|
CarbonMonoxideDetected 检测到一氧化碳|uint8_t|0|[0,1]|
CarbonDioxideLevel 二氧化碳水平|double|0|[0,100000]|
CarbonDioxidePeakLevel 二氧化碳峰值水平|double|0|[0,100000]|
CarbonDioxideDetected 测到二氧化碳|uint8_t|0|[0,1]|
ChargingState 电状态|uint8_t|0|[0,2]|
ClosedCaptions 隐藏式字幕|uint8_t|0|[0,1]|
CoolingThresholdTemperature 冷却阈值温度|double|10|[10,35]|
ColorTemperature 色温|uint32_t|200|[140,500]|
ContactSensorState 接触传感器状态|uint8_t|1|[0,1]|
ConfiguredName 配置名称|char \*|"unnamed"|||
CurrentAmbientLightLevel 当前环境光级别|double|1|[0.0001,100000]|
CurrentHorizontalTiltAngle 当前水平倾斜角度|int|0|[-90,90]|
CurrentAirPurifierState 当前空气净化器状态|uint8_t|1|[0,2]|
CurrentSlatState 当前板条状态|uint8_t|0|[0,2]|
CurrentPosition 当前位置|uint8_t|0|[0,100]|
CurrentVerticalTiltAngle 当前垂直倾斜角度|int|0|[-90,90]|
CurrentVisibilityState 当前可见性状态|uint8_t|0|[0,1]|
CurrentHumidifierDehumidifierState 当前加湿器除湿器状态|uint8_t|1|[0,3]|
CurrentDoorState 当前门状态|uint8_t|1|[0,4]|
CurrentFanState 当前风扇状态|uint8_t|1|[0,2]|
CurrentHeatingCoolingState 当前加热冷却状态|uint8_t|0|[0,2]|
CurrentHeaterCoolerState 当前加热器冷却器状态|uint8_t|1|[0,3]|
CurrentMediaState 当前媒体状态|uint8_t|0|[0,5]|
CurrentRelativeHumidity 当前相对湿度|double|0|[0,100]|
CurrentTemperature 当前温度|double|0|[0,100]|
CurrentTiltAngle 当前倾斜角度|int|0|[-90,90]|
FilterLifeLevel 过滤器生命等级|double|0|[0,100]|
FilterChangeIndication 过滤器变化指示|uint8_t|0|[0,1]|
FirmwareRevision 固件版本|char \*|"1.0.0"|||
HardwareRevision 硬件版本|char \*|"1.0.0"|||
HeatingThresholdTemperature 加热阈值温度|double|16|[0,25]|
HoldPosition 暂停位置|boolean|false|[0,1]|
Hue 色调|double|0|[0,360]|
Identify 确认|boolean|false|[0,1]|
Identifier 标识符|uint32_t|0|[0,255]|
InputDeviceType 输入设备类型|uint8_t|0|[0,6]|
InputSourceType 输入源类型|uint8_t|0|[0,10]|
InUse 正在使用|uint8_t|0|[0,1]|
IsConfigured 已配置|uint8_t|0|[0,1]|
LeakDetected 泄漏检测|uint8_t|0|[0,1]|
LockCurrentState 锁定当前状态|uint8_t|0|[0,3]|
LockPhysicalControls 锁定物理控制|uint8_t|0|[0,1]|
LockTargetState 锁定目标状态|uint8_t|0|[0,1]|
Manufacturer 制造商|char \*|"HomeSpan"|||
Model 型号|char \*|"HomeSpan-ESP32"|||
MotionDetected 运动检测|boolean|false|[0,1]|
Mute 静音|boolean|false|[0,1]|
Name 名称|char \*|"unnamed"|||
NitrogenDioxideDensity二氧化氮密度|double|0|[0,1000]|
ObstructionDetected 检测到障碍物|boolean|false|[0,1]|
PM25Density PM25 浓度|double|0|[0,1000]|
OccupancyDetected 检测到占用|uint8_t|0|[0,1]|
OutletInUse 插座正在使用|boolean|false|[0,1]|
On 开关|boolean|false|[0,1]|
OzoneDensity 臭氧密度|double|0|[0,1000]|
PictureMode 照片模式|uint8_t|0|[0,13]|
PM10Density PM10 浓度|double|0|[0,1000]|
PositionState 位置状态|uint8_t|2|[0,2]|
PowerModeSelection 电源模式选择|uint8_t|0|[0,1]|
ProgramMode 程序模式|uint8_t|0|[0,2]|
ProgrammableSwitchEvent 可编程开关事件|uint8_t|0|[0,2]|
RelativeHumidityDehumidifierThreshold 相对湿度除湿阈值|double|50|[0,100]|
RelativeHumidityHumidifierThreshold 对湿度加湿器阈值|double|50|[0,100]|
RemainingDuration 剩余时间|uint32_t|60|[0,3600]|
RemoteKey 遥控钥匙|uint8_t|0|[0,16]|
ResetFilterIndication 重置过滤器指示|uint8_t|0|[1,1]|
RotationDirection 旋转方向|int|0|[0,1]|
RotationSpeed 旋转速度|double|0|[0,100]|
Saturation 饱和度|double|0|[0,100]|
SecuritySystemAlarmType 安全系统警报类型|uint8_t|0|[0,1]|
SecuritySystemCurrentState 安全系统当前状态|uint8_t|3|[0,4]|
SecuritySystemTargetState 安全系统目标状态|uint8_t|3|[0,3]|
SerialNumber 序列号|char \*|"HS-12345"|||
ServiceLabelIndex 服务标签索引|uint8_t|1|[1,255]|
ServiceLabelNamespace 服务标签命名空间|uint8_t|1|[0,1]|
SlatType 烟雾检测|uint8_t|0|[0,1]|
SleepDiscoveryMode 睡眠发现模式|uint8_t|0|[0,1]|
SmokeDetected 检测到烟雾|uint8_t|0|[0,1]|
StatusActive 状态活动|boolean|true|[0,1]|
StatusFault 状态故障|uint8_t|0|[0,1]|
StatusJammed 状态卡住|uint8_t|0|[0,1]|
StatusLowBattery 状态低电量|uint8_t|0|[0,1]|
StatusTampered 状态篡改|uint8_t|0|[0,1]|
SulphurDioxideDensity 二氧化硫密度|double|0|[0,1000]|
SwingMode 摇摆模式|uint8_t|0|[0,1]|
SetDuration 设置持续时间|uint32_t|60|[0,3600]|
TargetAirPurifierState 目标空气净化器状态|uint8_t|1|[0,1]|
TargetFanState 目标风扇状态|uint8_t|1|[0,1]|
TargetTiltAngle 目标风扇状态|int|0|[-90,90]|
TargetHeaterCoolerState 目标加热器冷却器状态|uint8_t|0|[0,2]|
TargetHorizontalTiltAngle 目标水平倾斜角度|int|0|[-90,90]|
TargetHumidifierDehumidifierState 目标加湿器除湿器状态|uint8_t|0|[0,2]|
TargetPosition 目标位置|uint8_t|0|[0,100]|
TargetDoorState 目标门状态|uint8_t|1|[0,1]|
TargetHeatingCoolingState 目标加热器冷却器状态|uint8_t|0|[0,3]|
TargetMediaState 目标加热冷却状态|uint8_t|0|[0,2]|
TargetRelativeHumidity 目标相对湿度|double|0|[0,100]|
TargetTemperature 目标温度|double|16|[10,38]|
TargetVisibilityState 目标可见性状态|uint8_t|0|[0,1]|
TemperatureDisplayUnits 温度显示单位|uint8_t|0|[0,1]|
TargetVerticalTiltAngle 目标垂直倾斜角度|int|0|[-90,90]|
ValveType 阀门类型|uint8_t|0|[0,3]|
Version 版本|char \*|"1.0.0"|||
VOCDensity VOC 浓度|double|0|[0,1000]|
Volume 音量|uint8_t|0|[0,100]|
VolumeControlType 音量控制类型|uint8_t|0|[0,3]|
VolumeSelector 音量选择器|uint8_t|0|[0,1]|
WaterLevel 水位|double|0|[0,100]|

### HAP 格式代码（HAP-R2 表 6-5）

|HAP-R2 Format Code|HomeSpan C++ Type|
|------------------|-----------------|
|BOOL|boolean|
|UINT8|uint8_t|
|UINT16|uint16_t|
|UINT32|uint32_t|
|UINT64|uint64_t|
|INT|int|
|FLOAT|double|
|STRING|char \*|
|TLV8|(未实现)|
|DATA|uint8_t *|

---

[↩️](../README.md) 返回欢迎页面
