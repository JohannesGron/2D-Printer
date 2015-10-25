void setup() {
  Serial.begin(9600);
}

void loop() {
  steppermotor(Joystick(true), Joystick(false));
}


//Vipudan
//Input = ingenting
//Output = To værdier: 
//Den ene værdi skal indeholde information om hvorhen steppermotoren skal flytte sig i x-retningen (-1, 0, 1). 
//Den anden værdi skal indeholde information om hvorhen steppermotoren skal flytte sig i y-retningen (-1, 0, 1)

int Joystick(boolean xory) {
  if (xory) {
    //x
    return 1;
  } else {
    //y
    return 2;
  }
}

//Christoffer
void steppermotor(int x, int y) {
  Serial.println(x);

}
