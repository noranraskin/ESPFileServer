#ifndef ESPFileServer_h
#define ESPFileServer_h

#include <Arduino.h>

#if defined(ESP32)
    #define HARDWARE "ESP32"
    #include <WiFi.h>
    #include <ESPAsyncWebServer.h>
#endif



#endif