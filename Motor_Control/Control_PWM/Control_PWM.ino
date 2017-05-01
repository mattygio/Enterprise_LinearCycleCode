/**
  Connect the COM and Normally Closed terminals 
  the the positive of the battery and the positive
  of the motor. 

  Look into the Progressive Automation Website to wire
  up the Linear Actuator.\
  
  Production Code. Uses PWM and BJT to gradully increase Motor Speed 
*/


const int forwards = 12; //Attach to Number 3 on relay
const int backwards = 8; //Attach to Number 4 on relay
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

digitalWrite(forwards, HIGH);
delay(5000);// 13 should retract it to an ideal location. Number might need some
//fine tuning
digitalWrite(forwards,LOW);
digitalWrite(backwards,HIGH);
delay(1600);
digitalWrite(backwards,LOW);
}

void loop() {
  
  while(!digitalRead(LinActButton));
  LinAct();

}

void LinAct() {
  
 Serial.println("Linear Actuator Cycle");
 
 Motor(true); // Starts the Motor
 delay(2000);

 digitalWrite(backwards, HIGH);//Activate the relay one direction, they must be 
 delay(22000); // wait 2 seconds

 digitalWrite(backwards, LOW);//Deactivate both relays to brake the LA
 delay(6000);// wait 2 seconds

 digitalWrite(forwards, HIGH);
 delay(22000);// wait 2 seconds

 digitalWrite(forwards, LOW);

 delay(1000);
 Motor(false); // Stops the Motor

 Serial.println("Linear Actuator Cycle Complete");
 Serial.println("");
 
}

void Motor(boolean spin){
   Serial.println("Motor Function");
   Serial.println(spin); 
   Serial.println("");
   int NumberofSteps = 51;
   
   if(spin){
      for(int steps = 0; steps < NumberofSteps; steps++){
        // 25 percent to 75 percent; .9*255 ~ 230
        //                            0*255 ~ 0
        analogWrite(MotorForward, steps*5);
        delay(80);
      }
  }else if(!spin){
    for(int steps = NumberofSteps; steps > 0; steps--){
        // 75 percent to 25 percent; .75*255 ~ 190
        //                            .25*255 ~ 65
        analogWrite(MotorForward, steps*5);
        delay(80);
      }
      analogWrite(MotorForward,0);
  }
}


