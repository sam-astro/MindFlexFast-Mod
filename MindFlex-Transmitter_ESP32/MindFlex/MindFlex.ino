
#include "WiFi.h"
#include <HardwareSerial.h>


const char* ssid = "TP-Link_D834"; // Your WiFi SSID
const char* password = "1Luckycharm@"; // Your WiFi Password


WiFiServer wifiServer(80);
HardwareSerial SerialPort(2); // use UART2
 
void setup() {
  SerialPort.begin(57600, SERIAL_8N1, 16, 17); 
  Serial.begin(57600);
  
  Serial.println("Starting up...");
 
  delay(1000);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
 
  Serial.println("Connected to the WiFi network");
  Serial.println(WiFi.localIP());
 
  wifiServer.begin();
}

void loop() {
 
  WiFiClient client = wifiServer.available();

  int ii = 0;
  if (client) {
 
    while (client.connected()) {

      // Send test data (emulate device) (this would normally be sent by the MindWave device, so comment this out)
      if(SerialPort.available()==0){
        SerialPort.println(String(ii));
        ii++;
      }

      // If data is received from the MindWave, send it to the client via WiFi
      while (SerialPort.available()>0) {
        client.write(SerialPort.read());
      }

        //client.println("This is example test data: " + String(ii));
//      while (client.available()>0) {
//        char c = client.read();
//        Serial.write(c);
//      }
 
      //delay(10);
    }
 
    client.stop();
    Serial.println("Client disconnected");
 
  }
}
