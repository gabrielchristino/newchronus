#include "clock.h"
#include "tempo.h"

ESP32Time rtc(-3 * 3600); // offset in seconds GMT-3

void setTimeDate()
{
    rtc.setTime(getSegundo().toInt(), getMinuto().toInt(), getHora().toInt() + 3, getDia().toInt(), getMes().toInt(), getAno().toInt());
}

void setHora(int8_t valor)
{
    hora += valor;
    hora = hora == 255 ? 23 : hora > 23 ? 0 : hora;
}

String getHora() { return String(hora); }

void setMinuto(int8_t valor)
{
    minuto += valor;
    minuto = minuto == 255 ? 59 : minuto > 59 ? 0 : minuto;
}

String getMinuto() { return String(minuto); }

void setSegundo()
{
    segundo = 0;
}

String getSegundo() { return String(segundo); }

uint16_t isBissexto(uint16_t ano)
{
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

void setDia(int8_t valor)
{
    int8_t diasNoMes = 31;
    if (getMes().toInt() == 2)
        diasNoMes = isBissexto(getAno().toInt()) ? 29 : 28;
    if (getMes().toInt() == 4 || getMes().toInt() == 6 || getMes().toInt() == 9 || getMes().toInt() == 1)
        diasNoMes = 30;

    dia += valor;
    dia = dia == 255 ? diasNoMes : dia > diasNoMes ? 0 : dia;
}

String getDia() { return String(dia); }

void setMes(int8_t valor)
{
    mes += valor;
    mes = mes > 12 ? 0 : mes == -1 ? 12 : mes;
}

String getMes() { return String(mes); }

void setAno(int8_t valor)
{
    ano += valor;
}

String getAno() { return String(ano); }

String returnTime()
{
    hora = rtc.getTime("%H").toInt();
    minuto = rtc.getTime("%M").toInt();
    segundo = rtc.getTime("%S").toInt();
    return rtc.getTime("%R");
}

String returnDate()
{
    dia = rtc.getTime("%e").toInt();
    mes = rtc.getTime("%m").toInt();
    ano = rtc.getTime("%Y").toInt();
    return rtc.getTime("%a, %e %b");
}