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
// Example 17: Linked Services                            //
//             * implementing a multi-head Spa Shower     //
//                                                        //
////////////////////////////////////////////////////////////

//// 警告：此示例在 IOS 15.2 或 IOS 15.3 更新的某个地方停止正常工作，并且在 IOS 15.4.1 中无法正常工作，问题似乎在于
//家庭应用程序界面中单个阀门的渲染。 它们出现在 EVE HOMEKIT 应用程序中，但没有出现在 Apple 的 HOME 应用程序中。

#include "HomeSpan.h" 

  // HAP 通常将在同一附件中创建的多个服务视为彼此独立。 但是，某些 HAP 服务旨在代表对其他更典型服务的中央控制点。 
//例如，您可以创建一个具有一个或多个 Valve 服务的附件，每个服务独立运行。 但 HAP 还包括一个水龙头服务，可用于“控制”
//一个或多个阀门服务。 这是通过将水龙头服务链接到一个或多个 Valve 服务来完成的。
   // 只有少数类型的 HAP 服务允许/要求与其他服务建立链接，并且只能选择少数类型的服务作为链接。
  //可以使用 addLink() 方法在 HomeSpan 中创建链接服务。 例如，如果 spaShower 是指向水龙头服务的指针，而 ShowerHead 
  //和 handSprayer 都是指向阀门服务的指针，您可以将水龙头链接到阀门，如下所示：
  //
  //   spaShower->addLink(showerHead);
  //   spaShower->addLink(handSprayer);
  //
  //addLink 方法返回一个指向调用它的对象的指针，它为您提供了将上述两种方法组合成一行的选项，如下所示：
  //
  //   spaShower->addLink(showerHead)->addLink(handSprayer);

  // 请注意，HAP *不*提供“控制”服务操作“链接”服务所需的任何实际逻辑。这仍然必须由用户编程。更重要的是，逻辑需要符合 HAP 期望的服务行为，
//如控制服务的 HAP 文档中概述的那样。HAP 对链接服务真正做的唯一事情，除了让您做额外的工作之外，就是提供一个定制的 Tile向您显示控制
//服务及其链接的服务。
//
// 同样如上所述，只有少数服务支持链接服务协议。如果您对不支持链接的服务使用 addLink() 方法，HAP 将简单地忽略链接请求。但反之则不然。
// 如果您实现需要其他链接服务（例如水龙头）的服务，您必须创建这些链接才能使服务正常运行。
// 下面的示例 17 通过使用一个 HAP 水龙头服务和多个 HAP 阀门服务实现多头水疗淋浴来演示链接服务。像往常一样，我们将从 HAP 的水龙头和
// 阀门服务创建我们自己的“子”服务，以便我们可以添加所需的逻辑来实现我们的设备。但是，我们没有将所有逻辑放在单独的 *.h 文件中，而是
// 将它们直接包含在主草图文件（如下）中，以说明组织草图代码的另一种方法。
//
 //这个例子进一步说明了另一种编码风格选项：我们不实例化草图的 setup() 部分所需的所有服务，而是只实例化淋浴服务，并让淋浴服务本身实
 //例化所有阀门服务。事实上，我们的价值服务的整个定义完全封装在淋浴服务的定义中。
//
 //这有望为 HomeSpan 的灵活性提供一个很好的例子。因为所有 HomeSpan 组件都是使用标准 C++ 结构定义的（而不是基于某些预定义格式的外部
 //文件），所以您可以选择您喜欢的任何编码样式。样式之所以选择下面是因为它似乎很适合说明链接服务的工作方式。但请注意，只有 addLink()
 //方法创建了实际的链接。WaterValve 服务在 Shower Service 中定义的事实纯粹是一种样式选择，它本身并不创建链接。我们可以使用独立的结
 //构WaterValve 的定义和结果将是相同的。

//////////////////////////////////////

  // HAP 阀门服务需要激活特性和使用中特性。激活特性控制阀门是打开（激活）还是关闭（非激活）。此特性通常由用户通过主页应用程序控制。
