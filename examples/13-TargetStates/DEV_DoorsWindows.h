
////////////////////////////////////
//   DEVICE-SPECIFIC LED SERVICES //
////////////////////////////////////

struct DEV_GarageDoor : Service::GarageDoorOpener {     // 车库门开启器

  SpanCharacteristic *current;            // 参考当前门状态特性（特定于车库开门器）
  SpanCharacteristic *target;             // 参考目标门状态特性（特定于车库开门器）
  SpanCharacteristic *obstruction;        // 参考检测到的障碍物特性（特定于车库门开启器）

  DEV_GarageDoor() : Service::GarageDoorOpener(){       // constructor() method
        
    current=new Characteristic::CurrentDoorState(1);              // 初始值为 1 表示关闭
    target=new Characteristic::TargetDoorState(1);                // 初始值为 1 表示关闭
    obstruction=new Characteristic::ObstructionDetected(false);   // 初始值为 false 表示未检测到障碍物
    
    Serial.print("Configuring Garage Door Opener");   // 初始化消息
    Serial.print("\n");

  } // end constructor

  boolean update(){                              // update() method

    // see HAP Documentation for details on what each value represents

    if(target->getNewVal()==0){                     // 如果目标状态值设置为 0，则 HomeKit 请求门处于打开位置
      LOG1("Opening Garage Door\n");
      current->setVal(2);                           // 将当前状态值设置为 2，表示“打开中”
      obstruction->setVal(false);                   // 清除任何先前的障碍物检测
    } else {
      LOG1("Closing Garage Door\n");                // 否则目标状态值设置为 1，并且 HomeKit 请求门处于关闭位置
      current->setVal(3);                           // 将当前状态值设置为 3，这意味着“关闭中”    
      obstruction->setVal(false);                   // 清除任何先前的障碍物检测
    }
    
    return(true);                               // 返回true
  
  } // update

  void loop(){                                     // loop() method

    if(current->getVal()==target->getVal())        // 如果当前状态与目标状态匹配，则什么也不做——退出循环（）
      return;

    if(current->getVal()==3 && random(100000)==0){    // 这里我们模拟一个随机障碍物，但前提是门正在关闭（不打开）
      current->setVal(4);                             // 如果我们的模拟障碍物被触发，将当前状态设置为 4，这意味着“已停止”
      obstruction->setVal(true);                      // 并将检测到的障碍物设置为真
      LOG1("Garage Door Obstruction Detected!\n");
    }

    if(current->getVal()==4)                       //如果当前状态已停止，则无需再做任何事情 - 退出循环（）   
      return;

    // 只有当门处于表示主动打开或主动关闭的状态时，才会调用最后一段代码。
     // 如果有障碍物，门会“停止”并且不会重新启动，直到 HomeKit 控制器请求新的打开或关闭操作

    if(target->timeVal()>5000)                     // 通过监控自上次修改目标状态以来的时间，模拟一个需要 5 秒才能操作的车库门
      current->setVal(target->getVal());           // 将当前状态设置为目标状态
       
  } // loop
  
};

////////////////////////////////////

struct DEV_WindowShade : Service::WindowCovering {     //具有保持功能的电动窗帘

  SpanCharacteristic *current;                     // 引用“通用”当前位置特征（由各种不同的服务使用）
  SpanCharacteristic *target;                      // 引用“通用”目标位置特征（由各种不同的服务使用）

  DEV_WindowShade() : Service::WindowCovering(){       // constructor() method
        
    current=new Characteristic::CurrentPosition(0);     // 窗帘的位置范围从 0（完全降低）到 100（完全升高）
    
    target=new Characteristic::TargetPosition(0);       // 窗帘的位置范围从 0（完全降低）到 100（完全升高）
    target->setRange(0,100,10);                         // 将允许的目标位置范围设置为 0-100 IN STEPS of 10
        
    Serial.print("Configuring Motorized Window Shade");   // 初始化消息
    Serial.print("\n");

  } // end constructor

  boolean update(){                              // update() method

    // 下面的逻辑基于 HomeKit 在实践中的操作方式，这与 HAP 文档不一致。在该文档中，HomeKit 似乎支持完全打开或完全关闭窗帘，
    //并带有一个可选控件来将窗帘保持在给定的位置 移动时的中间位置。
 // 实际上，HomeKit 似乎没有实现任何形式的 HOLD 控制按钮，即使您实例化了该特性。相反，HomeKit 提供了一个完整的滑块控制，类似
    //  于灯泡的亮度控制，允许您设置确切的位置 从 0-100% 的窗帘。这消除了对任何类型的 HOLD 按钮的需要。 生成的逻辑也很简单：

    if(target->getNewVal()>current->getVal()){      // 如果请求的目标位置大于当前位置，只需记录“加注”消息
      LOG1("Raising Shade\n");                      // **没什么可做的 - HomeKit 会跟踪当前位置，因此知道需要加注
    } else 
    if(target->getNewVal()<current->getVal()){      //如果请求的目标位置小于当前位置，只需记录“提升”消息
      LOG1("Lowering Shade\n");                     // ** 没什么可做的 - HomeKit 会跟踪当前位置，因此知道需要降低
    }
        
    return(true);                               // return true
  
  } // update

  void loop(){                                     // loop() method

    // 这里我们模拟一个需要 5 秒才能移动到新目标位置的窗帘
    
    if(current->getVal()!=target->getVal() && target->timeVal()>5000){          // 如果自上次修改目标位置后已过去 5 秒...
      current->setVal(target->getVal());                                        // ...将当前位置设置为等于目标位置
    }

    // 请注意，没有理由将当前位置的连续更新发送到 HomeKit。HomeKit 不显示当前位置。相反，它只是将当前位置的值与用户在 Home App。
    //如果发现当前位置和目标位置相同，则知道窗帘已停止。否则根据指定的目标状态是大于还是小于当前状态，会报告窗帘正在上升或下降。
      

    // 根据 HAP，还需要特征位置状态。 然而，这似乎是重复的，考虑到 HomeKit 使用当前位置的方式，根本不需要。 如果没有定义位置状
    //态（因为它在技术上是必需的），HomeSpan 会警告您，但没有它也可以正常工作。 
    
  } // loop
  
};
