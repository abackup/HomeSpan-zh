# 步进电机控制

HomeSpan 包含专用类，可轻松控制通过步进电机驱动板连接到 ESP32 的步进电机。 这些类允许一个或多个步进电机在后台平稳且异步地运行，同时 HomeSpan 继续在前台运行。 在具有双处理器的设备上，步进电机控制可以在与 HomeSpan 相同或不同的处理器上运行。

HomeSpan 类包含控制步进电机的所有方法，称为 **StepperControl**。 然而，这是一个抽象类，不能直接实例化。 相反，您使用特定于驱动程序的子类（派生自 **StepperControl**）来实例化步进电机对象，其中包含配置和操作特定驱动器板的所有逻辑。 每个子类都支持一个或多个构造函数，允许您指定 ESP32 设备上的哪些输出引脚将连接到驱动板上所需的引脚：

* **[Stepper_TB6612](StepperDrivers/Stepper_TB6612.md)**
   * 该类用于操作由 [Toshiba TB6612](https://cdn-shop.adafruit.com/datasheets/TB6612FNG_datasheet_en_20121101.pdf) 芯片驱动的步进电机，无论使用或不使用 ESP32 PWM 引脚
   * 例如，请参阅 [Adafruit TB6612 1.2A DC/步进电机驱动器分线板](https://www.adafruit.com/product/2448)
   * 要使用，请将以下内容添加到草图顶部：`#include "extras/Stepper_TB6612.h"`
   * 构造函数 1: `Stepper_TB6612(int AIN1, int AIN2, int BIN1, int BIN2)`
     * 仅使用 ESP32 的 4 个数字引脚控制驱动板
     * 不提供电机微步的能力
   * 构造函数2：`Stepper_TB6612(int AIN1, int AIN2, int BIN1, int BIN2, int PWMA, int PWMB)`
     * 使用 ESP32 的 4 个数字引脚和 2 个 PWM 引脚控制驱动板
     * 增加 PWM 引脚可以对电机进行微步进
   
* **[Stepper_A3967](StepperDrivers/Stepper_A3967.md)**
   * 该类用于操作由 [Allegro A3967](https://cdn.sparkfun.com/datasheets/Robotics/A3967-Datasheet.pdf) 芯片驱动的步进电机
   * 例如，请参阅 [Sparkfun EasyDriver 步进电机板](https://www.sparkfun.com/products/12779)
   * 要使用，请将以下内容添加到草图顶部：`#include "extras/Stepper_A3967.h"`
   * 构造函数：`Stepper_A3967(int M1, int M2, int STEP, int DIR, int ENABLE)`
     * 使用 ESP32 的 5 个数字引脚控制驱动板
     * 微步进内置于驱动板中（不需要单独的 ESP32 PWM 引脚）

单击上面的任一驱动程序特定类，了解有关如何连接和配置特定驱动程序板的完整详细信息。

## 步进控制方法

**StepperControl** 类提供以下方法来操作和控制使用上述驱动程序特定类之一实例化的步进电机对象：

* `StepperControl *启用（）`
   * 使电流流向步进电机线圈，主动将电机保持在其位置
   * 返回指向自身的指针，以便方法可以菊花链式连接
     * 示例： `myMotor=(new Stepper_TB6612(23,32,22,14,33,27))->enable();`
      
* `StepperControl *禁用()`
   * 禁止电流流向步进电机线圈并使其处于高阻抗状态，从而使电机能够自由转动
   * 返回指向自身的指针，以便方法可以菊花链式连接
     * 示例： `myMotor=(new Stepper_TB6612(23,32,22,14,33,27))->disable();`

* `StepperControl *brake()`
   * 禁止电流流向步进电机线圈，但使它们处于低阻抗状态，防止电机自由转动
   * 仅适用于支持“短刹车”模式的驱动芯片，否则无效
   * 返回指向自身的指针，以便方法可以菊花链式连接
     * 示例： `myMotor=(new Stepper_TB6612(23,32,22,14,33,27))->brake();`

* `void move(int nSteps, uint32_t msDelay, endAction_t endAction=NONE)`
   * 启用步进电机并转动 *nSteps* 步。 请注意，这是一个 **非阻塞** 函数，在调用后立即返回，同时电机在后台转动 *nSteps* 步
    
     * *nSteps* - 要转动的步数。 正数使电机朝一个方向转动； 负数使电机朝相反方向转动； 如果电机已经在转动，则零值会导致电机“停止”
     * *msDelay* - 步骤之间暂停的延迟（以毫秒为单位）。 必须大于零。 数字越小，电机转得越快，但受电机本身的限制
     * *endAction* - 在电机完成移动 *nSteps* 步后*执行的可选操作。 选择包括：
    
       * **StepperControl::NONE** - 不采取任何操作； 步进电机处于启用状态（这是默认设置）
       * **StepperControl::DISABLE** - 步进电机电流被禁用
       * **StepperControl::BRAKE** - 步进电机置于制动状态
   * 如果在步进电机已经转动时调用此方法，转动的步数将重置为新的 *nSteps* 值。 可以更改 *nSteps* 的符号以在电机转动时反转电机的方向，尽管这可能并不理想，具体取决于电机在现实世界中的连接情况
   * 使用值 *nSteps=0* 调用此方法会导致电机停止（如果电机已经转动）。 如果电机不转动，则使用 *nSteps=0* 调用此方法只需启用电机并立即执行 *endAction*（如果指定）。
   * 示例： `myMotor.move(200,5,StepperControl::BRAKE);` 启动电机转动 200 步，步间延迟 5 毫秒。 当电机完成全部200步后，进入制动状态。
    
* `int 剩余步数()`
   * 返回需要转动的剩余步数
   * 可能为正或负，具体取决于电机转动方向
   * 如果电机不转动则返回零
   * 示例：`myMotor.move(200,5); while(myMotor.stepsRemaining()!=0); myMotor.move(-300,5);` 启动电机转动，等待完成所有 200 步，然后向相反方向转动电机 300 步

* `int 位置()`
   * 返回步进电机的绝对位置，定义为自初始启动以来转动的所有正负步数的累积和
   * 步进电机转动或停止时可以调用
   * 示例：`myMotor.move(-800,5); while(myMotor.stepsRemaining()); myMotor.move(200,5); while(myMotor.stepsRemaining()); Serial.print(myMotor.position())` 将在电机完成转动后打印 -600 的值（第一个方向 800 步，然后另一个方向 200 步）
 
* `void setPosition(int pos)`
   * 将当前位置计数器重置为 *pos*
   * 此方法*不*转动电机； 它仅重置由`position()`返回的内部位置计数器
   *此方法仅在电机未转动时有效（如果在电机转动时调用，内部位置计数器保持不变）
   * 示例：`myMotor.move(300,5); while(myMotor.stepsRemaining()); myMotor.setPosition(-200); myMotor.move(600,5); while(myMotor.stepsRemaining()); Serial.print(myMotor.position())`将在电机完成转动后打印+400的值
    
* `void moveTo(int nPosition, uint32_t msDelay, endAction_t endAction=NONE)`
   * 启用步进电机并将其转到位置 *nPosition*。 请注意，这是一个**非阻塞**函数，在调用后立即返回，同时步进电机转动直到到达*nPosition*
    
     * *nPosition* - 步进器应转动到的位置，其中位置定义为电机自初始启动以来已转动的累计正负步数，由 `position()` 返回
     * *msDelay* - 步骤之间暂停的延迟（以毫秒为单位）。 必须大于零。 数字越小，电机转得越快，但受电机本身的限制
     * *endAction* - 在电机到达*nPosition*后*执行的可选操作。 选择包括：* **StepperControl::NONE** - 不采取任何操作； 步进电机处于启用状态（这是默认设置）
       * **StepperControl::DISABLE** - 步进电机电流被禁用
       * **StepperControl::BRAKE** - 步进电机置于制动状态
   * 当步进电机已经转动时调用该方法是可以的； 电机将继续沿相同方向或反向旋转，直到到达指定的 *nPosition*
   * 调用 `moveTo()` 之后调用 `stepsRemaining()` 按预期工作 - 返回的值将是电机到达指定的 *nPosition* 之前剩余的步数
   * 请注意，“moveTo(nPosition)”在数学上与“move(nPosition-position())”相同，但“moveTo()”方法更准确，因为它直接在任务内部计算电机的位置，即 实际控制电机
 
* `StepperControl *setAccel(float accelSize, float accelSteps)`
   * 在步骤之间添加一组额外的延迟，以便电机在启动时逐渐加速，在停止时逐渐减速
  
     * *accelSize* - 附加延迟的最大大小，表示为乘以 `move()` 和 `moveTo()` 中使用的 *msDelay* 参数的因子。 必须是大于或等于0的值。值越大，加减速度的幅度越大。 值为零不会产生加速/减速
      
     * *accelSteps* - *accelSize* 因子呈指数衰减的步数，此时电机开始以 *msDelay* 参数指定的全速转动。 必须是大于或等于1的值。值越大，加减速周期越长
      
   * 步骤之间的总延迟（当 *stepsRemaining* 不为零时）由以下公式给出：
  $$totalDelay = msDelay \times (1 + accelSize \times (e^{\frac{-\mid nSteps-stepsRemaining \mid}{accelSteps}} + e^{\frac{-(\mid stepsRemaining \mid - 1)}{accelSteps}}))$$
    
   * 示例：`myMotor.setAccel(10,20); myMotor.move(200,5);`
     * 在第一步之后产生 55ms 的延迟，在第二步之后产生 52ms 的延迟，在第三步之后产生 50ms 的延迟，依此类推，直到在步骤 82 时附加延迟完全衰减，使得步骤之间的延迟保持固定在 5ms *msDelay* 参数指定。 然后，从步骤 118（剩余 82 个步骤）开始，延迟增加到 6ms； 在步骤134，它进一步增加到7ms，依此类推，直到在步骤199延迟再次达到其最大值55ms，就在电机在步骤200停止转动之前* 返回指向自身的指针，以便方法可以菊花链式连接
     * 示例： `myMotor=(new Stepper_TB6612(23,32,22,14,33,27))->setAccel(10,20);`
          
* `StepperControl *setStepType(int mode)`
   * 将电机的步进类型设置为以下 *mode* 枚举之一：
      
     * **StepperControl::FULL_STEP_ONE_PHASE** (0)
     * **StepperControl::FULL_STEP_TWO_PHASE** (1)
     * **StepperControl::HALF_STEP** (2)
     * **StepperControl::QUARTER_STEP** (4)
     * **StepperControl::EIGHTH_STEP** (8)
   * *mode* 可以使用枚举名称或其等效整数来指定
   * 返回指向自身的指针，以便方法可以菊花链式连接
     * 示例： `myMotor=(new Stepper_TB6612(23,32,22,14,33,27))->setStepType(StepperControl::HALF_STEP);`
   * 较小的步数类型可以使电机更平稳地运行，但需要更多的步数才能转动一整圈
     * 并非所有*模式*都受所有驱动芯片支持
     *四分之一和八分之一步模式需要微步 PWM 功能
   * 尽管不推荐，但可以在电机转动时更改步进类型*模式*
   * 请参阅[步进电机模式](StepperModes.md)，了解有关步进电机通常如何驱动的简要入门知识

### CPU 和任务优先级

所有 **StepperControl** 构造函数都支持*可选*最终参数，该参数由一对*大括号括起来的*数字组成（上面未显示）。 大括号中的第一个数字指定用于控制步进电机的后台任务的*优先级*。 大括号中的第二个数字指定 **StepperControl** 将用于运行后台控制任务的 CPU（0 或 1）（对于单处理器芯片，该数字将被忽略）。 此可选最终参数的默认（也是推荐）值为 {1,0}。 例子：

* `new Stepper_TB6612(23,32,22,14,{0,1})` 实例化了对 TB6612 芯片驱动的步进电机的控制，其中 ESP32 引脚 23、32、22 和 14 连接到 AIN1、AIN2 、BIN1 和 BIN2 引脚分别位于 TB6612 上； 后台任务的优先级设置为0； 并且任务将在cpu 1上运行（仅适用于双处理器芯片）

## 示例草图

下面是演示上述方法的简单草图：
```C++
// 使用基于 TB6612 的驱动板和半步 PWM 模式的 StepperControl 示例

#include "Stepper_TB6612.h" // 包含 TB6612 芯片的驱动程序

步进控制*电机； // 创建一个指向StepperControl的全局指针，以便可以在setup()和loop()中访问它

//////////////////////////////////////

无效设置（）{

   串行.开始(115200);
   延迟（1000）；
   Serial.printf("\nHomeSpan 步进控制\n\n");

   电机=新Stepper_TB6612(23,32,22,14,33,27); // 使用指定的可选 PWM 引脚（33 和 27）实例化电机对象

   电机->setStepType(StepperControl::HALF_STEP); // 将模式设置为HALF STEP，这意味着200步电机完成一转需要400步
   电机->setAccel(10,20); // 添加加速参数：额外延迟为 10 倍，衰减超过 20 步

   Serial.printf("将电机移动 400 步并等待电机停止...\n");
  
   电机->移动(-400,5); // 将电机移动 -400 步（1 转），步间间隔 5 毫秒。
   while(电机->剩余步数()); // 等待，直到没有剩余步骤

   Serial.printf("将电机移动到+1200的绝对位置（即反向1600步，或4转），无需等待...\n");
  
   电机->moveTo(1200,2,StepperControl::BRAKE); // 将电机移动到 1200 步的绝对位置，步间间隔 2ms； 完成后进入刹车状态

   // 即使setup()退出并且下面的loop()开始，电机也会继续在后台移动
}

//////////////////////////////////////

无效循环（）{
  
   Serial.printf("电机剩余 %d 步\n",motor->stepsRemaining());
  
   延迟（1000）； // 电机不受delay()影响
  
   if(电机->位置()==1200){
     Serial.printf("电机已到达最终位置，现已停止。\n");
     同时（1）；
   }
}
```
### 电动窗帘示例

一个完整的示例展示了如何在完整的 HomeSpan 草图中使用 *StepperControl* 类来使用 TB6612 和 A3967 驱动板控制电动窗帘，可以在 Arduino IDE 的 [*文件 → 示例 → HomeSpan → 其他示例下找到 → MotorizedWindowShade*](../examples/Other%20Examples/MotorizedWindowShade)。

## 创建您自己的 **StepperControl** 驱动程序

如果上述电机驱动程序类别均不适用于您的特定芯片或驱动板，则创建一个新驱动程序以在您的草图中使用是相对简单的。 这是因为在后台操作步进电机的所有逻辑都已嵌入抽象 **StepperControl** 类中。 要创建您自己的驱动程序，请首先创建从 **StepperControl** 派生的子类。 接下来，添加一个定义引脚的构造函数并根据需要执行任何初始化。 最后，定义 **StepperControl** 调用来操作电机的以下方法：

* `void onStep(boolean Direction)` - 包含基于 *direction* 参数使电机前进一步的逻辑
* `void onEnable()` - 包含启用电机驱动器的逻辑
* `void onDisable()` - 包含禁用电机驱动器的逻辑
* `void onBrake()` - 包含将电机置于短制动状态的逻辑
* `StepperControl *setStepType(int mode)` - 包含基于 *mode* 参数设置步骤类型模式的逻辑

只需要定义第一个方法“onStep()”。 如果任何其他方法不适用于您的特定驱动板，您可以保留任何其他方法未定义。 当然，您可以创建其他方法来反映驱动板可能支持的任何其他功能。

作为示例，下面是 **Stepper_A3967** 类的完整代码：
```C++
#include "StepperControl.h"

//////////////////////////
 
struct Stepper_A3967 : StepperControl {

  int m1Pin;
  int m2Pin;
  int stepPin;
  int dirPin;
  int enablePin;

//////////////////////////

  Stepper_A3967(int m1Pin, int m2Pin, int stepPin, int dirPin, int enablePin, std::pair<uint32_t, uint32_t> taskParams = {1,0}) : StepperControl(taskParams.first,taskParams.second){
    this->m1Pin=m1Pin;
    this->m2Pin=m2Pin;
    this->stepPin=stepPin;
    this->dirPin=dirPin;
    this->enablePin=enablePin;

    pinMode(m1Pin,OUTPUT);
    pinMode(m2Pin,OUTPUT);
    pinMode(stepPin,OUTPUT);
    pinMode(dirPin,OUTPUT);
    pinMode(enablePin,OUTPUT);

    setStepType(FULL_STEP_TWO_PHASE);
  }

//////////////////////////

  void onStep(boolean direction) override {
    digitalWrite(dirPin,direction);
    digitalWrite(stepPin,HIGH);
    digitalWrite(stepPin,LOW);      
  }

//////////////////////////

  void onEnable() override {
    digitalWrite(enablePin,0);
  }

//////////////////////////

  void onDisable() override {
    digitalWrite(enablePin,1);
  }

//////////////////////////

  StepperControl *setStepType(int mode) override {
    switch(mode){
      case FULL_STEP_TWO_PHASE:
        digitalWrite(m1Pin,LOW);
        digitalWrite(m2Pin,LOW);
        break;
      case HALF_STEP:
        digitalWrite(m1Pin,HIGH);
        digitalWrite(m2Pin,LOW);
        break;
      case QUARTER_STEP:
        digitalWrite(m1Pin,LOW);
        digitalWrite(m2Pin,HIGH);
        break;
      case EIGHTH_STEP:
        digitalWrite(m1Pin,HIGH);
        digitalWrite(m2Pin,HIGH);
        break;
      default:
        ESP_LOGE(STEPPER_TAG,"Unknown StepType=%d",mode);
    }
    return(this);
  }
  
};
```

---

[↩️](../README.md) Back to the Welcome page
