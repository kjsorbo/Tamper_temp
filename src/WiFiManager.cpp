#include "WiFiManager.h"
#include <Arduino.h>

WiFiManager::WiFiManager(const char* ssid, const char* password) 
    : _ssid(ssid), _password(password) {}

void WiFiManager::connect() {
    Serial.printf("Connecting to Wi-Fi: %s\n", _ssid);
    WiFi.begin(_ssid, _password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to Wi-Fi!");
}

bool WiFiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void WiFiManager::disconnect() {
    WiFi.disconnect(true);
    Serial.println("Disconnected from Wi-Fi.");
}
