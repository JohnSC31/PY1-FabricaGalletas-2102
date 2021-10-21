#include "structs.h"


// realiza una inserccion al inicio
void PackList::insertPack(Pack * pack){
    if(firstNodo == NULL){
        firstNodo = new PackNodo(pack);
        firstNodo->next = firstNodo->previous = firstNodo; // los 2 apuntan a primer nodo
    }else{
        PackNodo * newNodo = new PackNodo(pack);
        newNodo->next = firstNodo;
        newNodo->previous = firstNodo->previous;
        firstNodo->previous->next = newNodo;
        firstNodo->previous = newNodo;
    }

    cmbPacks->addItem(pack->name, 0);
    printData();
}

// busqueda de un paquete por nombre
Pack * PackList::searchPack(QString name){
    if (firstNodo != NULL){
        PackNodo * tmp = firstNodo;
        do{
            if (tmp->pack->name == name)
                return tmp->pack;
            tmp = tmp->next;
        }while(tmp!=firstNodo);

    }
    return NULL;
}

void PackList::printData(){
    QString str = "";
    if (firstNodo != NULL){
        PackNodo * tmp = firstNodo;
        do{
            str += tmp->pack->print() + "\n";
            tmp = tmp->next;
        }while(tmp!=firstNodo);

    }
    lblPacks->setText(str);
}
