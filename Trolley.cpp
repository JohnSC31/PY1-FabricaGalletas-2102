#include "structs.h"

Trolley::Trolley(){

}

void Trolley::__init__(double _gramCapacity, double _deliveryTime, ChocolateMachine * _chocolateMachine, DoughMachine * _doughMachine1,
                       DoughMachine * _doughMachine2){
    gramCapacity = _gramCapacity;
    deliveryTime = _deliveryTime;
    grams = 0;
    chocolateMachine = _chocolateMachine;
    doughMachine1 = _doughMachine1;
    doughMachine2 = _doughMachine2;
    printValues();
}


void Trolley::run(){

    while(isActive){

        while(isPause){
            sleep(1);
        }

        if(destinyMachine != 0){
            makeDelivery();
        }

        sleep(1);
        // lo que hace cuando esta activo
    }
}

// carga el carrito con los gramos de la peticion
// si esta excede la capacidad devuelve el exceso
double Trolley::loadGrams(double deliveryGrams){
    grams += deliveryGrams;
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
}


void Trolley::unloadGrams(){
    if(destinyMachine == 1){// maquina de mezcla 1
        doughMachine1->proccessingGrams += grams;
    }else if(destinyMachine == 2){ // maquina de mezcla 2
        doughMachine2->proccessingGrams += grams;
    }else if(destinyMachine == 3){ // maquina de mezcla 3
        chocolateMachine->proccessingGrams += grams;
    }

    grams = 0; // se resetean los gramos

}

void Trolley::updateValues(double _gramCapacity, double _deliveryTime){
    gramCapacity = _gramCapacity;
    deliveryTime = _deliveryTime;
    printValues();
}

void Trolley::printValues(){
    inpCapacityGrams->setText(QString::number(gramCapacity));
    inpDeliveryTime->setText(QString::number(deliveryTime));
}

void Trolley::pause(){
    controlBtn->setText("Encender");
    isPause = true;
}
void Trolley::resume(){
    controlBtn->setText("Apagar");
    isPause = false;
}
void Trolley::finish(){
    isActive = false;
}
