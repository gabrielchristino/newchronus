#include "power.h"
#include "clock.h"
#include "screen.h"
#include "buttons.h"
#include "configs.h"
#include "ota.h"

#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 60 * 60 * 24 /* Time ESP32 will go to sleep (in seconds) */
#define THRESHOLD 60

touch_pad_t touchPin;
esp_sleep_wakeup_cause_t wakeup_reason;

void wakeUpReason()
{

#ifdef SERIAL_ENABLED
    Serial.begin(115200);
#endif

    initSPIFFS();

    initScreen();

    createAP();
    updateCodeOta();

    initButtons();

    touchPin = esp_sleep_get_touchpad_wakeup_status();

    wakeup_reason = esp_sleep_get_wakeup_cause();
    Serial.print("wake ");
    Serial.println(wakeup_reason);
    switch (wakeup_reason)
    {
    case ESP_SLEEP_WAKEUP_TIMER:
#ifdef SERIAL_ENABLED
        Serial.println("Wakeup caused by timer");
#endif
        break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD:
#ifdef SERIAL_ENABLED
        Serial.print("Wakeup caused by touchpad");
        Serial.println(touchPin);
#endif
        if (touchPin == 6 /*ok*/)
        {
            moveMenu(16);
            break;
        }
        if (touchPin == 5 /*down*/ || touchPin == 7 /*up*/)
        {
            clearScreen();
            moveMenu(0);
            break;
        }
    default:
        setTimeDate();
        setSleepMode();
        Serial.println(getConfig("ota"));
        if (getConfig("ota") == "1")
        {
            Serial.println("on");
            resetTimer();
        }
        else
        {
            //moveMenu(0);
            Serial.println("off");
            turnOff();
        }
        break;
    }
}

void setSleepMode()
{
    touchSleepWakeUpEnable(12, THRESHOLD);
    touchSleepWakeUpEnable(14, THRESHOLD);
    touchSleepWakeUpEnable(27, THRESHOLD);

    // esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
}

void goToSleep()
{
#ifdef SERIAL_ENABLED
    Serial.println("bye");
#endif
    esp_deep_sleep_start();
    esp_light_sleep_start();
}