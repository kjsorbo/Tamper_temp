#ifndef POWERMANAGER_H
#define POWERMANAGER_H

#include <esp_sleep.h>

class PowerManager {
public:
    static void configureWakeup(uint64_t ext1_pin_mask, uint32_t time_to_sleep);
    static void enterDeepSleep();
    static void printWakeupReason();
};

#endif
