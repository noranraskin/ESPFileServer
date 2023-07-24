#ifndef ESPFileServer_h
#define ESPFileServer_h

#include <Arduino.h>

#if defined(ESP32)
    #define HARDWARE "ESP32"
    #include <WiFi.h> // Built-in
    #include <ESPAsyncWebServer.h> // https://github.com/me-no-dev/ESPAsyncWebServer
#endif


class ESPFileServerClass {
    public:
        void begin(AsyncWebServer *server, const char* url = "/files");
    private:
        AsyncWebServer *_server;
};

extern ESPFileServerClass FileServer;

#endif