////////////////////////////////////
//       设备专用 LED 服务         //
////////////////////////////////////

struct DEV_LED : Service::LightBulb {               // 开/关 LED

  int ledPin;                                       // 为此 LED 定义的引脚编号
  SpanCharacteristic *power;                        // 引用 On 特性
  
  DEV_LED(int ledPin) : Service::LightBulb(){       // 构造函数（）方法

    power=new Characteristic::On();                 
    this->ledPin=ledPin;                            
    pinMode(ledPin,OUTPUT);                         
    
    // 这里我们在构造函数首次调用时输出日志消息。
    // 我们使用LOG0()来确保无论LOG Level设置如何，消息始终输出。
    // 请注意，这使用LOG()的单参数形式，因此需要多次调用才能创建完整的消息

    LOG0("Configuring On/Off LED: Pin=");       // 初始化消息
    LOG0(ledPin);
    LOG0("\n");

  } // 结束构造函数

  boolean update(){                              // update() 方法

    // Here we output log messages whenever update() is called, which is helpful
    // for debugging purposes if your physical device is not functioning as expected.
    // Since it's just for debugging, we use LOG1() instead of LOG0().  Note we can
    // output both the current as well as the new power settings.  We've again
    // used the single-argument form of LOG() to create this message

    LOG1("Updating On/Off LED on pin=");
    LOG1(ledPin);
    LOG1(":  Current Power=");
    LOG1(power->getVal()?"true":"false");
    LOG1("  New Power=");
    LOG1(power->getNewVal()?"true":"false");
    LOG1("\n");

    digitalWrite(ledPin,power->getNewVal());      
   
    return(true);                               // 返回 true
  
  } //  更新
};
      
//////////////////////////////////

struct DEV_DimmableLED : Service::LightBulb {       // 可调光 LED

  LedPin *ledPin;                                   // 引用 Led Pin
  SpanCharacteristic *power;                        // 引用 On 特性
  SpanCharacteristic *level;                        // 参考亮度特征
  
  DEV_DimmableLED(int pin) : Service::LightBulb(){       // 构造函数（）方法

    power=new Characteristic::On();     
                
    level=new Characteristic::Brightness(50);       // 亮度特性初始值为 50%
    level->setRange(5,100,1);                       // 将亮度范围设置为最小 5% 到最大 100%，步长为 1%

    // Here we once again output log messages when the constructor is initially called.
    // However, this time we use the multi-argument form of LOG() that resembles a
    // standard printf() function, which makes for more compact code.

    LOG0("Configuring Dimmable LED: Pin=%d\n",pin);    // 初始化消息

    this->ledPin=new LedPin(pin);                   // 配置 PWM LED 以输出至指定引脚
    
  } // 结束构造函数

  boolean update(){                              // update() 方法

    // 请注意，由于 Dimmable_LED 具有两个可更新的特性，HomeKit 可能会请求更新其中一个或两个特性。
    // 我们可以使用每个特性的“isUpdated”标志，仅在 HomeKit 实际请求更新该特性时输出消息。
    // 由于只要服务中的至少一个特性有更新，就会调用 update()，因此电源、级别或两者的“isUpdated”标志都会被设置。

    // 如上所述，我们使用多参数形式的 LOG() 来创建消息。请注意，对于 DimmableLED，ledPin 有一个方法 getPin() 可以检索引脚号，因此您无需单独存储它。

    LOG1("Updating Dimmable LED on pin=%dL  Current Power=%s  Current Brightness=%d",ledPin->getPin(),power->getVal()?"true":"false",level->getVal());
  
    if(power->updated())
      LOG1("  New Power=%s",power->getNewVal()?"true":"false");

    if(level->updated())
      LOG1("  New Brightness=%d",level->getNewVal()); 

    LOG1("\n");
    
    ledPin->set(power->getNewVal()*level->getNewVal());    
   
    return(true);                               // 返回 true
  
  } //  更新
};
      
//////////////////////////////////
