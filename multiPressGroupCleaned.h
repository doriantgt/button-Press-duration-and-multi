//
//  multiPressGroup.cpp
//  buttonpresslib
//
//  Created by Dorian Tolman on 12/19/20.
//  Copyright © 2020 Dorian Tolman. All rights reserved.
//
#ifndef multiPressGroupCleaned_h
#define multiPressGroupCleaned_h

#include <iostream>
using namespace std;

#include "buttonduration.h"



class MultiPressButton{ //used in an single dimension array
public:
    uint16_t pressState; // not 0 , down 1, pressed 2,up 3
    uint16_t pressCode; //the user generated code for press time/duration;
    
    bool handled; //handled resets once per loop
    bool used;    //used is only true once
    
};
class MultiPressGroup{
public:
    uint16_t waitTime=3000;
    
    uint16_t startWait=0;
    uint16_t endWait=0;
    
    bool waitComplete=false; //end wait. end when true
    
    uint16_t numberOfPresses=0; //how many presses do you go up to
    uint16_t pressNumber=0; //which press are you on
    MultiPressButton *buttons;
    
    //constructor
    MultiPressGroup( MultiPressButton btns[], uint16_t numPresses){
        numberOfPresses = numPresses;
        buttons = btns;
    };
    
    void go( ButtonInterpreter inputButton){
        endWait = inputButton.currentTime;
    
        
        if (waitComplete) { //this used to be at the end
            waitComplete= false;

            pressNumber = 0;
            for (uint16_t i =0; i < numberOfPresses; i++) {
                buttons[i].pressCode = 0;
                buttons[i].pressState = 0;
            }
        }
        
        
        
        if (pressNumber<numberOfPresses) { //prevent bad access
            
            buttons[pressNumber].pressCode = inputButton.pressCode;
            buttons[pressNumber].pressState = inputButton.pressState;
            buttons[pressNumber].handled = inputButton.handled;
            buttons[pressNumber].used = inputButton.used;
            
            //   if( buttons[pressNumber].pressState != inputButton.pressState
            //      || buttons[pressNumber].pressCode != inputButton.pressCode){ }//do we need to do this?
            
            
        }
        
        
        
        if(pressNumber>numberOfPresses){ //end when press released at max number
        //    waitComplete = true;
            //do nothing?
        }
        
        
        if(waitTime < (uint16_t)(endWait - startWait)){
            waitComplete = true;
            
        }
        
        //reset multiPress
        if (inputButton.isPressed == false && inputButton.wasPressed == false && waitComplete == true) {
            pressNumber = 0;
            
        }
        
        //incriment button press when pressed up
        //start the wait countdown
        if(inputButton.pressState == 3 && inputButton.pressCode > 0 ){ //press up and has a code
            pressNumber++;
            startWait = inputButton.currentTime;
        }
        
        //prevent wait from starting when pressed
        if(inputButton.pressState > 0 && inputButton.pressCode > 0 ){
            startWait = inputButton.currentTime;
        }
        
        
        
        
        
    };
    //use only with press up events
    //if you use this funcion on a pressed event it will function oddly becuse the group will reset
    //but the button suppling the group will not.
    void resetMultiPress(){ //we don't want to clear the buttons here because it would stop the pass here
        //ie we want the the button to clear when reading the next button
        waitComplete = true;
    }
    
};










////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class ButComp {
public:
    
    uint16_t pressState=0; // not , down , pressed ,up
    uint16_t pressCode=0; //the user generated code for press time;
    uint16_t handleType=0; //0 handle/Once , use/1 every loop, 2 always
    
    bool handled=0; //this is like a
    bool used=0;
    
    ButComp(){};
    //constructor
    //  this was my original idea but I didn't like having the press type as an argument
    ButComp(uint16_t pressStateIn, uint16_t presscodeIn, HandleType handleTypeIn ){
        
        pressState = pressStateIn;
        pressCode = presscodeIn;
        handleType =  handleTypeIn;
    }
    
    
    //compare regular button
    bool is( ButtonInterpreter &inputButton){
        //maybe we don't need these
        bool isButtonTrue = false;
     
        //only handle if the state and code match
        if(inputButton.pressState == pressState && inputButton.pressCode == pressCode){ //does that state and code match?
        
            if ( handleType == 1 && inputButton.handled == true ) { // do one time
                inputButton.handled = false;
                isButtonTrue = true;
            }else if ( handleType == 2 &&  inputButton.used == true){ //use one time
                inputButton.used = false;
                isButtonTrue = true;
             }else if ( handleType == 3 ){
                 isButtonTrue = true;
             }
        }
        
        
        if(inputButton.pressState == pressState && inputButton.pressCode > pressCode){ //does that state and code match?
            if(handleType == 4 && inputButton.used == true ) {//presscode greater than used
                inputButton.used = false;
                isButtonTrue   = true;
            }else if( handleType == 5){ //presscode greater than always
                  isButtonTrue = true;
            }
        }
        
        return isButtonTrue;
    }
    

