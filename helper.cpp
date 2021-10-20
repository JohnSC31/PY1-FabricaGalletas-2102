#include <QString>
#include "helper.h"




// validacion de los strings del usuario
bool validStr(QString str){
    if(str != "")
        return true;

    return false;
}

// recibe un string y verifica si se puede convertir a number
bool validNumber(QString strNumber){
    try {
        double number = strNumber.toDouble();
        return true; // puede ser converido a double
    }  catch (...) {
        return false;
    }
}
