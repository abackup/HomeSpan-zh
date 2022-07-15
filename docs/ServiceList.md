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
| AirPurifier空气净化器 | Active活跃<br>CurrentAirPurifierState当前空气净化器状态<br>TargetAirPurifierState目标空气净化器状态 | Name名称<br>RotationSpeed旋转速度旋转速度<br>SwingMode摇摆模式<br>LockPhysicalControls锁定物理控制锁定物理控制 |
| AirQualitySensor空气质量传感器 | AirQuality空气质量 | Name名称<br>OzoneDensity臭氧密度<br>NitrogenDioxideDensity二氧化氮密度<br>SulphurDioxideDensity二氧化硫密度<br>PM25DensityPM25密度<br>PM10DensityPM10密度<br>VOCDensityVOC密度<br>StatusActive活跃状态活动<br>StatusFault状态故障状态故障<br>StatusTampered状态篡改<br>StatusLowBattery状态低电量 |
| BatteryService电池服务 | BatteryLevel电池电量<br>ChargingState充电状态<br>StatusLowBattery状态低电量 | Name名称 |
| CarbonDioxideSensor二氧化碳传感器 | CarbonDioxideDetected检测到二氧化碳 | Name名称<br>StatusActive活跃状态活动<br>StatusFault状态故障状态故障<br>StatusTampered<br>StatusLowBattery状态低电量<br>CarbonDioxideLevel二氧化碳水平<br>CarbonDioxidePeakLevel二氧化碳峰值水平 |
| CarbonMonoxideSensor一氧化碳传感器 | CarbonMonoxideDetected检测到一氧化碳 | Name名称<br>StatusActive活跃状态活动<br>StatusFault状态故障状态故障<br>StatusTampered状态篡改<br>StatusLowBattery状态低电量<br>CarbonMonoxideLevel一氧化碳水平<br>CarbonMonoxidePeakLevel一氧化碳峰值水平 |
| ContactSensor接触传感器 | ContactSensorState接触传感器状态 | Name名称<br>StatusActive活跃状态活动<br>StatusFault状态故障状态故障<br>StatusTampered状态篡改<br>StatusLowBattery状态低电量 |
| Door门 | CurrentPosition当前位置<br>TargetPosition目标位置<br>PositionState位置状态 | Name名称<br>HoldPosition<br>ObstructionDetected检测到障碍物 |
| Doorbell门铃 | ProgrammableSwitchEvent可编程开关事件 | Name名称<br>Volume音量<br>Brightness亮度 |
| Fan电扇 | Active活跃 | Name名称<br>CurrentFanState当前风扇状态<br>CTargetFanState目标风扇状态<br>RotationDirection旋转方向<br>RotationSpeed旋转速度<br>SwingMode<br>LockPhysicalControls锁定物理控制 |
| Faucet水龙头 | Active活跃 | StatusFault状态故障状态故障<br>Name名称 |
| FilterMaintenance过滤器维护 | FilterChangeIndication | Name名称<br>FilterLifeLevel过滤器生命等级<br>ResetFilterIndication重置过滤器指示 |
| GarageDoorOpener车库开门器 | CurrentDoorState当前门状态<br>TargetDoorState目标门状态<br>ObstructionDetected检测到障碍物 | LockCurrentState<br>LockTargetState<br>Name名称 |
| HAPProtocolInformationHAPP协议信息 | Version版本 | *none* |
| HeaterCooler加热器冷却器 | Active活跃<br>CurrentTemperature当前温度<br>CurrentHeaterCoolerState当前加热器冷却器状态<br>TargetHeaterCoolerState | Name名称<br>RotationSpeed旋转速度<br>TemperatureDisplayUnits<br>SwingMode<br>CoolingThresholdTemperature冷却阈值温度<br>HeatingThresholdTemperature加热阈值温度<br>LockPhysicalControls锁定物理控制 |
| HumidifierDehumidifier加湿器除湿机 | Active活跃<br>CurrentRelativeHumidity当前相对湿度<br>CurrentHumidifierDehumidifierState当前加湿器除湿器状态<br>TargetHumidifierDehumidifierState目标加湿器除湿器状态 | Name名称<br>RelativeHumidityDehumidifierThreshold<br>RelativeHumidityHumidifierThreshold相对湿度加湿器阈值<br>RotationSpeed旋转速度<br>SwingMode<br>WaterLevel<br>LockPhysicalControls锁定物理控制 |
| HumiditySensor | CurrentRelativeHumidity | Name名称<br>StatusActive活跃<br>StatusFault状态故障<br>StatusTampered<br>StatusLowBattery |
| InputSource | Identifier标识符 | ConfiguredName名称<br>IsConfigured<br>CurrentVisibilityState当前可见性状态<br>TargetVisibilityState目标可见性状态 |
| IrrigationSystem | Active活跃<br>ProgramMode<br>InUse | RemainingDuration<br>Name名称<br>StatusFault状态故障 |
| LeakSensor | LeakDetected | Name名称<br>StatusActive活跃<br>StatusFault状态故障<br>StatusTampered<br>StatusLowBattery |
| LightBulb | On | Brightness亮度<br>Hue<br>Name名称<br>Saturation饱和度<br>ColorTemperature |
| LightSensor | CurrentAmbientLightLevel | Name名称<br>StatusActive活跃<br>StatusFault状态故障<br>StatusTampered<br>StatusLowBattery |
| LockMechanism | LockCurrentState<br>LockTargetState | Name名称 |
| Microphone | Mute | Name名称<br>Volume音量 |
| MotionSensor | MotionDetected | Name名称<br>StatusActive活跃<br>StatusFault状态故障<br>StatusTampered<br>StatusLowBattery |
| OccupancySensor | OccupancyDetected | Name名称<br>StatusActive活跃<br>StatusFault状态故障<br>StatusTampered<br>StatusLowBattery |
| Outlet | On<br>OutletInUse | Name名称 |
| SecuritySystem | SecuritySystemCurrentState<br>SecuritySystemTargetState | Name名称<br>SecuritySystemAlarmType<br>StatusFault状态故障<br>StatusTampered |
| ServiceLabel | ServiceLabelName名称space | *none* |
| Slat | CurrentSlatState<br>SlatType | Name名称<br>SwingMode<br>CurrentTiltAngle<br>TargetTiltAngle |
| SmokeSensor | SmokeDetected | Name名称<br>StatusActive活跃<br>StatusFault状态故障<br>StatusTampered<br>StatusLowBattery |
| Speaker | Mute | Name名称<br>Volume音量 |
| StatelessProgrammableSwitch | ProgrammableSwitchEvent | Name名称<br>ServiceLabelIndex |
| Switch | On | Name名称 |
| Television | Active活跃 | ConfiguredName名称<br>Active活跃Identifier标识符<br>RemoteKey遥控钥匙<br>PowerModeSelection | 
| TemperatureSensor | CurrentTemperature当前温度 | Name名称<br>StatusActive活跃<br>StatusFault状态故障<br>StatusTampered<br>StatusLowBattery |
| Thermostat | CurrentHeatingCoolingState<br>TargetHeatingCoolingState<br>CurrentTemperature当前温度<br>TargetTemperature<br>TemperatureDisplayUnits | CoolingThresholdTemperature冷却阈值温度<br>CurrentRelativeHumidity<br>HeatingThresholdTemperature加热阈值温度<br>Name名称<br>TargetRelativeHumidity | 
| Valve | Active活跃<br>InUse<br>ValveType | SetDuration<br>RemainingDuration<br>IsConfigured<br>ServiceLabelIndex<br>StatusFault状态故障<br>Name名称 |
| Window | CurrentPosition<br>TargetPosition<br>PositionState位置状态 | Name名称<br>HoldPosition<br>ObstructionDetected检测到障碍物 |
| WindowCovering | CurrentPosition<br>TargetPosition | Name名称<br>PositionState位置状态<br>HoldPosition<br>CurrentHorizontalTiltAngle<br>TargetHorizontalTiltAngle<br>CurrentVerticalTiltAngle<br>TargetVerticalTiltAngle<br>ObstructionDetected检测到障碍物 |


