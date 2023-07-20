#include <WiFi.h>               // Built-in
#include <ESPFileServer.h>      // https://github.com/noranraskin/ESPFileServer
#include <ESPAsyncWebServer.h>  // https://github.com/me-no-dev/ESPAsyncWebServer

AsyncWebServer server(80);

const char* ssid = ""; // Your WiFi SSID
const char* password = ""; // Your WiFi Password

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi Failed!\n");
        return;
    }
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    // ESPFileServer is accessible at "<IP Address>/files" in browser
    FileServer.begin(&server);
    server.begin();
}

void loop() {
    // put your main code here, to run repeatedly:
}