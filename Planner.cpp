#include "structs.h"


Planner::Planner(){
   recipe = new Recipe();
}

void Planner::addOrderPlan(Order * order){
    planProduction.append(order);
    printData();
}


// Realizan los calculos de los gramos necesarios para completar el plan
double Planner::calcDoughPlanGrams(){
    double totalGrams = 0;

    for (int i = 0; i < planProduction.size(); ++i) {
        int orderCookies = planProduction.at(i)->pack->cookies * planProduction.at(i)->packAmount;
        totalGrams += orderCookies * recipe->doughAmount;
    }

    return totalGrams;
}

double Planner::calcChocoPlanGrams(){
    double totalGrams = 0;

    for (int i = 0; i < planProduction.size(); ++i) {
        int orderCookies = planProduction.at(i)->pack->cookies * planProduction.at(i)->packAmount;
        totalGrams += orderCookies * recipe->chocolateAmount;
    }

    return totalGrams;
}

void Planner::printData(){
     QString str = "";
    for(int i = 0; i < planProduction.size(); i++){
         str += planProduction.at(i)->print() + "\n";
    }

    lblProduction->setText(str);
}
