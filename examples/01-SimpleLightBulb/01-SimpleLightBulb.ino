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
// Example 1: A non-functioning on/off light control      //
//            constructed from basic HomeSpan components  //
//                                                        //
////////////////////////////////////////////////////////////


  // 欢迎来到HOMESPAN!
  
  // 第一个示例介绍 HomeSpan 库并演示如何实现简单的开/关灯控制
  // 使用 HomeSpan Accessory、Service 和 Characteristic 对象的组合。上传此草图后
  // 到您的 HomeSpan 设备并且该设备已与您的家配对，一个新的“灯泡”图块将出现在您 iPhone 的 Home 应用程序中，
  // iPad 或 Mac。
  
  // 虽然图块将完全可操作（即您可以将灯泡的状态从“开”或“关”更改），但我们还没有连接
  // HomeSpan 设备的实际灯或 LED，因此没有任何实际的东西会亮起。相反，在这个和接下来的几个例子中，我们将关注
  // 了解配置 HomeKit 控件的不同方式。从示例 5 开始，我们将 LED 连接到设备
  // 并介绍在您的 Home App 中实际打开和关闭 LED 的方法。

  // 注意：与 HomeSpan GitHub 页面上提供的文档一起查看时，所有 HomeSpan 示例都可以得到最好的理解。
  // 有关详细信息和参考，请参阅 https://github.com/HomeSpan/HomeSpan。特别是，您可能需要查看 HomeSpan API 概述
  // 继续之前的页面。
  
  // 这些示例还经常引用 Apple 的 HomeKit 附件协议规范，即 HAP。你可以下载这个
  // 直接来自 Apple，网址为 https://developer.apple.com/support/homekit-accessory-protocol。

  // 让我们开始吧...

#include "HomeSpan.h"         // HomeSpan 草图总是以包含 HomeSpan 库开始

void setup() {                // 您的 HomeSpan 代码应该放在标准的 Arduino setup() 函数中
 
  Serial.begin(115200);       // 启动串行连接，以便您可以接收 HomeSpan 诊断信息并使用 HomeSpan 的命令行界面 (CLI) 控制设备

  // HomeSpan 库创建一个名为“homeSpan”的全局对象，它封装了所有 HomeSpan 功能。
  // begin() 方法用于初始化 HomeSpan 并启动所有 HomeSpan 进程。
  
  // 前两个参数是Category和Name，HomeKit用来配置图标和名称
  // 最初将 HomeSpan 设备与 iPhone 配对时，Home App 中显示的设备的名称。
  
  // 此外，您在下面选择的名称将用作所有配件瓷砖的“默认名称”。当你第一次
  // 配对设备，Home App 将显示此默认名称并允许您更改它（对于每个 Accessory Tile）
  // 在配对完成之前。但是，即使在设备配对后，您也可以随时更改任何设备的名称
  // 通过任何 Tile 的设置屏幕直接从 Home App 中的 Accessory Tile。

  // 重要提示：您在下面选择的名称在您的所有 HomeSpan 设备中必须是唯一的！

  homeSpan.begin(Category::Lighting,"HomeSpan LightBulb");   // 初始化一个名为“HomeSpan Lightbulb”的 HomeSpan 设备，其中 Category 设置为 Lighting

  // 接下来，我们用单个 Accessory c 构建一个简单的 HAP Accessory Database
  // 每个都有自己需要的特性。
  
  new SpanAccessory();                              // 首先使用 SpanAccessory() 创建一个新的附件，不需要参数

    new Service::AccessoryInformation();            // HAP 要求每个 Accessory 实现一个 AccessoryInformation Service

  // 附件信息服务唯一需要的特性是特殊的识别特性。它不需要任何参数：
  
      new Characteristic::Identify();               // 创建所需的识别特征
      
  // 附件信息服务还包括这四个可选特征。它们不执行任何功能并且用于
  // 仅供参考 --- 它们的值显示在 HomeKit 的每个附件的设置面板中。随意
  // 取消注释这些行并实现它们的任意组合，或者根本没有。
                                                      
//      new Characteristic::Manufacturer("HomeSpan");   // 配件的制造商（任意文本字符串，每个配件都可以相同）
//      new Characteristic::SerialNumber("123-ABC");    // 配件序列号（任意字符串，每个配件都可以相同）
//      new Characteristic::Model("120-Volt Lamp");     // 配件型号（任意字符串，每个配件都可以相同）
//      new Characteristic::FirmwareRevision("0.9");    // 配件的固件（任意文本字符串，每个配件都可以相同）

  // *注意* HAP 要求附件信息服务始终在任何其他服务之前实例化，这就是我们首先创建它的原因。
  // 现在已经定义了所需的“信息”服务，我们终于可以创建我们的灯泡服务了

    new Service::LightBulb();                       // 创建灯泡服务
      new Characteristic::On();                       // 此服务需要“开”字符来打开和关闭灯

  // 这就是从头开始定义数据库所需的全部内容，包括所有必需的 HAP 元素，以控制单个灯泡。
  // 当然，这个草图还没有包含任何代码来实现灯的实际操作 - 没有什么可做的
  // 打开和关闭。但是您仍然会在您的家庭应用程序中看到一个灯泡图块，该图块可以打开和关闭它。

} // end of setup()

//////////////////////////////////////

void loop(){

  // 以上设置中的代码实现了附件属性数据库，但不执行任何操作。 HomeSpan 本身必须是
  // 不断轮询以查找来自控制器的请求，例如 iPhone 上的 Home App。下面的 poll() 方法就是这样
  // 需要在 loop() 的每次迭代中连续执行此操作
  
  homeSpan.poll();         // 运行 HomeSpan！
  
} // end of loop()

//恭喜！你已经创建了你的第一个 HomeSpan 草图，可以上传到你的 ESP32 板上并与 HomeKit 配对。
//
//
