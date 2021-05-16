// ESP32 Touch Test
// Just test touch pin - Touch0 is T0 which is on GPIO 4.
//#include "buttonduration.h"
//#include "multiPressGroupCleaned.h"
#include "defualtComparesCodes.hpp"

#include <iostream>
using namespace std;
void testSinglePress();
void testmultiPress();

 bool   pin2State =true;
 bool   pin3State =true;

//this is the object

   MultiPressButton testMultiButtons[3]; //create buttons for multi group
   MultiPressGroup testMultiPressGroup(testMultiButtons,3); //initialize multi group

void setup()
{
    testMultiPressGroup.waitTime = 2000; //default 3000

  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("ESP32 Touch Test");
}


 ButtonInterpreter testButton(defualtPressCodes, 3); //this should be called button interpreter;
                                    //
  
      
uint32_t debounceTest; //this is an iterator
uint16_t threshold =25;

static uint16_t lastTime=0; 
static uint16_t currentTime;
void loop()
{


if ( touchRead(T5) < threshold){
pin2State = true;  
}else{  pin2State = false; }

if ( touchRead(T3) < threshold){
pin3State = true;  
}else{  pin3State = false; }


testButton.go(pin2State, millis());

testMultiPressGroup.go(testButton);
    
 
 currentTime = millis();


  testmultiPress();
  //if( (uint16_t)(currentTime-lastTime) > 1000){
 
 testSinglePress();//}
 
}

void testmultiPress(){

if(testMultiPressGroup.waitComplete && clickClickComp.is(testMultiPressGroup)){
cout << " press press after wait"  << endl;
  
}
//if(testMultiPressGroup.waitComplete == true){
 //cout << currentTime << "  x  " << lastTime << " Last- current = " <<  (uint16_t)(currentTime-lastTime) << endl;  
 if( (uint16_t)(currentTime-lastTime) > 1000){


 cout << "number of presses  " << testMultiPressGroup.pressNumber << endl;

 for(int i =0; i<3; i++){
  cout << "press state "<< i << "  ="<<     testMultiPressGroup.buttons[i].pressState;
 cout << "  press code "<< i << "  ="<<     testMultiPressGroup.buttons[i].pressCode << endl;
 }

  cout << " wait true  :" << testMultiPressGroup.waitComplete << endl;

  lastTime =  currentTime;
 }


 
}

void testSinglePress(){
if(clickDown.is(testButton) ){
cout << "is PreZZed  " << debounceTest << endl;
 debounceTest++;

}
if(clickUp.is(testButton) ){
cout << "once is press UP" << endl;

}
if(clickUpUse.is(testButton) ){
cout << "use is press UP" << endl;

}
if(clickDown.is(testButton) ){
cout << "is Pressed shouldnt work"<< endl;

}
if(LpressDown.is(testButton) ){
cout << "long Pressed "<< endl;

}
if(HpressDown.is(testButton) ){
cout << "hold Pressed "<< endl;

}
if(HpressUp.is(testButton) ){
cout << "hold up "<< endl;

}
}
