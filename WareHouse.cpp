#include "structs.h"

WareHouse::WareHouse(){
    trolley = new Trolley();
}

void WareHouse::__init__(ChocolateMachine * chocolateMachine){
    currentRequest = NULL;
    trolley->__init__(300, 3, chocolateMachine);
}

void WareHouse::run(){
    trolley->start();

    while(isActive){

        while(isPause){
            sleep(1);
        }

        if(currentRequest ==  NULL && !requests.isEmpty()){
           updateCurrentRequest();
           qDebug() << "Almacen: Actualizo peticion";
        }

        if(currentRequest != NULL){
            proccessRequest();
            qDebug() << "Almacen: Procese la peticion";
        }

        qDebug() << "Almacen: Espero una peticion";

        sleep(1);
    }
    // despues de estar activo
}

// desencola de la cola de peticiones y la coloca como peticion actual
void WareHouse::updateCurrentRequest(){
    currentRequest = requests.dequeue();
}

// manipula el carrito hasta que complete la currentrequest
void WareHouse::proccessRequest(){
    while(!currentRequest->done){
        if(trolley->destinyMachine == 0){
            trolley->destinyMachine = currentRequest->machineId;
            currentRequest->gramAmount = trolley->loadGrams(currentRequest->gramAmount);
            if(currentRequest == 0){
                currentRequest->done = true;
            }
        }

        qDebug() << "Almacen: Estoy procesando peticion";
        if (!currentRequest->done)
            sleep(1); // espera un segundo para volver a intentar cargar el carrito
    }
    currentRequest = NULL;
}

// se agrega una peticion a la cola
void WareHouse::addRequest(Request * request){
    requests.enqueue(request);
}

void WareHouse::pause(){
    isPause = true;
}

void WareHouse::resume(){
    isPause = false;
}

void WareHouse::finish(){
    isActive = false;
}
