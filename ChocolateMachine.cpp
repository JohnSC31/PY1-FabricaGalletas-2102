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
    printConfig();

    planner = _planner; // planificador de la fabrica
    wareHouse = _wareHouse;
    chocolateConveyorBelt = _chocolateConveyorBelt;

}

void ChocolateMachine::run(){

    while(isActive){

        while(isPause){
            sleep(1);
        }
        printData();
        // funcionamiento de la maquina
        if(planner->calcChocoPlanGrams() > proccessedGrams){
            if(proccessingGrams < minGrams){
                makeRequest();
            }
            if(proccessingGrams - gramsPerTime >= 0){
                proccessGrams();
            }else{
                makeRequest();
            }


         }else{
            sleep(2); // si ya completa el plan va a esperar 2 segundos para revisar y hay ordenes nuevas
        }

    }

}

void ChocolateMachine::makeRequest(){
    // verifica si hay que procesar mas gramos de chocolate segun el plan de produccion

    // se realiza una peticion de lo necesario
    wareHouse->addRequest(new Request(maxGrams - proccessingGrams, id));

    while(proccessingGrams < minGrams){
        sleep(1); // espera a que le llege la peticion realizada
    }
}

void ChocolateMachine::proccessGrams(){
    proccessingGrams -= gramsPerTime;
    sleep(proccessTime);
    proccessedGrams += gramsPerTime;
    chocolateConveyorBelt->mutex->lock();
    double gramsExcced = chocolateConveyorBelt->addGrams(gramsPerTime);
    chocolateConveyorBelt->mutex->unlock();
    if(gramsExcced > 0){
        proccessingGrams += gramsExcced; // regresan los gramos que no pasaron a la banda
        proccessedGrams -= gramsExcced;
        pause(); // la maquina se pausa ya que la banda esta llena
    }
}

void ChocolateMachine::updateConfig(double _proccessTime, double _gramsPerTime, double _maxGrams, double _minGrams){
    proccessTime = _proccessTime;
    gramsPerTime = _gramsPerTime;
    maxGrams = _maxGrams;
    minGrams = _minGrams;
    printConfig();
}

void ChocolateMachine::printData(){
    lblChocolateMachine->setText( "Gramos actuales \n"+QString::number(proccessingGrams) + " \n\n Gramos procesados \n" + QString::number(proccessedGrams));
}

void ChocolateMachine::printConfig(){
    inpChocolateMachineProcessTime->setText(QString::number(proccessTime));
    inpChocolateMachineGramsTime->setText(QString::number(gramsPerTime));
    inpChocolateMachineMax->setText(QString::number(maxGrams));
    inpChocolateMachineMin->setText(QString::number(minGrams));
}


// funciones para control del thread
void ChocolateMachine::pause(){
    isPause = true;
    controlBtn->setText("Encender");
}

void ChocolateMachine::resume(){
    isPause = false;
    controlBtn->setText("Apagar");
}

void ChocolateMachine::finish(){
    isActive = false;
}
