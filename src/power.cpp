#include "power.h"
#include "clock.h"
#include "screen.h"

#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 60 * 60 * 24 /* Time ESP32 will go to sleep (in seconds) */
#define THRESHOLD 30

touch_pad_t touchPin;
esp_sleep_wakeup_cause_t wakeup_reason;

void wakeUpReason()
{
    touchPin = esp_sleep_get_touchpad_wakeup_status();

    wakeup_reason = esp_sleep_get_wakeup_cause();
    switch (wakeup_reason)
    {
    case ESP_SLEEP_WAKEUP_TIMER:
        // Serial.println("Wakeup caused by timer");
        break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD:
        // Serial.print("Wakeup caused by touchpad");
        // Serial.println(touchPin);
        if (touchPin == 0)
            showTime(); // ok
        if (touchPin == 5)
        {
            clearScreen();
            moveMenu(0);
        } // down
        if (touchPin == 9)
        {
            clearScreen();
            moveMenu(0);
        } // up
        break;
    default:
        setTimeDate();
        setSleepMode();
        turnOff();
        break;
    }
}

void setSleepMode()
{
    touchSleepWakeUpEnable(4, THRESHOLD);
    touchSleepWakeUpEnable(12, THRESHOLD);
    touchSleepWakeUpEnable(32, THRESHOLD);

    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
}

void goToSleep()
{
    // Serial.println("bye");
    esp_deep_sleep_start();
}