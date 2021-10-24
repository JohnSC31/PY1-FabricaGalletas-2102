#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // detectar el cambio de los comboboxs
    connect(ui->cmbTrays, SIGNAL(currentIndexChanged(int)), this, SLOT(on_cmbTrays_change(int)));
    connect(ui->cmbInspectors, SIGNAL(currentIndexChanged(int)), this, SLOT(on_cmbInspectors_change(int)));
    connect(ui->cmbTransports, SIGNAL(currentIndexChanged(int)), this, SLOT(on_cmbTransports_change(int)));


    // establecimiento de los parametros ui para las maquinas
    // Receta
    // Almacen
    factory->wareHouse->txtWarehouse = ui->lblWareHouse;
    factory->wareHouse->trolley->inpCapacityGrams = ui->inpCapacityGrams;
    factory->wareHouse->trolley->inpDeliveryTime = ui->inpDeliveryTime;
    factory->wareHouse->trolley->controlBtn = ui->btnControlTrolley;
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
    factory->chocolateMachine->controlBtn = ui->btnControlChocolateMachine;
    // Maquina de mezcla 1
    factory->doughMachine1->lblDoughMachine = ui->lblDoughMachine1;
    factory->doughMachine1->inpDoughMachineGramsTime = ui->inpDoughMachine1GramsTime;
    factory->doughMachine1->inpDoughMachineProcessTime = ui->inpDoughMachine1ProcessTime;
    factory->doughMachine1->inpDoughMachineMax = ui->inpDoughMachine1Max;
    factory->doughMachine1->inpDoughMachineMin = ui->inpDoughMachine1Min;
    factory->doughMachine1->controlBtn = ui->btnControlDoughMachine1;
    // Maquina de mezcla 2
    factory->doughMachine2->lblDoughMachine = ui->lblDoughMachine2;
    factory->doughMachine2->inpDoughMachineGramsTime = ui->inpDoughMachine2GramsTime;
    factory->doughMachine2->inpDoughMachineProcessTime = ui->inpDoughMachine2ProcessTime;
    factory->doughMachine2->inpDoughMachineMax = ui->inpDoughMachine2Max;
    factory->doughMachine2->inpDoughMachineMin = ui->inpDoughMachine2Min;
    factory->doughMachine2->controlBtn = ui->btnControlDoughMachine2;
    // Bandas transportadoras
    // de mezcla
    factory->doughConveyorBelt->lblGramsConveyorBelt = ui->lblDoughBelt;
    factory->doughConveyorBelt->inpGramsConveyorBeltMax = ui->inpDoughBeltMax;
    // chocolate
    factory->chocolateConveyorBelt->lblGramsConveyorBelt = ui->lblChocolateBelt;
    factory->chocolateConveyorBelt->inpGramsConveyorBeltMax = ui->inpChocolateBeltMax;
    // galletas 1 (despues de ensambaldora)
    factory->cookieConveyorBelt1->inpCookieBeltMax = ui->inpCookieBelt1Max;
    factory->cookieConveyorBelt1->lblCookieBelt = ui->lblCookieBelt1;
    //galletas 2 (despues de horno)
    factory->cookieConveyorBelt2->inpCookieBeltMax = ui->inpCookieBelt2Max;
    factory->cookieConveyorBelt2->lblCookieBelt = ui->lblCookieBelt2;
    //galletas 3 (en medio de los inspectores)
    factory->cookieConveyorBelt3->lblCookieBelt = ui->lblCookieBelt3;
    factory->cookieConveyorBelt3->inpCookieBeltMax = ui->inpCookieBelt3Max;
    // galletas 4 (despues de la inspecccion
    factory->cookieConveyorBelt4->inpCookieBeltMax = ui->inpCookieBelt4Max;
    factory->cookieConveyorBelt4->lblCookieBelt = ui->lblCookieBelt4;

    //Ensambladora
    factory->jointerMachine->lblJointerMachine = ui->lblJointerMachine;
    factory->jointerMachine->inpJointerMachineProccessTime = ui->inpJointerMachineProccessTime;
    factory->jointerMachine->inpJointerMachinePerTime = ui->inpJointerMachinePerTime;
    factory->jointerMachine->controlBtn = ui->btnControlJointerMachine;
    // Horno
    factory->kiln->controlBtn = ui->btnControlKiln;
    factory->kiln->inpCapacity = ui->inpKilnCapacity;
    factory->kiln->lblKilnTrays = ui->lblKilnTrays;
    factory->kiln->cmbTrays = ui->cmbTrays;
    factory->kiln->inpKilnTrayCookies = ui->inpKilnTrayCookies;
    factory->kiln->inpKilnBakingTime = ui->inpKilnBakingTime;
    factory->kiln->btnControlTray = ui->btnControlTray;
    // servicios de calidad
    factory->qosDepartment->lblQoS = ui->lblQoS;
    factory->qosDepartment->cmbInspectors = ui->cmbInspectors;
    factory->qosDepartment->inpInspectorTime = ui->inpInspectorTime;
    factory->qosDepartment->inpInspectorPerTime = ui->inpInspectorPerTime;
    factory->qosDepartment->inpInspectorProb = ui->inpInspectorProb;
    factory->qosDepartment->btnControlInspector = ui->btnControlInspector;
    // empacadora y transporte
    factory->baler->lblBaler = ui->lblBaler;
    factory->baler->btnControl = ui->btnControlBaler;
    factory->baler->inpBalerPerTime = ui->inpBalerPerTime;
    factory->baler->lblTransports = ui->lblTransports;
    factory->baler->cmbTransports = ui->cmbTransports;
    factory->baler->inpTransportMax = ui->inpTransportMax;
    factory->baler->inpTransportTime = ui->inpTransportTime;
    factory->baler->btnControlTransport = ui->btnControlTransport;
    // transporte
    // almacen final
    factory->finalWarehouse->lblSummary = ui->lblSummary;


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

