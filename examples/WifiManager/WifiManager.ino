#include <WiFiManager.h>        // https://github.com/tzapu/WiFiManager
#include <ESPFileServer.h>      // https://github.com/noranraskin/ESPFileServer
#include <ESPAsyncWebServer.h>  // https://github.com/me-no-dev/ESPAsyncWebServer

AsyncWebServer server(80);

void setup() {
    Serial.begin(115200);
    WiFiManager wm;
    wm.autoConnect("AutoConnectAP");

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    // ESPFileServer is accessible at "<IP Address>/files" in browser
    FileServer.begin(&server);
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    server.begin();
}

void loop() {
    // put your main code here, to run repeatedly:
}
