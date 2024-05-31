#include <Arduino.h>
#include "screen.h"
#include "clock.h"
#include "configs.h"

const uint8_t menuSize = 17;

void (*menuFunc[menuSize][4])(void) = {
    /*0*/{[]{moveMenu(14);},[]{moveMenu(menuSize - 1);},[]{returnTime(); returnDate(); moveMenu(1);}, []{displayMenu("Settings", "/power.bmp", "/settings.bmp", "/clock.bmp");}},

    /*1*/{[]{moveMenu(2);},[]{moveMenu(4);},[]{returnTime(); returnDate(); moveMenu(5);}, []{displayMenu("Set Time", "/back.bmp", "/clock.bmp", "/calendar.bmp");}},
    /*2*/{[]{moveMenu(3);},[]{moveMenu(1);},[]{returnTime(); returnDate(); moveMenu(9);}, []{displayMenu("Set date", "/clock.bmp", "/calendar.bmp", "/sleep.bmp");}},
    /*3*/{[]{moveMenu(4);},[]{moveMenu(2);},[]{returnTime(); returnDate(); moveMenu(13);}, []{displayMenu("Set screen time", "/calendar.bmp", "/sleep.bmp", "/back.bmp");}},
    /*4*/{[]{moveMenu(1);},[]{moveMenu(3);},[]{returnTime(); returnDate(); moveMenu(0);}, []{displayMenu("Back", "/sleep.bmp", "/back.bmp", "/clock.bmp");}},

    /*5*/{[]{setHora(1);callFunc(3);},[]{setHora(-1);callFunc(3);},[]{moveMenu(6);}, []{displayMenu("Hour " + getHora(), "", "/clock.bmp", "/clock.bmp");}},
    /*6*/{[]{setMinuto(1);callFunc(3);},[]{setMinuto(-1);callFunc(3);},[]{moveMenu(7);}, []{displayMenu("Minute " + getMinuto(), "", "/clock.bmp", "/clock.bmp");}},
    /*7*/{[]{setSegundo();callFunc(3);},[]{setSegundo();callFunc(3);},[]{moveMenu(8);}, []{displayMenu("Second " + getSegundo(), "", "/clock.bmp", "/save.bmp");}},
    /*8*/{[]{},[]{},[]{setTimeDate(); moveMenu(1);}, []{displayMenu("Save", "", "/save.bmp", "");}},

    /*9*/{[]{setAno(1);callFunc(3);},[]{setAno(-1);callFunc(3);},[]{moveMenu(10);}, []{displayMenu("Year " + getAno(), "", "/calendar.bmp", "/calendar.bmp");}},
    /*10*/{[]{setMes(1);callFunc(3);},[]{setMes(-1);callFunc(3);},[]{moveMenu(11);}, []{displayMenu("Month " + getMes(), "", "/calendar.bmp", "/calendar.bmp");}},
    /*11*/{[]{setDia(1);callFunc(3);},[]{setDia(-1);callFunc(3);},[]{moveMenu(12);}, []{displayMenu("Day " + getDia(), "", "/calendar.bmp", "/save.bmp");}},
    /*12*/{[]{},[]{},[]{setTimeDate(); moveMenu(2);}, []{displayMenu("Save", "", "/save.bmp", "");}},

    /*13*/{[]{setScreenTimeOut(1);callFunc(3);},[]{setScreenTimeOut(-1);callFunc(3);},[]{saveConfig("screenTimeout", getScreenTimeOut());moveMenu(3);}, []{displayMenu("Timeout " + getScreenTimeOut() + "s", "", "/sleep.bmp", "");}},

    /*14*/{[]{moveMenu(15);},[]{moveMenu(0);},[]{showTime();}, []{displayMenu("Time", "/settings.bmp", "/clock.bmp", "/calendar.bmp");}},
    /*15*/{[]{moveMenu(16);},[]{moveMenu(14);},[]{showCalendar();}, []{displayMenu("Calendar", "/clock.bmp", "/calendar.bmp", "/power.bmp");}},

    /*16*/{[]{moveMenu(0);},[]{moveMenu(15);},[]{turnOff();}, []{displayMenu("Sleep", "/calendar.bmp", "/power.bmp", "/settings.bmp");}},
};