#include "screen.h"
#include "power.h"
#include "clock.h"
#include "apps.h"

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
SPIFFS_ImageReader reader;

int currentTime = millis();
int startTime = 0;

uint8_t currentMenu = 0;
uint8_t currentSubMenu = 0;
bool inSubMenu = 0;

char* ultimoArquivo1;
char* ultimoArquivo2;
char* ultimoArquivo3;

void initScreen()
{
    SPIFFS.begin(true);

    pinMode(5, OUTPUT);
    digitalWrite(5, HIGH); // liga tela

    tft.setSPISpeed(40000000);
    tft.initR(INITR_MINI160x80_PLUGIN); // Init ST7735S mini display

    tft.setRotation(1);
    tft.cp437(true);
    // tft.enableDisplay(true);
    // tft.fillScreen(ST77XX_WHITE);
    // delay(100);
    // tft.fillScreen(ST77XX_BLACK);
    // delay(100);
    // tft.enableDisplay(false);
}

void showTime()
{
    // tft.enableDisplay(false);
    // tft.fillScreen(ST77XX_BLACK);

    tft.setTextColor(0xef5d);
    tft.setFont(&FreeSans24pt7b);
    tft.setTextWrap(true);
    drawImage("/fundo.bmp", 0, 0);
    int16_t x1, y1;
    uint16_t w, h;
    tft.getTextBounds(returnTime(), 0, 0, &x1, &y1, &w, &h); // Calculate w/h of text
    uint8_t x = (160 - w - 10);
    uint8_t y = h + 5;
    tft.setCursor(x, y);
    tft.println(returnTime());

    tft.setFont(&FreeSans9pt7b);
    tft.getTextBounds(returnDate(), 0, 0, &x1, &y1, &w, &h); // Calculate w/h of text
    x = (160 - w - 10);
    y = (80 - h + 5);
    tft.setCursor(x, y);
    tft.println(returnDate());
    tft.enableDisplay(true);
    screenTime();
}

void screenTime()
{
    currentTime = millis();
    startTime = currentTime;
    while (true)
    {
        currentTime = millis();
        if (currentTime - startTime > 5000)
        {
            turnOff();
            break;
        }
    }
}

void showColor()
{
    tft.fillScreen(ST77XX_GREEN);
    tft.enableDisplay(true);
}

void turnOff()
{
    tft.enableDisplay(false);
    tft.fillScreen(ST77XX_BLACK);
    digitalWrite(5, LOW);
    setSleepMode();
    goToSleep();
}

void displayMenu(String valor, char* arquivo1, char* arquivo2, char* arquivo3)
{
    // tft.enableDisplay(false);
    // tft.fillScreen(0xf79b);
    tft.fillRect(0, 50, 160, 50, 0xf79b);
    tft.setTextColor(0x73ad);
    tft.setFont(&FreeSans9pt7b);

    int16_t x1, y1;
    uint16_t w, h;
    tft.getTextBounds(valor, 0, 0, &x1, &y1, &w, &h); // Calculate w/h of text
    uint8_t x = (160 - w) / 2;
    uint8_t y = (87 - h);

    tft.setCursor(x, y);
    tft.println(valor);
    if(ultimoArquivo1 != arquivo1) if (arquivo1 != "") {drawImage(arquivo1, -15, 5);} else {tft.fillRect(0, 5, 29, 44, 0xf79b);}
    if(ultimoArquivo2 != arquivo2) if (arquivo2 != "") {drawImage(arquivo2, 58, 5);} else {tft.fillRect(58, 5, 44, 44, 0xf79b);}
    if(ultimoArquivo3 != arquivo3) if (arquivo3 != "") {drawImage(arquivo3, 131, 5);} else {tft.fillRect(131, 5, 29, 44, 0xf79b);}

    ultimoArquivo1 = arquivo1;
    ultimoArquivo2 = arquivo2;
    ultimoArquivo3 = arquivo3;
    tft.enableDisplay(true);
    // screenTime();
}

void moveMenu(uint8_t nivel)
{
    currentMenu = nivel;

    callFunc(3);
}

void callFunc(uint8_t i)
{
    (*menuFunc[currentMenu][i])();
}

void drawImage(char* arquivo, int16_t x, int16_t y)
{
  reader.drawBMP(arquivo, tft, x, y);
} 

void clearScreen()
{
    tft.fillScreen(0xf79b);
}