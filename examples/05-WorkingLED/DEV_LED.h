
////////////////////////////////////
//      特定于设备的 LED 服务      //
////////////////////////////////////

// 在这里，我们定义了我们的新 LED 服务！

struct DEV_LED : Service::LightBulb {               // 首先，我们从 HomeSpan 灯泡服务创建一个派生类

  int ledPin;                                       // 此变量存储为此 LED 定义的引脚号
  SpanCharacteristic *power;                        // 在这里，我们创建一个指向名为“power”的 SpanCharacteristic 的通用指针，我们将在下面使用它

  // 接下来我们定义 DEV_LED 的构造函数。 请注意，它需要一个参数 ledPin，
  // 它指定了 LED 连接到的引脚。
  
  DEV_LED(int ledPin) : Service::LightBulb(){

    power=new Characteristic::On();                 // 这是我们创建之前在 setup() 中定义的 On Characterstic 的地方。 将其保存在上面创建的指针中，以供下面使用
    this->ledPin=ledPin;                            // 不要忘记存储ledPin ...
    pinMode(ledPin,OUTPUT);                         // ...并将 ledPin 的模式设置为 OUTPUT（标准 Arduino 功能）
  } // 结束构造函数

  // 最后，我们使用实际打开/关闭 LED 的指令覆盖默认的 update() 方法。 注意 update() 返回类型 boolean
  boolean update(){            

    digitalWrite(ledPin,power->getNewVal());        // 使用标准 Arduino 函数根据对 power->getNewVal() 的调用返回来打开/关闭 ledPin（有关更多信息，请参见下文）
   
    return(true);                                   // 返回 true 表示更新成功（否则，如果由于某种原因无法打开 LED，则创建代码以返回 false）
  
  } // 更新
};
      
//////////////////////////////////

// update() 怎么工作: ------------------ 每当 HomeKit 控制器请求 HomeSpan 更新特性时，HomeSpan 都会为包含特性的 SERVICE 调用 update() 方法。它只调用一次，即使该服务
//请求多个特性更新。例如，如果您指示 HomeKit 打开一盏灯并将其设置为 50% 亮度，它将向 HomeSpan 发送两个请求：一个更新“灯泡服务的“开”特性从“假”变为“真”，另一个将同一服务
//的“亮度”特性更新为 50。这是非常低效的，并且需要用户处理对同一服务的多次更新。取而代之的是，HomeSpan 将这两个请求合并到一个对 Service 本身的 update() 调用中，您可以在其
//中处理同时更改的所有特性。在上面的示例中，我们只有一个特性要处理，所以这并不意味着什么。但在后面的例子中，我们将看到它是如何与多个特征一起工作的。
//
 //如何访问特性的新值和当前值 ----------------------------------------- -------------- HomeSpan 将其特性的值存储在一个联合结构中，该结构允许不同的类型，例如浮点数、布尔
 //值等。具体类型由 HAP 为每个特性定义。查找一个 Characteristic 是 uint8 还是 uint16 可能会很烦人，因此 HomeSpan 将所有这些细节都抽象出来。由于 C++ 坚持严格的变量类型，
 //这是通过使用模板方法来完成的。每个 Characteristic 都支持以下两种方法：getVal<type >() - 在转换为“type”后返回 Characteristic 的 CURRENT 值>getVal<int>() 以 int 形式返
 //回 SpanCharacterstic MyChar 的当前值，无论 HomeSpan 如何存储该值。类似地，MyChar->getVal<double>() 返回一个双精度值，即使它存储为布尔值（在这种情况下，您将获得 0.00 
 // 或 1.00）。当然，您需要确保了解预期值的范围，以免尝试使用 getVal<uint8_t>() 访问存储为 2 字节 int 的值。但是使用 getVal<int>() 来访问 HAP 坚持存储为浮点数的特性的值
 // 是完全可以的，即使它的范围严格在 0 到 100 之间，步长为 1。知道范围和步长是在确定可以将其作为 <int> 甚至是 <uint8_t> 访问时，您需要知道的一切。因为大多数 Characteristic 
  //值都可以正确地转换为 int，如果未指定模板参数，getVal 和 getNewVal 都默认为 <int>。正如您在上面看到的，我们通过简单地调用 power->getNewVal() 来检索 HomeKit 为我们命名为
 // “power”的 On Characteristic 请求的新值。由于没有指定模板参数，getNewVal() 将返回一个 int。由于 On Characteristic 本身存储为布尔值，getNewVal() 将返回 0 或 1，具体取决
 // 于 HomeKit 是否请求打开 Characteristic您可能还注意到，在上面的示例中，我们需要使用 getNewVal()，但没有在任何地方使用 getVal()。这是因为我们知道 HomeKit 请求打开或关闭 
  //LED 时该怎么做. LED 的当前状态（开或关）无关紧要。在后面的示例中，我们将看到设备的当前状态确实很重要的实例，我们将需要访问当前值和新值。最后，还有一种额外的 
  //Characteristic 方法，上面没有使用，但将在后面的示例中使用：updated()。此方法返回一个布尔值，指示 HomeKit 是否已请求更新 Characteristic，这意味着 getNewVal() 将包含它要
 // 为该特性设置新值。对于只有一个特性的服务，如上所述，我们不需要询问“电源”是否使用 power->updated() 更新，因为事实上 update() 方法因为服务被调用意味着 HomeKit 正在请求更新，
  //而唯一要更新的是“电源”。但是对于具有两个或更多特性的服务，可以调用 update() 并请求仅更新特性的一个子集。我们将在后面的多特性示例中找到 updated() 方法的好用处。
 // 
 //幕后：UPDATE() 的返回代码是做什么的 ------------------------- ----------------- HomeKit 要求每个 Characteristic 在尝试更新其值时返回一个特殊的 HAP 状态代码。HomeSpan 自
 //动处理大部分错误，例如未找到特征，或更新只读特征的请求。在这些情况下，甚至从未调用 update()。但如果是，HomeSpan 需要为每个要返回的特征返回 HAP 状态代码在该服务中更新。
 //
 //通过返回“true”，您告诉 HomeSpan 请求的 newValues 没问题，并且您已对物理设备进行了所需的更新。收到真实的返回值后，HomeSpan 通过将“newValue”数据元素复制到当前“值”数据元素。
 //然后 HomeSpan 向 HomeKit 发送一条带有表示“OK”的 HAP 代码的消息，这让 Controller 知道它请求的新值已被成功处理。HomeKit 在任何时候都不会要求或允许发送数据值从 HomeSpan 返回
// ，指示特征中的数据。当请求更新时，HomeKit 只期望 HAP 状态码 OK，或其他一些表示错误的状态码。要告诉 HomeSpan 向 Controller 发送错误码，表明您无法成功处理更新，只需更新() 
//  返回值“false”。HomeSpan 将返回值“false”转换为表示“UNABLE”的 HAP 状态代码，这将导致控制器显示设备没有响应。
 //您需要返回“false”的原因很少，因为 HomeSpan 或 HomeKit 本身会提前完成大量检查。例如，HomeKit 不允许您使用 Controller 甚至 Siri 来更改亮度将灯泡设置为您指定的允许值范围之
 //外的值。这意味着您收到的任何 update() 请求都应仅包含范围内的 newValue 数据元素。
