void setup() {

}

void loop() {
  String result = Joystick();
  steppermotor(result[0], result[1]);
}


String Joystick() {
  String x = "2";
  String y = "1";
  String b = x + y;
  return(x, y);  
}

void steppermotor(int x, int y) {
  
}
