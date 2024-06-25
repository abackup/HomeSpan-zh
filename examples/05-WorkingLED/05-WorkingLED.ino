////////////////////////////////////////////////////////////
//                                                        //
//    HomeSpan: A HomeKit implementation for the ESP32    //
//    ------------------------------------------------    //
//                                                        //
// Example 5: Two working on/off LEDs based on the        //
//            LightBulb Service                           //
//                                                        //
////////////////////////////////////////////////////////////


#include "HomeSpan.h" 
#include "DEV_LED.h"        

void setup() {

 

  Serial.begin(115200);

  homeSpan.begin(Category::Lighting,"HomeSpan LED");
  
  new SpanAccessory(); 
  
    new Service::AccessoryInformation(); 
      new Characteristic::Identify();                       

    new DEV_LED(16);        


  new SpanAccessory(); 
  
    new Service::AccessoryInformation();    
      new Characteristic::Identify();                       

  //  new Service::LightBulb();                     
  //    new Characteristic::On();                   
  
    new DEV_LED(17);                                

} 

void loop(){
  
  homeSpan.poll();
  
} 
