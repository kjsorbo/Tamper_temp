#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <WiFi.h>
#include <ESPAsyncWebServer.h>

class WiFiManager {
public:
    WiFiManager(const char* ssid, const char* password);
    void connect();
    void startAP();  // Start Access Point mode
    void startWebServer();  // Start the async web server
    bool isConnected();
    void disconnect();

private:
    const char* _ssid;
    const char* _password;
    AsyncWebServer server;  // Declare an AsyncWebServer instance
};

#endif
