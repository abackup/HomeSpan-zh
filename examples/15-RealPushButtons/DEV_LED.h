
////////////////////////////////////
//   DEVICE-SPECIFIC LED SERVICES //
////////////////////////////////////

#include "extras/PwmPin.h"                          // 各种 PWM 函数库

////////////////////////////////////

struct DEV_DimmableLED : Service::LightBulb {       //可调光LED

  // 此版本的可调光 LED 服务类似于示例 11 中最后使用的版本，但现在包括对 3 个物理按钮的支持
   // 执行以下操作：
   //
   //电源按钮：短按切换电源开/关； 长按将当前亮度保存为喜欢的级别； 双击将亮度设置为最喜欢的水平
   // 升高按钮：短按增加 1% 的亮度； 长按亮度增加10%； 双击将亮度增加到最大
   // 下按钮：短按降低亮度 1%； 长按降低亮度10%； 双击将亮度降至最低
  
  LedPin *ledPin;                                   // 参考 LED 引脚
  int powerPin;                                     // 新的！ 带按钮的引脚可打开/关闭 LED
  int raisePin;                                     // 新的！ 带按钮的引脚以增加亮度
  int lowerPin;                                     // 新的！ 带按钮的引脚以降低亮度
  int channel;                                      // 此 LED 使用的 PWM 通道（每个 LED 应该是唯一的）
  SpanCharacteristic *power;                        // 引用 On 特性
  SpanCharacteristic *level;                        // 参考亮度特性
  int favoriteLevel=50;                             // 新的！ 跟踪“最喜欢”的关卡

  // 新的！ 构造函数包括 3 个额外的参数来指定电源、升高和降低按钮的引脚号
  
  DEV_DimmableLED(int pin, int powerPin, int raisePin, int lowerPin) : Service::LightBulb(){

    power=new Characteristic::On();     
                
    level=new Characteristic::Brightness(favoriteLevel);       // 亮度特性，初始值等于最喜欢的级别
    level->setRange(5,100,1);                                  // 将亮度的范围设置为从最小值 5% 到最大值 100%，步长为 1%
    
    //新的！ 下面我们创建三个 SpanButton() 对象。 首先，我们根据需要指定引脚号，但允许 SpanButton() 使用
     // 长按（2000 毫秒）、单按（5 毫秒）和双按（200 毫秒）的默认值。 在第二个和第三个我们改变
     // 默认长按时间为 500 毫秒，适用于反复增加或减少亮度。
    
     // 增加/减少亮度，打开/关闭电源，设置/重置最喜欢的亮度级别的所有逻辑都找到了
     // 在下面的 button() 方法中。

    new SpanButton(powerPin);                       // 新的！ 使用引脚号“powerPin”上的按钮创建新的 SpanButton 以控制电源
    new SpanButton(raisePin,500);                   // 新的！ 使用引脚号“raisePin”上的按钮创建新的 SpanButton 以增加亮度
    new SpanButton(lowerPin,500);                   // 新的！ 使用引脚号“lowerPin”上的按钮创建新的 SpanButton 以降低亮度

    this->powerPin=powerPin;                        // 新的！ 保存电源按钮引脚号
    this->raisePin=raisePin;                        // 新的！ 保存增加亮度按钮引脚号
    this->lowerPin=lowerPin;                        // 新的！ 保存降低亮度按钮引脚号
    this->ledPin=new LedPin(pin);                   // 将 PWM LED 配置为输出到指定引脚

    Serial.print("Configuring Dimmable LED: Pin="); // 初始化消息
    Serial.print(ledPin->getPin());
    Serial.print(" Channel=");
    Serial.print(channel);
    Serial.print("\n");
    
  } // end constructor

