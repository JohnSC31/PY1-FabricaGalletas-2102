#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // btn connection
    connect(ui->btnStart, SIGNAL (released()),this, SLOT (on_btnStart_clicked()));
    connect(ui->btnAddOrder, SIGNAL (released()),this, SLOT (on_btnAddOrder_clicked()));
    connect(ui->btnAddPack, SIGNAL (released()),this, SLOT (on_btnAddPack_clicked()));
    connect(ui->btnUpdateRecipe, SIGNAL (released()),this, SLOT (on_btnUpdateRecipe_clicked()));
    connect(ui->btnUpdateTrolley, SIGNAL (released()),this, SLOT (on_btnUpdateTrolley_clicked()));



    // botones para el control de maquinas y personas
    connect(ui->btnUpdateRecipe, SIGNAL (released()),this, SLOT (on_btnControlTrolley_clicked()));




    // establecimiento de los parametros ui para las maquinas
    // Receta
    // Almacen
    factory->wareHouse->txtWarehouse = ui->lblWareHouse;
    factory->wareHouse->trolley->inpCapacityGrams = ui->inpCapacityGrams;
    factory->wareHouse->trolley->inpDeliveryTime = ui->inpDeliveryTime;
    // Planner
    factory->planner->lblProduction = ui->lblProduction;
    factory->planner->recipe->inputChocolate = ui->inpChocoRecipe;
    factory->planner->recipe->inputDough =  ui->inpDoughRecipe;
    // PackList
    factory->packList->cmbPacks = ui->cmbPacks;
    factory->packList->lblPacks = ui->lblPacks;
    // Maquina de chocolate
    factory->chocolateMachine->lblChocolateMachine = ui->lblChocolateMachine;
    factory->chocolateMachine->inpChocolateMachineGramsTime = ui->inpChocolateMachineGramsTime;
    factory->chocolateMachine->inpChocolateMachineProcessTime = ui->inpChocolateMachineProcessTime;
    factory->chocolateMachine->inpChocolateMachineMax = ui->inpChocolateMachineMax;
    factory->chocolateMachine->inpChocolateMachineMin = ui->inpChocolateMachineMin;
    // Maquina de mezcla 1
    factory->doughMachine1->lblDoughMachine = ui->lblDoughMachine1;
    factory->doughMachine1->inpDoughMachineGramsTime = ui->inpDoughMachine1GramsTime;
    factory->doughMachine1->inpDoughMachineProcessTime = ui->inpDoughMachine1ProcessTime;
    factory->doughMachine1->inpDoughMachineMax = ui->inpDoughMachine1Max;
    factory->doughMachine1->inpDoughMachineMin = ui->inpDoughMachine1Min;
    // Maquina de mezcla 2
    factory->doughMachine2->lblDoughMachine = ui->lblDoughMachine2;
    factory->doughMachine2->inpDoughMachineGramsTime = ui->inpDoughMachine2GramsTime;
    factory->doughMachine2->inpDoughMachineProcessTime = ui->inpDoughMachine2ProcessTime;
    factory->doughMachine2->inpDoughMachineMax = ui->inpDoughMachine2Max;
    factory->doughMachine2->inpDoughMachineMin = ui->inpDoughMachine2Min;

    // inicializacion de la fabrica
    factory->initFactory();


}

// SE CARGAN LOS COMPONENTES GRAFICOS


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnStart_clicked(){
   // El thread principal se coloca en running y todos los subthread de este tambien
   // boton que inicia la fabrica de galletas
    factory->run();
}

// agregar una orden al plan de produccion
void MainWindow::on_btnAddOrder_clicked(){
    QString packSelected = ui->cmbPacks->currentText();
    QString packNumber = ui->inpNumPacks->text();

    if(validStr(packNumber) && validNumber(packNumber)){
        ui->inpNumPacks->setText("");
        factory->planner->addOrderPlan(new Order(packNumber.toDouble(),  factory->packList->searchPack(packSelected)));
    }
}
// agregar un tipo de paquete nuevo
void MainWindow::on_btnAddPack_clicked(){
    QString nameTxt = ui->inpPackName->text();
    QString cookiesTxt = ui->inpPackCookies->text();

    if(validStr(nameTxt) && validNumber(cookiesTxt)){
       ui->inpPackName->setText("");
       ui->inpPackCookies->setText("");
       factory->packList->insertPack(new Pack(cookiesTxt.toDouble(), nameTxt, 3));
    }

}

// para actualizar la receta
void MainWindow::on_btnUpdateRecipe_clicked(){
    QString doughTxt = ui->inpDoughRecipe->text();
    QString chocoTxt = ui->inpChocoRecipe->text();

    if(validNumber(doughTxt) && validNumber(chocoTxt)){
      factory->planner->recipe->updateRecipe(doughTxt.toDouble(), chocoTxt.toDouble());
    }
}


// actualizar los valores del carrito
void MainWindow::on_btnUpdateTrolley_clicked(){
    QString capacityGrams = ui->inpCapacityGrams->text();
    QString deliveryTime = ui->inpDeliveryTime->text();

    if(validStr(capacityGrams) && validStr(deliveryTime) && validNumber(capacityGrams) && validNumber(deliveryTime)){
        factory->wareHouse->trolley->updateValues(capacityGrams.toDouble(), deliveryTime.toDouble());
    }
}


// --------------------------- METODOS PARA EL CONTROL DE PERSONAS Y MAQUINAS --------------------------------
void MainWindow::on_btnControlTrolley_clicked(){
    if(ui->btnControlTrolley->text() == "Apagar"){
        factory->wareHouse->trolley->pause();
        ui->btnControlTrolley->setText("Encender");

    }else if(ui->btnControlTrolley->text() == "Encender"){
        factory->wareHouse->trolley->resume();
        ui->btnControlTrolley->setText("Apagar");
    }
}
























