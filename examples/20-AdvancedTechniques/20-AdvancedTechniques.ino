/*********************************************************************************
 *  MIT License
 *  
 *  Copyright (c) 2022 Gregg E. Berman
 *  
 *  https://github.com/HomeSpan/HomeSpan
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *  
 ********************************************************************************/

//////////////////////////////////////////////////////////////////
//                                                              //
//       HomeSpan: A HomeKit implementation for the ESP32       //
//       ------------------------------------------------       //
//                                                              //
// Example 20: Demonstrates various advance HomeSpan functions  //
//             by implementing a Bridge in which one or more    //
//             Lightbulb Accessories can be added and deleted   //  
//             *dynamically* without needing to restart the     //
//             device                                           //
//                                                              //
//////////////////////////////////////////////////////////////////

#include "HomeSpan.h"

    // 在示例 20 中，我们将实现一个桥接设备，最多支持 10 个灯泡配件。 但是，我们不是预先指定灯的数量，而是
   // 将允许用户通过 CLI 动态添加和删除 Light Accessories。 更改会反映在 Home App 中，无需重新启动
   // 设备！ 注意这个例子使用了各种高级 HomeSpan 函数，以及 ESP32-IDF 和 C++ 的一些详细特性，但没有使用
   // 在前面的任何示例中。

   // 我们将使用一个包含 10 个元素的 C++ 数组，其中包含表示实现的每个灯泡附件的灯“ID”的整数。 ID 为零表示没有
   // 在该元素中定义的光。
  
#include <array>                // 包含 C++ 标准库数组容器

std::array<int,10> lights;      // 将“lights”声明为 10 个整数的数组

using std::fill;                // 将 std 库函数 fill、remove 和 find 放入全局命名空间中，这样我们就可以在下面使用它们，而无需以“std::”开头
using std::remove;
using std::find;

  // 我们将使用非易失性存储 (NVS) 来存储灯阵列，以便设备可以在重启时恢复当前配置

nvs_handle savedData;           // 将 savdData 声明为要与 NVS 一起使用的句柄（有关如何使用 NVS 存储的详细信息，请参阅 ESP32-IDF）


//////////////////////////////////////

void setup() {

  Serial.begin(115200);

  fill(lights.begin(),lights.end(),0);                   // 用 10 个元素中的每个元素中的零初始化灯光数组（未定义灯光配件）
  
  size_t len;  
  nvs_open("SAVED_DATA",NVS_READWRITE,&savedData);       // 在 NVS 中打开一个名为 SAVED_DATA 的新命名空间
  if(!nvs_get_blob(savedData,"LIGHTS",NULL,&len))        // 如果找到 LIGHTS 数据
    nvs_get_blob(savedData,"LIGHTS",&lights,&len);       // 检索数据

  homeSpan.setLogLevel(1);

  homeSpan.begin(Category::Lighting,"HomeSpan Lights");

  // 我们首先创建桥接配件

  new SpanAccessory(1);                                   // 为了清楚起见，我们在这里指定了 AID=1（如果留空，它将默认为 1）
    new Service::AccessoryInformation();
      new Characteristic::Identify();
      new Characteristic::Model("HomeSpan Dynamic Bridge");     // 定义模型是可选的

  // 现在我们根据灯光阵列中记录的内容创建灯光配件
  // 我们将使用 C++ 迭代器遍历所有元素，直到到达数组的末尾，或者找到一个值为零的元素

  for(auto it=lights.begin(); it!=lights.end() && *it!=0; it++)       // 循环遍历所有元素（当我们到达末尾时停止，或者点击一个值为 0 的元素）
    addLight(*it);                                                    // 使用等于存储在该元素中的整数的参数调用 addLight（在下面进一步定义）

  // 接下来，我们创建四个用户定义的 CLI 命令，以便我们可以从 CLI 添加和删除 Light Accessories。
  // 每个命令的功能在下面进一步定义。

  new SpanUserCommand('a',"<num> - add a new light accessory with id=<num>",addAccessory);
  new SpanUserCommand('d',"<num> - delete a light accessory with id=<num>",deleteAccessory);
  new SpanUserCommand('D'," - delete ALL light accessories",deleteAllAccessories);  
  new SpanUserCommand('u',"- update accessories database",updateAccessories);

  // 最后我们调用 autoPoll 开始轮询后台。 请注意，这纯粹是可选的，仅用于说明如何使用 autoPoll - 您可以通过将其包含在 Arduino loop() 函数中来调用
  //通常的 homeSpan.poll() 函数

  homeSpan.autoPoll();
  
} // end of setup()

// 通常 Arduino loop() 函数会在此处定义。 但是由于我们在 setup() 函数中使用了 autoPoll，
// 在这个草图中，我们根本不需要定义 loop() 函数！ 为什么我们不会得到错误？ 因为 HomeSpan 包括
// 默认的 loop() 函数，它可以防止编译器抱怨 loop() 未定义。

///////////////////////////

// 此函数创建一个新的灯附件，其中 n 为“ID”。
// 在上面的 setup() 中最初调用它来创建基于 Light Accessories
//关于存储在灯光数组中的内容。 它也被称为响应
// 在 CLI 中输入“a”（见下文），它会动态添加新的 Light Accessory
// 当设备运行时。

