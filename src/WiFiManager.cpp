#include "WiFiManager.h"
#include <SPIFFS.h>
#include <FS.h>
#include <Arduino.h>
#include <ArduinoOTA.h>  // Include ArduinoOTA library

WiFiManager::WiFiManager(const char* ssid, const char* password) 
    : _ssid(ssid), _password(password), server(80) {}

void WiFiManager::connect() {
    Serial.printf("Connecting to Wi-Fi: %s\n", _ssid);
    WiFi.begin(_ssid, _password);
    int retryCount = 0;
    while (WiFi.status() != WL_CONNECTED && retryCount < 20) {
        delay(500);
        Serial.print(".");
        retryCount++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nConnected to Wi-Fi!");

        // Start Arduino OTA service if connected to Wi-Fi
        setupOTA();
    } else {
        Serial.println("\nFailed to connect. Starting Access Point...");
        startAP();
        startWebServer();
    }
}

void WiFiManager::startAP() {
    // Start Access Point
    WiFi.softAP("Tamper00001", "12345678");
    Serial.println("Access Point Started: DeviceConfigAP");
    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());
}

void WiFiManager::startWebServer() {
    // Initialize SPIFFS
    if (!SPIFFS.begin(true)) {
        Serial.println("Failed to mount SPIFFS");
        return;
    }
    Serial.println("SPIFFS mounted successfully");

    // Serve the index.html from SPIFFS
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/index.html", "text/html");
    });

    // Handle form submission
    server.on("/configure", HTTP_POST, [](AsyncWebServerRequest *request) {
        String ssid, password, hubName, deviceId, sasKey;

        if (request->hasParam("ssid", true)) ssid = request->getParam("ssid", true)->value();
        if (request->hasParam("password", true)) password = request->getParam("password", true)->value();
        if (request->hasParam("hubName", true)) hubName = request->getParam("hubName", true)->value();
        if (request->hasParam("deviceId", true)) deviceId = request->getParam("deviceId", true)->value();
        if (request->hasParam("sasKey", true)) sasKey = request->getParam("sasKey", true)->value();

        // Save these values as needed
        Serial.printf("SSID: %s, Password: %s, Hub Name: %s, Device ID: %s, SAS Key: %s\n", 
                      ssid.c_str(), password.c_str(), hubName.c_str(), deviceId.c_str(), sasKey.c_str());

        request->send(200, "text/html", "<h2>Configuration Saved!</h2><p>Please reboot the device.</p>");
    });

    server.begin();
    Serial.println("Web Server Started");
}

void WiFiManager::setupOTA() {
    // Setup Arduino OTA callbacks
    ArduinoOTA.onStart([]() {
        String type = (ArduinoOTA.getCommand() == U_FLASH) ? "sketch" : "filesystem";
        Serial.println("Start updating " + type);
    });

    ArduinoOTA.onEnd([]() { Serial.println("\nEnd"); });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });

    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

    // Start the OTA service
    ArduinoOTA.begin();
    Serial.println("Arduino OTA Ready");
}

bool WiFiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void WiFiManager::disconnect() {
    WiFi.disconnect(true);
    Serial.println("Disconnected from Wi-Fi.");
}
