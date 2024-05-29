#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Fonts/FreeSans24pt7b.h>
#include <Fonts/FreeSans9pt7b.h>

#include <SPI.h>

#include <SPIFFS.h>
#include <SPIFFS_ImageReader.h>

#define TFT_CS 21
#define TFT_DC 19
#define TFT_RST 18
#define TFT_MOSI 17
#define TFT_SCLK 16


void initScreen();
void showTime();
void showCalendar();
void screenTime();
void showColor();
void turnOff();
void displayMenu(String valor, char* arquivo1, char* arquivo2, char* arquivo3);
void moveMenu(uint8_t nivel);
void callFunc(uint8_t i);
void drawImage(char* arquivo, int16_t x, int16_t y);
void clearScreen();