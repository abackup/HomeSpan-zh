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
// Example 11: Service Names:                             //
//             * setting the names of individual Services //
//             * changing the icons in a bridge Accessory //
//                                                        //
////////////////////////////////////////////////////////////

#include "HomeSpan.h" 

void setup() {

  // 如前面示例中所述，在配对设备时，Home App 将为每个 Accessory Tile 选择默认名称，除非您通过将 Name Characteristic
 //添加到每个 Accessory 的 Accessory Information Service（第一个除外，通常是桥接附件）。同样的过程也适用于具有多个服务
  //的附件中的服务名称，例如带灯的吊扇。配对时，Home App会根据所包含的Services类型为每个Service（如Fan、Fan 2、Light、
 // Light 2）选择默认名称。与Accessory Tiles的名称类似，您可以更改各个Services的名称在配对过程中出现提示时，或在从
//  Home App 的相应设置页面中配对后的任何时间。更重要的是，您可以通过简单地将 Name Characteristic 添加到任何 Service 
 // 来覆盖 Home App 生成的默认 Service 名称。但是，请注意，服务名称（无论是否被覆盖）仅在存在歧义的情况下才会出现在
 // Home App 中，例如具有相同类型的两个服务的 Accessory。但即使服务名称没有出现在 Home 中应用程序，Siri 仍将使用它通
//  过语音控制附件中的特定服务。在下面的示例中，我们创建了 5 个不同的功能附件，每个附件都说明了 Home 应用程序如何选择
//  名称和图标
  
  Serial.begin(115200);

  // 此设备将配置为网桥，类别设置为网桥

  homeSpan.begin(Category::Bridges,"HomeSpan Bridge");

  // Our first Accessory is the "Bridge" Accessory
  
  new SpanAccessory();  
    new Service::AccessoryInformation();
      new Characteristic::Identify(); 

  //我们的第一个配件是“桥”配件我们的第二个配件是单灯的吊扇。需要注意三点：* 配对时，Home App 会为这两个服务生成默认
 //名称“灯”和“风扇”。但是，这些名称不会显示在配件的控制屏幕上，因为灯光和风扇控件之间没有歧义 - 家庭应用程序以不同的
 // 方式显示它们*家庭应用程序用于配件瓷砖的图标是灯泡。为什么选择这个而不是风扇图标? 回想一下示例 3，对于具有多个服务
 // 的配件，如果使用哪个图标有任何歧义，Home App 会根据设备的类别进行选择。但是由于此设备配置为桥接器，因此类别没有提
 // 供任何有用的信息到 Home App。在这种情况下，Home App 为 Accessory Tile 选择一个图标，该图标与 Accessory 中的第一个
//  功能服务相匹配，在这种情况下，在 LightBulb* 中，当通过单击 Accessory Tile 打开控制屏幕时，LightB ulb控件出现在左
//  侧，Fan控件出现在右侧
  
  new SpanAccessory();  
    new Service::AccessoryInformation();
      new Characteristic::Identify(); 
      new Characteristic::Name("Light with Fan");            // this sets the name of the Accessory Tile
    new Service::LightBulb();                                // the icon of the Accessory Tile will be a Lightbulb, since this is the first functional Service
      new Characteristic::On();
    new Service::Fan();                             
      new Characteristic::Active();

  // 我们的第三个附件与第二个相同，只是我们交换了灯泡和风扇服务的顺序。结果是 Home 应用程序现在显示带有风扇图标而不
 //是灯泡图标的 Accessory Tile。此外，当通过单击附件磁贴打开控制屏幕时，风扇控件现在将出现在左侧，而灯泡控件将出现在右侧。
      
  new SpanAccessory();  
    new Service::AccessoryInformation();
      new Characteristic::Identify(); 
      new Characteristic::Name("Fan with Light");            // this sets the name of the Accessory Tile
    new Service::Fan();                                      // the icon of the Accessory Tile will be a Fan, since this is the first functional Service
      new Characteristic::Active();      
    new Service::LightBulb();                             
      new Characteristic::On();

  // 我们的第四个附件展示了如果我们实现两个相同的灯泡服务（没有任何风扇服务）会发生什么。由于这两个服务都是灯泡，
 //所以 Home App 会明智地为 Accessory Tile 选择一个灯泡图标。但是，当您单击 Accessory Tile 并打开控制屏幕时，您会
//  注意到 Home App 现在确实在下方显示了 Service 的名称每个控件。在这种情况下，Home App 使用默认名称“Light 1”和
 // “Light 2”。Home App 可能会显示每个 Service 的名称，因为这两个控件是相同的，否则无法判断哪个控件在运行哪个灯。
  
  new SpanAccessory();  
    new Service::AccessoryInformation();
      new Characteristic::Identify(); 
      new Characteristic::Name("Ceiling Lights");            // this sets the name of the Accessory Tile
    new Service::LightBulb();                             
      new Characteristic::On();      
    new Service::LightBulb();                             
      new Characteristic::On();

  // 我们的第五个附件将单个风扇服务与两个相同的灯泡服务组合在一起。由于实现的第一个功能服务是风扇，主页应用程序将为附件
 //图块选择一个风扇图标。此外，由于我们向两个灯泡服务添加了名称特征，它们的Home App 生成的默认名称（“Light 1”和“Light 2”）
//  将更改为指定的名称。最后，请注意 Home App 在控制屏幕上显示更紧凑的控件形式，因为存在三个服务。控件的排列和样式将取决于
 // 为每个服务实施的特征组合。
      
  new SpanAccessory();  
    new Service::AccessoryInformation();
      new Characteristic::Identify(); 
      new Characteristic::Name("Fan with Lights");           // this sets the name of the Accessory Tile
    new Service::Fan();                             
      new Characteristic::Active();      
    new Service::LightBulb();                             
      new Characteristic::Name("Main Light");                // this changes the default name of this LightBulb Service from "Light 1" to "Main Light"
      new Characteristic::On();
    new Service::LightBulb();                             
      new Characteristic::Name("Night Light");               // this changes the default name of this LightBulb Service from "Light 2" to "Night Light"
      new Characteristic::On();

  // 我们的第六个附件与第五个类似，只是我们为某些服务添加了更多功能。注意这如何改变控制屏幕上控件的布局。
  
  new SpanAccessory();  
    new Service::AccessoryInformation();
      new Characteristic::Identify(); 
      new Characteristic::Name("Multi-Function Fan");           
    new Service::Fan();                             
      new Characteristic::Active();   
      new Characteristic::RotationDirection();               // add a control to change the direcion of rotation
      new Characteristic::RotationSpeed(0);                  // add a control to set the rotation speed
    new Service::LightBulb();                             
      new Characteristic::Name("Main Light");                
      new Characteristic::On();
      new Characteristic::Brightness(100);                   // make this light dimmable (with intitial value set to 100%)
    new Service::LightBulb();                             
      new Characteristic::Name("Night Light");               // don't add anything new to this light               
      new Characteristic::On();

} // end of setup()

//////////////////////////////////////

void loop(){
  
  homeSpan.poll();
  
} // end of loop()
