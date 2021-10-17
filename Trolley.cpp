#include "structs.h"

Trolley::Trolley(){

}

void Trolley::__init__(double _gramCapacity, double _deliveryTime){
    gramCapacity = _gramCapacity;
    deliveryTime = _deliveryTime;
}


void Trolley::run(){

    while(isActive){

        while(isPause){
            sleep(1);
        }

        // lo que hace cuando esta activo
    }
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
