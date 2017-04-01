
//Pisca led na GPIO-2 a cada 4 segundos
void setup() {
  pinMode(2, OUTPUT);
}

void loop() {
  digitalWrite(2, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(4000);              // wait for a two seconds
  digitalWrite(2, HIGH);    // turn the LED off by making the voltage LOW
  delay(4000);              // wait for a two seconds
}
