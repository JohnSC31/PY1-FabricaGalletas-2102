#include "structs.h"

DoughMachine::DoughMachine(){

}


void DoughMachine::__init__(double _proccessTime, double _gramsPerTime, double _maxGrams, double _minGrams, int _id,
                            Planner * _planner, WareHouse * _wareHouse, GramsConveyorBelt * _doughConveyorBelt){
    proccessTime = _proccessTime;
    gramsPerTime = _gramsPerTime;
    maxGrams = _maxGrams;
    minGrams = _minGrams;
    proccessingGrams = 0;
    proccessedGrams = 0;
    id = _id;
    printConfig();

    planner = _planner;
    wareHouse = _wareHouse;
    doughConveyorBelt = _doughConveyorBelt;
}


void DoughMachine::run(){

    while(isActive){

        while(isPause){
            sleep(1);
        }
        printData();
        // funcionamiento de la maquina
        if(planner->calcDoughPlanGrams() / 2 > proccessedGrams){
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

void DoughMachine::makeRequest(){
    // se realiza una peticion de lo necesario
    wareHouse->addRequest(new Request(maxGrams - proccessingGrams, id));

    while(proccessingGrams < minGrams){
        sleep(1); // espera a que le llege la peticion realizada
    }
}

void DoughMachine::proccessGrams(){
    proccessingGrams -= gramsPerTime;
    sleep(proccessTime);
    proccessedGrams += gramsPerTime;
    doughConveyorBelt->mutex->lock();
    double gramsExcced = doughConveyorBelt->addGrams(gramsPerTime);
    doughConveyorBelt->mutex->unlock();
    if(gramsExcced > 0){
        proccessingGrams += gramsExcced; // regresan los gramos que no pasaron a la banda
        proccessedGrams -= gramsExcced;
        pause(); // la maquina se pausa ya que la banda esta llena
    }
}

void DoughMachine::updateConfig(double _proccessTime, double _gramsPerTime, double _maxGrams, double _minGrams){
    proccessTime = _proccessTime;
    gramsPerTime = _gramsPerTime;
    maxGrams = _maxGrams;
    minGrams = _minGrams;
    printConfig();
}

void DoughMachine::printData(){
    lblDoughMachine->setText( "Gramos actuales \n"+QString::number(proccessingGrams) + " \n\n Gramos procesados \n" + QString::number(proccessedGrams));
}

void DoughMachine::printConfig(){
    inpDoughMachineProcessTime->setText(QString::number(proccessTime));
    inpDoughMachineGramsTime->setText(QString::number(gramsPerTime));
    inpDoughMachineMax->setText(QString::number(maxGrams));
    inpDoughMachineMin->setText(QString::number(minGrams));
}


// funciones para control del thread
void DoughMachine::pause(){
    isPause = true;
    controlBtn->setText("Encender");
}

void DoughMachine::resume(){
    isPause = false;
    controlBtn->setText("Apagar");
}

void DoughMachine::finish(){
    isActive = false;
}



