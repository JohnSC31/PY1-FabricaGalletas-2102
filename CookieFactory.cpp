#include "structs.h"

CookieFactory::CookieFactory(){
    packList = new PackList();

    wareHouse = new WareHouse();

    planner = new Planner();

    mixMachine1 = new DoughMachine(2, 10, 400, 100);
    mixMachine2 = new DoughMachine(2, 10, 400, 100);
}


void CookieFactory::initFactory(){
    //inicializacion de las estructuras
    wareHouse->__init__();

    // inicializacion de la lista de paquetes
    packList->insertPack(new Pack(4, "Paquetito", 3));
    packList->insertPack(new Pack(10, "Paquete", 4));
    packList->insertPack(new Pack(16, "Tubo", 5));
}
