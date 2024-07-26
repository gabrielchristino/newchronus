#include <stdint.h>
#include "driver/touch_sensor.h"
#include <Arduino.h>

#define THRESHOLD 60
#define MEDIA_LEITURA 50

void initButtons();
void readButtons();