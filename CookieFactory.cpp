#include "structs.h"

CookieFactory::CookieFactory(){
    packList = new PackList();

    planner = new Planner();

    wareHouse = new WareHouse();

    doughConveyorBelt = new GramsConveyorBelt(100);
    chocolateConveyorBelt = new GramsConveyorBelt(100);

    chocolateMachine = new ChocolateMachine();

    mixMachine1 = new DoughMachine(2, 10, 400, 100);
    mixMachine2 = new DoughMachine(2, 10, 400, 100);
}


void CookieFactory::initFactory(){
    //inicializacion de las estructuras
    chocolateMachine->__init__(3, 20, 500, 50, 3, planner, wareHouse, chocolateConveyorBelt);
    wareHouse->__init__(chocolateMachine); // se pasan las maquinas de mezcla

    // inicializacion de la lista de paquetes
    packList->insertPack(new Pack(4, "Paquetito", 3));
    packList->insertPack(new Pack(10, "Paquete", 4));
    packList->insertPack(new Pack(16, "Tubo", 5));

    // inicializacion de ordenes
    planner->addOrderPlan(new Order(500, packList->searchPack("Paquetito")));
}

// pone a funcionar a todas las estructuras
void CookieFactory::run(){
    wareHouse->start();
    chocolateMachine->start();
}
