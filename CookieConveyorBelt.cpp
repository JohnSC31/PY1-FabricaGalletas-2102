#include "structs.h"


void CookieConveyorBelt::__init__(int _maxCookies, QMutex * _mutex){
    maxCookies = _maxCookies;
    mutex = _mutex;
    cookies = 0;
    printConfig();
    printData();
}

bool CookieConveyorBelt::canAddCookies(int newCookies){
    if(maxCookies - (cookies +  newCookies) >= 0){
        return true; // hay espacio
    }else{
        return false; // no hay espacio
    }
}

int CookieConveyorBelt::addCookies(int newCookies){
    cookies += newCookies;
    int cookiesExcess = maxCookies - cookies;
    if(cookiesExcess < 0){
        // hay un exceso de gramos en la banda
        cookies += cookiesExcess;
        printData();
        return -(cookiesExcess); // los gramos que se devuelven
    }

    printData();
    return 0;
}

void CookieConveyorBelt::printData(){
    lblCookieBelt->setText(" \n Actual: " + QString::number(cookies));
}

void CookieConveyorBelt::printConfig(){
    inpCookieBeltMax->setText(QString::number(maxCookies));
}

void CookieConveyorBelt::updateConfig(double _maxCookies){
    maxCookies = _maxCookies;
    printConfig();
}
