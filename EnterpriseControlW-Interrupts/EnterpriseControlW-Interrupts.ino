/**
  Connect the COM and Normally Closed terminals 
  the the positive of the battery and the positive
  of the motor. 

  Look into the Progressive Automation Website to wire
  up the Linear Actuator.
*/


const int forwards = 13; //Attach to forward relay for LinAct
const int backwards = 10; //Attach to reverse relay for LinAct
const int MotorForward = 8; // Attach to motor relay
const int LinActButton = 9; //Control Pin for Linear Actuator
const int MotorButton = 2; //Control Pin for Motor

long MotorlastDebounceTime = 0;  // the last time the output pin was toggled
long MotordebounceDelay = 100; 
int MotorbuttonState;             // the current reading from the input pin
int MotorlastButtonState = LOW;   // the previous reading from the input pin
boolean spinning = false;

long LinActlastDebounceTime = 0;  // the last time the output pin was toggled
long LinActdebounceDelay = 100; 
int LinActbuttonState;             // the current reading from the input pin
int LinActlastButtonState = LOW;


void setup() {
 
pinMode(forwards, OUTPUT);//set relay as an output
pinMode(backwards, OUTPUT);//set relay as an output
pinMode(MotorForward, OUTPUT);
digitalWrite(forwards, LOW);
digitalWrite(backwards, LOW);
pinMode(LinActButton,INPUT);
pinMode(MotorButton, INPUT);
Motor(); 
Serial.begin(9600);

}

void loop() {
  // read the state of the switch into a local variable:
  int Motorreading = digitalRead(MotorButton);

  // If the switch changed, due to noise or pressing:
  if (Motorreading != MotorlastButtonState) {
    // reset the debouncing timer
    MotorlastDebounceTime = millis();
  }

  if ((millis() - MotorlastDebounceTime) > MotordebounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (Motorreading != MotorbuttonState) {
      MotorbuttonState = Motorreading;
      if (MotorbuttonState == HIGH) {
        spinning = !spinning;
        Motor();
      }
    }
  }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  MotorlastButtonState = Motorreading;
  
  /**
     This section is for Linear Actuator Control
     I want to press the button and then the actuator
     will extend. Wait 8 seconds and then retract.  
  */
  
  int LinActreading = digitalRead(LinActButton);

  // If the switch changed, due to noise or pressing:
  if (LinActreading != LinActlastButtonState) {
    // reset the debouncing timer
    LinActlastDebounceTime = millis();
  }

  if ((millis() - LinActlastDebounceTime) > LinActdebounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (LinActreading != LinActbuttonState) {
      LinActbuttonState = LinActreading;
      if (LinActbuttonState == HIGH) {
        LinAct();
      }
    }
  }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  LinActlastButtonState = LinActreading;

}

void LinAct() {
  
 attachInterrupt(digitalPinToInterrupt(MotorButton), Motor, RISING);
 
 Serial.println("Linear Actuator Cycle");

 digitalWrite(forwards, LOW);
 digitalWrite(backwards, HIGH);//Activate the relay one direction, they must be 
 //different to move the motor
 delay(4000); // wait 2 seconds

 digitalWrite(forwards, LOW);
 digitalWrite(backwards, LOW);//Deactivate both relays to brake the motor
 delay(2000);// wait 2 seconds

 digitalWrite(forwards, HIGH);
 digitalWrite(backwards, LOW);//Activate the relay the other direction, they must be different 
 //to move the motor
 delay(4000);// wait 2 seconds

 digitalWrite(forwards, LOW);
 digitalWrite(backwards, LOW);//Deactivate both relays to brake the motor
// delay(4000);// wait 2 seconds

 Serial.println("Linear Actuator Cycle Complete");
 Serial.println("");
 detachInterrupt(digitalPinToInterrupt(MotorButton));
}

void Motor(){
   Serial.println("Motor Function");
   Serial.println(spinning); 
   Serial.println("");
   if(spinning){
     digitalWrite(MotorForward, LOW); 
  }else if(!spinning){
     digitalWrite(MotorForward, HIGH);//Deactivate relay to brake the motor
  }
}
