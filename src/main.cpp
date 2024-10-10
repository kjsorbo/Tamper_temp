#include <Arduino.h>
#include "WiFiManager.h"
#include "AzureIoTManager.h"
#include "PowerManager.h"
#include "iot_configs.h"
#include <ArduinoOTA.h>  // Include ArduinoOTA library

WiFiManager wifiManager(IOT_CONFIG_WIFI_SSID, IOT_CONFIG_WIFI_PASSWORD);
AzureIoTManager azureIoTManager(IOT_CONFIG_CONNECTION_STRING);

RTC_DATA_ATTR int bootCount = 0;

void setup() {
    Serial.begin(115200);
    delay(1000);

    ++bootCount;
    Serial.println("Boot number: " + String(bootCount));
    PowerManager::printWakeupReason();

    // Connect to Wi-Fi
    wifiManager.connect();

    if (wifiManager.isConnected()) {
        // If connected, set up ArduinoOTA
        ArduinoOTA.begin();  // Start the OTA service
        Serial.println("Arduino OTA Ready");

        // Connect to Azure IoT Hub and send telemetry
        azureIoTManager.connect();
        azureIoTManager.sendTelemetry("{\"message\":\"Hello, Azure!\"}");
    } else {
        Serial.println("Wi-Fi not connected, skipping Azure connection.");
    }

    // Configure sleep settings and enter deep sleep
    PowerManager::configureWakeup(BUTTON_PIN_BITMASK, TIME_TO_SLEEP);
    Serial.println("Entering deep sleep...");
    PowerManager::enterDeepSleep();
}

void loop() {
    // Handle OTA updates in the loop
    if (wifiManager.isConnected()) {
        ArduinoOTA.handle();  // Ensure ArduinoOTA can handle incoming updates
    }
}