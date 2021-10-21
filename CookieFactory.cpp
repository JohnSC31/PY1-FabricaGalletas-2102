#include "structs.h"

CookieFactory::CookieFactory(){
    packList = new PackList();

    planner = new Planner();

    wareHouse = new WareHouse();

    doughConveyorBelt = new GramsConveyorBelt(100, &doughConveyorBeltMutex);
    chocolateConveyorBelt = new GramsConveyorBelt(100, &chocoConveyorBeltMutex);

    chocolateMachine = new ChocolateMachine();

    doughMachine1 = new DoughMachine();
    doughMachine2 = new DoughMachine();
}


void CookieFactory::initFactory(){
    //inicializacion de las estructuras
    chocolateMachine->__init__(3, 20, 300, 50, 3, planner, wareHouse, chocolateConveyorBelt);
    doughMachine1->__init__(3, 20, 300, 50, 1, planner, wareHouse, doughConveyorBelt);
    doughMachine2->__init__(3, 20, 300, 50, 1, planner, wareHouse, doughConveyorBelt);
    wareHouse->__init__(chocolateMachine, doughMachine1, doughMachine2); // se pasan las maquinas de mezcla

    // inicializacion de la lista de paquetes
    packList->insertPack(new Pack(4, "Paquetito", 3));
    packList->insertPack(new Pack(10, "Paquete", 4));
    packList->insertPack(new Pack(16, "Tubo", 5));

    // inicializacion de ordenes
    planner->recipe->updateRecipe(30, 20);
    planner->addOrderPlan(new Order(100, packList->searchPack("Paquetito")));
}

// pone a funcionar a todas las estructuras
void CookieFactory::run(){
    wareHouse->start();
    chocolateMachine->start();
}
