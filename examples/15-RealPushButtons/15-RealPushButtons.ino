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
// Example 15: Real PushButtons                           //
//             * manually controlling a Dimmable LED      //
//                                                        //
//                                                        //
////////////////////////////////////////////////////////////

#include "HomeSpan.h" 
#include "DEV_LED.h"     

void setup() {

  // 在示例 14 中，我们看到了如何在 HomeKit 中模拟 PushButton tile，方法是自动重置 Characteristic，使其在短时间内“关闭”。然而，
 //有时我们希望能够使用实际的PushButtons（或瞬时开关）物理控制设备) 触发动作，例如打开电灯或风扇，或打开车库门。此外，我们希望 
//  HomeKit 反映此类手动操作导致的设备变化 - HomeKit 应该知道灯何时打开或手动关闭。
//一种方法是通过添加到派生服务的 loop() 方法中的自定义代码来监视按钮，检查按钮何时被按下，消除按钮噪音，在按下时执行一些操作，
//  并使用 setVal( ） 方法。或者您可以使用 HomeSpan 的内置 SpanButton() 对象。
//SpanButton() 是一个服务级对象，这意味着它将自己附加到您定义的最后一个服务。通常，您将直接在派生服务的构造函数中实例化多个 
 //            SpanButton() 对象。
//SpanButton() 支持三种类型的触发器：单次按钮按下、双次按下和长（扩展）按下。
//触发这些不同类型所需的按下的长度可以由 SpanButton() 的可选参数指定。由于大多数按钮在按下时会产生虚假噪音（然后在释放时再次产
  //           生），触发 SINGLE 按下的默认时间是 5ms。可以将其更改为更长的值，但不建议使用更短的值，因为这可能会允许虚假触发，
 //            除非您使用硬件对开关进行去抖动。
//SpanButton() 构造函数接受 4 个参数，顺序如下：pin - PushButton 连接到的 pin 号（必需）longTime - 按钮需要按下的最小时间长度
 //            （以毫秒为单位）才能被视为 LONG press (optional; default=2000 ms)singleTime- 最小时间长度（以毫秒为单位） 需要
  //           按下按钮才能被视为 SINGLE press（可选；默认值=5 ms）doubleTime- 最大时间长度（以毫秒为单位） ) 在两次按下按钮之
  //间创建两次按下（可选；默认值 = 200 毫秒）
//当 SpanButton() 被实例化时，它将 ESP32 上的指定引脚设置为带 PULL-UP 的 INPUT，这意味着该引脚在读取时通常会返回 HIGH 值。应连
 // 接实际的 PushButton，以便该引脚接地按下按钮时。
//HomeSpan 自动轮询所有具有关联 SpanButton() 对象的引脚并检查 LOW 值，这表明按钮被按下，但尚未释放。然后它启动一个计时器。如果
//  按钮在被按下少于 singleTime 毫秒后被释放，则没有任何反应.如果按钮被按下超过 singleTime 毫秒后释放，但小于 longTime 毫秒，
//  则触发 SINGLE 按下，除非您在 doubleTime 毫秒内再次按下以触发 DOUBLE 按下。如果按住按钮超过 longTime毫秒而不被释放，触发长按
 //。一旦触发长按，计时器就会重置，因此如果您按住按钮，另一个长按将在另一个 longTime 毫秒内触发。这将一直持续到您最终释放按钮。
  
//请注意，如果您设置 longTime > singleTime，SpanButton() 将仅触发 LONG 按下。此外，如果您将 doubleTime 设置为零，SpanButton() 
//  将无法触发 DOUBLE 按下。
//要在派生服务中使用 SpanButton()，您需要实现 button() 方法。与 loop() 方法类似，您的 button() 方法通常包含 getVal() 函数和 
//  setVal() 函数的某种组合，以及在物理设备上执行一些操作的代码（将引脚设置为高或低，打开风扇等）。但是，与 HomeSpan 每个轮询周
 // 期调用的 loop() 方法相比，HomeSpan 只调用 button()当附加到服务的按钮注册为单次、双次或长按时的方法。
 //同样与循环方法相比，button() 方法采用两个“int”参数，应定义如下：void button(int pin, int pressType)其中“pin”是被触发的
 // PushButton 的 pin 号，并且 pressType 设置为 0 表示单次按下，1 表示双击，2 表示长按。您还可以使用预定义的常量 SpanButton::
  //SINGLE、SpanButton::DOUBLE 和 SpanButton::LONG 代替数字 0、1 和 2（这是推荐的，尽管您将在示例 16 中看到为什么这些整数不能
  //被 C++ 枚举类替换）。
//当然你可以用你自己的名字替换变量“pin”和“pressType”。唯一的要求是定义符合“void button(int, int)”签名。当HomeSpan第一次启动时，
 // 它会检查所有包含一个或更多 SpanButton() 实例以确保您已经实现了自己的 button(int, int) 方法。如果没有，HomeSpan 将在串行监视
//  器上打印一条警告消息。如果您实例化 SpanButton() 但忘记创建按钮（ ) 方法，或者您使用错误的参数创建它。但也没有什么好事 - 按钮
//  按下被忽略。C++ 注意：为了额外检查，您还可以在方法定义之后放置上下文关键字“override”：void button(int buttonPin, int pressType) 
//  override {.. .your code...}这样做可以让编译器检查您是否确实覆盖了基类 button() 方法，而不是无意中创建了一个带有错误签名的
//  newbutton() 方法，该方法永远不会被 SpanButton() 调用.事实上，您也可以在 update() 和 loop() 方法的定义中添加“覆盖”，因为它们
 // 总是应该覆盖基类方法。
//为了演示 SpanButtons 在实践中的工作原理，我们将从示例 11 中使用的相同 LED 代码开始实现一个可调光 LED，但使用 3 个 SpanButton() 
//  对象执行不同的功能，展示不同类型的按下。将响应单次按下切换电源，打开电源并将亮度设置为“最喜欢”级别以响应双击，并设置一个新的
//  “最喜欢”级别以响应长按。* A“提升亮度” SpanButton，它将在单次按下时增加 1% 的亮度，在长按时重复增加 10% 的亮度，并在双次按下时
 // 跳到最大亮度。*“较低的亮度" SpanButton 响应单次按下会降低 1% 的亮度，响应长按会重复降低 10% 的亮度，并会跳到最小亮度以响应双击。
//像往常一样，所有代码都在 DEV_LED.h 中实现，带有 NEW！注释突出了示例 11 中的更改。您还会注意到，我们已经扩展了此版本派生的可调光 
//  LED 服务的构造函数，以包括每个按钮的引脚号。有关详细信息，请参阅 DEV_LED.h。
  
  Serial.begin(115200);

  homeSpan.begin(Category::Bridges,"HomeSpan Bridge");

  new SpanAccessory();  
    new Service::AccessoryInformation();
      new Characteristic::Identify(); 

  new SpanAccessory();                                                          
    new Service::AccessoryInformation();
      new Characteristic::Identify(); 
      new Characteristic::Name("PushButton LED");
    
    new DEV_DimmableLED(17,23,5,18);          // 新的！ 添加了三个额外的参数来指定三个 SpanButtons() 的引脚号 - 请参阅 DEV_LED.h
 
} // end of setup()

//////////////////////////////////////

void loop(){
  
  homeSpan.poll();
  
} // end of loop()
