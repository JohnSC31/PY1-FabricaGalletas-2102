#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "structs.h"
#include "helper.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     CookieFactory * factory = new CookieFactory();


    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_btnStart_clicked();
    void on_btnPause_clicked();
    void on_btnResume_clicked();
    void on_btnAddOrder_clicked();
    void on_btnAddPack_clicked();
    void on_btnUpdateRecipe_clicked();
    void on_btnUpdateTrolley_clicked();
    void on_btnUpdateDoughMachine1_clicked();
    void on_btnUpdateDoughMachine2_clicked();
    void on_btnUpdateChocolateMachine_clicked();
    // actualizar maquinas y personas
    void on_btnUpdateDoughBelt_clicked();
    void on_btnUpdateChocolateBelt_clicked();
    void on_btnUpdateCookieBelt1_clicked();
    void on_btnUpdateKiln_clicked();
    void on_btnUpdateCookieBelt2_clicked();
    void on_cmbTrays_change(int index);
    void on_btnUpdateTray_clicked();
    void on_cmbInspectors_change(int index);
    void on_btnUpdateInspector_clicked();
    void on_btnUpdateBaler_clicked();
    void on_cmbTransports_change(int index);
    void on_btnUpdateTransport_clicked();
    // control de maquinas y personas
    void on_btnControlTrolley_clicked();
    void on_btnControlChocolateMachine_clicked();
    void on_btnControlDoughMachine1_clicked();
    void on_btnControlDoughMachine2_clicked();
    void on_btnControlJointerMachine_clicked();
    void on_btnControlKiln_clicked();
    void on_btnControlTray_clicked();
    void on_btnControlInspector_clicked();
    void on_btnControlBaler_clicked();
    void on_btnControlTransport_clicked();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
