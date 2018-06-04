#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>


//SoftwareSerial mySerial(3,1); // RX, TX nodemcu 
SoftwareSerial mySerial(13,15); // RX, TX nodemcu
// Replace with your network credentials
const char* ssid = "TP-LINK_8ED13C";
const char* password = "51986131";
 
ESP8266WebServer server(80);   //instantiate server at port 80 (http port)
 
String page = "";

void setup(void){
  mySerial.begin(115200);
  //pinMode(1,OUTPUT); 
  pinMode(15,OUTPUT); 
  //the HTML of the web page
  page = "<h1>RoboPava LISTA PARA SERVIR</h1><p><a href=\"LEDOn\"><button>Calentar mate</button></a></p>";

  Serial.begin(115200);
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
   
  server.on("/", [](){
    server.send(200, "text/html", page);
  });
  server.on("/LEDOn", [](){
    server.send(200, "text/html", page);
    mySerial.write("80",2);

  });

  server.on("/temperatura",handleTemperatura);
  
  server.begin();
  Serial.println("Web server started!");
}


void handleTemperatura() {
    String message = "Calentando";
    StaticJsonBuffer<200> newBuffer;
    JsonObject& json = newBuffer.parseObject(server.arg("plain"));
    String temperatura = json["temperatura"];
    //newjson.printTo(Serial);
    mySerial.print(temperatura);
    server.send(200, "text/plain", message);
}
 
void loop(void){
  server.handleClient();
}
