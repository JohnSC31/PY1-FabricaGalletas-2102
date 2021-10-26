#ifndef STRUCTS_H
#define STRUCTS_H

#include <QString>
#include <QQueue>
#include <QtCore>
#include <QDebug>

// Ui includes
#include <QLabel>
#include <QTextBrowser>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

// ESTE ARCHIVO CONTINE LA DEFICION DE TODAS LAS ESTRUCTURAS PARA LA FABRICA DE GALLETAS

// Prototipos
struct Recipe; // la receta

struct Pack; // estructura para paquete
struct PackNodo; // nodo paquete
struct PackList; // lista de paquetes

struct RangeProbability;
struct Order;
struct Planner; // planificador

struct Trolley; // carrito transportador
struct Request; // peticion
struct WareHouse; // almacen

struct GramsConveyorBelt; // banda transportadora de gramos
struct CookieConveyorBelt; // banda transportadora de galletas


struct ChocolateMachine; // maquina de chocolate
struct DoughMachine; // maquina de mezcla

struct JointerMachine; // maquina ensambladora

struct Kiln; // horno
struct Tray; // bandeja

struct Qos; // departamento de calidad de servicio
struct Inspector;

struct Baler; // empacadora
struct Transport;

struct FinalWarehouse;

struct CookieFactory; // Estructura princial de la fabrica

struct Recipe{
    double doughAmount; // la receta por galleta
    double chocolateAmount; // receta por galleta

    // ui
    QLineEdit * inputDough;
    QLineEdit * inputChocolate;

public:
    Recipe();
    void updateRecipe(double _doughAmount, double _chocolateAmount);

};

// ---------------------------- ESTRUCTURAS PARA LOS PAQUETES -----------------------------------------
struct Pack{

public:
    int cookies; // cantidad de galletas por paquete
    QString name;
    double packTimePerPack; // tiempo de empaque para este paquete

public:
    Pack(int _cookies, QString _name, double _packTimePerPack){
        cookies = _cookies;
        name = _name;
        packTimePerPack = _packTimePerPack;
    }

    QString print(){
        return name + " - " + QString::number(cookies);
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
    QLabel * lblPacks;
    QComboBox * cmbPacks;

    PackList(){
        firstNodo = NULL;
        lblPacks = NULL;
    }

    void insertPack(Pack * pack);
    Pack * searchPack(QString);
    void printData();

};

// ---------------------------- ESTRUCTURAS  PARA PLANIFICACION -----------------------------------------
struct RangeProbability{
public:
    int min; // abierto
    int max; // cerrado

    RangeProbability(){
    }

    void __init__(int _min, int _max){
        min = _min;
        max = _max;
    }

    bool isInRange(int number){
        // pega la loteria y esta en el rango
        return number > min && number <= max;
    }


};

struct Order{
public:
    int packAmount;
    Pack * pack;
    int packedPackages; // paquetes enpacados de esta orden
    int finishedPacks; // paquetes listos en el almacen final
    RangeProbability * packProbability;
    bool done = false;

public:
    Order(int _packAmount, Pack * _pack){
        packAmount = _packAmount;
        pack = _pack;
        packedPackages = 0;
        finishedPacks = 0;
        packProbability = new RangeProbability;
    }

    QString print(){
        return QString::number(packAmount) + " - " + pack->name;
    }
};

struct Planner{
    public:
        QList<Order *> planProduction;
        Recipe * recipe;
        QLabel * lblProduction;
        QLineEdit * inputDough;
        QLineEdit * inputChocolate;

    public:
        Planner();
        void addOrderPlan(Order * order);
        double calcDoughPlanGrams();
        double calcChocoPlanGrams();
        void printData();
};

// ---------------------------- ESTRUCTURAS  PARA EL ALMACEN DE MATERIA PRIMA    -----------------------------------------
struct Trolley : public QThread{
public:
    double gramCapacity;
    double grams; // son los gramos actuales no se puede pasar de gram capacity
    double deliveryTime; // tiempo para realizar una entrega en segundos
    // punteros a todas las maquinas
    // int destinato (se actualiza solo cuando no tiene a donde ir)
    int destinyMachine = 0;
    ChocolateMachine * chocolateMachine;
    DoughMachine * doughMachine1;
    DoughMachine * doughMachine2;

    bool isActive = true;
    bool isPause = false;

    QLineEdit * inpCapacityGrams;
    QLineEdit * inpDeliveryTime;
    QPushButton * controlBtn;

public:
    Trolley();
    void __init__(double _gramCapacity, double _deliveryTime, ChocolateMachine * chocolateMachine,  DoughMachine * doughMachine1,
    DoughMachine * doughMachine2);
    void run();

