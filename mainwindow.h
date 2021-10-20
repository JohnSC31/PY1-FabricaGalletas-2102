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
    void on_btnAddPack_clicked();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
