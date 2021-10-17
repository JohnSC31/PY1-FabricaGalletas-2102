#include "structs.h"


Planner::Planner(){
   recipe = new Recipe(50, 30); // receta inicial
}

void Planner::addOrderPlan(Order * order){
    planProduction.append(order);
}


// Realizan los calculos de los gramos necesarios para completar el plan
double Planner::calcDoughPlanGrams(){
    double totalGrams = 0;

    for (int i = 0; i < planProduction.size(); ++i) {
        totalGrams += planProduction.at(i)->pack->cookies * recipe->doughAmount;
    }

    return totalGrams;
}

double Planner::calsChocoPlanGrams(){
    double totalGrams = 0;

    for (int i = 0; i < planProduction.size(); ++i) {
        totalGrams += planProduction.at(i)->pack->cookies * recipe->chocolateAmount;
    }

    return totalGrams;
}
