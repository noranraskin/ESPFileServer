#include "ESPFileServer.h"
#include <Arduino.h>
#include <FS.h>

#define USE_LITTLEFS // or #define USE_SPIFFS
#ifdef USE_LITTLEFS
    #include <LittleFS.h>
    #define FS LittleFS
#else
    #include <SPIFFS.h>
    #define FS SPIFFS
#endif

using namespace fs;

void ESPFileServerClass::begin(AsyncWebServer *server, const char* url) {
    FS.begin();
    _server = server;
    // _server->on(url, HTTP_GET, [](AsyncWebServerRequest *request) {
    //     request->send(SPIFFS, request->url());
    // });
    _server->on("/espfileserver-format-fs", HTTP_POST, [](AsyncWebServerRequest *request) {
        if (request->hasParam("format")) {
            if (request->getParam("format")->value() == "true") {
                request->send(200, "text/plain", "Formatting FS...");
                FS.format();
            }
        }
    });
    _server->on("/espfileserver-get-list-of-all-files", HTTP_GET, [](AsyncWebServerRequest *request) {
        String files = "";
        File root = FS.open("/");
        File file = root.openNextFile();
        while (file) {
            if (!file.isDirectory()) {
                files += file.name();
                files += "\n";
            }
            file = root.openNextFile();
        }
        request->send(200, "text/plain", files);
    });

    _server->on("/espfileserver-get-fs-info", HTTP_GET, [](AsyncWebServerRequest *request) {
        String info = "";
        info += "Total Bytes: ";
        info += FS.totalBytes();
        info += "\n";
        info += "Used Bytes: ";
        info += FS.usedBytes();
        info += "\n";
        request->send(200, "text/plain", info);
    });

    _server->serveStatic("/", FS, "/").setDefaultFile("index.html");
}

ESPFileServerClass FileServer;