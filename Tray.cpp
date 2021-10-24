#include "structs.h"


Tray::Tray(){

}


void Tray::__init__(int _maxCookies, int _bakingTime, CookieConveyorBelt * _cookieConveyorBelt2){
    maxCookies = _maxCookies;
    bakingTime = _bakingTime;
    cookieConveyorBelt = _cookieConveyorBelt2;
    cookies = 0;
}


void Tray::run(){

    while(isActive){

        while(isPause){
            sleep(1);
        }

        // funcionamiento de la maquina
        if(isFull()){ // hornea apenas esta llena
            isBaking = true;
            bakeCookies();
            isBaking = false;
         }else{
            sleep(1); // espera para revisar otra vez si ya esta llena
        }

    }
}

// cocina las galletas y la coloca en la siguiente banda si no puede sacarlas todas se pausa
void Tray::bakeCookies(){
    sleep(bakingTime);

    while(cookies > 0){
        cookieConveyorBelt->mutex->lock();
        cookies = cookieConveyorBelt->addCookies(cookies);
        cookieConveyorBelt->mutex->unlock();
        if(cookies == 0){
            resume();
            break;
        }
        pause();
        sleep(1);
    }
    // no se sale hasta que se vacie
}


bool Tray::isFull(){
    return maxCookies == cookies;
}

int Tray::addCookies(int newCookies){
    cookies += newCookies;
    int cookiesExcess = maxCookies - cookies;
    if(cookiesExcess < 0){
        // hay un exceso de gramos en la banda
        cookies += cookiesExcess;
        return -(cookiesExcess); // los gramos que se devuelven
    }
    return 0;
}


// funciones para control del thread
void Tray::pause(){
    isPause = true;
}

void Tray::resume(){
    isPause = false;
}

void Tray::finish(){
    isActive = false;
}

