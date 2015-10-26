//For joystick:
//Navngiver udgang A0 og A1
const int xanalog = A0;
const int yanalog = A1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  steppermotor(Joystick(xanalog), Joystick(yanalog));
}


//Vipudan
//Input = ingenting
//Output = To værdier: 
//Den ene værdi skal indeholde information om hvorhen steppermotoren skal flytte sig i x-retningen (-1, 0, 1). 
//Den anden værdi skal indeholde information om hvorhen steppermotoren skal flytte sig i y-retningen (-1, 0, 1)

int Joystick(int analog) {
  int value = analogRead(analog);
  if (value < 400) {          //hvis værdien er mindre en end 400 skal den gøre følgende:
    return (-1);
  }
  else if (value < 600 ) {   //hvis værdien er i mellem 400 og 600 skal den gøre følgende:
    return 0;
  }
  else {                     //hvis værdien 600 eller over skal den gøre følgende: 
    return 1;
  }
}

//Christoffer
void steppermotor(int x, int y) {
  Serial.println(x);
  Serial.println(y);
}