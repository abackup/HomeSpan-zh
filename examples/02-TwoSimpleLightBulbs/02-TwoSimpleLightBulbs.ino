////////////////////////////////////////////////////////////
//                                                        //
//    HomeSpan: A HomeKit implementation for the ESP32    //
//    ------------------------------------------------    //
//                                                        //
// Example 2: 两个不起作用的开/关灯泡                      //
//           由基本的 HomeSpan 组件构成                    //
//                                                        //
////////////////////////////////////////////////////////////


#include "HomeSpan.h"        

void setup() {


 
  Serial.begin(115200);

  homeSpan.begin(Category::Lighting,"HomeSpan LightBulb");   



  new SpanAccessory();                             
  
    new Service::AccessoryInformation();          
      new Characteristic::Identify();                 

    new Service::LightBulb();                       
      new Characteristic::On();                    


  new SpanAccessory();                              
  
    new Service::AccessoryInformation();           
      new Characteristic::Identify();                

    new Service::LightBulb();                      
      new Characteristic::On();                     


} 


void loop(){
  
  homeSpan.poll();         
  
} 
