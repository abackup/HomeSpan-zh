
////////////////////////////////////
//   DEVICE-SPECIFIC LED SERVICES //
////////////////////////////////////

struct DEV_TempSensor : Service::TemperatureSensor {     // 独立的温度传感器

  SpanCharacteristic *temp;                         //参考当前温度特性
  
  DEV_TempSensor() : Service::TemperatureSensor(){       //构造函数()方法
    
    //首先，我们实例化温度传感器的主要特征，即当前温度，并将其初始值设置为 20 度。对于真正的传感器，我们将读取读数并将其初始化
    //为该值。注意：HomeKit 对所有温度都使用摄氏度 温度设置。HomeKit 将根据 iPhone 上的设置在 HomeKit 应用程序中显示温度。 尽管
     // HAP 文档包含一个似乎允许设备通过为每个服务指定摄氏或华氏显示来覆盖此设置的特性，但它似乎不像宣传的那样工作。
    
    temp=new Characteristic::CurrentTemperature(-10.0);        // 实例化当前温度特性
    temp->setRange(-50,100);                                  // 将范围从 HAP 默认值 0-100 扩大到 -50 到 100，以允许负温度
        
    Serial.print("Configuring Temperature Sensor");           // 初始化消息
    Serial.print("\n");

  } // end constructor

  // 接下来我们创建 loop() 方法。此方法不接受任何参数并且不返回任何值。为了模拟实际传感器的温度变化，我们将使用 getVal() 函数
  //读取 temp Characteristic 的当前值，其中 <float> 作为模板参数；加0.5摄氏度；然后将结果存储在一个名为“温度”的浮点变量中。这将
   // 模拟 0.5 摄氏度（略小于 1 华氏度）的增量。我们将温度限制为 35.0 摄氏度，之后它重置为 10.0 和重新开始。最重要的是，我们将每
  //  5 秒执行一次，方法是使用 timeVal() 检查自上次修改以来经过的时间。
// 所有动作都发生在 setVal() 行中，我们将 temp Characteristic 的值设置为新的温度值。这告诉 HomeKit 向所有可用的控制器发送事件
  //  通知消息，让它们知道新的温度。请注意，setVal() 不是模板函数，不需要您将 <float> 指定为模板参数。这是因为 setVal() 可以根
   // 据您指定的参数确定类型。如果有任何歧义，您总是可以明确地转换参数，例如：setVal((float)temperature)。

  void loop(){

    if(temp->timeVal()>5000){                               // 检查自上次更新以来经过的时间，仅在大于 5 秒时继续
      float temperature=temp->getVal<float>()+0.5;          // “模拟”半度的温度变化......
      if(temperature>35.0)                                  // ...但在 -30C 重新开始之前将最大值限制在 35C
        temperature=-30.0;
      
      temp->setVal(temperature);                            // 设置新温度； 这会生成一个事件通知并重置经过的时间
      
      LOG1("Temperature Update: ");
      LOG1(temperature*9/5+32);
      LOG1("\n");            
    }
    
  } // loop
  
};
      
//////////////////////////////////

struct DEV_AirQualitySensor : Service::AirQualitySensor {     // 独立的空气质量传感器

  // 空气质量传感器与温度传感器类似，只是它支持多种测量。
   // 我们将使用其中的三个。 第一个是必需的，后两个是可选的。

  SpanCharacteristic *airQuality;                 // 参考空气质量特性，它是一个从 0 到 5 的整数
  SpanCharacteristic *o3Density;                  // 参考臭氧密度特性，它是从 0 到 1000 的浮点数
  SpanCharacteristic *no2Density;                 // 参考二氧化氮特性，它是从 0 到 1000 的浮点数
  
  DEV_AirQualitySensor() : Service::AirQualitySensor(){       // constructor() method
    
    airQuality=new Characteristic::AirQuality(1);                         // 实例化空气质量特性并将初始值设置为 1
    o3Density=new Characteristic::OzoneDensity(300.0);                    // 实例化臭氧密度特性并将初始值设置为 300.0
    no2Density=new Characteristic::NitrogenDioxideDensity(700.0);         // 实例化二氧化氮密度特性并将初始值设置为 700.0
    
    Serial.print("Configuring Air Quality Sensor");   // 初始化消息
    Serial.print("\n");

  } // end constructor

  void loop(){

    // 请注意，我们不会更新二氧化氮密度特性。 因此，这应该保持稳定在其初始值 700.0

    if(airQuality->timeVal()>5000)                            //每 5 秒修改一次空气质量特性
      airQuality->setVal((airQuality->getVal()+1)%6);         // 通过将当前值加一并保持在 0-5 范围内来模拟空气质量的变化

    if(o3Density->timeVal()>10000)                            // 每 10 秒修改一次臭氧密度特性值
      o3Density->setVal((double)random(200,500));             // 用 200 到 499 之间的随机值模拟变化。注意使用 (double) cast，因为 random() 返回一个整数
       
  } // loop

};
      
//////////////////////////////////

// 您应该在 HomeKit 应用程序中看到的内容
// -----------------------------------------------

// 如果你加载上面的例子，你的 HomeKit 应用应该会显示两个新的磁贴：一个标有“温度传感器”，另一个标有“空气质量”。温度传感器图块应
//指示 10C 至 35C（50F 至 95F）范围内的温度，该温度每 5 秒自动增加和更新 0.5C。空气质量图块应每 10 秒循环一次“质量”状态。状态在
//HomeKit 中显示为“未知”、“优秀”、“良好”、“一般”、“劣质”和“差”。
// 请注意，HomeKit 仅显示图块本身内的特性子集的值。在空气质量传感器的情况下，仅显示空气质量的质量状态。要查看其他特性的值，例如臭
// 氧密度和Nitrogen Dioxide Density，您需要点击磁贴，然后打开设置屏幕（如果 HomeKit 在控制屏幕上显示这些值而不是让您打开设置屏幕
 //会更好）。在设置屏幕上，您应该看到我们实例化的所有三个特性的值：空气质量、二氧化氮密度和臭氧密度。空气质量和臭氧密度应每 10 秒
 //更改一次。二氧化氮密度应保持稳定在初始值 700.0，因为我们从未使用 setVal() 来更新此特性。
 //如果您以 2 的 VERBOSITY 级别（在库的 Settings.h 文件中指定）运行 HomeSpan，您可以看到 HomeSpan 在后台每 5 秒向所有已注册的控制
 //器发送事件通知消息，用于温度传感器，并且每 5和 10 秒用于空气质量传感器。如果您仔细观察，您会发现空气质量传感器的事件通知消息仅
 //包含两个值 - 一个用于空气质量状态，一个用于臭氧密度。HomeSpan 未发送二氧化氮密度特性的值，因为它没有被 setVal() 函数改变。
 //最后注：HomeKit 应用程序中温度显示的小数位数与值本身的步长无关。这似乎是由 HomeKit 硬编码的：对于华氏温度，温度传感器图块不显示
 //小数，并且显示为最接近的整数度数（例如 72、73、74 度）；对于摄氏度，瓷砖允许半度分辨率和相应的 ROUNDS（例如，22.7 显示为 22.5，
 //22.8 显示为 23.0）。