//????????????????????????????????????????????????????????
    //compare multipress button
    bool is(MultiPressButton &inputButton){
        //maybe we don't need these
        bool isButtonTrue = false;
     
        //only handle if the state and code match
            if(inputButton.pressState == pressState && inputButton.pressCode == pressCode){ //does
           
                if ( handleType == 1 && inputButton.handled == true ) { // do one time
                    inputButton.handled = false;
                    isButtonTrue = true;
                }else if ( handleType == 2 &&  inputButton.used == true){ //use one time
                    inputButton.used = false;
                    isButtonTrue = true;
                }else if ( handleType == 3 ){
                    isButtonTrue = true;
                }
        }
        
        
        
        if(inputButton.pressState == pressState && inputButton.pressCode > pressCode){ //does that state and code match?
            if(handleType == 4 && inputButton.used == true ) {//presscode greater than used
                isButtonTrue   = true;
                inputButton.used = false;
            }else if( handleType == 5){ //presscode greater than always
                isButtonTrue = true;
            }
        }
        
        return isButtonTrue;
    }
    
    
    /*
    //when a press code changes it makes handled true
    void onceIsPressed(uint16_t code){ //presed down and hits code argument
        pressState = 2;
        pressCode = code;
        handleType = 1;
        
    }
    
    void useIsPressed(uint16_t code){ //presed down and hits code argument
        pressState = 2;
        pressCode = code;
        handleType = 2;
        
    }
    void useIsPressUp(uint16_t code){ //presed down and hits code argument
        //press up once is redundant becuase it can only be pressed up through 1 cycle
        //lets make its handle type use
        pressState = 3;
        pressCode = code;
        handleType = 2;
    }
    void onceIsPressUp(uint16_t code){ //presed down and hits code argument
        pressState = 3;
        pressCode = code;
        handleType = 1;
        
    }
    void alwaysIsPressed(uint16_t code){ //presed down and hits code argument
        pressState = 2;
        pressCode = code;
        handleType = 3;
        
    }
    
    void alwaysIsPressedGreaterThan(uint16_t code){ //presed down and hits code argument
        
        pressState = 2;
        pressCode = code;
        handleType = 5;
    }
    void UseIsPressedGreaterThan(uint16_t code){ //presed down and hits code argument
        
        pressState = 2;
        pressCode = code;
        handleType = 4;
    }
    
    
    */
    
};


class compareMulitButton{
public:
    uint16_t pressState=0; // not , down , pressed ,up
    uint16_t pressCode=0; //the user generated code for press time;
    
    uint16_t handleType=0; //0 handle/Once , use/1 every loop, 2 always
    bool handled=0; //this is like a
    bool used=0;
    compareMulitButton(){};
    //constructor
    //  this was my original idea but I didn't like having the press type as an argument
    compareMulitButton(uint16_t pressStateIn, uint16_t presscodeIn, HandleType handleTypeIn ){

        pressState = pressStateIn;
        pressCode = presscodeIn;
        handleType =  handleTypeIn;
        
    }
    
    
    bool is(ButComp &inputButton){
        //maybe we don't need these
       bool isButtonTrue = false; //maybe rename to allTrue

        //only handle if the state and code match
        if(inputButton.pressState == pressState && inputButton.pressCode == pressCode){ //does the state and code match?
            if ( handleType == 1 && inputButton.handled == true ) { // do one time
                inputButton.handled = false;
                isButtonTrue = true;
            }else if ( handleType == 2 &&  inputButton.used == true){ //use one time
                inputButton.used = false;
               isButtonTrue = true;
            }
        }
        
        
        
        if(inputButton.pressState == pressState && inputButton.pressCode > pressCode){ //does that state and code match?
            if(handleType == 4 && inputButton.used == true ) {//presscode greater than used
                isButtonTrue   = true;
                inputButton.used = false;
            }else if( handleType == 5){ //presscode greater than always
                isButtonTrue = true;
            }
        }
        
        return isButtonTrue;
    }
    
