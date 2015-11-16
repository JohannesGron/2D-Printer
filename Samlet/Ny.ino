#include <Stepper.h>                        //Vi inkluderer stepper biblioteket der gør det nemt at styre en stepper motor.
Stepper stepperX(400, 8, 9, 10, 11);        //Denne funktion laver en ny instans af Stepper klassen som repræsenterer vores stepper motor i x-retningen/y-retningen.
Stepper stepperY(400, 4, 5, 6, 7);          //Parameterne som vi angiver er: Stepper(steps/omdrejning, pin1, pin2, pin3, pin4)
const int joystickX = A0;                   //Navngiver analog0 (Beskriver joystickets position i x-aksen)
const int joystickY = A1;                   //Navngiver analog1 (Beskriver joystickets position i y-aksen)
const int switchx = A5;                     //Navngiver analog5 (Beskriver switchen værdi der sidder på y-aksen)
boolean opstart = true;                     //Variablen "opstart" fortæller om vi skal køre opstarts proceduren

int maxX = 2190;                            //Max steps på x-aksen
int xPosition = 0;                          //Flødeskumsdåsens position på x-aksen

int maxY = 2190;                            //Max steps på y-aksen
int yPosition = 0;                          //Flødeskumsdåsesn position på y-aksen


void setup() {
  Serial.begin(9600);
}

void loop() {
  if (opstart) {                            //Hvis dette er sandt kører vi opstarts proceduren
    int temp = analogRead(switchx);         //Vi læser spændingen på analog5
    if (temp > 1000) {                      //Hvis den er over 1000 så betyder det at der er forbindelse
      opstart = false;                      //Sætter vi variablen til at være = false
    } else {
      stepperX.step(-1);                    //Hvis der ikke er forbindelse gennem switchen(x) så skal stepper motoren flytte sig derhen imod
      delay(10);                            //Et lille delay så stepper motoren kan følge med
    }
  } else {
    moveStepper(joyPosition(joystickX), joyPosition(joystickY));  //Vi refererer til en funktion kaldt "moveStepper" med parameterne af en funktion for en switch
    delay(10);                              //Et lille delay så stepper motoren kan følge med
  }
}

int joyPosition(int analog) {                 //Dette er en funktion der returnerer en integer. Denne funkion har til opgave at returne retningen for joysticket
  int value = analogRead(analog);             //Arduinoen læser spændingen på den angivende joystick-port
  if (value < 150) {                          //Arduinoen omkriver spændingen på en analog port til et tal mellem 0 - 1023 (0V = 0, 5V = 1023).
    return (-1);                              //Hvis dette tal er under 150 så returnerer funktionen "-1"
  }
  else if (value < 873 ) {                    //Hvis tallet er under 873 så returnerer funktionen "0"
    return 0;
  }
  else {                                      //Hvis tallet er over 873 så returnerer funktionen "1"
    return 1;
  }
}


void moveStepper(int x, int y) {              //Dette er en funktion der imod overstående ikke returnerer en værdi. Denne funktion har til opgave at flytte stepper motoren
  if (x != 0) {                               //Hvis x-værdien af inputtet ikke er 0 så gør følgende
    int temp = xPosition + x;
    if (temp >= 0 && temp <= maxX){           //Tjekker om retningen for joysticket ikke overskrider en af vores grænser
      stepperX.step(x);                       //Hvis ikke så skal stepper motoren flytte sig i joystickets retning
      xPosition = temp;                       //Gemmer den nye position for flødeskumsdåsen
    }
  }
  if (y != 0) {                               //Hvis y-værdien af inputtet ikke er 0 så gør følgende
    int temp2 = yPosition + y;
    if (temp2 >= 0 && temp2 <= maxY){         //Tjekker om retningen for joysticket ikke overskrider en af vores grænser
      stepperY.step(y);                       //Hvis ikke så skal stepper motoren flytte sig i joystickets retning
      yPosition = temp2;                      //Gemmer den nye position for flødeskumsdåsen
    }
  }
}
