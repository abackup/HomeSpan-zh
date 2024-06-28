////////////////////////////////////////////////////////////
//                                                        //
//              HomeSpan：ESP32 的 HomeKit 实现           //
//    ------------------------------------------------    //
//                                                        //
//         示例 6：一个可工作的开/关 LED 和一个可工作       // 
//                的可调光 LED，均基于 LightBulb 服务      //
//                                                        //
//                                                        //
////////////////////////////////////////////////////////////


#include "HomeSpan.h" 
#include "DEV_LED.h"          

void setup() {

  // 示例 6 更改了示例 5，使 LED #2 现在是可调光的，而不仅仅是开/关。这要求我们创建一个新的派生服务，我们将命名为“DEV_DimmableLED”。
  // 我们不会创建新文件来存储此定义，而是将其添加到 DEV_LED.h 文件的末尾，该文件包含我们在示例 5 中创建的用于控制开/关 LED 的代码。
  // 将类似风格的服务分组到一个“.h”文件中可以更轻松地组织您的自定义设备。

  // 与往常一样，所有以前的评论都已删除，仅显示上一个示例中的新更改。

  // 注意：Arduino/ESP32 代码库不包含通常用于创建 PWM 输出以驱动 LED 亮度的 analogWrite() 函数。相反，ESP32 代码库本身包含一组用于
  // 创建 PWM 输出的函数，ESP32 芯片具有专门用于此目的的内置 PWM 功能。

  // HomeSpan 将所有这些 PWM 功能封装到一个名为 LedPin 的集成类中，这样就可以非常轻松地定义可调光 LED 引脚并将 PWM 级别（即占空比）
  // 设置为 0-100%。DEV_DimmableLED 中显示了此 LedPin 类的使用。
  
  Serial.begin(115200);

  homeSpan.begin(Category::Lighting,"HomeSpan LED");
  
  new SpanAccessory(); 
  
    new Service::AccessoryInformation(); 
      new Characteristic::Identify();                

    new DEV_LED(16);                // 创建一个连接到引脚 16 的开/关 LED（与示例 5 相同）

  new SpanAccessory(); 
  
    new Service::AccessoryInformation();    
      new Characteristic::Identify();                       
  
    new DEV_DimmableLED(17);        // 新！创建一个连接到引脚 17 的可调光（PWM 驱动）LED。请参阅 DEV_LED.h 末尾的新代码

} // setup() 结束

//////////////////////////////////////

void loop(){
  
  homeSpan.poll();
  
} // loop() 结束
