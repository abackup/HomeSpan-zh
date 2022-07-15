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
// Example 16: Stateless Programmable Switches            //
//                                                        //
////////////////////////////////////////////////////////////

#include "HomeSpan.h" 
#include "DEV_ProgButton.h"     

void setup() {

  // 示例 16 没有引入任何新的 HomeSpan 功能，而是展示了 HomeKit 的一个独特功能，您可以使用 HomeSpan 轻松访问该功能。在之前的
// 所有示例中，我们使用 ESP32 来控制本地设备 - 直接连接到 ESP32 设备的设备。然后我们看到了如何通过 HomeKit 的 iOS 或 MacOS 
//  Home App 或通过添加直接连接的本地按钮来控制设备到 ESP32 设备。
// 在这个例子中，我们做相反的事情，并使用 ESP32 上的按钮来控制其他 HomeKit 设备。
// 为此，我们使用 HomeKit 的 Stateless Programmable Switch Service。与其他只读服务（例如示例 12 中充分探讨的温度和空气质量传感器）
 // 类似，Stateless Programmable Switch Service 仅侦听来自 HomeSpan 的事件通知，而不侦听来自 HomeSpan 的事件通知。尝试控制或更新
 // HomeSpan 设备上的任何内容。更具体地说，无状态可编程开关服务侦听来自 HomeSpan 的 SINGLE、DOUBLE 或 LONG 按钮按下的通知。
// 这些按钮按下的含义是不受 HomeSpan 控制的。相反，您可以直接在 Home 应用程序中对其操作进行编程。以这种方式，HomeSpan 成为通用按钮
//  的平台，您可以通过编程来控制任何其他 HomeKit 配件，甚至触发 HomeKit 场景.
// 运行此配置并与 HomeKit 配对后，您的 Home App 应该会显示一个标有“PushButton Switches”的新图块。单击该图块将打开一个新页面，您可
 // 以在其中对每个按钮的操作进行编程。这些操作可以在无需修改 HomeSpan 代码，甚至重启设备。
  
 //代码非常简单，像往常一样，我们将所有功能封装在一个独立文件中：DEV_ProgButton.h。下面我们创建两个通用按钮，一个连接到引脚 23，一
  //个连接到引脚 5。参见 DEV_ProgButton。 h 了解完整的详细信息。
  
  Serial.begin(115200);

  homeSpan.begin(Category::Bridges,"HomeSpan Bridge");

  new SpanAccessory();  
    new Service::AccessoryInformation();
      new Characteristic::Identify();

  new SpanAccessory();                                                          
    new Service::AccessoryInformation();
      new Characteristic::Identify(); 
      new Characteristic::Name("PushButton Switches");

    // // 我们编写了 DEV_ProgButton 来接受两个参数。 第一个是 DEV_ProgButton.h 用于创建 SpanButton 的 pin 号。 第二个是 HomeKit 在编写 Home App 中每个按钮的操作时用作标签的索引号。 这些数字不必是连续的，也不必以 1 开头。它们只需要是唯一的，以便 HomeKit 可以区分它们。 请注意，如果您在任何给定附件中只有一个无状态可编程开关服务，则 HomeKit 不需要索引号。 由于我们有两个，我们必须指定两个唯一的索引号。
    
    new DEV_ProgButton(23,1);       // 在引脚 23 上创建无状态可编程开关服务，索引 = 1
    new DEV_ProgButton(5,2);        // 在引脚 5 上创建无状态可编程开关服务，索引 = 2
 
} // end of setup()

//////////////////////////////////////

void loop(){
  
  homeSpan.poll();
  
} // end of loop()
