#include "structs.h"

WareHouse::WareHouse(){
    trolley = new Trolley();
}

void WareHouse::__init__(ChocolateMachine * chocolateMachine, DoughMachine * doughMachine1, DoughMachine * doughMachine2){
    currentRequest = NULL;
    trolley->__init__(300, 3, chocolateMachine, doughMachine1, doughMachine2);
}

void WareHouse::run(){
    trolley->start();

    while(isActive){

        while(isPause){
            sleep(1);
        }

        printData();

        if(currentRequest ==  NULL && !requests.isEmpty()){
           updateCurrentRequest();
           proccessRequest();
        }

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
    double load = currentRequest->gramAmount;
    while(!currentRequest->done){
        if(trolley->destinyMachine == 0){
            trolley->destinyMachine = currentRequest->machineId;
            load = trolley->loadGrams(load); // cargamos y regresa el exceso
            currentRequest->deliveredAmount = currentRequest->gramAmount - load;
            if(load == 0){ // cargamos todo
                currentRequest->done = true;
                doneRequests.append(currentRequest); // se agrega a las completadas
            }

        }
        if (!currentRequest->done)
            sleep(1); // espera un segundo para volver a intentar cargar el carrito
    }
    currentRequest = NULL;
}

// se agrega una peticion a la cola
void WareHouse::addRequest(Request * request){
    requests.enqueue(request);
}


// Se actualiza el ui
void WareHouse::printData(){

    QQueue<Request* > dataRequests = requests;

    QString str = "Peticiones pendiente \n";

    while(!dataRequests.isEmpty()){
        str += dataRequests.dequeue()->print();
    }

    str += "Peticiones procesadas \n";

    for(int i = doneRequests.size() - 1; i >= 0; i--){
         str += doneRequests.at(i)->print();
    }

    txtWarehouse->setText(str);
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
