


#include "multiPressGroup.h" 
#include "defualtComparesCodes.hpp"

ButtonInterpreter buttonsInterpreter = ButtonInterpreter(defualtPressCodes, 3); //defualtPressCodes is in defualtComparesCodes.hpp 
                                       // ,3 his how many codes there are. This doens't use <arrays> but [arrays] 
                                   //so you need to tell the consturctor how many codes you have.
                                

bool pinState=false;


void setup() {
  Serial.begin(115200);

}

void loop() {
  

     uint16_t storedMillis = millis();

        byte threshold =11; 

        //esp32 touch 
         ////////// ////////// //////////
          if ( touchRead(T5) < threshold){
             delayMicroseconds(5); //Remove Ghost press sometimes esp32 will read touches that don't happen
          if ( touchRead(T5) < threshold){ 
          pinState = true;  }}else{  pinState = false; }
         


          //use the .go() to update the buttons
          buttonsInterpreter.go(pinState,  storedMillis);//the button interpreter handles everything

    if(clickUp.is(buttonsInterpreter)){ //short press automatically debounced
   Serial.println("clickUp");
    }
      if(clickUp.is(buttonsInterpreter)){//this handles the press so it can't be used again in the program
   Serial.println("Wont print becuase we alread used it");
    }
      if(clickDown.is(buttonsInterpreter)){ //will occur 1 time once the press is longer than debounce
   Serial.println("clickDown");
    }
    if(LpressUp.is(buttonsInterpreter)){//after 500ms and press up this occurs once
      Serial.println("\nlong clickUp");
    
    }
      if(HpressUp.is(buttonsInterpreter)){//after 2000ms and press up this occurs once
      Serial.println("\nHold (longer) clickUp");
    
    }
        if(HpressDown.is(buttonsInterpreter)){//after 2000ms and is pressed this occurs once
      Serial.println("\n Hold  clickDown");
    
    }
  if(LpressDownUse.is(buttonsInterpreter)){//same as LpressDown but will happen every loop
      Serial.print(".");
    
    }
    
   if(LpressDownUse.is(buttonsInterpreter)){//typically you'll use LpressDownUse with down. 
      Serial.println("wont occur because it's used this loop");
    
    }
    
     if(clickUpAlways.is(buttonsInterpreter)){//will happen if the click up is true no matter what
      Serial.println("always will happen");
    
    }

}
