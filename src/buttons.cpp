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
    btnUp.pin = 32;   // T9;
    btnDown.pin = 12; // T5;
    btnOk.pin = 4;    // T0;
}

void readButtons()
{
    btnUp.click([]
                {
                    callFunc(0); });
    btnDown.click([]
                  {
                    callFunc(1); });
    btnOk.click([]
                {
                    callFunc(2); });
}