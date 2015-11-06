/*
Udgange:
  Joystick
   - A0 -> x-aksen
   - A1 -> y-aksen
   - A2 -> knap
   - A3 -> Tom

  Stepper 1 (Fastgjort på jernet)
   - D04 -> Input 1
   - D05 -> Input 2
   - Do6 -> Input 3
   - Do7 -> Input 4

  Stepper 2 (Fastgjort til plastikken)
   - D08 -> Input 1
   - D09 -> Input 2
   - D10 -> Input 3
   - D11 -> Input 4

  Switch
   - A4 -> switch på jern
   - A5 -> switch på plastik
*/



#include <Stepper.h>

const int xJoystick = A0;    
const int yJoystick = A1;
const int buttonJoystick = A2;

const int switchX = A4;                                             //HUSK AT ÆNDRE
const int switchY = A5;                                             //HUSK AT ÆNDRE
             

const int stepsPerRevolution = 400;                                 //Steps på en omgang
const int maxX = 1000;                                              //Maks steps på x-aksen
const int maxY = 1000;                                              //Maks steps på y-aksen
int xPosition = 0;
int yPosition = 0;

Stepper stepperX(stepsPerRevolution, 4, 5, 6, 7);                   //Fastgjort på jernet
Stepper stepperY(stepsPerRevolution, 8, 9, 10, 11);                 //Fastgjort til plastikken

boolean start = true;


void setup() {
 
}


void loop() {
  if (start) {
    int tempX = analogRead(switchX);
    int tempY = analogRead(switchY);
    if (tempX > 900 && tempY > 900) {
      start = false;
    } else {
      if (tempX < 900) {
        stepperX.step(-1);
      }
      if (tempY < 900) {
        stepperY.step(-1);
      }  
    }
  } else {
    moveStepper(joyPosition(xJoystick), joyPosition(yJoystick));    //Flytter postition for skyderen 
  }
}


int joyPosition(int analog) {
  int value = analogRead(analog);
  if (value < 400) {                                                //hvis værdien er mindre en end 400
    return (-1);
  }
  else if (value < 600 ) {                                          //hvis værdien er i mellem 400 og 600
    return 0;
  }
  else {                                                            //hvis værdien er over 600
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
