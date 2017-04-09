
#include <LedControl.h>
#include <binary.h>

LedControl lc1 = LedControl(11,10,9,1);
//data pin 11
//clock pin 10
//csPin 9
//1 device total
int T = 200;
int intensity = 1;
int number = 1;
bool on = true;

void setup() {
  lc1.setIntensity(0,15); //Intensity goes from 0 to 15
  lc1.clearDisplay(0);
  lc1.shutdown(0, false);
  
}

void loop() {

     // valid coordinates 00 01 02 03
     //                   10 11 12 13
   
   lc1.setLed(0,1,4,on);
   on = !on;

     
   for(int i = 0; i < 2; i++){   //Lights all the LEDs in a row
     for(int j = 0; j < 4;j++){
       lc1.setLed(0,i,j,true);
       delay(T);
//         lc1.setLed(0,i,j,false); //uncomment this to have the light cycle along
     }
   } 
   
   for(int i = 0; i < 2; i++){ //Turns off all the LEDs in a row
     for(int j = 0; j < 4;j++){
       lc1.setLed(0,i,j,false);
       delay(T); 
     }
   } 
//     if(intensity == 16){ //Changes the intensity at each iteration
//       number = -1;
//     }else if(intensity == 1)
//     {
//        number = 1; 
//     }

//     lc1.setRow(0,0,B10100000); //alternates the LEDs in a row
//     lc1.setRow(0,1,B10010000);
//     delay(T);
//     lc1.setRow(0,0,B01010000);
//     lc1.setRow(0,1,B01100000);
//     delay(T);
//     
//     lc1.setIntensity(0,intensity);
//     intensity+=number;
  lc1.setIntensity(0,15);

     
}
