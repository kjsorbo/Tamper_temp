#include <Esp32MQTTClient.h>  // Use the correct header for ESP32 Azure IoT Arduino library
#include "AzureIoTManager.h"
#include <Arduino.h>
#include "iot_configs.h"

AzureIoTManager::AzureIoTManager(const char* connectionString)
    : _connectionString(connectionString) {}

bool AzureIoTManager::connect() {
    Serial.println("Connecting to Azure IoT Hub...");
    
    // Initialize the ESP32 Azure IoT library with the provided connection string
    if (Esp32MQTTClient_Init((const uint8_t*)_connectionString)) {
        Serial.println("Connected to Azure IoT Hub!");
        return true;
    } else {
        Serial.println("Failed to connect to Azure IoT Hub.");
        return false;
    }
}

bool AzureIoTManager::sendTelemetry(const char* telemetry) {
    // Use Esp32MQTTClient to send telemetry data
    return Esp32MQTTClient_SendEvent(telemetry);
}

void AzureIoTManager::disconnect() {
    // Use Esp32MQTTClient_Close to cleanly disconnect and release resources
    Esp32MQTTClient_Close();
    Serial.println("Disconnected from Azure IoT Hub.");
}
