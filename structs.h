#ifndef STRUCTS_H
#define STRUCTS_H

#include <QString>
#include <QQueue>
#include <QtCore>

// ESTE ARCHIVO CONTINE LA DEFICION DE TODAS LAS ESTRUCTURAS PARA LA FABRICA DE GALLETAS

// Prototipos
struct Cookie; // estructura de galleta
struct Recipe; // la receta

struct Pack; // estructura para paquete
struct PackNodo; // nodo paquete
struct PackList; // lista de paquetes

struct OrderNodo; // nodo orden
struct OrderList; // lista de ordenes
struct Planner; // planificador

struct Trolley; // carrito transportador
struct Request; // peticion
struct WareHouse; // almacen

struct GramsConveyorBelt; // banda transportadora de gramos
struct CookieConveyorBelt; // banda transportadora de galletas
struct CookieInspectionBelt;
struct Inspector;

struct ChocolateMachine; // maquina de chocolate
struct DoughMachine; // maquina de mezcla

struct JointerMachine; // maquina ensambladora

struct Kiln; // horno
struct Tray; // bandeja









struct Cookie{
    bool cooked;
    bool inspected;

    // constructor
    Cookie(){
        cooked = false;
        inspected = false;
    }

};

struct Recipe{
    double doughAmount; // la receta por galleta
    double chocolateAmount; // receta por galleta

    // constructor
    Recipe(double _doughAmount, double _chocolateAmount){
        doughAmount = _doughAmount;
        chocolateAmount = _chocolateAmount;
    }
};

// ---------------------------- ESTRUCTURAS PARA LOS PAQUETES -----------------------------------------
struct Pack{
    int cookies; // cantidad de galletas por paquete
    QString name;
    double packTimePerPack; // tiempo de empaque para este paquete
    int packCounter;
    int finishedPacks;

    // constructor
    Pack(int _cookies, QString _name, double _packTimePerPack){
        cookies = _cookies;
        name = _name;
        packTimePerPack = _packTimePerPack;
        finishedPacks = 0;
        packCounter = 0;
    }
};

// nodo de una lista circular doblemente enlazada
struct PackNodo{
    Pack * pack;
    PackNodo * next;
    PackNodo * previous;

    //constructor
    PackNodo(Pack * _pack){
        pack = _pack;
        next = previous = NULL;
    }
};

// Es una lista circular doblemente enlazada
struct PackList{
    PackNodo * firstNodo;

    PackList(){
        firstNodo = NULL;
    }

    void insertPack(Pack * pack);
    PackNodo * searchPack(QString);

};

// ---------------------------- ESTRUCTURAS  PARA PLANIFICACION -----------------------------------------
struct Order{
    int packAmount;
    QString packName;

    //construtor
    Order(int _packAmount, QString _packName){
        packAmount = _packAmount;
        packName = _packName;
    }
};

struct Planner{
    QList<Order> planProduction;

    Planner(){
    }

    void addOrderPlan(Order * order);
};

// ---------------------------- ESTRUCTURAS  PARA EL ALMACEN DE MATERIA PRIMA    -----------------------------------------
struct Trolley{
    double gramCapacity;
    QString location;
    QString destiny;
    bool status; // si esta encendido o apagado
    QMutex moving; // cuando esta realizando una entrega
    double deliveryTime; // tiempo para realizar una entrega en segundos

    Trolley(double _gramCapacity, double _deliveryTime){
        gramCapacity = _gramCapacity;
        deliveryTime = _deliveryTime;
        status = true;
        // falta agregar los atributos restantes si se necesitan
    }



};

struct Request{
    QString requestType;
    double gramAmount;
    double deliveryAmount;


    //constructor
    Request(QString _requestType, double _gramAmount){
        requestType = _requestType;
        gramAmount = _gramAmount;
        deliveryAmount = 0;
    }
};
//Solo se elimina una petición cuando amount – deliveryAmount = 0

