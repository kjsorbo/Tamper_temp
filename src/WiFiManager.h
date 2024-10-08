#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <WiFi.h>

class WiFiManager {
public:
    WiFiManager(const char* ssid, const char* password);
    void connect();
    bool isConnected();
    void disconnect();

private:
    const char* _ssid;
    const char* _password;
};

#endif
