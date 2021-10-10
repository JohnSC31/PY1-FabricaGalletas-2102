#include "mainwindow.h"

#include <QApplication>

// se hicieron cambios en mi rama

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
