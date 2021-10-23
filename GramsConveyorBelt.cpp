#include "structs.h"

void GramsConveyorBelt::__init__(double _maxGrams, QMutex * _mutex){
    maxGrams = _maxGrams;
    grams = 0;
    mutex = _mutex;

    printConfig();
}

// agrega los gramos y retorna los gramos que no se pudieron agregar o 0 por su defecto
double GramsConveyorBelt::addGrams(double newGrams){

    grams += newGrams;
    double gramExcess = maxGrams - grams;
    if(gramExcess < 0){
        // hay un exceso de gramos en la banda
        grams += gramExcess;
        printData();
        return -(gramExcess); // los gramos que se devuelven
    }

    printData();
    return 0;
}

void GramsConveyorBelt::printData(){
    lblGramsConveyorBelt->setText(" \n Actual:" + QString::number(grams));
}

void GramsConveyorBelt::printConfig(){
    inpGramsConveyorBeltMax->setText(QString::number(maxGrams));
}

void GramsConveyorBelt::updateConfig(double _maxGrams){
    maxGrams = _maxGrams;
    printConfig();
}
