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
}

// busqueda de un paquete por nombre
PackNodo * PackList::searchPack(QString name){
    if (firstNodo != NULL){
        PackNodo * tmp = firstNodo;
        do{
            if (tmp->pack->name == name)
                return tmp;
            tmp = tmp->next;
        }while(tmp!=firstNodo);

    }
    return NULL;
}
