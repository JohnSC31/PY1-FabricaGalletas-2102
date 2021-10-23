#include "structs.h"


JointerMachine::JointerMachine(){

}

void JointerMachine::__init__(double _proccessTime, double _cookiesPerTime, Planner * _planner, GramsConveyorBelt * _chocolateConveyorBelt,
                              GramsConveyorBelt * _doughConveyorBelt, CookieConveyorBelt * _cookieConveyorBelt){
    proccessTime = _proccessTime;
    cookiesPerTime = _cookiesPerTime;
    madeCookies = 0;
    planner = _planner;
    chocolateConveyorBelt = _chocolateConveyorBelt;
    doughConveyorBelt = _doughConveyorBelt;
    cookieConveyorBelt = _cookieConveyorBelt;
    printConfig();

}

void JointerMachine::run(){

    while(isActive){

        while(isPause){
            sleep(1);
        }
        printData();
        // funcionamiento de la maquina
        if(canMakeCookies()){
            makeCookies();
         }else{
            sleep(2); // espera 2 segundos para volver a preguntar si puede hacer galletas
        }

    }
}


bool JointerMachine::canMakeCookies(){
    if(doughConveyorBelt->grams - (planner->recipe->doughAmount * cookiesPerTime) >=0 &&
            chocolateConveyorBelt->grams - (planner->recipe->chocolateAmount * cookiesPerTime) >= 0){
        return true; // se pueden hacer las galletas por proceso
    }
    return false; // no hay materiales par las galletas
}

void JointerMachine::makeCookies(){
    if(cookieConveyorBelt ->canAddCookies(cookiesPerTime)){ // si esta llena la banda de galletas
        getGrams();
        sleep(proccessTime);
        madeCookies += cookiesPerTime;
        cookieConveyorBelt->mutex->lock();
        cookieConveyorBelt->addCookies(cookiesPerTime);
        cookieConveyorBelt->mutex->unlock();
    }else{
        pause(); // se pausa porque la banda esta llena
    }
}

void JointerMachine::getGrams(){
    doughConveyorBelt->mutex->lock();
    doughConveyorBelt->grams -= planner->recipe->doughAmount * cookiesPerTime;
    doughConveyorBelt->printData();
    doughConveyorBelt->mutex->unlock();
    chocolateConveyorBelt->mutex->lock();
    chocolateConveyorBelt->grams -= planner->recipe->chocolateAmount * cookiesPerTime;
    chocolateConveyorBelt->printData();
    chocolateConveyorBelt->mutex->unlock();
}



// imprime los datos en el label
void JointerMachine::printData(){
    lblJointerMachine->setText("Galletas " + QString::number(madeCookies));
}


void JointerMachine::printConfig(){
    inpJointerMachinePerTime->setText(QString::number(cookiesPerTime));
    inpJointerMachineProccessTime->setText(QString::number(proccessTime));
}


// funciones para control del thread
void JointerMachine::pause(){
    isPause = true;
    controlBtn->setText("Encender");
}

void JointerMachine::resume(){
    isPause = false;
    controlBtn->setText("Apagar");
}

void JointerMachine::finish(){
    isActive = false;
}
