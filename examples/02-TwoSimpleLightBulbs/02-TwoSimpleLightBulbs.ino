/*********************************************************************************
 *  MIT License
 *  
 *  Copyright (c) 2020-2022 Gregg E. Berman
 *  
 *  https://github.com/HomeSpan/HomeSpan
 
 *  特此免费授予任何获得本软件和相关文档文件（“软
 *  件”）副本的人，以不受限制地处理本软件，包括但不
 *  限于使用、复制、修改、合并的权利 、发布、分发、
 *  再许可和/或出售本软件的副本，并允许向其提供本
 *  软件的人这样做，但须符合以下条件：
 *  
 *  上述版权声明和本许可声明应包含在本软件的所有副
 *  本或大部分内容中。
 
 *  本软件按“原样”提供，不提供任何形式的明示或暗示
 *  保证，包括但不限于适销性、特定用途适用性和非侵
 *  权保证。 在任何情况下，作者或版权持有人均不对任
 *  何索赔、损害或其他责任承担任何责任，无论是在合
 *  同诉讼、侵权行为或其他方面，由本软件或本软件的
 *  使用或其他交易引起或与之相关软件。
 *  
 ********************************************************************************/
 
////////////////////////////////////////////////////////////
//                                                        //
//    HomeSpan: A HomeKit implementation for the ESP32    //
//    ------------------------------------------------    //
//                                                        //
// Example 2: 两个不起作用的开/关灯泡                      //
//           由基本的 HomeSpan 组件构成                    //
//                                                        //
////////////////////////////////////////////////////////////


#include "HomeSpan.h"         // 始终从包含 HomeSpan 库开始

void setup() {

  // 示例 2 通过实现两个灯泡来扩展示例 1，每个灯泡都作为自己的附件
 
  Serial.begin(115200);

  homeSpan.begin(Category::Lighting,"HomeSpan LightBulb");   // 初始化一个名为“HomeSpan Lightbulb”的 HomeSpan 设备，其中 Category 设置为 Lighting

  // 在这里，我们创建第一个灯泡附件，就像在示例 1 中一样

  new SpanAccessory();                              // 首先使用 SpanAccessory() 创建一个新的附件，不需要任何参数
  
    new Service::AccessoryInformation();            // HAP 要求每个附件都实施具有所需识别特征的附件信息服务
      new Characteristic::Identify();                 // 创建所需的标识

    new Service::LightBulb();                       // 创建灯泡服务
      new Characteristic::On();                       // 此服务需要“开”字符来打开和关闭灯

  // 现在我们创建第二个附件，它只是第一个附件的副本

  new SpanAccessory();                              // 首先使用 SpanAccessory() 创建一个新的附件，不需要任何参数
  
    new Service::AccessoryInformation();            // HAP 要求每个附件都实施具有所需识别特征的附件信息服务
      new Characteristic::Identify();                 // 创建所需的标识

    new Service::LightBulb();                       // 创建灯泡服务
      new Characteristic::On();                       // 此服务需要“开”字符来打开和关闭灯

  // 就是这样 - 我们的设备现在有两个配件，每个配件都在 Home 应用程序中显示为单独的 Tile！

  // 请注意，对于具有多个附件的设备，家庭应用程序会根据 homeSpan.begin() 中指定的名称为每个附件拼
  // 贴生成一个默认名称。 在这种情况下，第一个 Accessory Tile 的默认名称将是“HomeSpan
  // Lightbulb”，就像在示例 1 中一样，第二个 Accessory Tile 的默认名称将是“HomeSpan Lightbulb 2”。

// 您当然可以在配对期间 Home App 提示时从这些默认值更改每个 Accessory Tile 的名称。 你
   // 也可以通过打开设置页面直接从 Home App 更改任何 Accessory Tile 的名称，即使在配对之后
   // 对于任何给定的 Tile。

   // 在示例 7 中，我们将演示如何在 HomeSpan 草图中更改默认名称。

   // 重要提示：当从示例 1 移动到示例 2 时，您不必将设备与 HomeKit 重新配对。HomeSpan 会注意到
   // 属性数据库已经更新，程序重启时会广播一个新的配置号。 这应该
   // 使所有 iOS 和 MacOS HomeKit 控制器自动更新并反映上面的新配置。
} // end of setup()

//////////////////////////////////////

void loop(){
  
  homeSpan.poll();         // run HomeSpan!
  
} // end of loop()
