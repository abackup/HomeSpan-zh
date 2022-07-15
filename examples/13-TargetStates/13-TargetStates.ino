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
// Example 13: Target States and Current States           //
//             * implementing a Garage Door Opener        //
//             * implementing a motorized Window Shade    //
//                                                        //
////////////////////////////////////////////////////////////

#include "HomeSpan.h" 
#include "DEV_DoorsWindows.h" 

void setup() {

  // 在示例 12 中，我们看到了如何为服务实现 loop() 方法，以持续监控我们的设备，并使用 setVal() 和 timeVal() 定期向 HomeKit 
 //报告一个或多个特性的变化。在该示例中，我们实现了被动传感器独立操作，不需要用户输入，这意味着我们不需要实现任何 update() 方法。
  
 //在这个示例 13 中，我们通过实现两个新服务来演示同时使用 update() 和 loop() 方法：车库门开启器和电动窗帘。两个示例都展示了
 // HomeKit 的目标状态/当前状态框架。对于需要时间操作的物理设备（例如关门），HomeKit 服务通常使用：
//* HomeKit 通过对 HomeSpan 的 update() 请求设置的一个特性，它表示所需的目标状态，例如打开、关闭或在某些情况下打开或关闭的百分比；和
//* HomeSpan 用于在 loop() 方法中跟踪设备的当前状态以及使用 setVal() 将更改报告回 HomeKit 的一个只读特性。
// 并非所有 HomeKit 服务都使用相同的特性来定义目标和当前状态。一些服务使用特定于该服务的特性，而其他服务使用更通用的特性。共同的
 // 主题似乎是 HomeKit 猜测设备正在执行的操作，并通过比较它设置的目标状态特性的值和它以事件通知的形式接收的当前状态特性的值来相应
  //地更新它的平铺图标。当它们相同时，HomeKit 假定物理设备已到达所需的位置。当它们不同时，HomeKit 会假设某些东西会打开、关闭、
  //升高、降低等。HAP 文档中概述了每个服务的此过程的详细信息，但请注意该文档并不总是与最新版本的最新版本保持同步。 HomeKit 应用
 // 程序。有时需要进行一些试验和大量的反复试验才能完全理解每个服务如何响应不同的组合离子的特征值。
// 与往常一样，我们不会将 ESP32 连接到实际的车库门或窗帘，而是会模拟它们的响应和动作以用于说明目的。在某些方面，由于需要模拟值，
//  代码更复杂——如果我们实际上连接到车库门或窗帘，可能会更容易！
// 我们的两个派生服务的完整注释代码可以在 DEV_DoorsWindows.h 中找到。这些示例没有引入任何新的 HomeSpan 函数或特性。而是我们将迄
//  今为止学到的所有内容组合成两个相当复杂的服务。您可能想要参考 HAP这两个父服务的文档，以充分理解每个服务特征的不同值设置的含义。

  
  Serial.begin(115200);

  homeSpan.begin(Category::Bridges,"HomeSpan Bridge");

  new SpanAccessory();  
    new Service::AccessoryInformation();
      new Characteristic::Identify(); 
      
  new SpanAccessory();                                                          
    new Service::AccessoryInformation();
      new Characteristic::Identify(); 
      new Characteristic::Name("Garage Door");
    new DEV_GarageDoor();                                                               //创建车库开门器（参见 DEV_DoorsWindows.h 的定义）

  new SpanAccessory();                                                          
    new Service::AccessoryInformation();
      new Characteristic::Identify(); 
      new Characteristic::Name("Window Shade");
    new DEV_WindowShade();                                                              // 创建电动窗帘（参见 DEV_DoorsWindows.h 的定义）

} // end of setup()

//////////////////////////////////////

void loop(){
  
  homeSpan.poll();
  
} // end of loop()
