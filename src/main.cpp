#include <Arduino.h>

#include "screen.h"
#include "buttons.h"
#include "power.h"
#include "clock.h"

void setup()
{
  //Serial.begin(115200);

  initScreen();
  wakeUpReason();
  initButtons();
}

void loop()
{
  readButtons();
}
