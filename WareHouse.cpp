#include "structs.h"

WareHouse::WareHouse(){
    trolley = new Trolley();
}

void WareHouse::__init__(){
    currentRequest = NULL;
    trolley->__init__(300, 3);
}

void WareHouse::run(){
    trolley->run();

    while(isActive){

        while(isPause){
            sleep(1);
        }

        if((currentRequest ==  NULL || currentRequest->done) && !requests.isEmpty()){
           updateCurrentRequest();
        }

        if(currentRequest != NULL && !currentRequest->done){
            proccessRequest();
        }




        // lo que hace cuando esta activo
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



    }
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
