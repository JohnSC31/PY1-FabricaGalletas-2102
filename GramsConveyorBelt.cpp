#include "structs.h"


// agrega los gramos y retorna los gramos que no se pudieron agregar o 0 por su defecto
double GramsConveyorBelt::addGrams(double newGrams){

    grams += newGrams;
    double gramExcess = maxGrams - grams;
    if(gramExcess < 0){
        // hay un exceso de gramos en la banda
        grams += gramExcess;
        return -(gramExcess); // los gramos que se devuelven
    }

    return 0;
}
