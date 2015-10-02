/*
  Nedestående kode vil læse hvor meget volt (0 - 5V) der kommer ind på henholdsvis A0 og A1.
  Arduinoen omskriver Volt på eksempelvis A0 til et tal mellem 0 - 1023 som vi så kan bruge senere i forløbet.
*/

// Udgang A0 og A1 får nu et officielt navn som vi kan kalde i koden
int analog0 = A0;
int analog1 = A1;

void setup() {
  // Vi ønsker at starte seriel kommunikation med computeren. 
  // Vi angiver 9600 fordi så skriver den 9600 bits pr. sekundt til computeren. (9600 = standard)
  Serial.begin(9600);
}

void loop() {
  // Vi læser værdierne på udgang A0 og A1 og sætter det ligmed en integer
  int ana0value = analogRead(analog0);
  int ana1value = analogRead(analog1);

  // Vi skriver værdien ud i konsollen
  Serial.print(ana0value);
  Serial.print(" - ");
  Serial.println(ana1value);

  //Venter lige 5 millisekunder så omformeren fra analog til digital lige kan følge med
  delay(5);
}
