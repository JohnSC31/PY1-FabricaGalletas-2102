#include "structs.h"

Recipe::Recipe(double _doughAmount, double _chocolateAmount){
        doughAmount = _doughAmount;
        chocolateAmount = _chocolateAmount;
}


void Recipe::updateRecipe(double _doughAmount, double _chocolateAmount){
    doughAmount = _doughAmount;
    chocolateAmount = _chocolateAmount;
}
