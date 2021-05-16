//
//  mulitpress.c
//  buttonpresslib
//
//  Created by Dorian Tolman on 12/16/20.
//  Copyright © 2020 Dorian Tolman. All rights reserved.
//
#ifndef mulitpress_h
#define mulitpress_h

#include <iostream>
using namespace std;

class PressCoder{
public:
    uint16_t returnCode;
    uint16_t minDuration;
    uint16_t maxDuration;
    //    uint32_t returnCode : 8, minDuration : 12, maxDuration : 12; //possible bit field
    //constructor
    PressCoder(uint16_t code, uint16_t min, uint16_t max=0xFFFF){
        returnCode = code;
        minDuration = min;
        maxDuration = max;
    }
    
    uint16_t checkButton(uint16_t currentCode, uint16_t pressDuration){
        
        if(pressDuration> minDuration && pressDuration < maxDuration){
            return returnCode;}
        else{
            return currentCode;
        }
    }
    
};



class ButtonInterpreter{ //this is the active button
public:
    
    
    uint16_t startPress=0;
    uint16_t endPress=0;
    uint16_t currentTime=0;
    
    uint16_t pressState=0; // not , down , pressed ,up
    uint16_t pressCode=0; //the user generated code for press time;
    
    uint16_t numberOfCodes=0;
    PressCoder *codes;
    
    bool isPressed:1,wasPressed:1,handled:1,used:1;
    
   
    //constructor
    ButtonInterpreter(PressCoder codesArray[],uint16_t numOfCodes){
        isPressed=0; wasPressed=0; handled=0; used=0;
        codes = codesArray;
        numberOfCodes =   numOfCodes;
    //    STATICnumOfButtons = 0;
    }
    
    
    void go(bool buttonState, uint16_t currentTimeMillis){ //Xgo
        currentTime = currentTimeMillis;
        isPressed = buttonState;
      
        //bellow are the four logic state of having 2 bools to control presses
        
        if (isPressed == false && wasPressed == false) { //not pressed no longer pressUp
            startPress = currentTimeMillis;
            pressState = 0;
            pressCode = 0;
            
        }
        
        if (isPressed == true && wasPressed == false) {
            pressState = 2; //may need to be changed to 1 becuase press down may be phased out
            pressCode = 0; //this is in here and the if() above in case of debounce on release
            //senerio-> on release the button is bounce pressed the next time around
            
            startPress = currentTimeMillis;
            wasPressed = true;
        }
        
        //end press timer , press up
        if(isPressed == false && wasPressed == true){
            endPress = currentTimeMillis;
            wasPressed = false;
            pressState =3;//pressup
            
        }
        
        uint16_t duration = currentTimeMillis - startPress;
        //MAYBE MAKE THIS ENDPRESS SO THAT duration() always works
        
        for (uint16_t i=0; i<numberOfCodes; i++) { //check what code where at.
            
            
            uint16_t tempPressCode = codes[i].checkButton(pressCode, duration);
            
            if (tempPressCode > pressCode || pressState == 3) { //if press code has gone up
                                            //this means that press codes must go sequencially when declared
                handled = true; //new button state make useage of state available
                pressCode = tempPressCode;
                
            }
        }
        
        
        used = true; //used is always reset
        /*  //not sure if this should be done below
        if(pressCode == 0 && pressState == 0){ //if press is dead it can't be handled or used
             handled = false;
              used = false;
        }
        */
    }
    uint16_t duration(){
        
        return endPress - startPress;

    }
    
    //these press comparisions should be moved to comparitor class
    
    bool onceIsPressed(uint16_t code){ //presed down and hits code argument
        
        if (pressState == 2  && pressCode == code && handled == true){
            //    cout << " once pressed = " << handled << endl;
            handled = false;
            return true;}
        
        return false;
    }
    bool useIsPressed(uint16_t code){ //presed down and hits code argument
        
        if (pressState == 2  && pressCode == code && used == true){
            used = false;
            return true;}
        
        return false;
    }
    bool alwaysIsPressed(uint16_t code){ //presed down and hits code argument
        
        if (pressCode == code ){
            return true;}
        
        return false;
    }
    bool alwaysIsPressedGreaterThan(uint16_t code){ //presed down and hits code argument
        
        if (pressCode >= code ){
            return true;}
        
        return false;
    }
    bool onceIsPressUp(uint16_t code){ //presed down and hits code argument
        
        if (pressState == 3  && pressCode == code && handled == true){
            //    cout << " once pressed = " << handled << endl;
            handled = false;
            return true;}
        
        return false;
    }
    
    
    
};
//handle types are how the button gets passed and compared through the program
enum HandleType{
    
    Once =1, //clears the handled bit, good for using a press 1 time
    Use =2, //clears the use bit, good for using once per loop
    Always =3, //will always be true if pressState and PressCode match
    UseGreaterThan =4, //same as Use but will be true if pressCode is greater than the one supplied
    AlwaysGreaterThan =5 //same as Always but will be true if pressCode is greater than the one supplied
    
};

enum PressState {
    Not = 0,
    //when the button comes down
    Down = 1, //don't us this. Debounce with pressCode == 1 //maybe use if you have hardware debounce or delay debounce
  
    Pressed = 2, Held = 2,  //while holding the button
  
    Up = 3,  Released =3 //when you lift of the button
   
    
};


#endif
