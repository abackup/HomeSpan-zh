

struct DEV_LED : Service::LightBulb {               

  int ledPin;                                      
  SpanCharacteristic *power;                       
  
  DEV_LED(int ledPin) : Service::LightBulb(){

    power=new Characteristic::On();                 
    this->ledPin=ledPin;                          
    pinMode(ledPin,OUTPUT);                      
  } 


  boolean update(){            

    digitalWrite(ledPin,power->getNewVal());       
   
    return(true);                                 
  
  }
};

