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
    cookieConveyorBelt3 = new CookieConveyorBelt();
    cookieConveyorBelt4 = new CookieConveyorBelt();

    kiln = new Kiln();

    qosDepartment = new Qos();

    baler = new Baler();

    finalWarehouse = new FinalWarehouse();
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
    packList->insertPack(new Pack(2, "Paquetito", 3));
    packList->insertPack(new Pack(4, "Paquete", 4));
    packList->insertPack(new Pack(16, "Tubo", 5));

    // inicializacion de ordenes
    planner->recipe->updateRecipe(10, 5);
    planner->addOrderPlan(new Order(10, packList->searchPack("Paquetito")));
    planner->addOrderPlan(new Order(10, packList->searchPack("Paquete")));
    planner->addOrderPlan(new Order(10, packList->searchPack("Tubo")));

    cookieConveyorBelt1->__init__(50, &cookieConveyorBelt1Mutex);
    // maquina ensambladora
    jointerMachine->__init__(4, 5, planner, chocolateConveyorBelt, doughConveyorBelt, cookieConveyorBelt1);

    // banda 2 para la horno
    cookieConveyorBelt2->__init__(50, &cookieConveyorBelt2Mutex);
    // horno
    kiln->__init__(50, cookieConveyorBelt1, cookieConveyorBelt2);
    // banda para la inspeccion
    cookieConveyorBelt3->__init__(100, &cookieConveyorBelt3Mutex);
    cookieConveyorBelt4->__init__(50, &cookieConveyorBelt4Mutex);
    // inspeccion
    qosDepartment->__init__(cookieConveyorBelt2, cookieConveyorBelt3, cookieConveyorBelt4);
    // empacadora
    baler->__init__(5, planner, cookieConveyorBelt4);

    // almacen final
    finalWarehouse->__init__(planner);
}

// pone a funcionar a todas las estructuras
void CookieFactory::run(){
    wareHouse->start();
    chocolateMachine->start();
    doughMachine1->start();
    doughMachine2->start();
    jointerMachine->start();
    kiln->start();
    qosDepartment->start();
    baler->start();
    finalWarehouse->start();
}

void CookieFactory::pause(){
    wareHouse->pause();
    chocolateMachine->pause();
    doughMachine1->pause();
    doughMachine2->pause();
    jointerMachine->pause();
    kiln->pause();
    qosDepartment->pause();
    baler->pause();
}

void CookieFactory::resume(){
    wareHouse->resume();
    chocolateMachine->resume();
    doughMachine1->resume();
    doughMachine2->resume();
    jointerMachine->resume();
    kiln->resume();
    qosDepartment->resume();
    baler->resume();
}
