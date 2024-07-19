#include <Arduino.h>

#include "screen.h"
#include "buttons.h"
#include "power.h"
#include "ota.h"
#include "configs.h"

void setup()
{
  wakeUpReason();
}

void loop()
{
  readButtons();
  otaHandle();
  if(getConfig("ota") == "1") return;
  screenTimeOut();
}
