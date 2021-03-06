#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>

RF24 radio(7, 8); // CNS, CE
const byte address[6] = "00001";
boolean buttonState = 0;
const int portJoystick = 0;

void setup() {
  Serial.begin(57600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
  //radio.setRetries(15,15);
  radio.printDetails();
 
}

void loop() {
  delay(300);
  int joystickValue = analogRead(portJoystick);
  Serial.println("joystick: " + String(joystickValue));
  int angleValue = map(joystickValue, 0, 1023, 0, 180);
  Serial.println("Transmissor: " + String(angleValue));
  //radio.powerUp();
  bool ok = radio.write(&angleValue, sizeof(angleValue));
  delay(100);
}
