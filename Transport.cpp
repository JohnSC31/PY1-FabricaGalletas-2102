#include "structs.h"



Transport::Transport(){

}

void Transport::__init__(Planner * _planner, QString _packName, int _maxPacks, double _deliveryTime){
    packs = 0;
    packName = _packName;
    maxPacks = _maxPacks;
    deliveryTime = _deliveryTime;
    planner = _planner;
}


void Transport::run(){

    while(isActive){

        while(isPause){
            sleep(1); // no esta moviendo nada
        }

        if(isFull() && isAvailable){
            isAvailable = false;
            makePackDelivery();
            isAvailable = true;
        }

        sleep(1);
        // lo que hace cuando esta activo
    }

}


int Transport::loadPacks(int newPacks){
    packs += newPacks;
    double packExcess = maxPacks - packs;
    if(packExcess < 0){
        // hay un exceso de gramos en el transporte
        packs += packExcess;
        return -(packExcess); // los gramos que se devuelven
    }

    return 0;
}

void Transport::makePackDelivery(){
    sleep(deliveryTime / 2);
    unloadPacks(); // descarga los gramos en la maquina indicada
    sleep(deliveryTime / 2);
}

// le suma a los paquetes terminados
void Transport::unloadPacks(){

    for(int i = 0; i < planner->planProduction.size(); i++){
        if(planner->planProduction.at(i)->pack->name == packName){
            planner->planProduction.at(i)->finishedPacks += packs;
        }
    }

    packs = 0;
}

bool Transport::isFull(){
    return packs == maxPacks;
}

// funciones para control del thread
void Transport::pause(){
    isPause = true;
}

void Transport::resume(){
    isPause = false;
}

void Transport::finish(){
    isActive = false;
}

