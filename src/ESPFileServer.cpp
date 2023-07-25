#include "ESPFileServer.h"

#define USE_LITTLEFS // or #define USE_SPIFFS
#ifdef USE_LITTLEFS
    #include <LittleFS.h>
    #define FS LittleFS
#else
    #include <SPIFFS.h>
    #define FS SPIFFS
#endif

int iterateFiles(File *, JsonArray &, String = "");


void ESPFileServerClass::begin(AsyncWebServer *server, const char* url) {
    FS.begin();
    _server = server;

    _server->on("/espfileserver-format-fs", HTTP_POST, [](AsyncWebServerRequest *request) {
        Serial.println("Got request to format FS");
        if (request->hasParam("format")) {
            if (request->getParam("format")->value() == "true") {
                request->send(200, "text/plain", "Formatting FS...");
                FS.format();
                return;
            }
        }
        request->send(400, "text/plain", "Bad request");
    });

    _server->on("/espfileserver-get-list-of-all-files", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.println("Got request to get list of all files");
        File root = FS.open("/");
        AsyncResponseStream * response = request->beginResponseStream("application/json");
        DynamicJsonDocument obj(1024);
        JsonArray json = obj.to<JsonArray>();
        iterateFiles(&root, json);
        serializeJson(json, *response);
        request->send(response);
    });

    _server->on("/espfileserver-get-fs-info", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.println("Got request to get FS info");
        String info = "";
        info += "Total Bytes: ";
        info += FS.totalBytes();
        info += "\n";
        info += "Used Bytes: ";
        info += FS.usedBytes();
        info += "\n";
        request->send(200, "text/plain", info);
    });

    // _server->on("/espfileserver-download-file", HTTP_GET, [](AsyncWebServerRequest *request) {
    //     Serial.println("Got request to download file");
    //     if (request->hasParam("file")) {
    //         String file = request->getParam("file")->value();
    //         if (FS.exists(file)) {
    //             AsyncResponseStream * response = request->beginResponseStream("text/plain");
    //             File f = FS.open(file, "r");
    //             response->print(f.readString());
    //             request->send(response);
    //             return;
    //         } else {
    //             request->send(404, "text/plain", "File not found");
    //         }
    //     } else {
    //         request->send(404, "text/plain", "File not found");
    //     }
    // });
    
    _server->on("/espfileserver-move-file", HTTP_POST, [](AsyncWebServerRequest * request) {
        Serial.println("Got request to move file");
        if (request->hasParam("from") && request->hasParam("to")) {
            String from = request->getParam("from")->value();
            if (from[0] != '/') {from = "/" + from;}
            String to = request->getParam("to")->value();
            if (to[0] != '/') {to = "/" + to;}
            if (FS.exists(from)) {
                if (FS.rename(from, to)) {
                    request->send(200, "text/plain", "File moved");
                    return;
                } else {
                    request->send(500, "text/plain", "Failed to move file");
                    return;
                }
            } else {
                request->send(404, "text/plain", "File not found");
                return;
            }
        } else {
            request->send(400, "text/plain", "Bad request");
            return;
        }
    });

    _server->on("/espfileserver-delete-file", HTTP_DELETE, [](AsyncWebServerRequest *request) {
        Serial.println("Got request to delete file");
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

    _server->serveStatic("/espfileserver-download-file", FS, "/");
}

int iterateFiles(File * fp, JsonArray &json, String path) {
    File file = fp->openNextFile();
    int totalsize = 0;
    while (file) {
        JsonObject obj = json.createNestedObject();
        obj["name"] = String(file.name());
        if (file.isDirectory()) {
            String dirname = path + "/" + String(file.name());
            File newRoot = FS.open(dirname);
            if (!newRoot) {
                Serial.println("Failed to open directory");
            }
            JsonArray files = obj.createNestedArray("files");
            int dirsize = iterateFiles(&newRoot, files, dirname);
            obj["size"] = dirsize;
            totalsize += dirsize;
        } else {
            obj["size"] = file.size();
            totalsize += file.size();
        }
        file = fp->openNextFile();
    }
    return totalsize;
}

ESPFileServerClass FileServer;

