#include "WiFiManager.h"
#include <Arduino.h>

WiFiManager::WiFiManager(const char* ssid, const char* password) 
    : _ssid(ssid), _password(password), server(80) {}  // Initialize server on port 80

void WiFiManager::connect() {
    Serial.printf("Connecting to Wi-Fi: %s\n", _ssid);
    WiFi.begin(_ssid, _password);
    int retryCount = 0;
    
    // Attempt to connect for up to 10 seconds
    while (WiFi.status() != WL_CONNECTED && retryCount < 20) {
        delay(500);
        Serial.print(".");
        retryCount++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nConnected to Wi-Fi!");
    } else {
        Serial.println("\nFailed to connect. Starting Access Point...");
        startAP();
        startWebServer();
    }
}

void WiFiManager::startAP() {
    // Start Access Point
    WiFi.softAP("DeviceConfigAP", "12345678");
    Serial.println("Access Point Started: DeviceConfigAP");
    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());
}

void WiFiManager::startWebServer() {
    // Serve the configuration page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/html", "<h1>Device Configuration Page</h1><form method='post' action='/configure'>"
                                        "SSID: <input type='text' name='ssid'><br>"
                                        "Password: <input type='password' name='password'><br>"
                                        "Azure IoT Connection String: <input type='text' name='azureConnectionString'><br>"
                                        "<input type='submit' value='Save'></form>");
    });

    // Handle form submission
    server.on("/configure", HTTP_POST, [](AsyncWebServerRequest *request) {
        String ssid, password, azureConnectionString;

        if (request->hasParam("ssid", true)) ssid = request->getParam("ssid", true)->value();
        if (request->hasParam("password", true)) password = request->getParam("password", true)->value();
        if (request->hasParam("azureConnectionString", true)) azureConnectionString = request->getParam("azureConnectionString", true)->value();

        // Save these values (to NVS or wherever required)
        Serial.printf("SSID: %s, Password: %s, Azure: %s\n", ssid.c_str(), password.c_str(), azureConnectionString.c_str());

        request->send(200, "text/html", "<h2>Configuration Saved!</h2><p>Please reboot the device.</p>");
    });

    server.begin();
    Serial.println("Web Server Started");
}

bool WiFiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void WiFiManager::disconnect() {
    WiFi.disconnect(true);
    Serial.println("Disconnected from Wi-Fi.");
}
