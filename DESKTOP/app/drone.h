#ifndef DRONE_H
#define DRONE_H

#include "include.h"
#include "mainwindow.h"

class MainWindow;

class Drone : public QObject
{
    Q_OBJECT

public:
    Drone(MainWindow * window);
    void start();
    MainWindow * _window;

protected:
};

#endif // DRONE_H
