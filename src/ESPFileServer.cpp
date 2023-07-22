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

    _server->on("/espfileserver-download-file", HTTP_GET, [](AsyncWebServerRequest *request) {
        if (request->hasParam("file")) {
            String file = request->getParam("file")->value();
            if (FS.exists(file)) {
                AsyncResponseStream * response = request->beginResponseStream("text/plain");
                File f = FS.open(file, "r");
                response->print(f.readString());
                request->send(response);
                return;
            } else {
                request->send(404, "text/plain", "File not found");
            }
        } else {
            request->send(404, "text/plain", "File not found");
        }
    });

    _server->on("/espfileserver-delete-file", HTTP_DELETE, [](AsyncWebServerRequest *request) {
        if (request->hasParam("file")) {
            String file = request->getParam("file")->value();
            if (FS.exists(file)) {
                FS.remove(file);
                request->send(200, "text/plain", "File deleted");
                return;
            } else {
                request->send(404, "text/plain", "File not found");
            }
        } else {
            request->send(404, "text/plain", "File not found");
        }
    });

    _server->serveStatic("/", FS, "/").setDefaultFile("index.html");
}

ESPFileServerClass FileServer;