void addLight(int n){

  char name[32];
  sprintf(name,"Light-%d",n);                    // 使用指定的“ID”创建设备名称
  char sNum[32];
  sprintf(sNum,"%0.10d",n);                      //从 ID 创建序列号 - 这在我们使用 Home 应用程序将 Light 重命名为其他名称时很有帮助
    
  Serial.printf("Adding Accessory: %s\n",name);
  
  new SpanAccessory(n+1);                       // 重要提示：加 1，因为第一个 AID=1 的附件已被桥接附件使用
    new Service::AccessoryInformation();
      new Characteristic::Identify();
      new Characteristic::Name(name);
      new Characteristic::SerialNumber(sNum);
    new Service::LightBulb();
      new Characteristic::On(0,true);  
}

///////////////////////////

// 响应在 CLI 中键入“@a <number>”调用此函数。
// 它通过调用上面的 addLight(num) 添加一个 ID=num 的新 Light Accessory。

void addAccessory(const char *buf){
 
  int n=atoi(buf+1);                                // 读取指定的 <num> 的值

  if(n<1){                                          // 确保 <num> 大于 0
    Serial.printf("Invalid Accessory number!\n");
    return;
  }

  if(find(lights.begin(),lights.end(),n)!=lights.end()){              // 在现有的灯光数组中搜索这个ID - 如果找到，报告错误并返回
    Serial.printf("Accessory Light-%d already implemented!\n",n);
    return;
  }
  
  auto it=find(lights.begin(),lights.end(),0);                        // 在灯光阵列中找到下一个“空闲”元素（第一个值为 0 的元素）
  
  if(it==lights.end()){                                                       //如果没有元素为零，则数组已满，无法添加新灯光
    Serial.printf("Can't add any more lights - max is %d!\n",lights.size());
    return;
  }

  *it=n;                                                        // 保存灯号
  nvs_set_blob(savedData,"LIGHTS",&lights,sizeof(lights));      // 更新 NVS 中的数据
  nvs_commit(savedData); 
  addLight(n);                                                  // 调用上面的函数添加灯光配件！
}

///////////////////////////

// 这个函数删除一个现有的 Light Accessory 并被调用
// 响应在 CLI 中键入“@d <num>”。

void deleteAccessory(const char *buf){

  int n=atoi(buf+1);                                  // 同上，我们读取指定的 <num> 并检查它是否有效（即大于 0）

  if(n<1){
    Serial.printf("Invalid Accessory number!\n");
    return;
  }

 // 下面我们使用homeSpan方法deleteAccessory(aid)来彻底删除AID=n+1的Accessory。
   // 我们加 1 因为第一个 Light Accessory 的 AID 是 2，因为 Bridge Accessory 的 AID 是 1。
   // 如果找到与 AID 匹配的 Accessory，则 deleteAccessory() 方法返回 true，否则返回 false。
   // 删除附件时，HomeSpan 将为每个 Service、Characteristic、loop() 方法打印一条删除消息，
   // button() 方法和 SpanButton，与该附件关联。 这些是 1 级日志消息，因此您需要
   // 将草图中的日志级别设置为 1 或 2 以接收输出。

  if(homeSpan.deleteAccessory(n+1)){                            // 如果 deleteAccessory() 为真，则已找到匹配项
    Serial.printf("Deleting Accessory: Light-%d\n",n);
  
    fill(remove(lights.begin(),lights.end(),n),lights.end(),0);     // 从灯光数组中删除条目并用零填充任何未定义的元素
    nvs_set_blob(savedData,"LIGHTS",&lights,sizeof(lights));        // update data in the NVS
    nvs_commit(savedData);
    
  } else {   
    Serial.printf("No such Accessory: Light-%d\n",n);
  }
}

///////////////////////////

void deleteAllAccessories(const char *buf){

// 调用此函数以响应在 CLI 中键入“@D”。
// 删除所有灯光配件

  if(lights[0]==0){                                                   // 首先通过检查灯[0] 中的非零 ID 来检查至少有一个灯附件
    Serial.printf("There are no Light Accessories to delete!\n");
    return;
  }

  for(auto it=lights.begin(); it!=lights.end() && *it!=0; it++)       // 使用迭代器循环遍历灯光数组中的所有非零元素...
    homeSpan.deleteAccessory(*it+1);                                  // ... 并删除匹配的Light Accessory（不要忘记将Light ID加1以形成AID）
  fill(lights.begin(),lights.end(),0);                          // 将灯光数组中的所有元素清零，因为所有灯光配件都已删除
  nvs_set_blob(savedData,"LIGHTS",&lights,sizeof(lights));      // update data in the NVS
  nvs_commit(savedData);

  Serial.printf("All Light Accessories deleted!\n");
}

///////////////////////////

//最后，我们有了最重要的 updateAccessories 函数。
// 这是响应在 CLI 中键入“@u”而调用的。
// 虽然上面的函数可以用来添加和删除Light Accessories
// 动态地，已经连接到的控制器，例如 Home App
// 设备还不知道已经添加了额外的灯光配件（或
// 从）整体附件数据中删除。 为了让他们知道，HomeSpan 需要
// 增加 HAP 配置编号并通过 MDNS 重新广播它，所以所有
// 连接的控制器知道他们需要从设备请求刷新。

// 当您在 CLI 中键入“@u”时，您应该会看到设备之间有很多活动
// 以及任何连接的控制器，因为它们请求刷新。 请耐心等待 - 最多可能需要
// 分钟，以便更改正确反映在 iPhone 或 Mac 上的家庭应用程序中。

void updateAccessories(const char *buf){

  // 请注意，如果数据库确实发生了变化（例如，添加了一个或多个新的 Light Accessories），updateDatabase() 方法返回 true，如果没有任何变化，则返回 false
  
  if(homeSpan.updateDatabase())
    Serial.printf("Accessories Database updated.  New configuration number broadcasted...\n");
  else
    Serial.printf("Nothing to update - no changes were made!\n");
}

///////////////////////////
