#include "structs.h"



Kiln::Kiln(){
    // creacion de las bandejas
    for(int i = 0; i < 6; i++){
        trays.append(new Tray()); // genera las 6 bandejas
    }
}

void Kiln::__init__(int _cookieCapacity, CookieConveyorBelt * _cookieConveyorBelt1, CookieConveyorBelt * _cookieConveyorBelt2){
    cookieCapacity = _cookieCapacity;
    cookieConveyorBelt1 = _cookieConveyorBelt1;
    //inicializacion de las bandejas
    cmbTrays->addItem("Bandejas", -1);
    for(int i = 0; i < 6; i++){
        trays.at(i)->__init__(10, 5, _cookieConveyorBelt2);
        cmbTrays->addItem("Bandeja " + QString::number(i + 1), 22);
    }

    printConfig();
    printData();


}

void Kiln::run(){
    activeTrays(); // start a todas las bandejas

    while(isActive){

        while(isPause){
            sleep(1);
        }
        printData();
        // funcionamiento de la maquina
        if(cookieConveyorBelt1->cookies >= cookieCapacity){
            fillTrays();
         }else{
            sleep(2); // espera para volverlo a intentar
        }

    }

}

//Toma las galletas de la banda y las coloca en las bandejas
void Kiln::fillTrays(){
    //tomar las galletas de la banda
    cookieConveyorBelt1->mutex->lock();
    cookieConveyorBelt1->cookies -= cookieCapacity; // restan las galletas
    int cookiesExcess = cookieCapacity;

    for(int i = 0; i < trays.size(); i++){
        // si esta activa, no esta ocupada y no esta full
        if(trays.at(i)->isActive && !trays.at(i)->isBaking && !trays.at(i)->isFull()){
            cookiesExcess = trays.at(i)->addCookies(cookiesExcess);
        }

        if(cookiesExcess == 0){
            break; // ya no hay galletas para agregar
        }
    }

    if(cookiesExcess > 0){ // no se pudieron agregar todas
        cookieConveyorBelt1->cookies += cookiesExcess;
    }
    cookieConveyorBelt1->mutex->unlock();
    cookieConveyorBelt1->printData(); // actualiza lo que hayamos tomado
    printData();
}

// Activa y pone a correr cada una de las bandejas
void Kiln::activeTrays(){
    for(int i = 0; i < trays.size(); i++){
        trays.at(i)->start();
    }
}


void Kiln::printData(){
    QString trayStatus;
    QString str = "";
    for(int i = 0; i < trays.size(); i++){
        trayStatus = trays.at(i)->isActive ? "+":"-";
        str += trayStatus + " B" + QString::number(i + 1) +" "+ QString::number(trays.at(i)->cookies) + "/" + QString::number(trays.at(i)->maxCookies) + "\n";
    }
    lblKilnTrays->setText(str);
}

void Kiln::updateConfig(int _cookieCapacity){
    cookieCapacity = _cookieCapacity;
    printConfig();
}

void Kiln::printConfig(){
    inpCapacity->setText(QString::number(cookieCapacity));
}

// Configuraciones de las bandejas
void Kiln::printTrayConfig(int index){
    inpKilnTrayCookies->setText(QString::number(trays.at(index)->maxCookies));
    inpKilnBakingTime->setText(QString::number(trays.at(index)->bakingTime));
    //controlTrayBtn->setText(); // configurar el boton para encender y apagar
}

void Kiln::updateTrayConfig(int indexTray, int _maxCookies, int _bakingTime){
    trays.at(indexTray)->maxCookies = _maxCookies;
    trays.at(indexTray)->bakingTime = _bakingTime;
    printTrayConfig(indexTray);
    printData();
}

//void Kiln::controlTray(){

//}
// funciones para control del thread
void Kiln::pause(){
    isPause = true;
    controlBtn->setText("Encender");
}

void Kiln::resume(){
    isPause = false;
    controlBtn->setText("Apagar");
}

void Kiln::finish(){
    isActive = false;
}

