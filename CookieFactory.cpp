#include "structs.h"

CookieFactory::CookieFactory(){
    packList = new PackList();

    planner = new Planner();

    wareHouse = new WareHouse();

    doughConveyorBelt = new GramsConveyorBelt();
    chocolateConveyorBelt = new GramsConveyorBelt();

    chocolateMachine = new ChocolateMachine();

    doughMachine1 = new DoughMachine();
    doughMachine2 = new DoughMachine();

    jointerMachine = new JointerMachine();
    cookieConveyorBelt1 = new CookieConveyorBelt();
    cookieConveyorBelt2 = new CookieConveyorBelt();

    kiln = new Kiln();
}


void CookieFactory::initFactory(){
    //inicializacion de las estructuras
    doughConveyorBelt->__init__(100, &doughConveyorBeltMutex);
    chocolateConveyorBelt->__init__(100, &chocoConveyorBeltMutex);
    chocolateMachine->__init__(3, 20, 300, 50, 3, planner, wareHouse, chocolateConveyorBelt);
    doughMachine1->__init__(3, 20, 300, 50, 1, planner, wareHouse, doughConveyorBelt);
    doughMachine2->__init__(3, 20, 300, 50, 2, planner, wareHouse, doughConveyorBelt);
    wareHouse->__init__(chocolateMachine, doughMachine1, doughMachine2); // se pasan las maquinas de mezcla

    // inicializacion de la lista de paquetes
    packList->insertPack(new Pack(4, "Paquetito", 3));
    packList->insertPack(new Pack(10, "Paquete", 4));
    packList->insertPack(new Pack(16, "Tubo", 5));

    // inicializacion de ordenes
    planner->recipe->updateRecipe(20, 15);
    planner->addOrderPlan(new Order(100, packList->searchPack("Paquetito")));

    cookieConveyorBelt1->__init__(50, &cookieConveyorBelt1Mutex);
    // maquina ensambladora
    jointerMachine->__init__(4, 5, planner, chocolateConveyorBelt, doughConveyorBelt, cookieConveyorBelt1);

    // banda 2 para la empacadora
    cookieConveyorBelt2->__init__(50, &cookieConveyorBelt2Mutex);
    // horno
    kiln->__init__(50, cookieConveyorBelt1, cookieConveyorBelt2);
}

// pone a funcionar a todas las estructuras
void CookieFactory::run(){
    wareHouse->start();
    chocolateMachine->start();
    doughMachine1->start();
    doughMachine2->start();
    jointerMachine->start();
    kiln->start();
}
