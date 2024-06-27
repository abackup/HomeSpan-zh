////////////////////////////////////////////////////////////
//                                                        //
//              HomeSpan：ESP32 的 HomeKit 实现           //
//    ------------------------------------------------    //
//                                                        //
// 示例 2：由基本 HomeSpan 组件构成的两个不工作的开/关灯泡   //
//                                                        //
//                                                        //
////////////////////////////////////////////////////////////


#include "HomeSpan.h"        // 始终从包含 HomeSpan 库开始

void setup() {

  // 示例 2 在示例 1 的基础上进行了扩展，实现了两个灯泡，每个灯泡都是一个配件
 
  Serial.begin(115200);

  homeSpan.begin(Category::Lighting,"HomeSpan LightBulb");   // 初始化一个名为“HomeSpan Lightbulb”的 HomeSpan 设备，并将类别设置为照明

  // 在这里我们创建第一个灯泡配件，就像示例 1 一样

  new SpanAccessory();                              // 首先使用 SpanAccessory() 创建一个新的附件，不需要任何参数
  
    new Service::AccessoryInformation();            // HAP 要求每个配件都实现配件信息服务，并具有所需的识别特征
      new Characteristic::Identify();                 // 创建所需的标识

    new Service::LightBulb();                       // 创建灯泡服务
      new Characteristic::On();                       // 此服务需要“开启”特性来打开和关闭灯

  // 现在我们创建第二个附件，它只是第一个附件的副本

  new SpanAccessory();                              // 首先使用 SpanAccessory() 创建一个新的附件，不需要任何参数
  
    new Service::AccessoryInformation();            // HAP 要求每个配件都实现配件信息服务，并具备所需的识别特征
      new Characteristic::Identify();                 // 创建所需的标识  

    new Service::LightBulb();                       // 创建灯泡服务
      new Characteristic::On();                       // 此服务需要“On”特性来打开和关闭灯

  // 就是这样 - 我们的设备现在有两个配件，每个配件在 Home App 中显示为单独的 Tile！

  // 请注意，对于具有多个附件的设备，Home App 会根据 homeSpan.begin() 中指定的名称为每个附件 Tile 生成一个默认名称。
  // 在本例中，第一个附件 Tile 的默认名称将为“HomeSpan Lightbulb”（与示例 1 中一样），第二个附件 Tile 的默认名称
  // 将为“HomeSpan Lightbulb 2”。

  // 当然，在配对期间，当 Home App 提示时，您可以更改每个 Accessory Tile 的名称，使其不再是这些默认名称。
  // 即使在配对后，您也可以直接从 Home App 打开任何给定 Tile 的设置页面来更改任何 Accessory Tile 的名称。

  // 在示例 7 中，我们将演示如何在 HomeSpan 草图中更改默认名称。

  // 重要提示：从示例 1 移至示例 2 时，您无需重新将设备与 HomeKit 配对。HomeSpan 将注意到属性数据库已更新，
  // 并将在程序重新启动时广播新的配置编号。这应该会导致所有 iOS 和 MacOS HomeKit 控制器自动更新并反映上述新配置。
} // setup() 结束

//////////////////////////////////////

void loop(){
  
  homeSpan.poll();         // 运行 HomeSpan!
  
} // loop() 结束
