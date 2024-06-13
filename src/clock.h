#include <ESP32Time.h>
#include <cmath>

void setTimeDate();
void setHora(int8_t valor);
String getHora();
void setMinuto(int8_t valor);
String getMinuto();
void setSegundo();
String getSegundo();
void setDia(int8_t valor);
String getDia();
void setMes(int8_t valor);
String getMes();
void setAno(int8_t valor);
String getAno();
String returnTime();
String returnDate();
int8_t diasNoMes(uint8_t month, uint16_t year);
uint16_t isBissexto(uint16_t ano);
uint8_t getPrimeiroDiaMes(uint8_t month, uint16_t year);
double calculateMoonPhase(int year, int month, int day);
double julianDay(int year, int month, int day);