//使用中特性指定是否实际上有水（或气体等）流过阀门。这是因为打开阀门并不一定意味着水会流动。可能还有另一个现实世界的“主”阀门也需要
//在水开始之前打开流动。或者可能有另一个服务也必须处于活动状态才能使水流过阀门。因此，如果阀门打开，InUse 可以为真或假，但只有在阀
//门关闭时它才能为假。 Home App 无法更改 InUse Characteristic。它仅由 Home App 作为状态读取。
//可以创建一个多阀门附件，其中每个阀门都独立于 Home 应用程序进行控制，HomeSpan 使用内部逻辑根据打开或关闭的阀门组合确定哪些阀门有水
//流动 (InUse=true)而哪些没有（InUse=false）。
//HAP 水龙头服务用于为与其链接的所有阀门创建一个“中央控制开关”。主页应用程序在水龙头的控制页面上将每个阀门显示为一个小图标。单击阀
//门图标可切换它的打开/关闭，以及相应地更改图标。但是，除非淋浴控制开关本身也打开，否则水不应该流动。因此，您需要编码以实现 HAP 水
//龙头的逻辑是仅在以下情况下将阀门的 InUse Characteristic 设置为 true阀门打开并且淋浴器打开。如果淋浴器随后关闭，阀门保持打开状态
//，但使用中特性需要重置为假。同样，如果淋浴器重新打开，每个阀门的使用中特性是open 需要设置为 true。这模仿了带有中央控制开关的实际
//淋浴器的操作方式。
//此外，当您操作淋浴和阀门控件时，家庭应用程序会显示 4 条状态消息之一：
//关闭：淋浴开关关闭，每个阀门的使用中特性设置为假（任何地方都没有水流）；停止：淋浴开关关闭，但至少有一个阀门的使用中特性设置为真。
//大概这表示阀门正在关闭；STARTING：淋浴开关打开，但每个阀门的 InUse Characteristic 设置为 FALSE。这表示淋浴正在等待水开始流动；
//RUNNING：淋浴开关打开, 并且至少有一个阀门的 InUse Characteristic 设置为 TRUE。这表明水在流动。
//请注意，淋浴服务仅监控其连接阀门的使用中特性。它不监视链接阀门的活动特性。此外，打开和关闭淋浴开关不应更改任何阀门的活动特性。
//以下是实现所有这些 HAP 所需逻辑的代码：
  
struct Shower : Service::Faucet {                 // 这是我们的 Shower 结构，我们将其定义为 HomeSpan Faucet 结构的子类

  SpanCharacteristic *active=new Characteristic::Active();      //我们的实现只需要 Active Characteristic

  Shower(int nHeads){                  // 这是淋浴的构造函数。 它需要一个参数来指定喷头的数量（WaterValve）
    for(int i=0;i<nHeads;i++)             //对于每个需要的喷头 ---
      addLink(new WaterValve(this,i+1));  // --- 实例化一个新的 WaterValve 并将其链接到淋浴器。 此外，将 Shower 对象的指针传递给 WaterValve 构造函数。 我们将在下面看到原因。
  }
  
  struct WaterValve : Service::Valve {                            // 在这里，我们将 WaterValve 结构定义为 HomeSpan Valve Service 的子类
    SpanCharacteristic *active=new Characteristic::Active(1);;     // 活动特性用于指定阀门是活动（打开）还是非活动（关闭）
    SpanCharacteristic *inUse=new Characteristic::InUse();        //InUser Characteristic 用于指定水是否实际流过值
    Shower *shower;                                               // 存储指向“控制”淋浴服务的指针
   
    WaterValve(Shower *s, int i){                             // this is constructor for WaterValve.  It takes a single argument that points to the "controlling" Shower Service
      shower=s;                                                   // store the pointer to the Shower Service
      new Characteristic::ValveType(2);                           // specify the Value Type (2=Shower Head; see HAP R2 for other choices)
    }
    
    boolean update() override {                                   // HomeSpan calls this whenever the Home App requests a change in a Valve's Active Characteristic
      if(shower->active->getVal())                                // here's where we use the pointer to Shower: ONLY if the Shower object itself is active---
        inUse->setVal(active->getNewVal());                       // --- do we update the InUse Characteristic to reflect a change in the status of flowing water.
      return(true);                                               // Note that the Valve itself will still change from Active to Inactive (or vice versa) regardless of the status of the Shower
    }
    
    void loop() override {                                                    // Here we check if the Shower is turned on or off, and determine if that means we need to update the Valve
      if(shower->active->getVal() && active->getVal() && !inUse->getVal())    // If the Shower is Active, and the Valve is Active, but InUse is NOT Active...
        inUse->setVal(1);                                                     // ...set the InUse Characteristic to Active
      else if(!shower->active->getVal() && inUse->getVal())                   // Otherwise, if the Shower is NOT Active but InUse is Active...
        inUse->setVal(0);                                                     // ...set the InUse Characteristic to NOT Active
    }

  }; // WaterValve
};

//////////////////////////////////////

void setup() {

  Serial.begin(115200);
  
  homeSpan.begin(Category::ShowerSystems,"HomeSpan Shower");

  new SpanAccessory();  
    new Service::AccessoryInformation();
      new Characteristic::Identify();                    
    
    new Shower(4);                                          // Create a Spa Shower with 4 spray heads

} // end of setup()

//////////////////////////////////////

void loop(){
  
  homeSpan.poll();
  
} // end of loop()

//////////////////////////////////////
