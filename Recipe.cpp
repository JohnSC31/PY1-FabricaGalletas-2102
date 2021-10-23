#include "structs.h"

Recipe::Recipe(){
}


void Recipe::updateRecipe(double _doughAmount, double _chocolateAmount){
    doughAmount = _doughAmount;
    chocolateAmount = _chocolateAmount;
    // se imprime en la interfaz
    inputDough->setText(QString::number(doughAmount));
    inputChocolate->setText(QString::number(chocolateAmount));


}