    void makeDelivery();
    void unloadGrams();
    double loadGrams(double);
    void updateValues(double _gramCapacity, double _deliveryTime);
    void printValues();


    void pause();
    void resume();
    void finish();


};

struct Request{
public:
    double gramAmount;
    double deliveredAmount;
    int machineId;
    bool done;

public:
    Request(double _gramAmount, int _machineId){
        gramAmount = _gramAmount;
        deliveredAmount = 0;
        machineId = _machineId;
        done = false;

    }

    QString print(){
        QString typeGrams = machineId != 3 ? "Mezcla" : "Chocolate";
        QString str = typeGrams + "->" + QString::number(gramAmount) + " - " + QString::number(deliveredAmount) + "\n";

        return str;
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

    //ui
    QLabel * txtWarehouse;

public:
    WareHouse();
    void __init__(ChocolateMachine *, DoughMachine *, DoughMachine *);
    void run();

    void updateCurrentRequest();
    void proccessRequest();
    void addRequest(Request *);
    void printData();

    void pause();
    void resume();
    void finish();
};

// ---------------------------- ESTRUCTURAS LAS BANDAS TRANSPORTADORAS DE GRAMOS (CHOCOLATE, MEZCLA) -------------------
struct GramsConveyorBelt{
public:
    double maxGrams;
    double grams;
    QMutex * mutex;

    //ui
    QLabel * lblGramsConveyorBelt;
    QLineEdit * inpGramsConveyorBeltMax;

public:
    GramsConveyorBelt(){
    }

public:
    void __init__(double _maxGrams, QMutex * _mutex);
    double addGrams(double newGrams);
    void printData();
    void printConfig();
    void updateConfig(double);
};

// ---------------------------- ESTRUCTURAS LAS BANDAS TRANSPORTADORAS DE GALLETAS -------------------
struct CookieConveyorBelt{
public:
    QMutex * mutex;
    int cookies;
    int maxCookies;

    //ui
    QLabel * lblCookieBelt;
    QLineEdit * inpCookieBeltMax;

public:
    CookieConveyorBelt(){

    }

    void __init__(int _maxCookies, QMutex * _mutex);\
    bool canAddCookies(int newCookies);
    int addCookies(int newCookies);
    void printData();
    void printConfig();
    void updateConfig(double);
};

// ---------------------------- ESTRUCTURAS PARA LAS MAQUINAS DE MEZCLA Y CHOCOLATE -------------------

struct ChocolateMachine : public QThread{
public:
    double proccessTime;
    double gramsPerTime;
    double maxGrams;
    double minGrams;
    double proccessingGrams;
    double proccessedGrams;
    int id;

    Planner * planner;
    WareHouse * wareHouse;
    GramsConveyorBelt * chocolateConveyorBelt;

    //thread
    bool isActive = true;
    bool isPause = false;

    //ui
    QLabel * lblChocolateMachine;
    QLineEdit * inpChocolateMachineProcessTime;
    QLineEdit * inpChocolateMachineGramsTime;
    QLineEdit * inpChocolateMachineMax;
    QLineEdit * inpChocolateMachineMin;
    QPushButton * controlBtn;

public:
    ChocolateMachine();
    void __init__(double _proccessTime, double _gramsPerTime, double _maxGrams, double _minGrams, int _id, Planner * planner,
                  WareHouse * _wareHouse, GramsConveyorBelt *_chocolateConveyorBelt);
    void run();

    void makeRequest();
    void proccessGrams();
    void placeOnConveyorBelt();
    void updateConfig(double _proccessTime, double _gramsPerTime, double _maxGrams, double _minGrams);
    void printData();
    void printConfig();

    void pause();
    void resume();
    void finish();
};

// maquina de mezcla
struct DoughMachine : public QThread{
    public:
        double proccessTime;
        double gramsPerTime;
        double maxGrams;
        double minGrams;
        double proccessingGrams;
        double proccessedGrams;
        int id;

        Planner * planner;
        WareHouse * wareHouse;
        GramsConveyorBelt * doughConveyorBelt;

        //thread
        bool isActive = true;
        bool isPause = false;

        //ui
        QLabel * lblDoughMachine;
        QLineEdit * inpDoughMachineProcessTime;
        QLineEdit * inpDoughMachineGramsTime;
        QLineEdit * inpDoughMachineMax;
        QLineEdit * inpDoughMachineMin;
        QPushButton * controlBtn;

    public:
        DoughMachine();
        void __init__(double _proccessTime, double _gramsPerTime, double _maxGrams, double _minGrams, int _id,
                      Planner * planner, WareHouse * _wareHouse, GramsConveyorBelt * _doughConveyorBelt);
        void run();

