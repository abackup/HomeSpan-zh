
////////////////////////////////////////////////////
//   DEVICE-SPECIFIC PROGRAMMABLE SWITCH SERVICES //
////////////////////////////////////////////////////

struct DEV_ProgButton : Service::StatelessProgrammableSwitch {       // 无状态可编程开关
 
  SpanCharacteristic *switchEvent;                  // 对 ProgrammableSwitchEvent 特性的引用
  
  DEV_ProgButton(int buttonPin, int index) : Service::StatelessProgrammableSwitch(){

    switchEvent=new Characteristic::ProgrammableSwitchEvent();  // 可编程开关事件特性（将设置为 SINGLE、DOUBLE 或 LONG press）
    new Characteristic::ServiceLabelIndex(index);               // 设置服务标签索引（仅当每个服务有多个无状态可编程交换机时才需要）
   
                
    new SpanButton(buttonPin);                                  // 创建新的 SpanButton

    Serial.print("Configuring Programmable Pushbutton: Pin=");  // 初始化消息
    Serial.print(buttonPin);
    Serial.print("  Index=");
    Serial.print(index);
    Serial.print("\n");
    
  } // end constructor

  // 我们不需要实现 update() 方法或 loop() 方法 - 只需 button() 方法：

  void button(int pin, int pressType) override {

    LOG1("Found button press on pin: ");            //记录消息总是一个好主意
    LOG1(pin);
    LOG1("  type: ");
    LOG1(pressType==SpanButton::LONG?"LONG":(pressType==SpanButton::SINGLE)?"SINGLE":"DOUBLE");
    LOG1("\n");

   // 所有动作都发生在下面的这一行中。 我们只需将可编程开关事件特性的值设置为 pressType 提供的值。
   //pressType 的值（0=SpanButton::SINGLE、1=SpanButton::DOUBLE 和 2=SpanButton::LONG）旨在匹配可编程
    //开关事件特性的所需值。

    switchEvent->setVal(pressType);                // 设置switchEvent Characteristic的值

  }

};
      
//////////////////////////////////
