#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // btn connection
    connect(ui->btnStart, SIGNAL (released()),this, SLOT (on_btnStart_clicked()));
    connect(ui->btnAddPack, SIGNAL (released()),this, SLOT (on_btnAddPack_clicked()));


    // inicializacion de la fabrica
    factory->initFactory(ui->lblWareHouse, ui->lblProduction, ui->lblPacks, ui->lblChocolateMachine);


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

void MainWindow::on_btnAddPack_clicked(){
    QString nameTxt = ui->inpPackName->text();
    QString cookiesTxt = ui->inpPackCookies->text();
    if(validStr(nameTxt) && validNumber(cookiesTxt)){

       factory->packList->insertPack(new Pack(cookiesTxt.toDouble(), nameTxt, 3));
    }

}
