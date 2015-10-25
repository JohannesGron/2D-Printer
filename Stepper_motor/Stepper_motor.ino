/*
 Stepper Motor Control - one step at a time

 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 13 of the Arduino.

 The motor will step one step at a time, very slowly.  You can use this to
 test that you've got the four wires of your stepper wired to the correct
 pins. If wired correctly, all steps should be in the same direction.

 Use this also to count the number of steps per revolution of your motor,
 if you don't know it.  Then plug that number into the oneRevolution
 example to see if you got it right.
 */

#include <Stepper.h>

const int stepsPerRevolution = 400;  // Steps per revolution/omgang for motoren

// Initialiserer stepper library for pin 8 til 13:
Stepper myStepperx(stepsPerRevolution, 8, 9, 12, 13); // Ændrer pins for x-retningen
Stepper mySteppery(stepsPerRevolution, 8, 9, 12, 13); // Ændrer pins for y-retningen

int stepCountx = 0;         // numre af steps motoren har taget i x-retningen
int stepCounty = 0;         // numre af steps motoren har taget i y-retningen

void setup() {
  // initialisere serial portene:
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
}

void loop() {
  //(skal slette int x = 1 og int y = 1). Vi indlæser x og y fra Joysticket.
  int x = 1; // slettes
  int y = 0; // slettes
  steppermotor(x, y);
}

void steppermotor(int x, int y){
  int maks = 1000; // Maks-værdien for x- og y-aksen så vi ved at den ikke kommer ud over maks.
  // Motor for x-retningen
  int xvariable = stepCountx + x;
  if (xvariable >= 0 && xvariable <= maks){
    myStepperx.step(x);
    stepCountx = xvariable;
  }

  // Motor for y-retningen
  int yvariable = stepCounty + y;
  if (yvariable >= 0 && yvariable <= maks){
    mySteppery.step(y);
    stepCounty = yvariable;
  }
  
  // Serial for at teste og se x- og y-værdierne 
  Serial.print("steps x: ");
  Serial.println(stepCountx);
  Serial.print("steps y: ");
  Serial.println(stepCounty);
  delay(100); //Delay som kan ændres så flødeskummet kan tilpasses med farten
}

/*
  if (stepCountx >= 1 && stepCountx < maks){ // stepCountx skal være større eller lig med 1, og stepCountx skal være mindre end maks-værdien.
    myStepperx.step(x);
    stepCountx = stepCountx + x;
  } else if (stepCountx == 0 && x == 1){ // stepCountx skal være lig med 0 og x skal være lig med 1.
    myStepperx.step(x);
    stepCountx = stepCountx + x;
  } else if (stepCountx == maks && x == -1){ // stepCountx skal være lig med maks og x lig med -1.
    myStepperx.step(x);
    stepCountx = stepCountx + x;
  }

  // Motor for y-retningen
  if (stepCounty >= 1 && stepCounty < maks){
    mySteppery.step(y);
    stepCounty = stepCounty + y;
  } else if (stepCounty == 0 && y == 1){
    mySteppery.step(y);
    stepCounty = stepCounty + y;
  } else if (stepCounty == maks && y == -1){
    mySteppery.step(y);
    stepCounty = stepCounty + y;
  }
*/
