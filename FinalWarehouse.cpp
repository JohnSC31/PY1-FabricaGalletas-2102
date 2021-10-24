#include "structs.h"


FinalWarehouse::FinalWarehouse(){

}

void FinalWarehouse::__init__(Planner * _planner){
    planner = _planner;
}

void FinalWarehouse::run(){
    while(isActive){

        while(isPause){
            sleep(1);
        }
        printData();
        // funcionamiento de la maquina
        sleep(1);

    }
}


void FinalWarehouse::printData(){
    QString str = "";
    QString orderPackName;
    int finishedPackages;
    for(int i = 0; i < planner->planProduction.size(); i++){
        orderPackName = planner->planProduction.at(i)->pack->name;
        finishedPackages = planner->planProduction.at(i)->finishedPacks;
        str += orderPackName + " - " + QString::number(finishedPackages) + "\n";
    }
    lblSummary->setText(str);
}


