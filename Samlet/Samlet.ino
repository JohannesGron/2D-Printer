/*
Udgange:
  Joystick
   - A0 -> X-aksen
   - A1 -> Y-aksen
   - A2 -> Knap
   - A3 -> Tom

  Switch
   - A4 -> Switch(X)
   - A5 -> Switch(Y)

  Stepper 1 (X)
   - D04 -> Input 1
   - D05 -> Input 2
   - Do6 -> Input 3
   - Do7 -> Input 4

  Stepper 2 (Y)
   - D08 -> Input 1
   - D09 -> Input 2
   - D10 -> Input 3
   - D11 -> Input 4

  DCMotor 
   - D12 -> Input 1
   - D13 -> Input 2
*/


#include <Stepper.h>

//Joystick
const int xJoystick = A0;    
const int yJoystick = A1;
const int bJoystick = A2;

//Switch
const int switchX = A4;                                             
const int switchY = A5;                                             
             
//Stepper motor
Stepper stepperX(400, 4, 5, 6, 7);
Stepper stepperY(400, 8, 9, 10, 11);

//DC motor
const int DCinput1 = 12;
const int DCinput2 = 13;


const int maxX = 1000;                                              //Maks steps på x-aksen
const int maxY = 1000;                                              //Maks steps på y-aksen

int xPosition = 0;
int yPosition = 0;

boolean opstart = true;
boolean state = false;                                              //False = off, True = on
boolean working = false;
long previousMillis = 0;

void setup() {
  pinMode(DCinput1, OUTPUT);
  pinMode(DCinput2, OUTPUT);
}


void loop() {
  if (opstart) {
    int tempX = analogRead(switchX);
    int tempY = analogRead(switchY);
    if (tempX > 900 && tempY > 900) {
      opstart = false;
    } else {
      if (tempX < 900) {
        stepperX.step(-1);
      }
      if (tempY < 900) {
        stepperY.step(-1);
      } 
    }
  } else {
    if (working && (!state && millis() - previousMillis > 500) || (state && millis() - previousMillis > 300)) {
      working = false;
      state = !state;
      digitalWrite(DCinput1, LOW);
      digitalWrite(DCinput2, LOW);
    }
    
    int temp = analogRead(bJoystick);
    if (temp > 1000) {
      if (!state && !working) {
        working = true;
        previousMillis = millis();
        digitalWrite(DCinput1, HIGH);
        digitalWrite(DCinput2, LOW);
      }
    } else {
      if (state && !working) {
        working = true;
        previousMillis = millis();
        digitalWrite(DCinput1, LOW);
        digitalWrite(DCinput2, HIGH);
      }
    }
    moveStepper(joyPosition(xJoystick), joyPosition(yJoystick));    //Flytter postition for skyderen 
  }
}


int joyPosition(int analog) {
  int value = analogRead(analog);
  if (value < 150) {                                                
    return (-1);
  }
  else if (value < 873 ) {                                         
    return 0;
  }
  else {                                                         
    return 1;
  }
}


void moveStepper(int x, int y) {
  int temp = xPosition + x;
  if (temp >= 0 && temp <= maxX){
    stepperX.step(x);
    xPosition = temp;
  }

  int temp2 = yPosition + y;
  if (temp2 >= 0 && temp2 <= maxY){
    stepperY.step(y);
    yPosition = temp2;
  }
}
