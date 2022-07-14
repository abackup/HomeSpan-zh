/*********************************************************************************
 *  MIT License
 *  
 *  Copyright (c) 2020-2022 Gregg E. Berman
 *  
 *  https://github.com/HomeSpan/HomeSpan
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *  
 ********************************************************************************/
 
////////////////////////////////////////////////////////////
//                                                        //
//    HomeSpan: A HomeKit implementation for the ESP32    //
//    ------------------------------------------------    //
//                                                        //
// Example 12: Service Loops (and Event Notifications)    //
//             * implementing a Temperature Sensor        //
//             * implementing an Air Quality Sensor       //
//                                                        //
////////////////////////////////////////////////////////////

#include "HomeSpan.h" 
#include "DEV_Sensors.h" 

void setup() {

  // 到目前为止，我们已经看到 HomeSpan 允许您使用自己的构造函数和 update() 方法创建派生服务。对于许多应用程序，这将是全部所需。
 //但是，对于许多其他类型的应用程序，您可能需要采取行动或者在没有来自 HomeKit 的任何提示或请求的情况下执行一些后台操作。为了执行
 // 后台操作和动作，每个 Service 都实现了一个 loop() 方法。默认的 loop() 方法是什么都不做，这对于我们之前的所有示例都很好。但是
 // 如果你需要执行一些连续的后台动作，你就可以需要做的是为你的派生服务实现一个loop()方法。在每个HomeSpan轮询周期结束时，每个实现
//  自己代码的服务都会调用loop()方法。在这种方式下，loop() 方法类似于 Arduino IDE 本身中的 main loop() 方法——除了它可以为每个服务
 // 定制。在本例 12 中，我们探索了使用 loop() 方法来实现两个新配件 - 温度传感器和空气质量传感器。当然，出于本示例的目的，我们实际
 // 上不会将这些物理设备连接到 ESP32，但我们将模拟“读取”它们的属性。这是实现 loop() 方法的主要目的之一。它允许您读取传感器或执行
//  某种重复的、特定于服务的操作。一旦您在 loop() 方法中读取（或模拟读取）传感器的值，您需要以某种方式将其传达回 HomeKit，以便新
//  值可以反映在 HomeKit 控制器中。这可能仅用于信息目的（例如温度传感器）或 HomeKit 本身可以使用它来触发其他设备（如果实现门传感器
//  可能会发生这种情况）。幸运的是，HomeSpan 使得将 Characteristic 的值传回 HomeKit 变得容易。在前面的示例中，我们看到了如何使用
//  getVal() 和 getNewVal() 来读取 HomeKit 请求的当前和更新的 Characteristic 值。要执行相反的操作，我们只需使用一个方法称为 
//  setVal()。使用此函数设置 Characteristic 的值有两件事情。首先，它会导致 HomeSpan 将 Event Notification 消息发送回 HomeKit，
 // 让 HomeKit 知道 Characteristic 的新值。由于消息会创建网络流量，HomeSpan 会跟踪所有 setVal( ) 更改所有服务并创建一个单独的事件
 // 通知消息，在每个轮询周期结束时一起报告所有更改。当您使用 setVal() 更改 Characteristic 的值时，HomeSpan 所做的第二件事是重置该
//  Characteristic 的内部计时器，该计时器跟踪自上次修改以来已经过去了多长时间，无论是来自先前的 setVal() 指令，还是由 HomeKit 
//  本身通过调用 update()。您可以使用 timeVal() 方法查询自上次修改以来的时间，该方法以毫秒为单位返回经过的时间。通过在 loop() 中
//  调用此函数，您可以确定何时是读取新传感器的时间，或何时执行其他操作行动。
 //注意：不建议使用 setVal() 连续更改特性值，因为这会产生大量网络流量，因为 HomeSpan 会向所有已注册的 HomeKit 控制器发送事件通知
//  bck。执行内部计算、在不同引脚上生成信号和尽可能频繁地执行您可能需要的任何其他内部操作。但将 setVal() 的使用限制在合理的频率，
//  例如温度传感器可能每分钟一次。除非 Characteristic 的值，否则不要使用 setVal()更改，但确实使用它来立即通知 HomeKit 一些时间敏感
 // 的事情，例如开门或触发烟雾报警器。
 //像往常一样，此示例的所有逻辑都封装在新的独立派生服务中。您将在 DEV_Sensors.h 文件中找到下面实例化的 DEV_TempSensor() 和 
//  DEV_AirQualitySensor() 服务的完整注释定义。如上所述，此示例仅用于说明目的——我们实际上并没有将温度传感器或空气质量传感器连接到
//  我们的 ESP32 设备。因此，我们没有定义服务以使用任何参数来指定引脚号或实现所需的任何其他信息一个实际的传感器。相反，为了了解设备
//  的工作情况，我们通过使用 setVal() 修改特征值来模拟周期性变化，其中包含重复值序列或随机值。有关完整详细信息，请参阅 DEV_Sensors.h。
// 一旦你理解了这些例子，你应该能够使用实现你自己的 loop() 方法，并使用 setVal() 和 timeVal() 来实现 HomeKit 服务的任意组合，以及
//  需要你的设备向 HomeKit 控制器发送定期更新消息的特性，从烟雾报警器到门传感器。
  
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

} // end of setup()

//////////////////////////////////////

void loop(){
  
  homeSpan.poll();
  
} // end of loop()

//////////////////////////////////////