void MainWindow::on_btnPause_clicked(){
    factory->pause();
}

void MainWindow::on_btnResume_clicked(){
    factory->resume();
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
    QString packTime = ui->inpPackTime->text();

    if(validStr(nameTxt) && validNumber(cookiesTxt) && validNumber(packTime)){
       ui->inpPackName->setText("");
       ui->inpPackCookies->setText("");
       factory->packList->insertPack(new Pack(cookiesTxt.toDouble(), nameTxt, packTime.toDouble()));
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

// actualizar los valores de la maquina de mazcla 1
void MainWindow::on_btnUpdateDoughMachine1_clicked(){
    QString processTime = ui->inpDoughMachine1ProcessTime->text();
    QString gramsPerTime = ui->inpDoughMachine1GramsTime->text();
    QString maxGrams = ui->inpDoughMachine1Max->text();
    QString minGrams = ui->inpDoughMachine1Min->text();

    if(validNumber(processTime) && validNumber(gramsPerTime) && validNumber(maxGrams) && validNumber(minGrams)){
        factory->doughMachine1->updateConfig(processTime.toDouble(), gramsPerTime.toDouble(), maxGrams.toDouble(), minGrams.toDouble());
    }
}

// actualizar los valores de la maquina de mazcla 1
void MainWindow::on_btnUpdateDoughMachine2_clicked(){
    QString processTime = ui->inpDoughMachine2ProcessTime->text();
    QString gramsPerTime = ui->inpDoughMachine2GramsTime->text();
    QString maxGrams = ui->inpDoughMachine2Max->text();
    QString minGrams = ui->inpDoughMachine2Min->text();

    if(validNumber(processTime) && validNumber(gramsPerTime) && validNumber(maxGrams) && validNumber(minGrams)){
        factory->doughMachine2->updateConfig(processTime.toDouble(), gramsPerTime.toDouble(), maxGrams.toDouble(), minGrams.toDouble());
    }
}

// actualizar los datos de la maquina de chocolate
void MainWindow::on_btnUpdateChocolateMachine_clicked(){
    QString processTime = ui->inpChocolateMachineProcessTime->text();
    QString gramsPerTime = ui->inpChocolateMachineGramsTime->text();
    QString maxGrams = ui->inpChocolateMachineMax->text();
    QString minGrams = ui->inpChocolateMachineMin->text();

    if(validNumber(processTime) && validNumber(gramsPerTime) && validNumber(maxGrams) && validNumber(minGrams)){
        factory->chocolateMachine->updateConfig(processTime.toDouble(), gramsPerTime.toDouble(), maxGrams.toDouble(), minGrams.toDouble());
    }
}

// actualizacion de banda transportadora de mezcla
void MainWindow::on_btnUpdateDoughBelt_clicked(){
    QString maxGrams = ui->inpDoughBeltMax->text();

    if(validNumber(maxGrams)){
        factory->doughConveyorBelt->updateConfig(maxGrams.toDouble());
    }
}

// actualizacion de banda transportadora de chocolate
void MainWindow::on_btnUpdateChocolateBelt_clicked(){
    QString maxGrams = ui->inpChocolateBeltMax->text();

    if(validNumber(maxGrams)){
        factory->chocolateConveyorBelt->updateConfig(maxGrams.toDouble());
    }
}

// actualizar los datos de la banda de galletas 1
void MainWindow::on_btnUpdateCookieBelt1_clicked(){
    QString maxCookies = ui->inpCookieBelt1Max->text();

    if(validNumber(maxCookies)){
        factory->cookieConveyorBelt1->updateConfig(maxCookies.toInt());
    }
}

// actualizar los datos de la banda de galletas 2
void MainWindow::on_btnUpdateCookieBelt2_clicked(){
    QString maxCookies = ui->inpCookieBelt2Max->text();

    if(validNumber(maxCookies)){
        factory->cookieConveyorBelt2->updateConfig(maxCookies.toInt());
    }
}

// actualizar los datos del horno
void MainWindow::on_btnUpdateKiln_clicked(){
    QString maxCookies = ui->inpKilnCapacity->text();

    if(validNumber(maxCookies)){
        factory->kiln->updateConfig(maxCookies.toInt());
    }
}

// combo box de las bandejas
void MainWindow::on_cmbTrays_change(int index){
   if(index == 0){
       ui->inpKilnTrayCookies->setText("");
       ui->inpKilnBakingTime->setText("");
   }else{
       factory->kiln->printTrayConfig(index - 1);
       if(index - 1 == 0 || index - 1 == 1){
           ui->btnControlTray->setEnabled(false);
       }else{
           ui->btnControlTray->setEnabled(true);
       }
   }
}

void MainWindow::on_btnUpdateTray_clicked(){
    int trayIndex = ui->cmbTrays->currentIndex();
    QString maxCookies = ui->inpKilnTrayCookies->text();
    QString bakingTime = ui->inpKilnBakingTime->text();
    QString status = ui->btnControlTray->text();
    if(validNumber(maxCookies) && validNumber(bakingTime) && trayIndex >= 0){
        factory->kiln->updateTrayConfig(trayIndex - 1, maxCookies.toInt(), bakingTime.toInt(), status);
    }

}

// combo box de los inspectores
void MainWindow::on_cmbInspectors_change(int index){
   if(index == 0){
       ui->inpInspectorTime->setText("");
       ui->inpInspectorPerTime->setText("");
       ui->inpInspectorProb->setText("");
   }else{
       factory->qosDepartment->printInspectorConfig(index);
   }
}

void MainWindow::on_btnUpdateInspector_clicked(){
    int inspector = ui->cmbInspectors->currentIndex();
    QString cookiesPerTime = ui->inpInspectorPerTime->text();
    QString processTime = ui->inpInspectorTime->text();
    QString wasteProb = ui->inpInspectorProb->text();
    QString status = ui->btnControlInspector->text();
    if(validNumber(cookiesPerTime) && validNumber(processTime) && validNumber(wasteProb) && inspector >= 0){
        factory->qosDepartment->updateInspectorConfig(inspector, cookiesPerTime.toInt(), processTime.toDouble(), wasteProb.toDouble(), status);
    }

}

// actualizacion de la empacadora
void MainWindow::on_btnUpdateBaler_clicked(){
    QString packsPerTime = ui->inpBalerPerTime->text();

    if(validNumber(packsPerTime)){
        factory->baler->updateConfig(packsPerTime.toInt());
    }
}

// actualizacion del transporte
void MainWindow::on_cmbTransports_change(int index){
   if(index == 0){
       ui->inpTransportMax->setText("");
       ui->inpTransportTime->setText("");
   }else{
       factory->baler->printTransportConfig(index - 1);
   }
}

void MainWindow::on_btnUpdateTransport_clicked(){
    int trasnportIndex = ui->cmbTransports->currentIndex();
    QString maxPacks = ui->inpTransportMax->text();
    QString deliveryTime = ui->inpTransportTime->text();
    QString status = ui->btnControlTransport->text();
    if(validNumber(maxPacks) && validNumber(deliveryTime) && trasnportIndex >= 0){
        factory->baler->updateTransportConfig(trasnportIndex - 1, maxPacks.toInt(), deliveryTime.toDouble(), status);
    }

}

// --------------------------- METODOS PARA EL CONTROL DE PERSONAS Y MAQUINAS --------------------------------
void MainWindow::on_btnControlTrolley_clicked(){
    if(ui->btnControlTrolley->text() == "Apagar"){
        factory->wareHouse->trolley->pause();

    }else if(ui->btnControlTrolley->text() == "Encender"){
        factory->wareHouse->trolley->resume();
    }
}

void MainWindow::on_btnControlChocolateMachine_clicked(){
    if(ui->btnControlChocolateMachine->text() == "Apagar"){
        factory->chocolateMachine->pause();

    }else if(ui->btnControlChocolateMachine->text() == "Encender"){
        factory->chocolateMachine->resume();
    }
}

void MainWindow::on_btnControlDoughMachine1_clicked(){
    if(ui->btnControlDoughMachine1->text() == "Apagar"){
        factory->doughMachine1->pause();

    }else if(ui->btnControlDoughMachine1->text() == "Encender"){
        factory->doughMachine1->resume();
    }
}

void MainWindow::on_btnControlDoughMachine2_clicked(){
    if(ui->btnControlDoughMachine2->text() == "Apagar"){
        factory->doughMachine2->pause();

    }else if(ui->btnControlDoughMachine2->text() == "Encender"){
        factory->doughMachine2->resume();
    }
}

void MainWindow::on_btnControlJointerMachine_clicked(){
    if(ui->btnControlJointerMachine->text() == "Apagar"){
        factory->jointerMachine->pause();

    }else if(ui->btnControlJointerMachine->text() == "Encender"){
        factory->jointerMachine->resume();
    }

}

void MainWindow::on_btnControlKiln_clicked(){
    if(ui->btnControlKiln->text() == "Apagar"){
        factory->kiln->pause();

    }else if(ui->btnControlKiln->text() == "Encender"){
        factory->kiln->resume();
    }

}

void MainWindow::on_btnControlTray_clicked(){
    if(ui->btnControlTray->text() == "Apagar"){
        ui->btnControlTray->setText("Encender");

    }else if(ui->btnControlTray->text() == "Encender"){
        ui->btnControlTray->setText("Apagar");
    }
}

void MainWindow::on_btnControlInspector_clicked(){
    if(ui->btnControlInspector->text() == "Apagar"){
        ui->btnControlInspector->setText("Encender");

    }else if(ui->btnControlInspector->text() == "Encender"){
        ui->btnControlInspector->setText("Apagar");
    }
}

void MainWindow::on_btnControlBaler_clicked(){
    if(ui->btnControlBaler->text() == "Apagar"){
        factory->baler->pause();

    }else if(ui->btnControlBaler->text() == "Encender"){
        factory->baler->resume();
    }
}

void MainWindow::on_btnControlTransport_clicked(){
    if(ui->btnControlTransport->text() == "Apagar"){
        ui->btnControlTransport->setText("Encender");

    }else if(ui->btnControlTransport->text() == "Encender"){
        ui->btnControlTransport->setText("Apagar");
    }
}


























