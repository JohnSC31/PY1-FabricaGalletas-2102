#include "structs.h"

DoughMachine::DoughMachine(double _proccessTime, double _gramsPerTime, double _maxGrams, double _minGrams){
    proccessTime = _proccessTime;
    gramsPerTime = _gramsPerTime;
    maxGrams = _maxGrams;
    minGrams = _minGrams;
    status = true;
    proccessingGrams = 0;
    proccessedGrams = 0;
}

void DoughMachine::makePetition(){

}
