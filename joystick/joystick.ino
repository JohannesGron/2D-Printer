//Navngiver udgang A0 og A1
const int HORIZ = A0;
const int VERT = A1; 

int ledPin = 13; // choose the pin for the LED
int inPin = 7;   // choose the input pin (for a pushbutton)
int val = 0;     // variable for reading the pin status

void setup() {
  // Vi starter en ny seriel komunikation med computeren
  // Den skal sende 9600 bits pr.sekund
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);  // declare LED as output
  pinMode(inPin, INPUT);    // declare pushbutton as input

}
//void loop kan ikke retunere værdier
void loop() {

  // Vi laver variabler, hvor vi henter vædierne fra analog-indgangene
  int horizvalue = analogRead(HORIZ);
  int vertvalue = analogRead(VERT);

  //For x-aksen:
  
  if(horizvalue < 400){
    return -1;
  } 
  //hvis værdien er i mellem 400 og 600 skal den gøre følgende:
  else if (horizvalue < 600 ){
    return 0;
  }
  //hvis værdien 600 eller over skal den gøre følgende: 
  else{
    return 1;     
  }

  //for y-aksen:

 if(vertvalue < 400){
    return -1;
  } 
  //hvis værdien er i mellem 400 og 600 skal den gøre følgende:
  else if (vertvalue < 600 ){
    return 0;
  }
  //hvis værdien 600 eller over skal den gøre følgende: 
  else{
    return 1;     
  }


  // Får fremvist værdierne på konsollen
  Serial.print(horizvalue);
  Serial.print(" _ ");
  Serial.println(vertvalue);

  delay(5);

  




  val = digitalRead(inPin);  // read input value
  if (val == HIGH) {         // check if the input is HIGH (button released)
    digitalWrite(ledPin, LOW);  // turn LED OFF
  } else {
    digitalWrite(ledPin, HIGH);  // turn LED ON
  }


}
