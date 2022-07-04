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
// Example 4: 带可调光吸顶灯的变速吊扇                     //
//                                                        //
////////////////////////////////////////////////////////////


#include "HomeSpan.h"         // 始终从包含 HomeSpan 库开始

void setup() {

// 示例 4 通过添加特性来设置风扇速度、风扇方向和亮度，扩展了示例 3 中的第一个附件。
// 为了便于阅读，所有先前的评论都已被删除，并添加了新的评论以显示与上一个示例的显式更改。
 
  Serial.begin(115200); 

  homeSpan.begin(Category::Fans,"HomeSpan Ceiling Fan");  

  new SpanAccessory();                            
  
    new Service::AccessoryInformation();                
      new Characteristic::Identify();                        

    new Service::LightBulb();                      
      new Characteristic::On(true);            //新：提供参数设置其初始值。 在这种情况下，这意味着灯泡将在启动时打开

    // 除了设置特性的初始值外，还可以覆盖 HAP 指定的默认最小/最大/步长范围。
    // 我们使用 setRange() 方法来做到这一点：
    
    // setRange(min, max, step), where
    //
    // min = minimum allowed value
    // max = maximum allowed value
    // step = step size (可以留空，在这种情况下保留 HAP 默认值)

    // 可以在任何支持范围覆盖的基于数字的特征上调用 setRange() 方法。 应用于方法的最简单方法是正确调用它
    // 在实例化一个新特性之后。 以这种方式链接方法时，不要忘记将“new”命令括在括号中。
    
    // 这里我们创建一个 Brightness Characteristic 来设置 LightBulb 的亮度，初始值为 50% 和一个允许范围
    // 从 20-100% 以 5% 为步长。 有关详细信息，请参阅下面的注释 1 和 2：
 
      (new Characteristic::Brightness(50))->setRange(20,100,5);    

    new Service::Fan();                             
      new Characteristic::Active();             
      new Characteristic::RotationDirection();                        // 新：这允许控制风扇的旋转方向
      (new Characteristic::RotationSpeed(50))->setRange(0,100,25);    // 新：这允许控制风扇的转速，初始值为 50%，范围为 0-100，步长为 25%

  // 注意 1：将亮度特性的初始值设置为 50% 本身不会导致 HomeKit 在启动时将灯打开到 50%。
  // 相反，这由 On Characteristic 的初始值控制，在这种情况下恰好设置为 true。 如果它设置为 false 或
  //  未指定（默认为 false），则灯泡将在启动时关闭。 但是，第一次打开它就会跳到50%的亮度。 同样的
  //  逻辑适用于风扇的 Active 和 RotationSpeed 特性。

  // 注 2：支持值范围的特性的默认范围在 HAP 第 9 节中指定。对于亮度，范围默认为 min=0%，max=100%，step=1%。
  // 使用 setRange() 将最小亮度从 0% 更改为 20%（或任何非零值）可提供更好的 HomeKit 体验。 这是因为灯泡的功率是
  //  由 On Characteristic 控制的，并且允许 Brightness 低至 0% 有时会导致 HomeKit 打开灯泡但 Brightness=0%，
  //  这不是很直观。 当要求 Siri 一直降低亮度，然后打开灯泡时，可能会发生这种情况。 通过将最小值设置为 20%，
 //   HomeKit 始终确保灯泡打开时有一些亮度值。

} // end of setup()

//////////////////////////////////////

void loop(){
  
  homeSpan.poll();         // run HomeSpan!
  
} // end of loop()
