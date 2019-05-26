#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    Q_INIT_RESOURCE(TEMMMPO);
    return a.exec();
}
