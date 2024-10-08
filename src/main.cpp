#include <Arduino.h>
#include "WiFiManager.h"
#include "AzureIoTManager.h"
#include "PowerManager.h"
#include "iot_configs.h"

WiFiManager wifiManager(IOT_CONFIG_WIFI_SSID, IOT_CONFIG_WIFI_PASSWORD);
AzureIoTManager azureIoTManager(IOT_CONFIG_CONNECTION_STRING);

RTC_DATA_ATTR int bootCount = 0;

void setup() {
    Serial.begin(115200);
    delay(1000);

    ++bootCount;
    Serial.println("Boot number: " + String(bootCount));
    PowerManager::printWakeupReason();

    wifiManager.connect();
    azureIoTManager.connect();

    // Send telemetry data
    azureIoTManager.sendTelemetry("{\"message\":\"Hello, Azure!\"}");

    PowerManager::configureWakeup(BUTTON_PIN_BITMASK, TIME_TO_SLEEP);
    PowerManager::enterDeepSleep();
}

void loop() {}