        void makeRequest();
        void proccessGrams();
        void placeOnConveyorBelt();
        void updateConfig(double _proccessTime, double _gramsPerTime, double _maxGrams, double minGrams);
        void printData();
        void printConfig();

        void pause();
        void resume();
        void finish();
};

// ---------------------------- ESTRUCTURAS PARA LA MAQUINA ENSAMBLADORA-------------------
struct JointerMachine : public QThread{
public:
    GramsConveyorBelt * chocolateConveyorBelt;
    GramsConveyorBelt * doughConveyorBelt;
    CookieConveyorBelt * cookieConveyorBelt;
    Planner * planner;
    double proccessTime;
    double cookiesPerTime;
    int madeCookies;

    //thread
    bool isActive = true;
    bool isPause = false;

    //ui
    QLabel * lblJointerMachine;
    QLineEdit * inpJointerMachineProccessTime;
    QLineEdit * inpJointerMachinePerTime;
    QPushButton * controlBtn;

public:
    JointerMachine();
    void __init__(double _proccessTime, double _cookiesPerTime, Planner * _planner, GramsConveyorBelt * _chocolateConveyorBelt,
                  GramsConveyorBelt * _doughConveyorBelt, CookieConveyorBelt * _cookieConveyorBelt);
    void run();

    bool canMakeCookies(); // verifica si hay gramos en las bandas para hacer las galletas por tiempo
    void getGrams(); // saca gramos de mezcla y chocolate de las bandas
    void makeCookies(); // espera el tiempo y hace las galletas y las coloca en la banda de galletas
    void placeOnConveyorBelt(); // coloca en la banda de galletas
    void updateConfig(double _proccessTime, double _cookiesPerTime);
    void printData(); // imprime datos actuales
    void printConfig();

    void pause();
    void resume();
    void finish();


};


// ---------------------------- ESTRUCTURAS PARA EL HORNO -------------------
struct Kiln : public QThread{
public:
    int cookieCapacity;
    QList<Tray *> trays;
    CookieConveyorBelt * cookieConveyorBelt1; // banda 1
    CookieConveyorBelt * cookieConveyorBelt2; // banda 2

    //thread
    bool isActive = true;
    bool isPause = false;

    //ui
    QPushButton * controlBtn;
    QLineEdit * inpCapacity;
    QLabel * lblKilnTrays;
    QComboBox * cmbTrays;
    QLineEdit * inpKilnTrayCookies;
    QLineEdit * inpKilnBakingTime;
    QPushButton * btnControlTray;

public:
    Kiln();
    void __init__(int _cookieCapacity, CookieConveyorBelt * _cookieConveyorBelt1, CookieConveyorBelt * _cookieConveyorBelt2);
    void run();

    void updateConfig(int _cookieCapacity);
    void printData();
    void printConfig();
    void fillTrays();
    void activeTrays();
    void printTrayConfig(int indexTray);
    void updateTrayConfig(int indexTray, int _maxCookies, int _bakingTime, QString status);
    void pause();
    void resume();
    void finish();
};


struct Tray : public QThread{
    int maxCookies;
    double bakingTime;
    int cookies;
    bool isBaking = false; // para ver si esta ocupada o no
    CookieConveyorBelt * cookieConveyorBelt;

    //thread
    bool isActive = true;
    bool isPause = false;

public:
    Tray();
    void __init__(int maxCookies, int bakingTime, CookieConveyorBelt * _cookieConveyorBelt2);
    void run();

    int addCookies(int newCookies);
    bool isFull();
    void bakeCookies();

    void pause();
    void resume();
    void finish();

};

// ----------------------------- ESTRUCTURAS PARA SUPERVISORES DE CALIDAD ------------------------------
// departamento de calidad de servicio (revisan las galletas)
struct Qos : public QThread{
public:
    Inspector * inspector1;
    Inspector * inspector2;
    CookieConveyorBelt * cookieConveyorBelt1;
    CookieConveyorBelt * cookieConveyorBelt2;
    CookieConveyorBelt * cookieConveyorBelt3;
    //thread
    bool isActive = true;
    bool isPause = false;
    //ui
    QLabel * lblQoS;
    QComboBox * cmbInspectors;
    QLineEdit * inpInspectorTime;
    QLineEdit * inpInspectorPerTime;
    QLineEdit * inpInspectorProb;
    QPushButton * btnControlInspector;

public:
    Qos();
    void __init__(CookieConveyorBelt * cookieConveyorBelt1, CookieConveyorBelt * cookieConveyorBelt2, CookieConveyorBelt * cookieConveyorBelt3);
    void run();

