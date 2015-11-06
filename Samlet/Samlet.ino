/*
Udgange:
  Joystick:
   - A0 -> x-aksen
   - A1 -> y-aksen
   - A2 -> knap
   - A3 -> Tom

  Stepper 1 (Fastgjort på jernet):
   - D04 -> Input 1
   - D05 -> Input 2
   - Do6 -> Input 3
   - Do7 -> Input 4

  Stepper 2 (Fastgjort til plastikken):
   - D08 -> Input 1
   - D09 -> Input 2
   - D10 -> Input 3
   - D11 -> Input 4

  Switch
   - A4
   - A5
*/

//Navngiver udgang A0 og A1
const int xanalog = A0;
const int yanalog = A1;


void setup() {
  Serial.begin(9600);
}

void loop() {
  steppermotor(Joystick(xanalog), Joystick(yanalog));
}


/*
Denne funktion har Vipudan ansvaret for.
Formålet med denne funktion er at retunere en værdi der fortæller om Joysticket bliver flyttet på.
 - Input -> hvilken analog indgang som der skal læses på.
 - Output -> retunere enten (-1, 0, 1) hvilket angiver hvilken vej som stepper motoren skal køre 
*/

int Joystick(int analog) {
  int value = analogRead(analog);
  if (value < 400) {          //hvis værdien er mindre en end 400
    return (-1);
  }
  else if (value < 600 ) {   //hvis værdien er i mellem 400 og 600
    return 0;
  }
  else {                     //hvis værdien er over 600
    return 1;
  }
}


//Christoffer
void steppermotor(int x, int y) {
  Serial.println(x);
  Serial.println(y);
}
