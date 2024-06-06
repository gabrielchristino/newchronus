#include "power.h"
#include "clock.h"
#include "screen.h"
#include "buttons.h"
#include "configs.h"
#include "ota.h"

#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 60 * 60 * 24 /* Time ESP32 will go to sleep (in seconds) */
#define THRESHOLD 30

touch_pad_t touchPin;
esp_sleep_wakeup_cause_t wakeup_reason;

void wakeUpReason()
{

    initSPIFFS();

    initScreen();
    
    updateCodeOta();

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
        if (touchPin == 0 /*ok*/)
        {
            showTime();
            break;
        }
        if (touchPin == 5 /*down*/ || touchPin == 9 /*up*/)
        {
            initButtons();
            clearScreen();
            moveMenu(0);
            break;
        }
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
    #ifdef SERIAL_ENABLED
        Serial.println("bye");
    #endif
    esp_deep_sleep_start();
}