
////////////////////////////////////
//   DEVICE-SPECIFIC LED SERVICES //
////////////////////////////////////

// 注意：此示例仅用于演示如何在 HomeSpan 中模拟按钮。 闪烁例程的长度比 HomeSpan 应该花费在 update() 
//上的时间长得多。 要查看这对 HomeKit 的影响，请尝试将闪烁次数更改为 50，或将其保持为 3 并增加 update() 
//  中的延迟时间，以使闪烁例程花费 10 秒或更长时间。 激活后，HomeKit 如果在一定时间内没有收到 update() 的
 // 返回消息，就会认为设备已经无响应。

// 在实践中，按钮仿真用于非常短的例程，例如驾驶
// 一个 IR LED 或一个 RF 发射器，用于向远程设备发送代码。

// 与示例 9 相比的新行和更改行被标记为“新！”

struct DEV_Blinker : Service::LightBulb {           // LED Blinker

  int ledPin;                                       // pin number defined for this LED
  int nBlinks;                                      // NEW! number of times to blink
  
  SpanCharacteristic *power;                        // reference to the On Characteristic
  
  DEV_Blinker(int ledPin, int nBlinks) : Service::LightBulb(){       // constructor() method

    power=new Characteristic::On();                 
        
    this->ledPin=ledPin;                            
    this->nBlinks=nBlinks;                           // NEW! number of blinks
    pinMode(ledPin,OUTPUT);                         
    
    Serial.print("Configuring LED Blinker: Pin=");   // initialization message
    Serial.print(ledPin);
    Serial.print("  Blinks=");                       // NEW! add output message for number of blinks
    Serial.print(nBlinks);
    Serial.print("\n");

  } // end constructor

  boolean update(){                              // update() method

    // 新的！ 我们不是根据 newValue 打开或关闭 LED，而是将其闪烁
     // 指定的次数，完成后保持在关闭位置。
     // 此行已删除...
    
    // digitalWrite(ledPin,power->getNewVal());      

    // 并被如下取代

    if(power->getNewVal()){                       // 检查以确保 HomeKit 要求我们“打开”这个设备（否则忽略）

      LOG1("Activating the LED Blinker on pin=");
      LOG1(ledPin);
      LOG1("\n");

      for(int i=0;i<nBlinks;i++){                     // 循环指定的闪烁次数
        digitalWrite(ledPin,HIGH);                    // turn pin on
        delay(100);                                   // wait 100 ms
        digitalWrite(ledPin,LOW);                     // turn pin off
        delay(250);                                   // wait 250 ms
      }
      
    } // if newVal=true

    // 请注意，以上 100 毫秒和 250 毫秒的延迟仅用于说明目的
     //（所以你可以看到 LED 闪烁）。 在实践中，如果您控制的是 IR LED
     // 或射频发射器，整个信号可能会在 10 毫秒内传输。
    return(true);                               // return true
  
  } // update

 //新的！ 这里我们实现了一个非常简单的 loop() 方法，它检查电源特性是否
   //“开启”至少 3 秒。 如果是这样，它会将值重置为“关闭”（假）。

  void loop(){

    if(power->getVal() && power->timeVal()>3000){   //检查 power 是否为真，并且自上次修改以来的时间大于 3 秒
      LOG1("Resetting Blinking LED Control\n");     // log message  
      power->setVal(false);                         // set power to false
    }      
    
  } // loop
  
};
      
//////////////////////////////////

// HomeKit 错误说明：在本示例的开发过程中发现了 HomeKit 中的一个明显错误。
// 如果你有一个Accessory 有三个或更多Service，并且Accessory 收到通知消息
// 来自设备，并且 HomeKit 界面打开以显示此 Service tile 的详细控制
// 在 HomeKit 应用程序中，由于某种原因 HomeKit 会向设备发送一个 update() 请求，请求
// 将 Characteristic 设置为它刚刚从事件通知接收到的值。 不应该使用 HomeKit
// 发送更新请求以响应事件通知。