  boolean update(){                              // update() method

    LOG1("Updating Dimmable LED on pin=");
    LOG1(ledPin->getPin());
    LOG1(":  Current Power=");
    LOG1(power->getVal()?"true":"false");
    LOG1("  Current Brightness=");
    LOG1(level->getVal());
  
    if(power->updated()){
      LOG1("  New Power=");
      LOG1(power->getNewVal()?"true":"false");
    }

    if(level->updated()){
      LOG1("  New Brightness=");
      LOG1(level->getNewVal());
    } 

    LOG1("\n");
    
    ledPin->set(power->getNewVal()*level->getNewVal());    
   
    return(true);                               // return true
  
  } // update

  // 新的！ 这是定义所有 PushButton 操作的 button() 方法。 记下签名，并使用“覆盖”一词

  void button(int pin, int pressType) override {

    LOG1("Found button press on pin: ");            // 记录消息总是一个好主意
    LOG1(pin);
    LOG1("  type: ");
    LOG1(pressType==SpanButton::LONG?"LONG":(pressType==SpanButton::SINGLE)?"SINGLE":"DOUBLE");
    LOG1("\n");

    int newLevel;

    if(pin==powerPin){
      if(pressType==SpanButton::SINGLE){            // 如果单按电源按钮..
        power->setVal(1-power->getVal());           // ...切换功率特性的值
      } else
      
      if(pressType==SpanButton::DOUBLE){            // 如果双击电源按钮...
        power->setVal(1);                           // ...打开电源
        level->setVal(favoriteLevel);               // ...并将亮度设置为最喜欢的级别
      } else
      
      if(pressType==SpanButton::LONG) {             // 如果长按电源按钮...
        favoriteLevel=level->getVal();              // ...保存当前亮度级别
        LOG1("Saved new brightness level=");        // ...并输出日志信息
        LOG1(favoriteLevel);
        LOG1("\n");        
        ledPin->set((1-power->getVal())*level->getVal());       // 闪烁 LED 表示新级别已保存
        delay(100);
        ledPin->set((1-power->getVal())*level->getVal());
      }
      
    } else

    if(pin==raisePin){                                                   
      if(pressType==SpanButton::DOUBLE){            // if a DOUBLE press of the raise button...
        power->setVal(1);                           // ...turn on power
        level->setVal(100);                         // ...and set brightness to the max level
      } else {
      
      newLevel=level->getVal()+(pressType==SpanButton::LONG?10:1);   // get current brightness level and increase by either 10% (LONG press) or 1% (SINGLE press)
      if(newLevel>100)                                               // don't allow new level to exceed maximium of 100%
        newLevel=100;
      level->setVal(newLevel);                                       // set the value of the brightness Characteristic to this new level
      }
      
    } else

    if(pin==lowerPin){                                                   
      if(pressType==SpanButton::DOUBLE){            // if a DOUBLE press of the lower button...
        power->setVal(1);                           // ...turn on power
        level->setVal(5);                           // ...and set brightness to the min level
      } else {
      
      newLevel=level->getVal()-(pressType==SpanButton::LONG?10:1);   // get current brightness level and decrease by either 10% (LONG press) or 1% (SINGLE press)
      if(newLevel<5)                                                 // don't allow new level to fall below minimum of 5%  
        newLevel=5;
      level->setVal(newLevel);                                       // set the value of the brightness Characteristic to this new level
      }

    }

//在示例 14 中，我们看到了如何在 HomeKit 中模拟 PushButton tile，方法是自动重置 Characteristic，使其在短时间内“关闭”。然而，
//有时我们希望能够使用实际的PushButtons（或瞬时开关）物理控制设备) 触发动作，例如打开电灯或风扇，或打开车库门。此外，我们希望
//HomeKit 反映此类手动操作导致的设备变化 - HomeKit 应该知道灯何时打开或手动关闭。
//一种方法是通过添加到派生服务的 loop() 方法中的自定义代码来监视按钮，检查按钮何时被按下，消除按钮噪音，在按下时执行一些操作，并使
//用 setVal( ） 方法。或者您可以使用 HomeSpan 的内置 SpanButton() 对象。
//SpanButton() 是一个服务级对象，这意味着它将自己附加到您定义的最后一个服务。通常，您将直接在派生服务的构造函数中实例化多个
//SpanButton() 对象。
//SpanButton() 支持三种类型的触发器：单次按钮按下、双次按下和长（扩展）按下。
//触发这些不同类型所需的按下的长度可以由 SpanButton() 的可选参数指定。由于大多数按钮在按下时会产生虚假噪音（然后在释放时再次产生），
//触发 SINGLE 按下的默认时间是 5ms。可以将其更改为更长的值，但不建议使用更短的值，因为这可能会允许虚假触发，除非您
//使用硬件对开关进行去抖动。
//SpanButton() 构造函数接受 4 个参数，顺序如下：pin - PushButton 连接到的 pin 号（必需）longTime - 按钮需要按下的最小时间长度（以
//毫秒为单位）才能被视为 LONG press (optional; default=2000 ms)singleTime- 最小时间长度（以毫秒为单位） 需要按下按
//钮才能被视为 SINGLE press（可选；默认值=5 ms）doubleTime- 最大时间长度（以毫秒为单位） ) 在两次按下按钮之间创建两
//次按下（可选；默认值 = 200 毫秒）
//当 SpanButton() 被实例化时，它将 ESP32 上的指定引脚设置为带 PULL-UP 的 INPUT，这意味着该引脚在读取时通常会返回 HIGH 值。应连接实
//际的 PushButton，以便该引脚接地按下按钮时。
//HomeSpan 自动轮询所有具有关联 SpanButton() 对象的引脚并检查 LOW 值，这表明按钮被按下，但尚未释放。然后它启动一个计时器。如果按钮
//在被按下少于 singleTime 毫秒后被释放，则没有任何反应.如果按钮被按下超过 singleTime 毫秒后释放，但小于 longTime 毫秒，则触
//发 SINGLE 按下，除非您在 doubleTime 毫秒内再次按下以触发 DOUBLE 按下。如果按住按钮超过 longTime毫秒而不被释放，触发长按。
//一旦触发长按，计时器就会重置，因此如果您按住按钮，另一个长按将在另一个 longTime 毫秒内触发。这将一直持续到您最终释放按钮。
//请注意，如果您设置 longTime > singleTime，SpanButton() 将仅触发 LONG 按下。此外，如果您将 doubleTime 设置为零，SpanButton() 将
// 无法触发 DOUBLE 按下。
//要在派生服务中使用 SpanButton()，您需要实现 button() 方法。与 loop() 方法类似，您的 button() 方法通常包含 getVal() 函数和 
//setVal() 函数的某种组合，以及在物理设备上执行一些操作的代码（将引脚设置为高或低，打开风扇等）。但是，与 HomeSpan 每个轮询
//周期调用的 loop() 方法相比，HomeSpan 只调用 button()当附加到服务的按钮注册为单次、双次或长按时的方法。
//不要忘记为实际的 LED 设置新的功率和电平——上面的代码本身只会改变 HomeKit 中的特性值！我们仍然需要对实际的 LED 本身采取行动。
//请注意，下面的行类似于上面 update() 方法中使用的 ledPin->set 函数，但并不相同。在 update() 方法中，我们使用 getNewVal() 是因为
//我们想更改 LED 以匹配用户通过 HomeKit 控制器请求的新值。我们不需要（也不能）使用 setVal() 在 update() 方法中修改这些值，
//因为 HomeSpan 会自动为我们执行此操作，前提是我们返回 StatusCode::OK在 update() 方法的末尾。
//但是在 button() 方法中，getNewVal() 没有任何意义，因为 HomeKit 不会调用 button() 方法来响应来自 HomeKit Controller 接口的用户
//请求。相反，我们手动更改了一个或多个 Characteristic 的值使用 setVal() 响应 SINGLE、DOUB
    
    ledPin->set(power->getVal()*level->getVal());       // update the physical LED to reflect the new values

  }

};
      
//////////////////////////////////
