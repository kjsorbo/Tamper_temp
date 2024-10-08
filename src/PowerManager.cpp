#include "PowerManager.h"
#include <Arduino.h>

void PowerManager::configureWakeup(uint64_t ext1_pin_mask, uint32_t time_to_sleep) {
    esp_sleep_enable_ext1_wakeup(ext1_pin_mask, ESP_EXT1_WAKEUP_ANY_HIGH);
    esp_sleep_enable_timer_wakeup(time_to_sleep * 1000000ULL);
}

void PowerManager::enterDeepSleep() {
    Serial.println("Going to sleep now...");
    esp_deep_sleep_start();
}

void PowerManager::printWakeupReason() {
    esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
    switch (wakeup_reason) {
        case ESP_SLEEP_WAKEUP_EXT1: Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
        case ESP_SLEEP_WAKEUP_TIMER: Serial.println("Wakeup caused by timer"); break;
        default: Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason); break;
    }
}
