#include <Stepper.h>

const int stepsPerRevolution = 400;                                 //Steps på en omgang
Stepper stepperY(stepsPerRevolution, 8, 9, 10, 11);                   //Fastgjort på jernet

const int switchY = A5;
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
      int temp = analogRead(switchY);
      if (temp > 1000) {
        continuee = false;
      } else {
        stepperY.step(-1);    //OBS
        count += 1;
        Serial.println(count);
      }   
    }
  }  
}
