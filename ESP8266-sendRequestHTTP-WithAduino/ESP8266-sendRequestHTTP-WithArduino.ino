 
#include <SoftwareSerial.h>
 
//RX pino 2, TX pino 3
SoftwareSerial esp8266(2, 3);
 
#define DEBUG true
String serv = "192.168.1.113";

void setup()
{
  Serial.begin(9600);
  esp8266.begin(19200);
 
  sendData("AT+RST\r\n", 2000, DEBUG); // rst
  // Conecta a rede wireless
  sendData("AT+CWJAP=\"LABSE\",\"labse0987\"\r\n", 2000, DEBUG);
  delay(3000);
  sendData("AT+CWMODE=1\r\n", 1000, DEBUG);
  // Mostra o endereco IP
  //sendData("AT+CIFSR\r\n", 1000, DEBUG);
  // Configura para multiplas conexoes
  delay(1500);
  sendData("AT+CIPMUX=0\r\n", 1000, DEBUG);
  delay(1500);
  // Inicia o web server na porta 80
  //sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG);
  //delay(3000);
  // Mostra o endereco IP
  sendData("AT+CIFSR\r\n", 1000, DEBUG);
  delay(1500);
  // Mostra o endereco IP
  sendData("AT+CIPMODE=0\r\n", 1000, DEBUG);
  delay(1500);
  // Mostra o endereco IP
  sendData("AT+CIPSTO?\r\n", 1000, DEBUG);
  delay(1500);
  // Mostra o endereco IP
  //sendData("AT+CIPSTO=300\r\n", 1000, DEBUG);


}
 
void loop()
{
  // Verifica se o ESP8266 esta enviando dados
  int GSRvalue = readGSRSensor();
  sendRequest(GSRvalue);
}

int readGSRSensor(){
  return 1;
}

void sendRequest(int GSRValue){

  sendData("AT+CIPSTART=\"TCP\",\"192.168.1.113\",80\r\n", 3000, DEBUG);
  String request = "GET /IoT/teste.php HTTP/1.1\r\nHost: 192.168.1.113\r\nUser-Agent: ESP8266\r\nConnection: close\r\n\r\n";
  sendData("AT+CIPSEND="+String(request.length())+"\r\n", 300, DEBUG);
  Serial.println("Enviando requisicao request: ");
  Serial.println(request.length());
  sendData(request, 300, DEBUG);
  Serial.println("\n");

}
 
String sendData(String command, const int timeout, boolean debug)
{
  // Envio dos comandos AT para o modulo
  String response = "";
  esp8266.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (esp8266.available())
    {
      // The esp has data so display its output to the serial window
      char c = esp8266.read(); // read the next character.
      response += c;
    }
  }
  if (debug)
  {
    Serial.print(response);
  }
  return response;
}
