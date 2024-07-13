#include <WiFi.h>
#include <WiFiMulti.h>

// Define WiFi credentials
#define ssid "iPhone"
#define password "mmmm0000"

// #define ssid "gtchris100"
// #define password "carsled100"

// Define server details and file path
#define PATH_FIRMWARE "https://raw.githubusercontent.com/gabrielchristino/newchronus/develop/.pio/build/esp32doit-devkit-v1/firmware.bin"
#define PATH_SPIFFS "https://raw.githubusercontent.com/gabrielchristino/newchronus/develop/.pio/build/esp32doit-devkit-v1/spiffs.bin"

void createAP();
void updateCodeOta();
void otaHandle();
