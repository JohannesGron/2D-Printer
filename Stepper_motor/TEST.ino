#include <Stepper.h>

const int stepsPerRevolution = 400;  // Steps per revolution/omgang for motoren

// Initialiserer stepper library for pin 8 til 13:
Stepper myStepperx(stepsPerRevolution, 8, 9, 12, 13); // Ændrer pins for x-retningen

void setup() {
  // initialisere serial portene:
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
}

void loop() {
  delay(2000);
  myStepperx.step(1);
}
