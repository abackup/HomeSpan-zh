////////////////////////////////////////////////////////////
//                                                        //
//    HomeSpan: A HomeKit implementation for the ESP32    //
//    ------------------------------------------------    //
//                                                        //
// Example 3: A simple on/off ceiling fan with an         //
//            on/off ceiling light                        //
//                                                        //
////////////////////////////////////////////////////////////


#include "HomeSpan.h"         

void setup() {

  
 
  Serial.begin(115200);      

  homeSpan.begin(Category::Fans,"HomeSpan Ceiling Fan");  

  new SpanAccessory();                             
  
    new Service::AccessoryInformation();            

    new Service::LightBulb();                       
      new Characteristic::On();                      


    new Service::Fan();                             
      new Characteristic::Active();                   


  new SpanAccessory();                              
    new Service::AccessoryInformation();            
      new Characteristic::Identify();                

    new Service::LightBulb();                       
      new Characteristic::On();                       



} 


void loop(){
  
  homeSpan.poll();       
  
} 
