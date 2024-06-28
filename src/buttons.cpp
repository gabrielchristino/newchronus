#include <Arduino.h>

#include "buttons.h"
#include "screen.h"

struct BTN
{
    uint8_t pin;
    bool lastState;
    int lastTime;
    void click(void (*callback)())
    {
        uint8_t valor = touchRead(pin);
        // Serial.println(valor);
        // if(pin == 12) drawDebug(String(valor));
        bool state = (valor < THRESHOLD && valor > 0);
        int nowTime = millis();
        if (!state && state != lastState && (nowTime - lastTime > 500))
        {
            callback();
            lastTime = nowTime;
        }
        lastState = state;
    };
};

BTN btnUp;
BTN btnDown;
BTN btnOk;

void initButtons()
{
    btnUp.pin = 27;   // T7;
    btnDown.pin = 12; // T5;
    btnOk.pin = 14;    // T6;
}

void readButtons()
{
    btnUp.click([]
                { resetTimer(); callFunc(0); });
    btnDown.click([]
                  { resetTimer(); callFunc(1); });
    btnOk.click([]
                { resetTimer(); callFunc(2); });
}