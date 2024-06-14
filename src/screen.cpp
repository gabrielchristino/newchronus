#include "screen.h"
#include "power.h"
#include "clock.h"
#include "apps.h"
#include "configs.h"

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
SPIFFS_ImageReader reader;

uint8_t screenTimeValue = 0;
unsigned long previousMillis = 0;

uint8_t currentMenu = 0;
uint8_t currentSubMenu = 0;
bool inSubMenu = 0;

char *ultimoArquivo1;
char *ultimoArquivo2;
char *ultimoArquivo3;

uint8_t mesSelecionado = getMes().toInt();
uint8_t anoSelecionado = getAno().toInt();

void initScreen()
{
    pinMode(5, OUTPUT);
    digitalWrite(5, HIGH); // liga tela

    tft.setSPISpeed(40000000);
    tft.initR(INITR_MINI160x80_PLUGIN); // Init ST7735S mini display

    tft.setRotation(1);
    tft.cp437(true);

    screenTimeValue = getConfig("screenTimeout").toInt();
#ifdef SERIAL_ENABLED
    Serial.println("inicio " + String(screenTimeValue));
#endif
}

void showTime()
{
    tft.setTextColor(0xef5d);
    tft.setFont(&FreeSans24pt7b);
    tft.setTextWrap(true);
    // drawImage("/fundo.bmp", 0, 0);
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

    double moonPhase = calculateMoonPhase(getAno().toInt(), getMes().toInt(), getDia().toInt());
    drawMoonPhase(moonPhase);

    tft.enableDisplay(true);
}

void setScreenTimeOut(int8_t valor)
{
    screenTimeValue += valor;
    if (screenTimeValue < 5)
        screenTimeValue = 5;
    if (screenTimeValue > 255)
        screenTimeValue = 255;
}

String getScreenTimeOut()
{
    return String(screenTimeValue);
}

void screenTimeOut()
{
    int tempoTela = getScreenTimeOut().toInt();
    unsigned long currentMillis = millis();
    if (tempoTela != 0 && currentMillis - previousMillis >= tempoTela * 1000)
    {
        turnOff();
        previousMillis = currentMillis;
    }
}

void resetTimer()
{
    previousMillis = millis();
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

void displayMenu(String valor, char *arquivo1, char *arquivo2, char *arquivo3)
{
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
    if (ultimoArquivo1 != arquivo1)
        if (arquivo1 != "")
        {
            drawImage(arquivo1, -15, 5);
        }
        else
        {
            tft.fillRect(0, 5, 29, 44, 0xf79b);
        }
    if (ultimoArquivo2 != arquivo2)
        if (arquivo2 != "")
        {
            drawImage(arquivo2, 58, 5);
        }
        else
        {
            tft.fillRect(58, 5, 44, 44, 0xf79b);
        }
    if (ultimoArquivo3 != arquivo3)
        if (arquivo3 != "")
        {
            drawImage(arquivo3, 131, 5);
        }
        else
        {
            tft.fillRect(131, 5, 29, 44, 0xf79b);
        }

    ultimoArquivo1 = arquivo1;
    ultimoArquivo2 = arquivo2;
    ultimoArquivo3 = arquivo3;
    tft.enableDisplay(true);
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

void drawImage(char *arquivo, int16_t x, int16_t y)
{
    reader.drawBMP(arquivo, tft, x, y);
}

void clearScreen()
{
    tft.fillScreen(0xf79b);
}

void showCalendar(uint8_t mover)
{
    mesSelecionado += mover;
    if (mesSelecionado > 12)
    {
        mesSelecionado = 1;
        anoSelecionado += 1;
    }
    if (mesSelecionado < 1)
    {
        mesSelecionado = 12;
        anoSelecionado -= 1;
    }
    clearScreen();
    String listaMeses[12] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
    tft.setTextColor(ST7735_BLACK);
    tft.setFont(&FreeMono9pt7b);

    tft.setCursor(64, 40);
    tft.print(listaMeses[mesSelecionado - 1]);

    delay(1000);
    tft.fillRect(64, 31, 32, 10, 0xf79b);

    int x = 4;
    int y = 13;
    String weekDays[7] = {"D", "S", "T", "Q", "Q", "S", "S"};
    for (int i = 1; i <= 7; i++)
    {
        tft.setCursor(x + 5, y);
        tft.print(weekDays[i - 1]);
        x += 22;
    }

    x = 4 + getPrimeiroDiaMes(mesSelecionado, getAno().toInt()) * 22;
    y += 13;

    for (int i = 1; i <= diasNoMes(mesSelecionado, getAno().toInt()); i++)
    {
        tft.setTextColor(0x73ad);
        if (i == getDia().toInt() && mesSelecionado == getMes().toInt())
            tft.setTextColor(0xec10);
        tft.setCursor(i < 10 ? x + 5 : x, y); // adjust for single digit days
        tft.print(i);
        x += 22;
        if (x > 140)
        {
            x = 4;
            y += 13;
        }
    }

    tft.enableDisplay(true);
}

void wellcome()
{
    clearScreen();
    tft.setTextColor(0x73ad);
    drawImage("/logo.bmp", 40, 0);
}

void drawMoonPhase(double phase)
{
    uint8_t x = 25;
    uint8_t y = 25;
    uint8_t r = 10;
    tft.fillCircle(x, y, r, ST77XX_BLACK);
    tft.drawCircle(x, y, r, ST77XX_WHITE);

    /*
    0 - New Moon
    1 - Waxing Crescent
    2 - First Quarter
    3 - Waxing Gibbous
    4 - Full Moon
    5 - Waning Gibbous
    6 - Last Quarter
    7 - Waning Crescent
    ______________________________________________________
    |    |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
    | a1 |  r  |  r  |  r  |  r  |  r  |  0  |-r/2 | -r  |
    | a2 |  r  | r/2 |  0  |-r/2 | -r  | -r  | -r  | -r  |
    */

    double a1 = phase <= 4 ? r : -(r / 2) * phase + 3 * r;
    double a2 = phase >= 4 ? -r : -(r / 2) * phase + r;

    for (double i = a2; i < a1; i++)
    {
        drawEllipse(x, y, i, r, ST77XX_WHITE, 90, 270);
    }
}

void drawEllipse(int x, int y, int rx, int ry, uint16_t color, uint16_t start = 90, uint16_t end = 270)
{
    int x0 = x - rx;
    int y0 = y - ry;
    int x1 = x + rx;
    int y1 = y + ry;

    for (int i = start; i < end; i++)
    {
        float a = i * PI / 180.0;
        int px = x + rx * cos(a);
        int py = y + ry * sin(a);
        tft.drawLine(px, py, px, py, color);
    }
}