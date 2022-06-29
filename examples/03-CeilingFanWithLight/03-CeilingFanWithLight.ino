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
// Example 3: A simple on/off ceiling fan with an         //
//            on/off ceiling light                        //
//                                                        //
////////////////////////////////////////////////////////////


#include "HomeSpan.h"         // 始终从包含 HomeSpan 库开始

void setup() {

  // 示例 3 展示了如何将多个服务添加到单个配件中，从而使我们能够创建多功能配件，例如带有吸顶灯的吊扇
 
  Serial.begin(115200);      // 启动串行连接 - 您需要输入您的 WiFi 凭据

  homeSpan.begin(Category::Fans,"HomeSpan Ceiling Fan");  // 初始化 HomeSpan - 注意 Category 已设置为“Fans”

  //我们首先创建一个灯泡附件，就像示例 1 和 2 中一样

  new SpanAccessory();                              // 首先使用 SpanAccessory() 创建一个新的附件，不需要任何参数
  
    new Service::AccessoryInformation();            // HAP 要求每个附件都实施具有所需识别特征的附件信息服务

    new Service::LightBulb();                       // 创建灯泡服务
      new Characteristic::On();                       // 此服务需要“开”字符来打开和关闭灯

  //现在我们在同一个附件中添加一个风扇服务

    new Service::Fan();                             // 创建粉丝服务
      new Characteristic::Active();                   // 此服务需要“活动”角色来打开和关闭风扇

 // 与示例 2 类似，我们还将实现一个灯泡作为第二个附件

  new SpanAccessory();                              // 首先使用 SpanAccessory() 创建一个新的附件，不需要任何参数
    new Service::AccessoryInformation();            // HAP 要求每个附件都实施具有所需识别特征的附件信息服务
      new Characteristic::Identify();                 // 创建所需的标识

    new Service::LightBulb();                       // 创建灯泡服务
      new Characteristic::On();                       // 此服务需要“一个”特性来打开和关闭灯 

  // 如果一切正常，您现在应该在 Home App 中看到两个 Tiles：
  // 
  //  * 一个名为“HomeSpan Ceiling Fan”的瓷砖，带有风扇图标。
  //    单击此 Tile 应打开控制页面，左侧显示 Fan 控件，右侧显示 Light 控件
  //
  //  * 一个名为“HomeSpan Ceiling Fan 2”的瓷砖，
  //   带有一个灯泡图标。 单击此 Tile 应切换 Light On/Off
  
  //在这个例子中加入第二个灯泡配件的原因是为了说明设备的类别对各种图标的影响。
  // 在 homeSpan.begin() 中将 Category 设置为 Fan 有两个目的。 首先，它将设备本身的图标
  //（如 Home App 在初始配对期间显示的那样）设置为风扇。 其次，当存在歧义时，它可以帮助
  //  Home App 确定用于 Accessory Tile 的图标。 第二个附件只包含一个灯泡服务，因此家庭应
  //  用程序明智地使用灯泡图标作为磁贴。 但是 Home App 应该为第一个包含风扇服务和灯泡服务
  //  的附件使用什么图标？ 风扇或灯泡图标都有意义。 将设备的类别设置为风扇会导致 Home App 
  //  为第一个附件选择风扇图标。
  
  // 作为对此的测试，取消配对设备； 将类别更改为照明（如示例 2 所示）； 重新加载草图； 
  // 并重新配对设备。 您现在应该看到“HomeSpan Ceiling Fan”瓷砖的图标是一个灯泡，附件的控制屏幕
  //  应该在左侧显示 Light 控件，在右侧显示 Fan 控件。

  // 重要提示：HomeKit 控制器通常会缓存大量信息。 如果您的控制器未更新以匹配上述配置，
  //  只需在控制器中选择附件，然后在设置下选择“删除附件”，但在重新配对设备之前，
  //   在 HomeSpan CLI 中键入“H”。 这会强制 HomeSpan 重新启动并生成一个新的设备 ID，
  //   以便在您重新配对时它在 Home 应用程序中看起来“全新”。

} // end of setup()

//////////////////////////////////////

void loop(){
  
  homeSpan.poll();         // run HomeSpan!
  
} // end of loop()
