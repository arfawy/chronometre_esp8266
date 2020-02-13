#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <Wire.h>

const char* ssid = "Dracula";
const char* password = "@rf@wy12345";

int seconds = 0;
AsyncWebServer server(80);

String getSeconds() {
  return String(seconds);
}
void resetSeconds(){
  seconds = 0;
}

String processor(const String& var){
  if (var == "SECONDS"){
    return getSeconds();
  }
}
 
void setup(){

  Serial.begin(115200);

  // Initialisation de SPIFFS
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  
  // Connexion au Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println(WiFi.localIP());

  // Route pour /
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  // Route pour le chargement du fichier style.css
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/css/style.css", "text/css");
  });
  // Route pour le chargement du fichier script.js
  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/js/script.js", "application/javascript");
  });
  server.on("/seconds", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", getSeconds().c_str());
  });
  server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request){
    resetSeconds();  
    request->redirect("/");
  });

  // Start server
  server.begin();
}
 
void loop(){
  delay(1000);
  seconds++;
}
