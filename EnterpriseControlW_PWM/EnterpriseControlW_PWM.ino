/**
  Connect the COM and Normally Closed terminals 
  the the positive of the battery and the positive
  of the motor. 

  Look into the Progressive Automation Website to wire
  up the Linear Actuator.\
  
  Production Code. Uses PWM and BJT to gradully increase Motor Speed 
*/


const int forwards = 12; //Attach to Number 3 on relay
const int backwards = 7; //Attach to Number 4 on relay
const int MotorForward = 10; // Attach to motor relay
const int LinActButton = 9; //Control Pin for Linear Actuator

void setup() {
pinMode(forwards, OUTPUT);//set relay as an output
pinMode(backwards, OUTPUT);//set relay as an output
pinMode(MotorForward, OUTPUT);
digitalWrite(forwards, LOW);
digitalWrite(backwards, LOW);
pinMode(LinActButton,INPUT);

analogWrite(MotorForward,0); // sets motor to not be moving
Serial.begin(9600);

digitalWrite(backwards, HIGH); //Fully extends the Linear Actuator to position it
delay(17000); //17 seconds should extend it all the way
digitalWrite(backwards,LOW); // flip it into reverse.
digitalWrite(forwards, HIGH);
delay(13000);// 13 should retract it to an ideal location. Number might need some
//fine tuning
digitalWrite(forwards,LOW);
}

void loop() {
  
  while(!digitalRead(LinActButton));
  LinAct();

}

void LinAct() {
  
 Serial.println("Linear Actuator Cycle");
 
 Motor(true); // Starts the Motor

 digitalWrite(backwards, HIGH);//Activate the relay one direction, they must be 
 delay(10000); // wait 2 seconds

 digitalWrite(backwards, LOW);//Deactivate both relays to brake the motor
 delay(8000);// wait 2 seconds

 digitalWrite(forwards, HIGH);
 delay(10000);// wait 2 seconds

 digitalWrite(forwards, LOW);

  Motor(false); // Stops the Motor

 Serial.println("Linear Actuator Cycle Complete");
 Serial.println("");
 
}

void Motor(boolean spin){
   Serial.println("Motor Function");
   Serial.println(spin); 
   Serial.println("");
   if(spin){
     
      for(int steps = 0; steps < 26; steps++){
        // 25 percent to 75 percent; .75*255 ~ 190
        //                            .25*255 ~ 65
        analogWrite(MotorForward, steps*5 + 65);
        delay(50);
      }
     
  }else if(!spin){

    for(int steps = 25; steps > 0; steps--){
        // 75 percent to 25 percent; .75*255 ~ 190
        //                            .25*255 ~ 65
        analogWrite(MotorForward, steps*5 + 65);
        delay(50);
      }
      analogWrite(MotorForward,0);
  }
}


