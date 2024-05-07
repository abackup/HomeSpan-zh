原文时间：2024.1.22 ，翻译时间：2024.5.7

# 电视服务和特点

HomeSpan 包括许多不属于 HAP-R2 的未记录的电视服务和特征。尽管更广泛的 HomeKit 社区已经确定了每个电视服务和特性的 UUID 和规范，但只有通过反复试验才能确定正确的使用方法。本页记录了使用 iOS 15.1 中提供的 Home 应用程序在 HomeSpan 中试验不同电视服务和特性的结果。本文档应该被认为是可靠的，但 Apple 当然可以随时更改 Home App 中此类服务和特征的行为，而无通知。

### `Category::Television`

使用 `Category::Television` 作为 `homeSpan.begin()` 中的类别来指定电视配件。这会导致 Home App 在附件列表中显示电视图标。然而，这似乎只适用于第一个实施的附件。如果您创建具有多个电视配件的设备，或将电视配件放置在桥接配件后面，则电视的图标将转换为通用 HomeKit 符号。

### `Service::Television()`

使用 `Service::Television()` 作为服务来创建电视配件图块。它支持两个主要特征：

* `Characteristic::Active()` - 这个 HAP-R2 标准特征用于打开或关闭电视。这是必需的特征

* `Characteristic::ConfiguredName()` - 这是 `Characteristic::Name()` 的可选电视特定版本，似乎是设置电视默认名称的唯一方法。与所有其他 HomeKit 服务不同，Home App 在与 `Service::Television()` 一起使用时会忽略使用 `Characeteristic::Name()` 指定的任何名称

基于上述内容，以下代码片段定义了一个带有基本开/关开关的简单电视配件：

```C++
new Service::Television();
  new Characteristic::Active(0);                    // set power to OFF at start-up
  new Characteristic::ConfiguredName("Sony TV");    // optional Characteristic to set name of TV
```
可以通过其他两个可选特性启用对电视的更高级控制：

* `Characteristic::RemoteKey()` - 这个只写的数字特性使 HomeSpan 能够从位于控制中心下的 iPhone 上的远程控制小部件中读取按钮按下。 这个小部件通常用于控制 Apple TV，但似乎上面创建的任何电视配件也可以通过远程控制小部件进行操作。 小部件的布局（不能修改）包括 4 个箭头、一个中央选择按钮、一个播放/暂停按钮、一个大的“后退”按钮和一个“信息”按钮。 当按下“键”时，Home App 会向 `Characteristic::RemoteKey()` 发送更新，HomeSpan 可以使用通常的 `update()` 方法读取该更新。 值如下：
* 
  * 4 = 向上箭头
  * 5 = 向下箭头
  * 6 = 左箭头
  * 7 = 右箭头
  * 8 = 中心选择按钮
  * 9 = 后退按钮
  * 11 = 播放/暂停按钮
  * 15 = 信息按钮
  
* `Characteristic::PowerModeSelection()` - 这个只写的特性导致文本“查看电视设置”出现在电视配件设置页面下的家庭应用程序中。 当按下此文本时，Home App 会向 `Characteristic::PowerModeSelection()` 发送一个 value=0 的更新，HomeSpan 可以使用通常的 `update()` 方法读取该更新
* 
* `Characteristic::ActiveIdentifier()` - 此数字 Characteristic 用于控制电视的输入源（例如 HDMI-1、HDMI-2、Netflix 等）。 它仅在使用 `Service::InputSource()` 定义和链接输入源时使用（见下文），在这种情况下它是*必需*特性

### `Service::InputSource()`

使用 `Service::InputSource()` 为电视创建新的输入源选择，例如 HDMI-1、HDMI-2、Netflix 等。`Service::InputSource()` 的使用是可选的 - 它是在没有选择不同输入源的能力的情况下创建电视服务完全可以。但是，如果使用，添加的每个输入源服务都应该在*与它所应用的电视服务相同的*附件中定义，并且***必须***使用 `addLink()` 链接到该电视服务。如果 Home App 发现任何未链接到电视服务的输入源服务，则会出现异常行为。

输入源可以出现在家庭应用程序中的两个位置。第一个位于输入源“选择器”中，当您打开电视的控件（即长按附件拼贴）时，该输入源“选择器”显示在开/关电源按钮下方。这是您更改电视输入源的方法。输入源出现的第二个位置是电视附件的设置页面。您可以在此处更改输入源的名称，以及配置是在输入源选择器中包含还是排除特定输入源。

