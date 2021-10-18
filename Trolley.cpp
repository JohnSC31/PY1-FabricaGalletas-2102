#include "structs.h"

Trolley::Trolley(){

}

void Trolley::__init__(double _gramCapacity, double _deliveryTime, ChocolateMachine * _chocolateMachine){
    gramCapacity = _gramCapacity;
    deliveryTime = _deliveryTime;
    grams = 0;
    chocolateMachine = _chocolateMachine;
}


void Trolley::run(){

    while(isActive){

        while(isPause){
            sleep(1);
        }

        if(destinyMachine != 0){
            makeDelivery();
        }


        qDebug() << "Carrito: Estoy esperando entrega";
        sleep(1);
        // lo que hace cuando esta activo
    }
}

// carga el carrito con los gramos de la peticion
// si esta excede la capacidad devuelve el exceso
double Trolley::loadGrams(double deliveryGrams){
    grams += deliveryGrams;
    qDebug() << "Carrito: Me cargan";
    double gramExcess = gramCapacity - grams;
    if(gramExcess < 0){
        // hay un exceso de gramos en el carrito
        grams += gramExcess;
        return -(gramExcess); // los gramos que se devuelven
    }

    return 0;
}


void Trolley::makeDelivery(){
    sleep(deliveryTime / 2);
    unloadGrams(); // descarga los gramos en la maquina indicada
    sleep(deliveryTime / 2);
    destinyMachine = 0; // ya no tiene que hacer nada
    qDebug() << "Carrito: Realice entrega";
}


void Trolley::unloadGrams(){
    if(destinyMachine == 1){// maquina de mezcla 1

    }else if(destinyMachine == 2){ // maquina de mezcla 2

    }else if(destinyMachine == 3){ // maquina de mezcla 3
        chocolateMachine->proccessingGrams += grams;
    }

    grams = 0; // se resetean los gramos

}

void Trolley::pause(){
    isPause = true;
}
void Trolley::resume(){
    isPause = false;
}
void Trolley::finish(){
    isActive = false;
}
