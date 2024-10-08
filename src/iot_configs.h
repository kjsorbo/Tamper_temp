#ifndef IOT_CONFIGS_H
#define IOT_CONFIGS_H

// ==================== Wi-Fi Configuration ====================
#define IOT_CONFIG_WIFI_SSID         "Garasjen"             // Your Wi-Fi SSID
#define IOT_CONFIG_WIFI_PASSWORD     "themancave"           // Your Wi-Fi Password

// ================== Azure IoT Hub Configuration ==================
#define IOT_CONFIG_IOTHUB_FQDN       "TamperTest2024v1.azure-devices.net" // Azure IoT Hub hostname
#define IOT_CONFIG_DEVICE_ID         "ESP32C6v1"                          // Azure IoT Hub Device ID
#define IOT_CONFIG_DEVICE_KEY        "ElnY3bFuP/ENsvZSh4nx6ppllL/h6K8GWMCzySYZYFg=" // Device Key for authentication

// ================== Device Connection String ===================
// Azure IoT Hub requires a specific connection string format, which includes the FQDN, Device ID, and Device Key.
#define IOT_CONFIG_CONNECTION_STRING "HostName=TamperTest2024v1.azure-devices.net;DeviceId=ESP32C6v1;SharedAccessKey=ElnY3bFuP/ENsvZSh4nx6ppllL/h6K8GWMCzySYZYFg="

// =============== Optional X.509 Certificate Authentication ===============
// Uncomment the following lines if using X.509 certificate-based authentication
//#define IOT_CONFIG_USE_X509_CERT
#ifdef IOT_CONFIG_USE_X509_CERT
    #define IOT_CONFIG_DEVICE_CERT     "-----BEGIN CERTIFICATE-----\n...\n-----END CERTIFICATE-----"
    #define IOT_CONFIG_DEVICE_CERT_PRIVATE_KEY "-----BEGIN PRIVATE KEY-----\n...\n-----END PRIVATE KEY-----"
#endif

// ===================== Power Management =====================
#define TIME_TO_SLEEP                60                      // Time ESP32 will go to sleep (in seconds)
#define BUTTON_PIN_BITMASK           (1ULL << GPIO_NUM_0)    // GPIO pin bitmask for wakeup from deep sleep (using GPIO 0 in this example)

#endif // IOT_CONFIGS_H