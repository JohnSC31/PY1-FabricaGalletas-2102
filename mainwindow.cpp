#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // btn connection
    connect(ui->btnStart, SIGNAL (released()),this, SLOT (on_btnStart_clicked()));
}

// SE CARGAN LOS COMPONENTES GRAFICOS


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnStart_clicked(){
   // El thread principal se coloca en running y todos los subthread de este tambien
   // boton que inicia la fabrica de galletas
}
