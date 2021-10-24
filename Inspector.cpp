#include "structs.h"



Inspector::Inspector(){

}

void Inspector::__init__(int _cookiesPerTime, double _processTime, double _wasteProbability, CookieConveyorBelt * _cookieConveyorBeltBefore, CookieConveyorBelt * _cookieConveyorBeltNext){
    wasteProbabilty = _wasteProbability; // portentaje de probailidad
    cookiesPerTime = _cookiesPerTime;
    proccessTime = _processTime;
    provedCookies = 0;
    wastedCookies = 0;

    cookieConveyorBeltBefore = _cookieConveyorBeltBefore;
    cookieConveyorBeltNext = _cookieConveyorBeltNext;
}


void Inspector::run(){
    while(isActive){

        while(isPause){
            sleep(1);
        }
        \
        if(cookieConveyorBeltBefore->cookies >= cookiesPerTime){
           proccessCookies();

        }else{
            sleep(2);
        }



    }
}

void Inspector::proccessCookies(){
        sleep(proccessTime);
        cookieConveyorBeltBefore->mutex->lock();
        cookieConveyorBeltBefore->cookies -= cookiesPerTime;
        int cookiesExcess = 0;
        for(int i = 0; i < cookiesPerTime; i++){
            int random = ranGenerator.bounded(0, 100);
            if(random > wastedCookies){
                cookieConveyorBeltNext->mutex->lock();
                cookiesExcess = cookieConveyorBeltNext->addCookies(1);
                cookieConveyorBeltNext->mutex->unlock();
                if(cookiesExcess > 0){
                    cookieConveyorBeltBefore->cookies += cookiesExcess;
                    pause();
                    break;
                }
                provedCookies++;
            }else{
               wastedCookies++;
            }
        }
        cookieConveyorBeltBefore->printData();
        cookieConveyorBeltBefore->mutex->unlock();

}


// Funciones para el thread
void Inspector::pause(){
    isPause = true;
}

void Inspector::resume(){
    isPause = false;
}

void Inspector::finish(){
    isActive = false;
}