### 特征类型和默认值

|Characteristic|Type|Default
|---|---|---|
|Active|uint8_t|0|
|ActiveIdentifier|uint32_t|0|
|AirQuality|uint8_t|0|
|BatteryLevel|uint8_t|0|
|Brightness|int|0|
|CarbonMonoxideLevel|double|0|
|CarbonMonoxidePeakLevel|double|0|
|CarbonMonoxideDetected|uint8_t|0|
|CarbonDioxideLevel|double|0|
|CarbonDioxidePeakLevel|double|0|
|CarbonDioxideDetected|uint8_t|0|
|ChargingState|uint8_t|0|
|CoolingThresholdTemperature|double|10| 
|ColorTemperature|uint32_t|50|
|ConfiguredName|char \*|"unnamed"|
|ContactSensorState|uint8_t|1|
|CurrentAmbientLightLevel|double|1|
|CurrentHorizontalTiltAngle|int|0|
|CurrentAirPurifierState|uint8_t|1|
|CurrentSlatState|uint8_t|0|
|CurrentPosition|uint8_t|0|
|CurrentVerticalTiltAngle|int|0|
|CurrentHumidifierDehumidifierState|uint8_t|1|
|CurrentDoorState|uint8_t|1|
|CurrentFanState|uint8_t|1|
|CurrentHeatingCoolingState|uint8_t|0|
|CurrentHeaterCoolerState|uint8_t|1|
|CurrentRelativeHumidity|double|0|
|CurrentTemperature|double|0|
|CurrentTiltAngle|int|0|
|CurrentVisibilityState|uint8_t|0|
|FilterLifeLevel|double|0|
|FilterChangeIndication|uint8_t|0|
|FirmwareRevision|char \*|"1.0.0"|
|HardwareRevision|char \*|"1.0.0"|
|HeatingThresholdTemperature|double|16|
|HoldPosition|boolean|false|
|Hue|double|0|
|Identifier|uint32_t|0|
|Identify|boolean|false|
|InUse|uint8_t|0|
|IsConfigured|uint8_t|0|
|LeakDetected|uint8_t|0|
|LockCurrentState|uint8_t|0|
|LockPhysicalControls|uint8_t|0|
|LockTargetState|uint8_t|0|
|Manufacturer|char \*|"HomeSpan"|
|Model|char \*|"HomeSpan-ESP32"|
|MotionDetected|boolean|false|
|Mute|boolean|false|
|Name|char \*|"unnamed"|
|NitrogenDioxideDensity|double|0|
|ObstructionDetected|boolean|false|
|PM25Density|double|0|
|OccupancyDetected|uint8_t|0|
|OutletInUse|boolean|false|
|On|boolean|false|
|OzoneDensity|double|0|
|PM10Density|double|0|
|PositionState|uint8_t|2|
|PowerModeSelection|uint8_t|0|
|ProgramMode|uint8_t|0|
|ProgrammableSwitchEvent|uint8_t|0|
|RelativeHumidityDehumidifierThreshold|double|50|
|RelativeHumidityHumidifierThreshold|double|50|
|RemainingDuration|uint32_t|60|
|RemoteKey|uint8_t|0|
|ResetFilterIndication|uint8_t|0|
|RotationDirection|int|0|
|RotationSpeed|double|0|
|Saturation|double|0|
|SecuritySystemAlarmType|uint8_t|0|
|SecuritySystemCurrentState|uint8_t|3|
|SecuritySystemTargetState|uint8_t|3| 
|SerialNumber|char \*|"HS-12345"|
|ServiceLabelIndex|uint8_t|1|
|ServiceLabelNamespace|uint8_t|1|
|SlatType|uint8_t|0|
|SmokeDetected|uint8_t|0|
|StatusActive|boolean|true|
|StatusFault|uint8_t|0|
|StatusJammed|uint8_t|0|
|StatusLowBattery|uint8_t|0|
|StatusTampered|uint8_t|0|
|SulphurDioxideDensity|double|0|
|SwingMode|uint8_t|0|
|TargetAirPurifierState|uint8_t|1|
|TargetFanState|uint8_t|1|
|TargetTiltAngle|int|0|
|SetDuration|uint32_t|60|
|TargetHorizontalTiltAngle|int|0|
|TargetHumidifierDehumidifierState|uint8_t|0|
|TargetPosition|uint8_t|0|
|TargetDoorState|uint8_t|1|
|TargetHeaterCoolerState|uint8_t|0|
|TargetHeatingCoolingState|uint8_t|0|
|TargetRelativeHumidity|double|0|
|TargetTemperature|double|16|
|TemperatureDisplayUnits|uint8_t|0|
|TargetVerticalTiltAngle|int|0|
|TargetVisibilityState|uint8_t|0|
|ValveType|uint8_t|0|
|Version|char \*|"1.0.0"|
|VOCDensity|double|0|
|Volume|uint8_t|0|
|WaterLevel|double|0|


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
