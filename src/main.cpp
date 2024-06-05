#include <Arduino.h>

#include "screen.h"
#include "buttons.h"
#include "power.h"
#include "ota.h"

void setup()
{
#ifdef SERIAL_ENABLED
  Serial.begin(115200);
#endif

  wakeUpReason();
}

void loop()
{
  readButtons();
  screenTimeOut();
  otaHandle();
}
