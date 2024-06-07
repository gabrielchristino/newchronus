#include <Arduino.h>
#include "screen.h"
#include "clock.h"
#include "configs.h"

const uint8_t menuSize = 20;

void (*menuFunc[menuSize][4])(void) = {
    /*0*/{[]{moveMenu(15);},[]{moveMenu(19);},[]{returnTime(); returnDate(); moveMenu(1);}, []{displayMenu("Settings", "/power.bmp", "/settings.bmp", "/clock.bmp");}},

    /*1*/{[]{moveMenu(2);},[]{moveMenu(5);},[]{returnTime(); returnDate(); moveMenu(6);}, []{displayMenu("Set Time", "/back.bmp", "/clock.bmp", "/calendar.bmp");}},
    /*2*/{[]{moveMenu(3);},[]{moveMenu(1);},[]{returnTime(); returnDate(); moveMenu(10);}, []{displayMenu("Set date", "/clock.bmp", "/calendar.bmp", "/sleep.bmp");}},
    /*3*/{[]{moveMenu(4);},[]{moveMenu(2);},[]{returnTime(); returnDate(); moveMenu(14);}, []{displayMenu("Set screen time", "/calendar.bmp", "/sleep.bmp", "/ota.bmp");}},
    /*4*/{[]{moveMenu(5);},[]{moveMenu(3);},[]{saveConfig("ota", getConfig("ota") == "1" ? "0" : "1");ESP.restart();}, []{displayMenu(getConfig("ota") == "1" ? "Over the air" : "Wired", "/sleep.bmp", "/ota.bmp", "/back.bmp");}},
    /*5*/{[]{moveMenu(1);},[]{moveMenu(4);},[]{returnTime(); returnDate(); moveMenu(0);}, []{displayMenu("Back", "/ota.bmp", "/back.bmp", "/clock.bmp");}},

    /*6*/{[]{setHora(1);callFunc(3);},[]{setHora(-1);callFunc(3);},[]{moveMenu(7);}, []{displayMenu("Hour " + getHora(), "", "/clock.bmp", "/clock.bmp");}},
    /*7*/{[]{setMinuto(1);callFunc(3);},[]{setMinuto(-1);callFunc(3);},[]{moveMenu(8);}, []{displayMenu("Minute " + getMinuto(), "", "/clock.bmp", "/clock.bmp");}},
    /*8*/{[]{setSegundo();callFunc(3);},[]{setSegundo();callFunc(3);},[]{moveMenu(9);}, []{displayMenu("Second " + getSegundo(), "", "/clock.bmp", "/save.bmp");}},
    /*9*/{[]{},[]{},[]{setTimeDate(); moveMenu(1);}, []{displayMenu("Save", "", "/save.bmp", "");}},

    /*10*/{[]{setAno(1);callFunc(3);},[]{setAno(-1);callFunc(3);},[]{moveMenu(11);}, []{displayMenu("Year " + getAno(), "", "/calendar.bmp", "/calendar.bmp");}},
    /*11*/{[]{setMes(1);callFunc(3);},[]{setMes(-1);callFunc(3);},[]{moveMenu(12);}, []{displayMenu("Month " + getMes(), "", "/calendar.bmp", "/calendar.bmp");}},
    /*12*/{[]{setDia(1);callFunc(3);},[]{setDia(-1);callFunc(3);},[]{moveMenu(13);}, []{displayMenu("Day " + getDia(), "", "/calendar.bmp", "/save.bmp");}},
    /*13*/{[]{},[]{},[]{setTimeDate(); moveMenu(2);}, []{displayMenu("Save", "", "/save.bmp", "");}},

    /*14*/{[]{setScreenTimeOut(1);callFunc(3);},[]{setScreenTimeOut(-1);callFunc(3);},[]{saveConfig("screenTimeout", getScreenTimeOut());moveMenu(3);}, []{displayMenu("Timeout " + getScreenTimeOut() + "s", "", "/sleep.bmp", "");}},

    /*15*/{[]{moveMenu(17);},[]{moveMenu(0);},[]{moveMenu(16);}, []{displayMenu("Time", "/settings.bmp", "/clock.bmp", "/calendar.bmp");}},
    /*16*/{[]{},[]{},[]{clearScreen();displayMenu("", "", "", "");moveMenu(15);}, []{showTime();}},

    /*17*/{[]{moveMenu(19);},[]{moveMenu(15);},[]{moveMenu(18);}, []{displayMenu("Calendar", "/clock.bmp", "/calendar.bmp", "/power.bmp");}},
    /*18*/{[]{showCalendar(1);},[]{showCalendar(-1);},[]{clearScreen();displayMenu("", "", "", "");moveMenu(17);}, []{showCalendar(0);}},

    /*19*/{[]{moveMenu(0);},[]{moveMenu(17);},[]{turnOff();}, []{displayMenu("Sleep", "/calendar.bmp", "/power.bmp", "/settings.bmp");}},
};