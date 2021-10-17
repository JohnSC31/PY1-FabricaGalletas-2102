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

struct CookieFactory; // Estructura princial de la fabrica

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

public:
    Recipe(double _doughAmount, double _chocolateAmount);
    void updateRecipe(double _doughAmount, double _chocolateAmount);

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
public:
    int packAmount;
    Pack * pack;

public:
    Order(int _packAmount, Pack * _pack){
        packAmount = _packAmount;
        pack = _pack;
    }
};

struct Planner{
    public:
        QList<Order *> planProduction;
        Recipe * recipe;

    public:
        Planner();
        void addOrderPlan(Order * order);
        double calcDoughPlanGrams();
        double calsChocoPlanGrams();
};

// ---------------------------- ESTRUCTURAS  PARA EL ALMACEN DE MATERIA PRIMA    -----------------------------------------
struct Trolley : public QThread{
public:
    double gramCapacity;
    double grams; // son los gramos actuales no se puede pasar de gram capacity
    double deliveryTime; // tiempo para realizar una entrega en segundos
    // punteros a todas las maquinas
    // int destinato (se actualiza solo cuando no tiene a donde ir)

    bool isActive = true;
    bool isPause = false;

public:
    Trolley();
    void __init__(double _gramCapacity, double _deliveryTime);
    void run();



    void pause();
    void resume();
    void finish();


};

struct Request{
public:
    QString requestType;
    double gramAmount;
    double deliveredAmount;
    bool done;

public:
    Request(QString _requestType, double _gramAmount){
        requestType = _requestType;
        gramAmount = _gramAmount;
        deliveredAmount = 0;
        done = false;

    }


};

//Solo se elimina una petición cuando amount – deliveryAmount = 0
struct WareHouse : public QThread{
public:
    QQueue<Request *> requests; // cola de peticiones
    QList<Request *> doneRequests; // lista de peticiones terminadas
    Request * currentRequest;
    Trolley * trolley;

    // thread
    bool isActive = true;
    bool isPause = false;

public:
    WareHouse();
    void __init__();
    void run();

    void updateCurrentRequest();
    void proccessRequest();
    void addRequest(Request *);

    void pause();
    void resume();
    void finish();
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
public:
    double proccessTime;
    double gramsPerTime;
    double maxGrams;
    double minGrams;
    double proccessingGrams;
    double proccessedGrams;

    //thread
    bool isActive = true;
    bool isPause = false;

public:
    ChocolateMachine(double _proccessTime, double _gramsPerTime, double _maxGrams, double _minGrams);

    void makePetition();
};

// maquina de mezcla
struct DoughMachine{
    public:
        double proccessTime;
        double gramsPerTime;
        double maxGrams;
        double minGrams;
        bool status; // si esta encendida o apagada
        double proccessingGrams;
        double proccessedGrams;

    public:
        DoughMachine(double, double, double, double);
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


// ---------------------------- ESTRUCTURA DE FABRICA -------------------

struct CookieFactory{
    public: // atributos
        Planner * planner; // planificador
        PackList *  packList;
        WareHouse * wareHouse; // almacen
        DoughMachine * mixMachine1; // maquina mezcla 1
        DoughMachine * mixMachine2; // maquina mezcla 2
        ChocolateMachine * chocolateMachine; // maquina de chocolate




    public: // metodos
        CookieFactory();
        void initFactory(); // inicializa los valores predeterminados

};

#endif // STRUCTS_H