总体思路是，您的草图应该实现一个包含所有潜在输入的完整列表的电视附件，使用与电视标签匹配的名称，例如“HDMI 1”、“组件 1”、“HDMI 2”等。如果您的电视遥控器有 Netflix、HBO Max、Amazon Prime 等专用按钮，您也可以将它们添加到列表中。创建此通用列表后，您可以直接从 Home 应用程序中重命名和启用每个输入源。例如，您可以将“HDMI 1”重命名为“Comcast Cable”，将“HDMI 2”重命名为“Sony Blue-Ray”。如果您没有连接到“组件 1”，您可以将其从输入源选择器中排除。这使得配置和重新配置您的电视输入源变得容易，而无需更改或更新您的 HomeSpan 草图。

所有这些都是通过使用以下一些或全部特征的组合来实现的：

* `Characteristic::ConfiguredName()` - 类似于应用于 `Service::Television()` 时的使用方式，此特征允许您设置输入源的默认名称。请注意，如果您在 Home 应用程序中更改输入源的名称，则会向 HomeSpan 发送带有新名称的更新，供您在需要时在草图中使用。这与用于许多其他服务的通常的 `Characteristic::Name()` 非常不同，并且在 Home App 中执行的名称更改永远不会传回附件

* `Characteristic::Identifier()` - 这个数字特征为每个输入源设置一个 ID。任何无符号的 32 位数字都可以用作 ID，只要它是*唯一的*并且不被同一电视服务中的任何其他输入源使用。当您使用 Home App 中的输入源选择器选择特定的输入源时，来自电视服务（见上文）的 `Characteristic::ActiveIdentifier()` 将更新为与所选输入对应的 ID 匹配的值资源。在 HomeSpan 中，您只需使用 `update()` 方法来确定何时更新 `Characteristic::ActiveIdentifer()`，并根据其值选择哪个输入源。 HomeKit 似乎不需要为输入源定义“Characteristic::Identifier()”。但是，如果没有设置，Home App 将不允许它在 Input Source Selector 中显示为选项，这违背了创建 Input Source 的目的！

* `Characteristic::IsConfigured()` - 此特征确定是否允许输入源作为选项出现在 Home 应用程序的输入源选择器中。如果定义了 IsConfigured() 并将其设置为 0，则输入源将出现在“设置”页面中，但将被排除在输入源选择器之外。如果 IsConfigured() 已定义并设置为 1，则输入源将出现在设置页面中，并且还将作为选项包含在输入源选择器中。如果没有为输入源定义 `Characteristic::IsConfigured()`，该源仍将作为选项出现在输入源选择器中，但它不会*出现在设置页面上的输入源列表中。这意味着您将无法从 Home App 重命名输入源，也无法在输入选择器中将其切换为允许的选项（见下文）

* `Characteristic::CurrentVisibilityState()` 和 `Characteristic::TargetVisibilityState()` - 这两个特征协同工作，就像任何当前状态/目标状态对一样。当为输入源定义这些时，如果还定义了“Characteristic::IsConfigured()”，则设置页面上输入源名称旁边会出现一个复选框切换。单击该复选框会导致 Home App 在 0 到 1 之间切换 TargetVisibilityState，其中 0 具有讽刺意味的是，该复选框是*选中*，而 1 表示它是*未选中*（与您的预期相反！）。如果您在 HomeSpan 中阅读此更新，则可以使用 `setVal()` 更改 CurrentVisibiltyState() 以匹配 TargetVisibilityState()。将 CurrentVisibilityState() 设置为 0 意味着输入源在输入源选择器中显示为一个选项。将 CurrentVisibilityState() 设置为 1 意味着它不会显示为选择。请注意，这些功能仅在使用 `Characteristic::Identifier()` 为输入源设置 ID 并且 IsConfigured() 已定义并设置为 1 时才起作用

### 例子

请参阅 [*文件 → 示例 → HomeSpan → 其他示例 → 电视*](../Other%20Examples/Television) 以获得完整的工作示例，以展示使用上述特征的不同组合的效果。 此外，不要忘记查看 [HomeSpan 项目](https://github.com/topics/homespan) 页面，了解一些真实世界的电视草图和控制器示例。


### 感谢

非常感谢@unreality 让 PR 包含了电视代码和相关功能！





---

[↩️](../README.md) 返回欢迎页面
