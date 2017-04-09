
/* Production Code for the Enterprise
 *  The control groups will be 00 01 02 03 04 05 06 07
 *  Group 1 = 00 01; inner LED
 *  Group 2 = 02 03; 2nd to inner LED
 *  Group 3 = 04 05; 2nd to outer LED
 *  Group 4 = 06 07; outer LED
 *  Written by Matt Giovannucci
 *  4/9/17
 *  
 *  Notes to self on style of LEDs
 *  1. light up one from inner circle to outer circle
 *  2. turn off one from inner circle to outer circle
 *  3. Turn each LED on from inner circle to outer circle while 
 *    keeping them all on. then flash them twice
 *  4. Randomly turn on one LED and flash and turn off
 */
 
#include <LedControl.h>
#include <binary.h>

LedControl lc1 = LedControl(11,10,9,1);
//data pin 11
//clock pin 10
//csPin 9
//1 device total
int T = 200;
int state;

void setup() {
  lc1.setIntensity(0,15); //Intensity goes from 0 to 15
  lc1.clearDisplay(0);
  lc1.shutdown(0, false);
  
}

void loop() {

     // valid coordinates 00 01 02 03
     //                   10 11 12 13
  state = random(4);
  if (state == 0){
    State0();
  }
  else if(state == 1){
    State1();
  }
  else if(state == 2){
    State2();
  }
  else if(state == 3){
    State3();
  }

  
} // end loop

void State0(){ // Walk one by one LED from the center to the ends
  setALL_LEDs(false);
  for(int j = 0; j < 5; j++){ // cycle 5 times
    for(int i = 0; i<4; i++){ // step through each LED
      setControl_Group(i,true);
      delay(T);
      setControl_Group(i,false);
    }
    setALL_LEDs(true);
    delay(T*3);
    setALL_LEDs(false);
    delay(T/2);
  }
}

void State1(){
  setALL_LEDs(true);
  for(int j = 0; j < 5; j++){ // cycle 5 times
    for(int i = 0; i<4; i++){ // step through each LED
      setControl_Group(i,false);
      delay(T);
      setControl_Group(i,true);
    }
    setALL_LEDs(false);
    delay(T*2);
    setALL_LEDs(true);
    delay(T/2);
  }
}

void State2() {
  setALL_LEDs(false);
  for(int j = 0; j < 5; j++){ // cycle 5 times
    for(int i = 0; i<4; i++){ // step through each LED
      setControl_Group(i,true);
      delay(T);
      for(int k = 0; k < 3; k++){
        setALL_LEDs(false);
        delay(T/2);
        setALL_LEDs(true);
        delay(T/2);
      }
    }
  }
}

void State3(){
  int Group;
  bool onoff[] = {true,true,true,true};
  setALL_LEDs(true);
  for(int h = 0; h < 20; h++){
    Group = random(4);
    setControl_Group(Group,onoff[Group]);
    onoff[Group] = !onoff[Group];
  }
}


void setControl_Group(int GroupNum, bool onoff)
{
  if (GroupNum == 0){
      lc1.setLed(0,0,0,onoff);
      lc1.setLed(0,0,1,onoff);
  }
  else if (GroupNum == 1){
      lc1.setLed(0,0,2,onoff);
      lc1.setLed(0,0,3,onoff);
  }
  else if (GroupNum == 2){
      lc1.setLed(0,0,4,onoff);
      lc1.setLed(0,0,5,onoff);
  }
    else if (GroupNum == 3){
      lc1.setLed(0,0,6,onoff);
      lc1.setLed(0,0,7,onoff);
  }
}

void setALL_LEDs(bool onoff){
  lc1.setLed(0,0,0,onoff);
  lc1.setLed(0,0,1,onoff);
  lc1.setLed(0,0,2,onoff);
  lc1.setLed(0,0,3,onoff);
  lc1.setLed(0,0,4,onoff);
  lc1.setLed(0,0,5,onoff);
  lc1.setLed(0,0,6,onoff);
  lc1.setLed(0,0,7,onoff);
}


