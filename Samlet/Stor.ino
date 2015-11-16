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


#include <Stepper.h>                          //Vi inkluderer stepper biblioteket der gør det nemt at styre en stepper motor.

const int xJoystick = A0;                     //Navngiver analog0 (Beskriver joystickets position i x-aksen)
const int yJoystick = A1;                     //Navngiver analog1 (Beskriver joystickets position i y-aksen)
const int bJoystick = A2;                     //Navngiver analog2 (Beskriver knappens status på joystick-boardet)

const int switchX = A4;                       //Navngiver analog4 (Beskriver switchen værdi der sidder på x-aksen)
const int switchY = A5;                       //Navngiver analog5 (Beskriver switchen værdi der sidder på y-aksen)

Stepper stepperX(400, 4, 5, 6, 7);            //Denne funktion laver en ny instans af Stepper klassen som repræsenterer vores stepper motor i x-retningen/y-retningen.
Stepper stepperY(400, 8, 9, 10, 11);          //Parameterne som vi angiver er: Stepper(steps/omdrejning, pin1, pin2, pin3, pin4)

const int DCinput1 = 12;                      //Navngiver digital pin 12 (+5V/GND til DC motoren)
const int DCinput2 = 13;                      //Navngiver digital pin 13 (+5V/GND til DC motoren)

const int maxX = 1000;                        //Maks steps på x-aksen
const int maxY = 1000;                        //Maks steps på y-aksen

int xPosition = 0;                            //x-positionen for flødeskumsdåsen
int yPosition = 0;                            //y-positionen for flødeskumsdåsen

boolean opstart = true;                       //Variablen "opstart" fortæller om vi skal køre opstarts proceduren
boolean state = false;                        //Variablen "state" beskriver om flødeskummen er tændt eller åbnet (false = lukket, true = åbent)
boolean working = false;                      //Variablen "working" beskriver om DC motoren er igang med at enten tænde eller slukke for flødeskummen

long previousMillisDC = 0;                    //Denne variable husker hvornår Arduinoen startede med at tænde/slukke for flødeskummen
long previousMillisStepper = 0;               //Denne variable husker hvornår Arduinoen sidst flyttede et step


void setup() {
  pinMode(DCinput1, OUTPUT);                  //Vi forklarer Arduinoen at de to udgange til DC motoren skal være output og deraf handle ud fra det
  pinMode(DCinput2, OUTPUT);
}

void loop() {
  if (opstart) {                              //Vi kigger på variablen "opstart" og hvis den er "true" så går den ind i if udsagnet
    int tempX = analogRead(switchX);          //Vi læser spændingen på port A4
    int tempY = analogRead(switchY);          //Vi læser spændingen på port A5
    if (tempX > 900 && tempY > 900) {         //Hvis der er forbindelse gennem begge switches må det betyde at flødeskumsdåsen er i koordinatet (0,0) så
      opstart = false;                        //sætter vi variablen til at være = false
    } else {
      if (tempX < 900) {                      //Hvis der ikke er forbindelse gennem switchen(x) så skal stepper motoren flytte sig derhen imod
        stepperX.step(-1);
      }
      if (tempY < 900) {
        stepperY.step(-1);                    //Det samme igen. Hvis der ikke er forbindelse igennem switchen på y-aksen så skal den flytte sig derhen
      }
    }
  } else {                                    //Nu ligger flødeskumsdåsen i koordinatet (0,0)

    if (millis() - previousMillisStepper > 50) {                        //Dette sørger for at stepper motoren maks kan udføre 20 steps pr. sekund.
      previousMillisStepper = millis();                                 //Vi husker tidpunktet for hvornår den fik lov til at udgøre et step
      moveStepper(joyPosition(xJoystick), joyPosition(yJoystick));      //Vi refererer til en funktion kaldt "moveStepper" med parameterne af en funktion for en switch
    }

    if (working && (!state && millis() - previousMillisDC > 500) || (state && millis() - previousMillisDC > 300)) {
      working = false;                        //Overstående if udtryk tjekker om vi er igang med at "arbejde" på enten at lukke eller åbne for flødeskummen.
      state = !state;                         //Derudover så tjekker den om der er gået 500 ms efter arbejdet med at tænde er påbegyndt eller 300 ms for at lukke
      digitalWrite(DCinput1, LOW);            //Hvis udtrykket er sandt stopper vi for arbejdet og sætter den nye status for flødeskummen.
      digitalWrite(DCinput2, LOW);            //Vi slukker for strømmen så der ikke kommer strøm ud til DC motoren der styrer åbene og lukke mekanismen
    }

    int temp = analogRead(bJoystick);         //Læser spændingen for knappen på joystick-modulet
    if (temp > 1000) {                        //Hvis den er over 1000 (hvilket betyder at den bliver trykket på) så skal den gå ind i denne if udtry
      if (!state && !working) {               //Hvis den ikke allerede er tændt eller er på vej til at blive
        working = true;                       //Arduinoen arbejder på at tænde for flødeskummen
        previousMillisDC = millis();          //Vi husker starttidspunktet
        digitalWrite(DCinput1, HIGH);         //Vi tænder for strømmen og får transistorene på vores H-bro-modul til at åbne
        digitalWrite(DCinput2, LOW);          //Vi slukker for strømmen og får nogle af transistorene på vores H-bro-modul til at lukke
      }
    } else {                                  //Hvis knappen ikke bliver trykket på
      if (state && !working) {                //Hvis der er tændt for flødeskummen og den ikke arbejder så skal den gøre følgende
        working = true;                       //Arduinoen arbejder på at tænde for flødeskummen
        previousMillisDC = millis();          //Vi husker starttidspunktet så vi husker at slukke igen
        digitalWrite(DCinput1, LOW);          //Vi slukker for strømmen og får nogle af transistorene på vores H-bro-modul til at lukke
        digitalWrite(DCinput2, HIGH);         //Vi tænder for strømmen og får transistorene på vores H-bro-modul til at åbne
      }
    }
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
