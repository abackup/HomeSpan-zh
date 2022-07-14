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
// Example 14: Emulated PushButtons                       //
//                                                        //
////////////////////////////////////////////////////////////

#include "HomeSpan.h" 
#include "DEV_Blinker.h"     

void setup() {

   // 尽管 HomeKit 和 HomeKit 附件协议 (HAP) 规范为创建 iOS 和 MacOS 控制的设备提供了一个非常灵活的框架，但它们并不包含
 //所有可能需要的功能。一个非常常见的 HomeKit 似乎不包含的特性是一个简单的按钮，就像您在遥控器上找到的那种类型。与可以“开”
  //或“关”的开关不同，按钮没有状态。相反，一个按钮在被按下时会执行一些动作，这就是它所做的一切，直到它再次被按下。虽然 HomeKit
  //不包含这样的 Characteristic，但在 HomeSpan 中很容易模拟。为此，只需定义一个带有布尔特性的 Service（例如 On Characteristic）
  //，并创建一个 update() 方法来执行要执行的操作当“按钮”被“按下”（即设置为 true）时。您可以停在那里并在 HomeKit 中放置一些像按钮
 // 一样的东西，但它看起来不像按钮，因为每次按下设备的磁贴时在 HomeKit 中，控制器将在显示打开和关闭之间切换。按下显示状态已打开的
 // 磁贴，并将更改为关闭，当您实际上想要重新触发某种“打开”动作时不是很满意。理想情况下，我们希望 HomeKit 通过点亮来确认您已按下设
 // 备的磁贴，向 update() 发送请求，然后在一两秒后自动将自身重置为“关闭”位置。这确实可以模拟点亮按钮。幸运的是，通过使用 Service 
//  的 loop() 函数，很容易在 HomeSpan 中模拟这一点。只需像往常一样使用它自己的 update() 方法编写派生服务，并实现一个 loop() 方法，
//  该方法在一段时间后“重置”一个或多个特征。这类似于我们在 with 循环中所做的() 方法在前面两个示例中，除了简单得多，因为唯一的逻辑是
 // 在几秒钟后使用 timeVal() 和 setVal() 将 Characteristic 的值设置为“关闭”。示例 14 通过实现一个“按钮”服务来让 LED 闪烁 3 次来演
 // 示这一点。这本身并不是很有用。但它是一个很好的模型，用于展示如何实现一个将音量调高命令发送到电视;或一个射频发射器来控制一些远程
//   设备，比如吊扇。所有功能都包含在一个新定义的“DEV_Blinker”服务中，该服务可以在 DEV_Blinker.h 中找到。此新服务是示例 9 中的 
//   DEV_LED 服务的副本，经过修改以使其成为通用闪烁 LED。与往常一样，此示例 14 和原始示例 9 之间的更改和新行已被特别注释。
  Serial.begin(115200);

  homeSpan.begin(Category::Bridges,"HomeSpan Bridge");
  
  // 定义桥接附件
 
  new SpanAccessory();  
    new Service::AccessoryInformation();
      new Characteristic::Identify(); 
  
  // *** NEW *** 定义了一个连接到引脚 16 的 LED 闪烁器附件，闪烁 3 次

  new SpanAccessory();                                                          
    new Service::AccessoryInformation();
      new Characteristic::Identify(); 
      new Characteristic::Name("LED Blinker");
    new DEV_Blinker(16,3);                                                      // DEV_Blinker 需要两个参数 - 引脚和闪烁次数

} // end of setup()

//////////////////////////////////////

void loop(){
  
  homeSpan.poll();
  
} // end of loop()