    //convenenience constructorish functions
    /*
    //when a press code changes it makes handled true
    void onceIsPressed(uint16_t code){ //presed down and hits code argument
        pressState = 2;
        pressCode = code;
        handleType = 1;
        
    }
    
    void useIsPressed(uint16_t code){ //presed down and hits code argument
        pressState = 2;
        pressCode = code;
        handleType = 2;
        
    }
    void useIsPressUp(uint16_t code){ //presed down and hits code argument
        //press up once is redundant becuase it can only be pressed up through 1 cycle
        //lets make its handle type use
        pressState = 3;
        pressCode = code;
        handleType = 2;
    }
    void onceIsPressUp(uint16_t code){ //presed down and hits code argument
        pressState = 3;
        pressCode = code;
        handleType = 1;
        
    }
    void alwaysIsPressed(uint16_t code){ //presed down and hits code argument
        pressState = 2;
        pressCode = code;
        handleType = 3;
        
    }
    
    void alwaysIsPressedGreaterThan(uint16_t code){ //presed down and hits code argument
        
        pressState = 2;
        pressCode = code;
        handleType = 5;
    }
    void UseIsPressedGreaterThan(uint16_t code){ //presed down and hits code argument
        
        pressState = 2;
        pressCode = code;
        handleType = 4;
    }
    
    */
};

class MultiCompareGroup{
public:
    uint16_t numberOfPresses=0;
    uint16_t arrayOrPtrs=0; //0 not initialized, 1 array, 2 array of ptrs
    
    ButComp *compareButtonsArray;// compareMulitButton ARRAY
    ButComp **compareButtonsPtrs;// compareMulitButton ARRAY OF PTRS to save memeory

    //constructor
    
    MultiCompareGroup( ButComp btns[], uint16_t numPresses){ ///array of buttonComparers
        numberOfPresses = numPresses;
        compareButtonsArray = btns;
        arrayOrPtrs =1;
    };
    
    MultiCompareGroup( ButComp* btns[], uint16_t numPresses){ //array of pointers to butttonComparers
        numberOfPresses = numPresses;
        compareButtonsPtrs = btns;
        arrayOrPtrs =2;

    };
    

    
    bool  is( MultiPressGroup inputButtonGroup){ //MultiPressButton
        bool allTrue = true;
        
      
        
        //we have to create temporary buttons to preserve the state of the incoming button if it doesn't change
        MultiPressButton tempArray[inputButtonGroup.numberOfPresses];
       
        for( uint16_t i=0 ; i< numberOfPresses; i++) {
            tempArray[i] = inputButtonGroup.buttons[i];
        }
    
        //create a multiPress group.
        MultiPressGroup tempGroup( tempArray , inputButtonGroup.numberOfPresses); //temp group
        
        
        for( uint16_t i=0 ; i< numberOfPresses; i++) {
            
            if(arrayOrPtrs == 1){//array of compares used
            if( compareButtonsArray[i].is( tempArray[i] ) == false ){
                
                allTrue = false;

            }
            }else{ //  if(arrayOrPtrs == 2){//array of pointers compares used
            
                if( compareButtonsPtrs[i]->is( tempArray[i]) == false ){
                    
                    allTrue = false;
                 
                }
            }
        }
        if(allTrue){
           // cout << "Perfect match!  Perfect match!  Perfect match!"  << endl;
            
            for( uint16_t i=0 ; i< numberOfPresses; i++) {
                inputButtonGroup.buttons[i] = tempArray[i];
            }
            
        }
        return allTrue;
    }
};

#endif
