////////////////////////////////////////////////////////////
//                                                        //
//              HomeSpan：ESP32 的 HomeKit 实现           //
//    ------------------------------------------------    //
//                                                        //
//            示例 12：服务循环（和事件通知）               //
//                    * 实现温度传感器                     //
//                    * 实现空气质量传感器                 //
//                                                        //
////////////////////////////////////////////////////////////

#include "HomeSpan.h" 
#include "DEV_Sensors.h" 

void setup() {

  // 到目前为止，我们已经看到 HomeSpan 允许您使用自己的构造函数和 update() 方法创建派生服务。对于许多应用程序来说，这将是所需的全部。
  // 但是，对于许多其他类型的应用程序，您可能需要采取行动或执行一些后台操作，而无需 HomeKit 的任何提示或请求。

  // 要执行后台操作和动作，每个服务都实现一个 loop() 方法。默认的 loop() 方法不执行任何操作，这对于我们之前的所有示例来说都是没问题的。
  // 但如果您需要执行一些连续的后台操作，您需要做的就是为派生服务实现一个 loop() 方法。在每个 HomeSpan 轮询周期结束时，将为每个实现其
  // 自己代码的服务调用 loop() 方法。以这种方式，loop() 方法类似于 Arduino IDE 本身中的主 loop() 方法 - 但它可以针对每个服务进行自定义。

  // 在此示例 12 中，我们探索了使用 loop() 方法来实现两个新配件 - 温度传感器和空气质量传感器。当然，为了本示例的目的，我们实际上不会将
  // 这些物理设备连接到 ESP32，但我们将模拟“读取”它们的属性。这是实现 loop() 方法的主要目的之一。它允许您读取传感器或执行某种重复的、特定于服务的操作。

  // 一旦您在 loop() 方法中读取（或模拟读取）传感器的值，您需要以某种方式将其传回 HomeKit，以便新值可以反映在 HomeKit 控制器中。
  // 这可能严格用于信息目的（例如温度传感器），也可能由 HomeKit 本身用来触发其他设备（如果实现门传感器，可能会发生这种情况）。

  // 幸运的是，HomeSpan 使向 HomeKit 回传 Characteristics 值变得简单。在前面的示例中，我们看到了如何使用 getVal() 和 getNewVal() 
  // 读取 HomeKit 请求的当前和更新的 Characteristic 值。要执行相反的操作，我们只需使用名为 setVal() 的方法。使用此函数设置 
  // Characteristic 的值有两个作用。首先，它会导致 HomeSpan 向 HomeKit 回传事件通知消息，让 HomeKit 知道 Characteristic 的新值。
  // 由于消息会产生网络流量，因此 HomeSpan 会跟踪所有服务中的所有 setVal() 更改，并在每个轮询周期结束时创建一个事件通知消息来报告所有更改。

  // 当您使用 setVal() 更改 Characteristic 的值时，HomeSpan 执行的第二件事是重置该 Characteristic 的内部计时器，该计时器会跟踪自
  // 上次修改以来的时间，无论是来自之前的 setVal() 指令，还是由 HomeKit 本身通过调用 update()。您可以使用方法 timeVal() 查询自上次
  // 修改以来的时间，该方法返回以毫秒为单位的已用时间。通过从 loop() 中调用此函数，您可以确定何时需要读取新的传感器，或何时执行其他操作。

  // 注意：不建议使用 setVal() 连续更改特性值，因为这会产生大量网络流量，因为 HomeSpan 会将事件通知发送回所有已注册的 HomeKit 控制器。
  // 可以执行内部计算、在不同引脚上生成信号以及根据需要频繁执行您可能需要的任何其他内部操作。但请将 setVal() 的使用限制在合理的频率，
  // 例如对于温度传感器，可能每分钟一次。除非特性值发生变化，否则不要使用 setVal()，但请使用它立即通知 HomeKit 一些时间敏感的事情，
  // 例如开门或烟雾警报触发。

  // 与往常一样，此示例的所有逻辑都封装在新的独立派生服务中。您将在 DEV_Sensors.h 文件中找到下面实例化的 DEV_TempSensor() 和 DEV_AirQualitySensor() 
  // 服务的完整注释定义。如前所述，此示例仅用于指导目的 - 我们实际上并未将温度传感器或空气质量传感器连接到我们的 ESP32 设备。因此，我们没有定义服务以
  // 接受任何参数来指定引脚号或实现实际传感器所需的任何其他信息。相反，为了了解设备的实际工作方式，我们通过使用 setVal() 修改特性值来模拟周期性变化，
  // 该 setVal() 可以是一系列重复值或随机值。有关完整详细信息，请参阅 DEV_Sensors.h。

  // 一旦您理解了这些示例，您应该能够使用自己的 loop() 方法实现并将 setVal() 和 timeVal() 用于任何具有特性的 HomeKit 服务组合，这些特性要求您的设备
  // 向 HomeKit 控制器发送定期更新消息，范围从烟雾报警器到门传感器。

  Serial.begin(115200);

  homeSpan.begin(Category::Bridges,"HomeSpan Bridge");

  new SpanAccessory();  
    new Service::AccessoryInformation();
      new Characteristic::Identify(); 
      
  new SpanAccessory();
    new Service::AccessoryInformation();
      new Characteristic::Identify(); 
      new Characteristic::Name("Temp Sensor");
    new DEV_TempSensor();                                                                // Create a Temperature Sensor (see DEV_Sensors.h for definition)

  new SpanAccessory();
    new Service::AccessoryInformation();
      new Characteristic::Identify(); 
      new Characteristic::Name("Air Quality");  
    new DEV_AirQualitySensor();                                                          // Create an Air Quality Sensor (see DEV_Sensors.h for definition)

} // setup() 结束

//////////////////////////////////////

void loop(){
  
  homeSpan.poll();
  
} // loop() 结束

//////////////////////////////////////
