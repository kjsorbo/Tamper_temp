#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <WiFi.h>
#include <ESPAsyncWebServer.h>

class WiFiManager {
public:
    WiFiManager(const char* ssid, const char* password);
    void connect();
    void startAP();
    void startWebServer();
    bool isConnected();
    void disconnect();

private:
    const char* _ssid;
    const char* _password;
    AsyncWebServer server;   // Declare the AsyncWebServer instance
};

#endif
