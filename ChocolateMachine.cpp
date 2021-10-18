#include "structs.h"


ChocolateMachine::ChocolateMachine(){
}

void ChocolateMachine::__init__(double _proccessTime, double _gramsPerTime, double _maxGrams, double _minGrams, int _id, Planner * _planner,
                                WareHouse * _wareHouse, GramsConveyorBelt * _chocolateConveyorBelt){
    proccessTime = _proccessTime;
    gramsPerTime = _gramsPerTime;
    maxGrams = _maxGrams;
    minGrams = _minGrams;
    proccessingGrams = 0;
    proccessedGrams = 0;
    id = _id;

    planner = _planner; // planificador de la fabrica
    wareHouse = _wareHouse;
    chocolateConveyorBelt = _chocolateConveyorBelt;

}

void ChocolateMachine::run(){

    while(isActive){

        while(isPause){
            sleep(1);
        }

        // funcionamiento de la maquina
        if(planner->calsChocoPlanGrams() > proccessedGrams){
            if(proccessingGrams < minGrams){
                makeRequest();
            }
            qDebug() << "Maq Choco: Voy a procesar";
            proccessGrams();
         }



        sleep(1);

    }

}

void ChocolateMachine::makeRequest(){
    // verifica si hay que procesar mas gramos de chocolate segun el plan de produccion

    // se realiza una peticion de lo necesario
    wareHouse->addRequest(new Request(maxGrams - proccessingGrams, id));

    while(proccessingGrams < minGrams){
        sleep(1); // espera a que le llege la peticion realizada
        qDebug() << "Maq Choco: Espero refuerzos";
    }
}

void ChocolateMachine::proccessGrams(){
    if(proccessingGrams - gramsPerTime >= 0){
        proccessingGrams -= gramsPerTime;
        sleep(proccessTime);
        proccessedGrams += gramsPerTime;
        double gramsExcced = chocolateConveyorBelt->addGrams(gramsPerTime);
        if(gramsExcced > 0){
            proccessingGrams += gramsExcced; // regresan los gramos que no pasaron a la banda
            proccessedGrams -= gramsExcced;
            pause(); // la maquina se pausa ya que la banda esta llena
            qDebug() << "Maq Choco: Se lleno la banda de chocolate";
        }
    }else{
        makeRequest();
    }
}

// funciones para control del thread
void ChocolateMachine::pause(){
    isPause = true;
}

void ChocolateMachine::resume(){
    isPause = false;
}

void ChocolateMachine::finish(){
    isActive = false;
}
