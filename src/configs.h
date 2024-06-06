#include <Arduino.h>
#include <SPIFFS.h>

#define OTA_ENABLED true
#define SERIAL_ENABLED true

void initSPIFFS();
String searchForKey(File file, String key);
String getConfig(String key);
void replaceLine(File file, String startOfLine, String newLine);
void saveConfig(String key, String value);