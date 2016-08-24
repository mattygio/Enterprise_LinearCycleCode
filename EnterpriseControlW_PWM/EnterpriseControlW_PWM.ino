/**
  Connect the COM and Normally Closed terminals 
  the the positive of the battery and the positive
  of the motor. 

  Look into the Progressive Automation Website to wire
  up the Linear Actuator.
*/


const int forwards = 12; //Attach to Number 3 on relay
const int backwards = 7; //Attach to Number 4 on relay
const int MotorForward = 10; // Attach to motor relay
const int LinActButton = 9; //Control Pin for Linear Actuator
const int MotorButton = 3; //Control Pin for Motor

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
Motor(spinning); 
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
        Motor(spinning);
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
  
 Serial.println("Linear Actuator Cycle");

// digitalWrite(forwards, LOW);
 digitalWrite(backwards, HIGH);//Activate the relay one direction, they must be 
 //different to move the motor
 delay(4000); // wait 2 seconds

// digitalWrite(forwards, LOW);
 digitalWrite(backwards, LOW);//Deactivate both relays to brake the motor
 delay(2000);// wait 2 seconds

 digitalWrite(forwards, HIGH);
// digitalWrite(backwards, LOW);//Activate the relay the other direction, they must be different 
 //to move the motor
 delay(4000);// wait 2 seconds

 digitalWrite(forwards, LOW);
// digitalWrite(backwards, LOW);//Deactivate both relays to brake the motor
// delay(4000);// wait 2 seconds

 Serial.println("Linear Actuator Cycle Complete");
 Serial.println("");
}

void Motor(boolean spin){
   Serial.println("Motor Function");
   Serial.println(spin); 
   Serial.println("");
   if(spin){
     setPwmFrequency(MotorForward, 1024);

     
//     for(int i = 0; i < 200000; i++) 
//     {
//       digitalWrite(MotorForward,HIGH);
//       delay(50);
//       digitalWrite(MotorForward,LOW);
//       delay(50);
//     }
     analogWrite(MotorForward, 255*.5); //Using 50% duty cycle 
     //so it goes at 50% of full speed
  }else if(!spin){
     digitalWrite(MotorForward, HIGH);//Deactivate relay to brake the motor
  }
}

/**
 * Divides a given PWM pin frequency by a divisor.
 * 
 * The resulting frequency is equal to the base frequency divided by
 * the given divisor:
 *   - Base frequencies:
 *      o The base frequency for pins 3, 9, 10, and 11 is 31250 Hz.
 *      o The base frequency for pins 5 and 6 is 62500 Hz.
 *   - Divisors:
 *      o The divisors available on pins 5, 6, 9 and 10 are: 1, 8, 64,
 *        256, and 1024.
 *      o The divisors available on pins 3 and 11 are: 1, 8, 32, 64,
 *        128, 256, and 1024.
 * 
 * PWM frequencies are tied together in pairs of pins. If one in a
 * pair is changed, the other is also changed to match:
 *   - Pins 5 and 6 are paired on timer0
 *   - Pins 9 and 10 are paired on timer1
 *   - Pins 3 and 11 are paired on timer2
 * 
 * Note that this function will have side effects on anything else
 * that uses timers:
 *   - Changes on pins 3, 5, 6, or 11 may cause the delay() and
 *     millis() functions to stop working. Other timing-related
 *     functions may also be affected.
 *   - Changes on pins 9 or 10 will cause the Servo library to function
 *     incorrectly.
 * 
 * Thanks to macegr of the Arduino forums for his documentation of the
 * PWM frequency divisors. His post can be viewed at:
 *   http://forum.arduino.cc/index.php?topic=16612#msg121031
 */
void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x7; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}