struct WareHouse{
    Trolley * trolley;
    QQueue<Request> requests; // cola de peticiones
    QList<Request> doneRequests; // lista de peticiones terminadas

    //constructor
    WareHouse(double trolleyGramCapacity, double trolleyDeliveryTime){
        trolley = new Trolley(trolleyGramCapacity, trolleyDeliveryTime);
    }

    void proccessPetition();

};

// ---------------------------- ESTRUCTURAS LAS BANDAS TRANSPORTADORAS DE GRAMOS (CHOCOLATE, MEZCLA) -------------------
struct GramsConveyorBelt{
    double maxGrams;
    double grams;
    QMutex mutex;

    GramsConveyorBelt(double _maxGrams){
        maxGrams = _maxGrams;
        grams = 0;
    }
};

// ---------------------------- ESTRUCTURAS LAS BANDAS TRANSPORTADORAS DE GALLETAS -------------------
struct CookieConveyorBelt{
    QMutex mutex;
    QQueue<Cookie> queue;
    int maxCookies;

    CookieConveyorBelt(int _maxCookies){
        maxCookies = _maxCookies;
    }
};

// banda transportadora de galletas con inspectores
struct CookieInspectionBelt{
    QMutex mutex;
    QQueue<Cookie> queue;
    int maxCookies;
    Inspector * inspector1;
    Inspector * inspector2;

    CookieInspectionBelt(){
//        inspector1 = new Inspector();
    }
};

struct Inspector{
    double wasteProbabilty;
    int provedCookies;
    int wastedCookies;
    bool status;

    Inspector(){
        wasteProbabilty = 3; // generar un random para el porcentaje de desecho
        provedCookies = 0;
        wastedCookies = 0;
    }

};

// ---------------------------- ESTRUCTURAS PARA LAS MAQUINAS DE MEZCLA Y CHOCOLATE -------------------

struct ChocolateMachine{

    double proccessTime;
    double gramsPerTime;
    double maxGrams;
    double minGrams;
    bool status; // si esta encendida o apagada
    double proccessingGrams;
    double proccessedGrams;

    ChocolateMachine(double _proccessTime, double _gramsPerTime, double _maxGrams, double _minGrams){
        proccessTime = _proccessTime;
        gramsPerTime = _gramsPerTime;
        maxGrams = _maxGrams;
        minGrams = _minGrams;
        status = true;
        proccessingGrams = 0;
        proccessedGrams = 0;
    }

    void makePetition();
};

// maquina de mezcla
struct DoughMachine{

    double proccessTime;
    double gramsPerTime;
    double maxGrams;
    double minGrams;
    bool status; // si esta encendida o apagada
    double proccessingGrams;
    double proccessedGrams;

    DoughMachine(double _proccessTime, double _gramsPerTime, double _maxGrams, double _minGrams){
        proccessTime = _proccessTime;
        gramsPerTime = _gramsPerTime;
        maxGrams = _maxGrams;
        minGrams = _minGrams;
        status = true;
        proccessingGrams = 0;
        proccessedGrams = 0;
    }

    void makePetition();
};

// ---------------------------- ESTRUCTURAS PARA LA MAQUINA EMSAMBLADORA-------------------
struct JointerMachine{
    GramsConveyorBelt * chocolateConveyorBelt;
    GramsConveyorBelt * doughConveyorBelt;
    double proccessTime;
    double cookiesPerTime;
    int madeCookies;


    JointerMachine(){
        chocolateConveyorBelt = new GramsConveyorBelt(300);
        doughConveyorBelt = new GramsConveyorBelt(300);
    }

    // crea la galleta con la receta correspondiente y resta de la banda de gramos lo usado
    // coloca las galletas hechas en la banda de galletas del horno
    void createCookie();


};


// ---------------------------- ESTRUCTURAS PARA EL HORNO -------------------
struct Kiln{
    int cookieCapacity;
    QList<Tray> trays;
    bool status;
};

struct Tray{
    int cookieCapacity;
    int maxCookies;
    double bakingTime;
    bool status;

};



#endif // STRUCTS_H
