#include <Arduino.h>
#include <screen.h>
#include <clock.h>

const uint8_t menuSize = 15;

void (*menuFunc[menuSize][4])(void) = {
    {[]{moveMenu(12);},[]{moveMenu(menuSize - 1);},[]{returnTime(); returnDate(); moveMenu(1);}, []{displayMenu("Settings", "/power.bmp", "/settings.bmp", "/clock.bmp");}},

    {[]{moveMenu(2);},[]{moveMenu(3);},[]{returnTime(); returnDate(); moveMenu(4);}, []{displayMenu("Set Time", "/back.bmp", "/clock.bmp", "/calendar.bmp");}},
    {[]{moveMenu(3);},[]{moveMenu(1);},[]{returnTime(); returnDate(); moveMenu(8);}, []{displayMenu("Set date", "/clock.bmp", "/calendar.bmp", "/back.bmp");}},
    {[]{moveMenu(1);},[]{moveMenu(2);},[]{returnTime(); returnDate(); moveMenu(0);}, []{displayMenu("Back", "/calendar.bmp", "/back.bmp", "/clock.bmp");}},

    {[]{setHora(1);callFunc(3);},[]{setHora(-1);callFunc(3);},[]{moveMenu(5);}, []{displayMenu("Hour " + getHora(), "", "/clock.bmp", "/clock.bmp");}},
    {[]{setMinuto(1);callFunc(3);},[]{setMinuto(-1);callFunc(3);},[]{moveMenu(6);}, []{displayMenu("Minute " + getMinuto(), "", "/clock.bmp", "/clock.bmp");}},
    {[]{setSegundo();callFunc(3);},[]{setSegundo();callFunc(3);},[]{moveMenu(7);}, []{displayMenu("Second " + getSegundo(), "", "/clock.bmp", "/save.bmp");}},
    {[]{},[]{},[]{setTimeDate(); moveMenu(1);}, []{displayMenu("Save", "", "/save.bmp", "");}},

    {[]{setAno(1);callFunc(3);},[]{setAno(-1);callFunc(3);},[]{moveMenu(9);}, []{displayMenu("Year " + getAno(), "", "/calendar.bmp", "/calendar.bmp");}},
    {[]{setMes(1);callFunc(3);},[]{setMes(-1);callFunc(3);},[]{moveMenu(10);}, []{displayMenu("Month " + getMes(), "", "/calendar.bmp", "/calendar.bmp");}},
    {[]{setDia(1);callFunc(3);},[]{setDia(-1);callFunc(3);},[]{moveMenu(11);}, []{displayMenu("Day " + getDia(), "", "/calendar.bmp", "/save.bmp");}},
    {[]{},[]{},[]{setTimeDate(); moveMenu(2);}, []{displayMenu("Save", "", "/save.bmp", "");}},

    {[]{moveMenu(13);},[]{moveMenu(0);},[]{showTime();}, []{displayMenu("Time", "/settings.bmp", "/clock.bmp", "/calendar.bmp");}},
    {[]{moveMenu(14);},[]{moveMenu(12);},[]{showCalendar();}, []{displayMenu("Calendar", "/clock.bmp", "/calendar.bmp", "/power.bmp");}},

    {[]{moveMenu(0);},[]{moveMenu(13);},[]{turnOff();}, []{displayMenu("Sleep", "/calendar.bmp", "/power.bmp", "/settings.bmp");}},
};