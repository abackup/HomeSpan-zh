# HomeSpan 服务和特点

HomeSpan 实现了所有 [HAP-R2](https://developer.apple.com/homekit/specification/) 服务和特性，除了那些涉及视频或音频流、Apple TV 或高级锁定管理的服务和特性（即所有 HAP 服务，除了那些需要具有 TLV8 数据类型的特性）。

HomeSpan 服务和特性作为 C++ 类实现，其名称与 Apple 在 [HAP-R2](https://developer.apple.com/homekit/specification/)的第 8 和 9 节中指定的拼写和大小写完全匹配，但是没有任何空格。 HomeSpan 服务在 HomeSpan 的 `Service` 命名空间中定义。 HomeSpan 特征在 HomeSpan 的 `Characteristic` 命名空间中定义。例如，HomeSpan 将 *Carbon Dioxide Sensor* 服务 (HAP Service 8.7) 定义为 `Service::CarbonDioxideSensor`，将 *Carbon Dioxide Detected* Characteristic (HAP Characteristic 9.16) 定义为 `Characteristic::CarbonDioxideDetected`。

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

| Service服务 | Required Characteristics必需特性 | Optional Characteristics可选特性 |
| ------- | -------------------- | ------------------- |
| AccessoryInformation配件信息| FirmwareRevision固件版本<br>Identity身份<br>Manufacturer制造商<br>Model型号<br>Name名称名称<br>SerialNumber序列号 | HardwareRevision硬件版本 |
| AirPurifier空气净化器 | Active活跃<br>CurrentAirPurifierState当前空气净化器状态<br>TargetAirPurifierState目标空气净化器状态 | Name名称<br>RotationSpeed旋转速度<br>SwingMode摇摆模式<br>LockPhysicalControls锁定物理控制 |
| AirQualitySensor空气质量传感器 | AirQuality空气质量 | Name名称<br>OzoneDensity臭氧密度<br>NitrogenDioxideDensity二氧化氮密度<br>SulphurDioxideDensity二氧化硫密度<br>PM25DensityPM25密度<br>PM10DensityPM10密度<br>VOCDensityVOC密度<br>StatusActive活跃状态状态<br>StatusFault状态故障<br>StatusTampered状态篡改<br>StatusLowBattery状态低电量 |
| BatteryService电池服务 | BatteryLevel电池电量<br>ChargingState充电状态<br>StatusLowBattery状态低电量 | Name名称 |
| CarbonDioxideSensor二氧化碳传感器 | CarbonDioxideDetected检测到二氧化碳 | Name名称<br>StatusActive活跃状态状态<br>StatusFault状态故障<br>StatusTampered状态篡改<br>StatusLowBattery状态低电量<br>CarbonDioxideLevel二氧化碳水平<br>CarbonDioxidePeakLevel二氧化碳峰值水平 |
| CarbonMonoxideSensor一氧化碳传感器 | CarbonMonoxideDetected检测到一氧化碳 | Name名称<br>StatusActive活跃状态状态<br>StatusFault状态故障<br>StatusTampered状态篡改<br>StatusLowBattery状态低电量<br>CarbonMonoxideLevel一氧化碳水平<br>CarbonMonoxidePeakLevel一氧化碳峰值水平 |
| ContactSensor接触传感器 | ContactSensorState接触传感器状态 | Name名称<br>StatusActive活跃状态状态<br>StatusFault状态故障<br>StatusTampered状态篡改<br>StatusLowBattery状态低电量 |
| Door门 | CurrentPosition当前位置当前位置<br>TargetPosition目标位置目标位置<br>PositionState位置状态 | Name名称<br>HoldPosition暂停位置<br>ObstructionDetected检测到障碍物 |
| Doorbell门铃 | ProgrammableSwitchEvent可编程开关事件 | Name名称<br>Volume音量<br>Brightness亮度 |
| Fan电扇 | Active活跃 | Name名称<br>CurrentFanState当前风扇状态<br>CTargetFanState目标风扇状态<br>RotationDirection旋转方向<br>RotationSpeed旋转速度<br>SwingMode摇摆模式<br>LockPhysicalControls锁定物理控制 |
| Faucet水龙头 | Active活跃 | StatusFault状态故障<br>Name名称 |
| FilterMaintenance过滤器维护 | FilterChangeIndication过滤器变化指示 | Name名称<br>FilterLifeLevel过滤器生命等级<br>ResetFilterIndication重置过滤器指示 |
| GarageDoorOpener车库开门器 | CurrentDoorState当前门状态<br>TargetDoorState目标门状态<br>ObstructionDetected检测到障碍物 | LockCurrentState锁定当前状态<br>LockTargetState锁定目标状态<br>Name名称 |
| HAPProtocolInformationHAPP协议信息 | Version版本 | *none* |
| HeaterCooler加热器冷却器 | Active活跃<br>CurrentTemperature当前温度<br>CurrentHeaterCoolerState当前加热器冷却器状态<br>TargetHeaterCoolerState目标加热器冷却器状态 | Name名称<br>RotationSpeed旋转速度<br>TemperatureDisplayUnits温度显示单位<br>SwingMode摇摆模式<br>CoolingThresholdTemperature冷却阈值温度<br>HeatingThresholdTemperature加热阈值温度<br>LockPhysicalControls锁定物理控制 |
| HumidifierDehumidifier加湿器除湿机 | Active活跃<br>CurrentRelativeHumidity当前相对湿度当前相对湿度<br>CurrentHumidifierDehumidifierState当前加湿器除湿器状态<br>TargetHumidifierDehumidifierState目标加湿器除湿器状态 | Name名称<br>RelativeHumidityDehumidifierThreshold相对湿度除湿阈值<br>RelativeHumidityHumidifierThreshold相对湿度加湿器阈值<br>RotationSpeed旋转速度<br>SwingMode摇摆模式<br>WaterLevel水位<br>LockPhysicalControls锁定物理控制 |
| HumiditySensor湿度传感器 | CurrentRelativeHumidity当前相对湿度 | Name名称<br>StatusActive活跃状态<br>StatusFault状态故障<br>StatusTampered状态篡改<br>StatusLowBattery状态低电量 |
| InputSource输入源 | Identifier标识符 | ConfiguredName名称<br>IsConfigured已配置<br>CurrentVisibilityState当前可见性状态<br>TargetVisibilityState目标可见性状态 |
| IrrigationSystem灌溉系统 | Active活跃<br>ProgramMode程序模式<br>InUse正在使用 | RemainingDuration剩余时间<br>Name名称<br>StatusFault状态故障 |
| LeakSensor泄漏传感器 | LeakDetected泄漏检测 | Name名称<br>StatusActive活跃状态<br>StatusFault状态故障<br>StatusTampered状态篡改<br>StatusLowBattery状态低电量 |
| LightBulb灯泡 | On开启| Brightness亮度<br>Hue色调<br>Name名称<br>Saturation饱和度<br>ColorTemperature |
| LightSensor光传感器 | CurrentAmbientLightLevel当前环境光级别 | Name名称<br>StatusActive活跃状态<br>StatusFault状态故障<br>StatusTampered状态篡改<br>StatusLowBattery状态低电量 |
| LockMechanism锁定机制 | LockCurrentState锁定当前状态<br>LockTargetState锁定目标状态 | Name名称 |
| Microphone麦克风 | Mute静音 | Name名称<br>Volume音量 |
| MotionSensor运动传感器 | MotionDetected运动检测 | Name名称<br>StatusActive活跃状态<br>StatusFault状态故障<br>StatusTampered状态篡改<br>StatusLowBattery状态低电量 |
| OccupancySensor占用传感器 | OccupancyDetected检测到占用 | Name名称<br>StatusActive活跃状态<br>StatusFault状态故障<br>StatusTampered状态篡改<br>StatusLowBattery状态低电量 |
| Outlet插座| On开关<br>OutletInUse正在使用 | Name名称 |
| SecuritySystem安保系统 | SecuritySystemCurrentState安保系统当前状态<br>SecuritySystemTargetState安全系统目标状态 | Name名称<br>SecuritySystemAlarmType安全系统警报类型<br>StatusFault状态故障<br>StatusTampered状态篡改 |
| ServiceLabel服务标签 | ServiceLabelNamespace服务标签命名空间 | *none* |
| Slat | CurrentSlatState<br>SlatType | Name名称<br>SwingMode摇摆模式<br>CurrentTiltAngle当前倾斜角度<br>TargetTiltAngle目标倾斜角度 |
| SmokeSensor烟雾传感器 | SmokeDetected烟雾检测 | Name名称<br>StatusActive活跃状态<br>StatusFault状态故障<br>StatusTampered状态篡改<br>StatusLowBattery状态低电量 |
| Speaker扬声器 | Mute静音 | Name名称<br>Volume音量 |
| StatelessProgrammableSwitch无状态可编程开关 | ProgrammableSwitchEvent可编程开关事件 | Name名称<br>ServiceLabelIndex服务标签索引 |
| Switch | On开启| Name名称 |
| Television电视 | Active活跃 | ConfiguredName名称<br>ActiveIdentifier标识符<br>RemoteKey遥控钥匙<br>PowerModeSelection电源模式选择 | 
| TemperatureSensor温度感应器 | CurrentTemperature当前温度 | Name名称<br>StatusActive活跃状态<br>StatusFault状态故障<br>StatusTampered状态篡改<br>StatusLowBattery状态低电量 |
| Thermostat恒温器 | CurrentHeatingCoolingState当前加热冷却状态<br>TargetHeatingCoolingState目标加热冷却状态<br>CurrentTemperature当前温度<br>TargetTemperature目标温度<br>TemperatureDisplayUnits温度显示单位 | CoolingThresholdTemperature冷却阈值温度<br>CurrentRelativeHumidity当前相对湿度<br>HeatingThresholdTemperature加热阈值温度<br>Name名称<br>TargetRelativeHumidity目标相对湿度 | 
| Valve阀门 | Active活跃<br>InUse正在使用<br>ValveType阀门类型 | SetDuration设置持续时间<br>RemainingDuration剩余时间<br>IsConfigured已配置<br>ServiceLabelIndex服务标签索引<br>StatusFault状态故障<br>Name名称 |
| Window窗 | CurrentPosition当前位置<br>TargetPosition目标位置<br>PositionState位置状态 | Name名称<br>HoldPosition暂停位置<br>ObstructionDetected检测到障碍物 |
| WindowCovering窗帘 | CurrentPosition当前位置<br>TargetPosition目标位置 | Name名称<br>PositionState位置状态<br>HoldPosition暂停位置<br>CurrentHorizontalTiltAngle当前水平倾斜角度<br>TargetHorizontalTiltAngle目标水平倾斜角度<br>CurrentVerticalTiltAngle当前垂直倾斜角度<br>TargetVerticalTiltAngle目标垂直倾斜角度<br>ObstructionDetected检测到障碍物 |

### 特征类型和默认值

|Characteristic特征|Type类型|Default默认值
|---|---|---|
|Active|uint8_t|0|
|ActiveIdentifier活动标识符|uint32_t|0|
|AirQuality空气质量|uint8_t|0|
|BatteryLevel电池电量|uint8_t|0|
|Brightness亮度|int|0|
|CarbonMonoxideLevel一氧化碳水平|double|0|
|CarbonMonoxidePeakLevel一氧化碳峰值水平|double|0|
|CarbonMonoxideDetected检测到一氧化碳|uint8_t|0|
|CarbonDioxideLevel二氧化碳水平|double|0|
|CarbonDioxidePeakLevel二氧化碳峰值水平|double|0|
|CarbonDioxideDetected检测到二氧化碳|uint8_t|0|
|ChargingState充电状态|uint8_t|0|
|CoolingThresholdTemperature冷却阈值温度|double|10| 
|ColorTemperature色温|uint32_t|50|
|ConfiguredName配置名称|char \*|"unnamed"|
|ContactSensorState接触传感器状态|uint8_t|1|
|CurrentAmbientLightLevel当前环境光级别|double|1|
|CurrentHorizontalTiltAngle当前水平倾斜角度|int|0|
|CurrentAirPurifierState当前空气净化器状态|uint8_t|1|
|CurrentSlatState|uint8_t|0|
|CurrentPosition当前位置|uint8_t|0|
|CurrentVerticalTiltAngle当前垂直倾斜角度|int|0|
|CurrentHumidifierDehumidifierState当前加湿器除湿器状态|uint8_t|1|
|CurrentDoorState当前门状态|uint8_t|1|
|CurrentFanState当前风扇状态|uint8_t|1|
|CurrentHeatingCoolingState当前加热冷却状态|uint8_t|0|
|CurrentHeaterCoolerState当前加热器冷却器状态|uint8_t|1|
|CurrentRelativeHumidity当前相对湿度|double|0|
|CurrentTemperature当前温度|double|0|
|CurrentTiltAngle当前倾斜角度|int|0|
|CurrentVisibilityState当前可见性状态|uint8_t|0|
|FilterLifeLevel过滤器生命等级|double|0|
|FilterChangeIndication过滤器变化指示|uint8_t|0|
|FirmwareRevision固件版本|char \*|"1.0.0"|
|HardwareRevision硬件版本|char \*|"1.0.0"|
|HeatingThresholdTemperature加热阈值温度|double|16|
|HoldPosition暂停位置|boolean|false|
|Hue色调|double|0|
|Identifier标识符|uint32_t|0|
|Identify确认|boolean|false|
|InUse正在使用|uint8_t|0|
|IsConfigured已配置|uint8_t|0|
|LeakDetected泄漏检测|uint8_t|0|
|LockCurrentState锁定当前状态|uint8_t|0|
|LockPhysicalControls锁定物理控制|uint8_t|0|
|LockTargetState锁定目标状态|uint8_t|0|
|Manufacturer制造商|char \*|"HomeSpan"|
|Model型号|char \*|"HomeSpan-ESP32"|
|MotionDetected运动检测|boolean|false|
|Mute静音|boolean|false|
|Name名称|char \*|"unnamed"|
|NitrogenDioxideDensity二氧化氮密度|double|0|
|ObstructionDetected检测到障碍物|boolean|false|
|PM25Density|double|0|
|OccupancyDetected检测到占用|uint8_t|0|
|OutletInUse正在使用|boolean|false|
|On开关|boolean|false|
|OzoneDensity臭氧密度|double|0|
|PM10Density|double|0|
|PositionState位置状态|uint8_t|2|
|PowerModeSelection电源模式选择|uint8_t|0|
|ProgramMode程序模式|uint8_t|0|
|ProgrammableSwitchEvent可编程开关事件|uint8_t|0|
|RelativeHumidityDehumidifierThreshold相对湿度除湿阈值|double|50|
|RelativeHumidityHumidifierThreshold相对湿度加湿器阈值|double|50|
|RemainingDuration剩余时间|uint32_t|60|
|RemoteKey遥控钥匙|uint8_t|0|
|ResetFilterIndication重置过滤器指示|uint8_t|0|
|RotationDirection旋转方向|int|0|
|RotationSpeed旋转速度|double|0|
|Saturation饱和度|double|0|
|SecuritySystemAlarmType安全系统警报类型|uint8_t|0|
|SecuritySystemCurrentState安全系统当前状态|uint8_t|3|
|SecuritySystemTargetState安全系统目标状态|uint8_t|3| 
|SerialNumber序列号|char \*|"HS-12345"|
|ServiceLabelIndex服务标签索引|uint8_t|1|
|ServiceLabelNamespace服务标签命名空间|uint8_t|1|
|SlatType|uint8_t|0|
|SmokeDetected烟雾检测|uint8_t|0|
|StatusActive状态活动|boolean|true|
|StatusFault状态故障|uint8_t|0|
|StatusJammed状态卡住|uint8_t|0|
|StatusLowBattery状态低电量|uint8_t|0|
|StatusTampered状态篡改|uint8_t|0|
|SulphurDioxideDensity二氧化硫密度|double|0|
|SwingMode摇摆模式|uint8_t|0|
|TargetAirPurifierState目标空气净化器状态|uint8_t|1|
|TargetFanState目标风扇状态|uint8_t|1|
|TargetTiltAngle目标倾斜角度|int|0|
|SetDuration设置持续时间|uint32_t|60|
|TargetHorizontalTiltAngle目标水平倾斜角度|int|0|
|TargetHumidifierDehumidifierState目标加湿器除湿器状态|uint8_t|0|
|TargetPosition目标位置|uint8_t|0|
|TargetDoorState目标门状态|uint8_t|1|
|TargetHeaterCoolerState目标加热器冷却器状态|uint8_t|0|
|TargetHeatingCoolingState目标加热冷却状态|uint8_t|0|
|TargetRelativeHumidity目标相对湿度|double|0|
|TargetTemperature目标温度|double|16|
|TemperatureDisplayUnits温度显示单位|uint8_t|0|
|TargetVerticalTiltAngle目标垂直倾斜角度|int|0|
|TargetVisibilityState目标可见性状态|uint8_t|0|
|ValveType阀门类型|uint8_t|0|
|Version版本|char \*|"1.0.0"|
|VOCDensityVOC密度|double|0|
|Volume音量|uint8_t|0|
|WaterLevel水位|double|0|


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
|TLV8|(not implemented)|
|DATA|(not implemented)|

---

[↩️](README.md) 返回欢迎页面
