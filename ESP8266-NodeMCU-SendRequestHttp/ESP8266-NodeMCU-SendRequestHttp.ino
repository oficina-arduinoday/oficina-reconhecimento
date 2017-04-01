#include <ESP8266WiFi.h>
#include <WiFiClient.h>
 
// WiFi information
const char WIFI_SSID[] = "Arduino";
const char WIFI_PSK[] = "364455391a";
 
// Remote site information
const char http_site[] = "gisexp.icomp.ufam.edu.br";
const int http_port = 80;
String nome = "seunome";
String valor = "10";
 
// Global variables
WiFiClient client;
 
void setup() {
  Serial.begin(115200);
  Serial.println("connect");
  connectWiFi();
  // Attempt to connect to website
}
 
void loop() {
  Serial.println("sendrequest");
  sendRequest();
  Serial.println("receive");
  receive_data();
  delay(2000);
}
 
// Attempt to connect to WiFi
void connectWiFi() {
  // Set WiFi mode to station (client)
  WiFi.mode(WIFI_STA);
  
  // Initiate connection with SSID and PSK
  WiFi.begin(WIFI_SSID, WIFI_PSK);
  
  // Blink LED while we wait for WiFi connection
  while ( WiFi.status() != WL_CONNECTED ) {
    //digitalWrite(LED_PIN, led_status);
   // led_status ^= 0x01;
    delay(100);
  }
}
 
void disconnectWifi(){
  // If the server has disconnected, stop the client and WiFi  
  // Close socket and wait for disconnect from WiFi
  client.stop();
  if ( WiFi.status() != WL_DISCONNECTED ) {
      WiFi.disconnect();
  }  
}

void receive_data(){
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
}

// Perform an HTTP GET request to a remote page
bool sendRequest() {
  // Attempt to make a connection to the remote server
  if (!client.connect(http_site, http_port)) {
    return false;
  }
  
  // Make an HTTP GET request
//  client.println("GET /arduinoDay/emotionrecognition.php?GSRValue="+String(gsrvalue)+" HTTP/1.1");
  client.println("GET /arduinoday/nodemcu.php?nome="+nome+"&valor="+valor+" HTTP/1.1");
  client.print("Host: ");
  client.println(http_site);
  client.println("User-Agent: ESP8266");
  client.println("Connection: close");
  client.println();
  
  return true;
}
