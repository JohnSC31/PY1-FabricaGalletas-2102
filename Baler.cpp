#include "structs.h"



Baler::Baler(){

}


void Baler::__init__(int _packsPerTime, Planner * _planner, CookieConveyorBelt * _cookieConveyorBelt){
    packsPerTime = _packsPerTime;
    planner =_planner;
    cookieConveyorBelt = _cookieConveyorBelt;

    // decidir el paquete a empacar primero
    printConfig();
}

void Baler::initTransports(){
    cmbTransports->addItem("Transportes", 0);
    for(int i = 0; i < planner->planProduction.size(); i++){
        transports.append(new Transport());
        transports.at(i)->__init__(planner, planner->planProduction.at(i)->pack->name, 20, 3);
        transports.at(i)->start();
        cmbTransports->addItem(planner->planProduction.at(i)->pack->name, i);
    }

    printTransportData();

}

void Baler::run(){

    initTransports();
    updateCurrentPack(); // cual paquete se hace primero

    while(isActive){

        while(isPause){
            sleep(1);
        }
        printData();
        printTransportData();
        // funcionamiento de la maquina
        if(currentOrder != NULL && currentOrder->packAmount > currentOrder->packedPackages){
            if(cookieConveyorBelt->cookies >= currentOrder->pack->cookies * packsPerTime){
                // hay galletas suficientes para enpacar la cantidad de paquetes por tiempo de la orden actual
                pack();
            }else{
                sleep(2);

            }

        }else{
            // actualizar la orden actual
            if(currentOrder != NULL){
                currentOrder->done = true;
            }

            updateCurrentPack();
            qDebug() << currentOrder->pack->name;
        }
        sleep(1);

    }
}


void Baler::pack(){
    // tomamos las galletas que necesitamos para hacer los paquetes por tiempo
    cookieConveyorBelt->mutex->lock();
    cookieConveyorBelt->cookies -= currentOrder->pack->cookies * packsPerTime;
    cookieConveyorBelt->mutex->unlock();
    sleep(currentOrder->pack->packTimePerPack * packsPerTime);
    currentOrder->packedPackages += packsPerTime;
    printData();
    placeOnTransport();
    printTransportData();
}

// colocamos los paquetes hechos en el transporte correspondiente si esta disponible
void Baler::placeOnTransport(){
    int packExcess = 0;
    for(int i = 0; i < transports.size(); i++){
         // encontramos el transporte
        if(transports.at(i)->packName == currentOrder->pack->name){
            // esperamos a que tenga espacio y este lleno
            while(!transports.at(i)->isAvailable || transports.at(i)->isFull()){
                sleep(1); // esperamos hasta que este disponible
                qDebug() << "Espero a que este disponible el transporte";
            }

            do{
                packExcess = transports.at(i)->loadPacks(packsPerTime);
                sleep(1);
            }while(packExcess > 0);

        }
    }
}

void Baler::updateCurrentPack(){
    int minProbability = 0;
    int maxProbability = 100;
    int planSize = planner->planProduction.size();
    for(int i = 0; i < planSize; i++){
        if(!planner->planProduction.at(i)->done){
            if((i + 1) == planSize){
                // esta en el ultimo
                planner->planProduction.at(i)->packProbability->__init__(minProbability, maxProbability);
            }else{
                int randNumber = randomGen.bounded(minProbability, maxProbability);
                planner->planProduction.at(i)->packProbability->__init__(minProbability, randNumber);
                minProbability += randNumber;
            }
        }
    }

    int lotery = randomGen.bounded(0, 100);
    // revisa quien se pego la loteria de se el siguiente en empacar
    for(int i = 0; i < planSize; i++){
        if(!planner->planProduction.at(i)->done){
            if(planner->planProduction.at(i)->packProbability->isInRange(lotery)){
                currentOrder = planner->planProduction.at(i);
            }
        }
    }
    qDebug() << "Se asigna paquete a empacar";
}


void Baler::printData(){
    QString str = "";
    QString orderPackName;
    int packedPackages;
    for(int i = 0; i < planner->planProduction.size(); i++){
        orderPackName = planner->planProduction.at(i)->pack->name;
        packedPackages = planner->planProduction.at(i)->packedPackages;
        str += orderPackName + " - " + QString::number(packedPackages) + "\n";
    }
    lblBaler->setText(str);
}

void Baler::updateConfig(int _packsPerTime){
    packsPerTime = _packsPerTime;
    printConfig();
}

void Baler::updateTransportConfig(int index, int _maxPacks, double _deliveryTime, QString status){
    transports.at(index)->maxPacks = _maxPacks;
    transports.at(index)->deliveryTime = _deliveryTime;
    if(status == "Encender"){
        transports.at(index)->pause();
    }else{
        transports.at(index)->resume();
    }
    printTransportConfig(index);
    printTransportData();
}

void Baler::printConfig(){
    inpBalerPerTime->setText(QString::number(packsPerTime));
}

void Baler::printTransportConfig(int index){
    inpTransportMax->setText(QString::number(transports.at(index)->maxPacks));
    inpTransportTime->setText(QString::number(transports.at(index)->deliveryTime));
    // control btn
    btnControlTransport->setText(transports.at(index)->isPause ? "Encender" : "Apagar");
}

void Baler::printTransportData(){
    QString status;
    QString str = "";
    for(int i = 0; i < transports.size(); i++){
        status = transports.at(i)->isPause ? "-":"+";
        str += status +" "+ transports.at(i)->packName +" "+ QString::number(transports.at(i)->packs) + "/" + QString::number(transports.at(i)->maxPacks) + "\n";
    }
    lblTransports->setText(str);
}
// funciones para control del thread
void Baler::pause(){
    isPause = true;
    btnControl->setText("Encender");
}

void Baler::resume(){
    isPause = false;
    btnControl->setText("Apagar");
}

void Baler::finish(){
    isActive = false;
}
