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

| Service | Required Characteristics | Optional Characteristics |
| ------- | -------------------- | ------------------- |
| AccessoryInformation| FirmwareRevision<br>Identity<br>Manufacturer<br>Model<br>Name<br>SerialNumber | HardwareRevision |
| AirPurifier | Active<br>CurrentAirPurifierState<br>TargetAirPurifierState | Name<br>RotationSpeed<br>SwingMode<br>LockPhysicalControls |
| AirQualitySensor | AirQuality | Name<br>OzoneDensity<br>NitrogenDioxideDensity<br>SulphurDioxideDensity<br>PM25Density<br>PM10Density<br>VOCDensity<br>StatusActive<br>StatusFault<br>StatusTampered<br>StatusLowBattery |
| BatteryService | BatteryLevel<br>ChargingState<br>StatusLowBattery | Name |
| CarbonDioxideSensor | CarbonDioxideDetected | Name<br>StatusActive<br>StatusFault<br>StatusTampered<br>StatusLowBattery<br>CarbonDioxideLevel<br>CarbonDioxidePeakLevel |
| CarbonMonoxideSensor | CarbonMonoxideDetected | Name<br>StatusActive<br>StatusFault<br>StatusTampered<br>StatusLowBattery<br>CarbonMonoxideLevel<br>CarbonMonoxidePeakLevel |
| ContactSensor | ContactSensorState | Name<br>StatusActive<br>StatusFault<br>StatusTampered<br>StatusLowBattery |
| Door | CurrentPosition<br>TargetPosition<br>PositionState | Name<br>HoldPosition<br>ObstructionDetected |
| Doorbell | ProgrammableSwitchEvent | Name<br>Volume<br>Brightness |
| Fan | Active | Name<br>CurrentFanState<br>TargetFanState<br>RotationDirection<br>RotationSpeed<br>SwingMode<br>LockPhysicalControls |
| Faucet | Active | StatusFault<br>Name |
| FilterMaintenance | FilterChangeIndication | Name<br>FilterLifeLevel<br>ResetFilterIndication |
| GarageDoorOpener | CurrentDoorState<br>TargetDoorState<br>ObstructionDetected | LockCurrentState<br>LockTargetState<br>Name |
| HAPProtocolInformation | Version | *none* |
| HeaterCooler | Active<br>CurrentTemperature<br>CurrentHeaterCoolerState<br>TargetHeaterCoolerState | Name<br>RotationSpeed<br>TemperatureDisplayUnits<br>SwingMode<br>CoolingThresholdTemperature<br>HeatingThresholdTemperature<br>LockPhysicalControls |
| HumidifierDehumidifier | Active<br>CurrentRelativeHumidity<br>CurrentHumidifierDehumidifierState<br>TargetHumidifierDehumidifierState | Name<br>RelativeHumidityDehumidifierThreshold<br>RelativeHumidityHumidifierThreshold<br>RotationSpeed<br>SwingMode<br>WaterLevel<br>LockPhysicalControls |
| HumiditySensor | CurrentRelativeHumidity | Name<br>StatusActive<br>StatusFault<br>StatusTampered<br>StatusLowBattery |
| InputSource | Identifier | ConfiguredName<br>IsConfigured<br>CurrentVisibilityState<br>TargetVisibilityState |
| IrrigationSystem | Active<br>ProgramMode<br>InUse | RemainingDuration<br>Name<br>StatusFault |
| LeakSensor | LeakDetected | Name<br>StatusActive<br>StatusFault<br>StatusTampered<br>StatusLowBattery |
| LightBulb | On | Brightness<br>Hue<br>Name<br>Saturation<br>ColorTemperature |
| LightSensor | CurrentAmbientLightLevel | Name<br>StatusActive<br>StatusFault<br>StatusTampered<br>StatusLowBattery |
| LockMechanism | LockCurrentState<br>LockTargetState | Name |
| Microphone | Mute | Name<br>Volume |
| MotionSensor | MotionDetected | Name<br>StatusActive<br>StatusFault<br>StatusTampered<br>StatusLowBattery |
| OccupancySensor | OccupancyDetected | Name<br>StatusActive<br>StatusFault<br>StatusTampered<br>StatusLowBattery |
| Outlet | On<br>OutletInUse | Name |
| SecuritySystem | SecuritySystemCurrentState<br>SecuritySystemTargetState | Name<br>SecuritySystemAlarmType<br>StatusFault<br>StatusTampered |
| ServiceLabel | ServiceLabelNamespace | *none* |
| Slat | CurrentSlatState<br>SlatType | Name<br>SwingMode<br>CurrentTiltAngle<br>TargetTiltAngle |
| SmokeSensor | SmokeDetected | Name<br>StatusActive<br>StatusFault<br>StatusTampered<br>StatusLowBattery |
| Speaker | Mute | Name<br>Volume |
| StatelessProgrammableSwitch | ProgrammableSwitchEvent | Name<br>ServiceLabelIndex |
| Switch | On | Name |
| Television | Active | ConfiguredName<br>ActiveIdentifier<br>RemoteKey<br>PowerModeSelection | 
| TemperatureSensor | CurrentTemperature | Name<br>StatusActive<br>StatusFault<br>StatusTampered<br>StatusLowBattery |
| Thermostat | CurrentHeatingCoolingState<br>TargetHeatingCoolingState<br>CurrentTemperature<br>TargetTemperature<br>TemperatureDisplayUnits | CoolingThresholdTemperature<br>CurrentRelativeHumidity<br>HeatingThresholdTemperature<br>Name<br>TargetRelativeHumidity | 
| Valve | Active<br>InUse<br>ValveType | SetDuration<br>RemainingDuration<br>IsConfigured<br>ServiceLabelIndex<br>StatusFault<br>Name |
| Window | CurrentPosition<br>TargetPosition<br>PositionState | Name<br>HoldPosition<br>ObstructionDetected |
| WindowCovering | CurrentPosition<br>TargetPosition | Name<br>PositionState<br>HoldPosition<br>CurrentHorizontalTiltAngle<br>TargetHorizontalTiltAngle<br>CurrentVerticalTiltAngle<br>TargetVerticalTiltAngle<br>ObstructionDetected |


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
