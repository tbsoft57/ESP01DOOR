#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>

#define OTAName  "ESP01DOOR"
#define WifiSSID "TBSOFT"
#define WifiPass "TB04011966"
#define IP   51
#define io0  0 // -> Doit être Pulled-Up par une resistance externe au Boot si elle est cablée sur autre chose (sinon Mode flash Boot)
#define io1  1
#define io2  2
#define io3  3
#define tx   1
#define rx   3
#define R1   io0
#define R2   io2

ESP8266WebServer server(80);

String door;

void setup() {
  // pinMode(tx, FUNCTION_3); pinMode(rx, FUNCTION_3); // -> transforme tx et rx en GPIO
  pinMode(R1,  OUTPUT); 
  pinMode(R2,  OUTPUT); 
  WiFi.config(IPAddress(192, 168, 0, IP), IPAddress(192, 168, 0, 1), IPAddress(255, 255, 255, 0));
  WiFi.hostname(OTAName); WiFi.mode(WIFI_STA); WiFi.begin(WifiSSID, WifiPass);
  while (WiFi.status() != WL_CONNECTED) { delay(250); }
  ArduinoOTA.setHostname(OTAName); ArduinoOTA.begin();  
  server.on("/", HTTP_GET, root);
  server.begin(); 
}

void loop() { server.handleClient(); ArduinoOTA.handle(); }

void root() { 
  door = server.arg("door"); 
  if (door=="car") {
    digitalWrite(R1, HIGH);    
    delay(250);
    digitalWrite(R1, LOW);    
  } else if (door=="feet") {
    digitalWrite(R2, HIGH);    
    delay(250);
    digitalWrite(R2, LOW);        
  }
  server.send(200, "text/plain", "Ok" );
}

