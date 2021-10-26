#include "structs.h"


Qos::Qos(){
    inspector1 = new Inspector();
    inspector2 = new Inspector();
}

void Qos::__init__(CookieConveyorBelt * _cookieConveyorBelt1, CookieConveyorBelt * _cookieConveyorBelt2, CookieConveyorBelt * _cookieConveyorBelt3){
    inspector1->__init__(2, 2, 10, _cookieConveyorBelt1, _cookieConveyorBelt2);
    inspector2->__init__(2, 2, 10, _cookieConveyorBelt2, _cookieConveyorBelt3);

    cmbInspectors->addItem("Inspectores", -1);
    cmbInspectors->addItem("Inspector 1", 1);
    cmbInspectors->addItem("Inspector 2", 2);

    printData(); // imprime los datos de los inspectores
}

void Qos::run(){
    // inician los inspectores a trabajar
    inspector1->start();
    inspector2->start();

    while(isActive){

        while(isPause){
            sleep(1);
        }

        printData();
        sleep(1); // imprimira la data cada 1 segundo

    }
}

// impresion de los datos de los inspectores
void Qos::printData(){
    QString str = "";
    QString status = inspector1->isPause ? "-": "+";
    str += status + "Insp1 " + QString::number(inspector1->provedCookies) + " / " + QString::number(inspector1->wastedCookies) + "\n";
    status = inspector2->isPause ? "-": "+";
    str += status + "Insp2 " + QString::number(inspector2->provedCookies) + " / " + QString::number(inspector2->wastedCookies) + "\n";

    lblQoS->setText(str);
}

void Qos::printInspectorConfig(int inspector){
    if(inspector == 1){
        inpInspectorPerTime->setText(QString::number(inspector1->cookiesPerTime));
        inpInspectorTime->setText(QString::number(inspector1->proccessTime));
        inpInspectorProb->setText(QString::number(inspector1->wasteProbabilty));
        // control btn
        btnControlInspector->setText(inspector1->isPause ? "Encender" : "Apagar");
    }else{
        inpInspectorPerTime->setText(QString::number(inspector2->cookiesPerTime));
        inpInspectorTime->setText(QString::number(inspector2->proccessTime));
        inpInspectorProb->setText(QString::number(inspector2->wasteProbabilty));
        // control btn
        btnControlInspector->setText(inspector2->isPause ? "Encender" : "Apagar");
    }
}

void Qos::updateInspectorConfig(int inspector, int _cookiesPerTime, double _processTime, double _wasteProbability, QString status){
    if(inspector == 1){
        inspector1->cookiesPerTime = _cookiesPerTime;
        inspector1->proccessTime = _processTime;
        inspector1->wasteProbabilty = _wasteProbability;
        if(status == "Encender"){
            inspector1->pause();
        }else{
            inspector1->resume();
        }
    }else{
        inspector2->cookiesPerTime = _cookiesPerTime;
        inspector2->proccessTime = _processTime;
        inspector2->wasteProbabilty = _wasteProbability;
        if(status == "Encender"){
            inspector2->pause();
        }else{
            inspector2->resume();
        }
    }

    printData();
    printInspectorConfig(inspector);
}

// Funciones para el thread
void Qos::pause(){
    isPause = true;
}

void Qos::resume(){
    isPause = false;
}

void Qos::finish(){
    isActive = false;
}
