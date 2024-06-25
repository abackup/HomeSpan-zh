////////////////////////////////////////////////////////////
//                                                        //
//    HomeSpan: A HomeKit implementation for the ESP32    //
//    ------------------------------------------------    //
//                                                        //
// Example 4: 带可调光吸顶灯的变速吊扇                     //
//                                                        //
////////////////////////////////////////////////////////////


#include "HomeSpan.h"         

void setup() {


 
  Serial.begin(115200); 

  homeSpan.begin(Category::Fans,"HomeSpan Ceiling Fan");  

  new SpanAccessory();                            
  
    new Service::AccessoryInformation();                
      new Characteristic::Identify();                        

    new Service::LightBulb();                      
      new Characteristic::On(true);         

      (new Characteristic::Brightness(50))->setRange(20,100,5);    

    new Service::Fan();                             
      new Characteristic::Active();             
      new Characteristic::RotationDirection();                        
      (new Characteristic::RotationSpeed(50))->setRange(0,100,25);    

} 



void loop(){
  
  homeSpan.poll();        
  
} 
