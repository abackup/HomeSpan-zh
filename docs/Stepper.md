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
