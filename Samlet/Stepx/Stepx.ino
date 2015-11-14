#include <Stepper.h>

const int stepsPerRevolution = 400;                                 //Steps på en omgang
Stepper stepperX(stepsPerRevolution, 4, 5, 6, 7);                   //Fastgjort på jernet

const int switchX = A4;
boolean continuee = true;

long interval = 10;
long previousMillis = 0;
int count = 0;


void setup() {
  Serial.begin(9600);
}

void loop() {
  if (continuee) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > interval) {
      int temp = analogRead(switchX);
      if (temp > 1000) {
        continuee = false;
      } else {
        stepperX.step(-1);    //OBS
        count += 1;
        Serial.println(count);
      }   
    }
  }  
}
