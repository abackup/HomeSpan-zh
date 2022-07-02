#include "HomeSpan.h" 

void setup() {  
 
  Serial.begin(115200);    
  homeSpan.begin(Category::Lighting,"HomeSpan LightBulb");   
  
  new SpanAccessory();                            
    new Service::AccessoryInformation();           
      new Characteristic::Identify();                                                                   
//    new Characteristic::Manufacturer("HomeSpan");   // 配件的制造商（任意文本字符串，每个配件都可以相同）
//    new Characteristic::SerialNumber("123-ABC");    // 配件序列号（任意字符串，每个配件都可以相同）
//    new Characteristic::Model("120-Volt Lamp");     // 配件型号（任意字符串，每个配件都可以相同）
//    new Characteristic::FirmwareRevision("0.9");    // 配件的固件（任意文本字符串，每个配件都可以相同）
    new Service::LightBulb();                       // 创建灯泡服务
      new Characteristic::On();                       // 此服务需要“开”字符来打开和关闭灯

} // end of setup()


void loop(){
  
  homeSpan.poll();        
  
} 