    void printData();
    void printInspectorConfig(int inspector);
    void updateInspectorConfig(int inspector, int _cookiesPerTime, double _processTime, double _wasteProbability, QString status);
    void pause();
    void resume();
    void finish();

};

struct Inspector: public QThread{
public:
    double wasteProbabilty;
    QRandomGenerator ranGenerator;
    int provedCookies;
    int wastedCookies;
    int cookiesPerTime;
    double proccessTime;
    CookieConveyorBelt * cookieConveyorBeltBefore;
    CookieConveyorBelt * cookieConveyorBeltNext;

    //thread
    bool isActive = true;
    bool isPause = false;

public:
    Inspector();
    void __init__(int cookiesPerTime, double processTime, double wasteProbability, CookieConveyorBelt * cookieConveyorBeltBefore, CookieConveyorBelt * cookieConveyorBeltNext);
    void run();

    void proccessCookies();

    void pause();
    void resume();
    void finish();
};

// ------------------------------------ ESTRUCTURAS PARA EL EMPACADO Y TRANSPORTE -----------------------------
struct Baler :public QThread{
public:
    int packsPerTime;
    Order * currentOrder = NULL;
    Planner * planner;
    QList<Transport *> transports;
    CookieConveyorBelt * cookieConveyorBelt;
    QRandomGenerator randomGen;
    // thread
    bool isActive = true;
    bool isPause = false;

    //ui
    QLabel * lblBaler;
    QLineEdit * inpBalerPerTime;
    QPushButton * btnControl;
    // transporte
    QComboBox * cmbTransports;
    QLineEdit * inpTransportMax;
    QLineEdit * inpTransportTime;
    QPushButton * btnControlTransport;
    QLabel * lblTransports;


public:
    Baler();
    void __init__(int _packsPerTime, Planner * _planner, CookieConveyorBelt * _cookieConveyorBelt);
    void run();

    void initTransports();
    void updateCurrentPack();
    void pack();
    void placeOnTransport();
    void printData();
    void updateConfig(int _packsPerTime);
    void printConfig();
    // transporte
    void printTransportConfig(int index);
    void updateTransportConfig(int index, int _maxPacks, double deliveryTime, QString status);
    void printTransportData();

    void pause();
    void resume();
    void finish();

};


struct Transport : public QThread{
public:
    QString packName;
    int maxPacks;
    double deliveryTime;
    int packs; // paquetes actuales
    bool isAvailable = true;
    Planner * planner;

    // thread
    bool isActive = true;
    bool isPause = false;

    //ui

public:
    Transport();
    void __init__(Planner * _planner, QString _packName, int _maxPacks, double _deliveryTime);
    void run();

    int loadPacks(int newPacks);
    void makePackDelivery();
    void unloadPacks();
    bool isFull();

    void pause();
    void resume();
    void finish();
};



// ------------------------- ESTRUCTURA DEL ALAMACEN FINAL ----------------------------
struct FinalWarehouse: public QThread{
public:
    Planner * planner;

    //thread
    bool isActive = true;
    bool isPause = false;

    //ui
    QLabel * lblSummary;

public:
    FinalWarehouse();

    void __init__(Planner * planner);
    void run();

    void printData();
};


// ---------------------------- ESTRUCTURA DE FABRICA -------------------

struct CookieFactory{
    public: // atributos
        Planner * planner; // planificador
        PackList *  packList;
        WareHouse * wareHouse; // almacen

        GramsConveyorBelt * doughConveyorBelt;
        GramsConveyorBelt * chocolateConveyorBelt;
        DoughMachine * doughMachine1; // maquina mezcla 1
        DoughMachine * doughMachine2; // maquina mezcla 2
        ChocolateMachine * chocolateMachine; // maquina de chocolate
        Kiln * kiln;

        JointerMachine * jointerMachine;
        CookieConveyorBelt * cookieConveyorBelt1;
        CookieConveyorBelt * cookieConveyorBelt2;
        CookieConveyorBelt * cookieConveyorBelt3;
        CookieConveyorBelt * cookieConveyorBelt4;

        // inspeccion
        Qos * qosDepartment;

        // empacadora y transporte
        Baler * baler;
        // almacen final

        FinalWarehouse * finalWarehouse;

        // mutex
        QMutex doughConveyorBeltMutex; // mutex para la banda de gramos de mezcla
        QMutex chocoConveyorBeltMutex; // mutex para a banda de gamos de chocolate
        QMutex cookieConveyorBelt1Mutex;
        QMutex cookieConveyorBelt2Mutex;
        QMutex cookieConveyorBelt3Mutex;
        QMutex cookieConveyorBelt4Mutex;

    public: // metodos
        CookieFactory();

        // inicializa los valores predeterminados
        void initFactory();
        void run(); // pone a funcionar la fabrica

        void pause();
        void resume();
};

#endif // STRUCTS_H
