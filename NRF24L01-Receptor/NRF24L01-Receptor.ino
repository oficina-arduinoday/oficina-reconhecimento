#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
//#define portServo 6
#include <printf.h>

RF24 radio(7, 8); // CNS, CE
const byte address[6] = "00001";
const int portServo = 6;
Servo myServo;

void setup() {
  Serial.begin(9600);
  myServo.attach(portServo);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.startListening();
  //radio.printDetails();
}

void loop() {
  //radio.powerUp();
  //delay(50);
  Serial.println("receptor - aqui1");
  if (radio.available()) {
    int angleV = 0;
    Serial.println("receptor - aqui2");
    radio.read(&angleV, sizeof(angleV));
    Serial.println("receptor - aqui3");
    myServo.write(angleV);
    Serial.println("Receptor: " + String(angleV));
    delay(5);
  }
}
