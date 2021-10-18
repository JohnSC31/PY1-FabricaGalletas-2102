#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    CookieFactory * factory = new CookieFactory();

    factory->initFactory();
    factory->run();

    return a.exec();
}
