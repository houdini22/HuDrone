#include "mainwindow.h"
#include <QApplication>
#include "include.h"

int main(int argc, char *argv[])
{
    qRegisterMetaType<SteeringData>("SteeringData");
    qRegisterMetaType<SendingData>("SendingData");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
