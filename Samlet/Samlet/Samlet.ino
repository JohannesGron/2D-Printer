void setup() {
  Serial.begin(9600);
}

void loop() {
  String result = Joystick();
  steppermotor(result[0], result[1]);
}


String Joystick() {
  String x = "2";
  x = x + "3";
  
  String y = "1";
  y = y + 1;
  return(x, y);  
}

void steppermotor(int x, int y) {
  Serial.println(x);
  Serial.println(y);
}
