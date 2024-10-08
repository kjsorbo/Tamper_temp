#ifndef AZUREIOTMANAGER_H
#define AZUREIOTMANAGER_H


#include <Esp32MQTTClient.h>  // Using ESP32 Azure IoT Hub library
#include "iot_configs.h"      // Configuration settings for Azure IoT Hub

class AzureIoTManager {
public:
    AzureIoTManager(const char* connectionString);
    bool connect();
    bool sendTelemetry(const char* telemetry);
    void disconnect();

private:
    const char* _connectionString;
};

#endif
