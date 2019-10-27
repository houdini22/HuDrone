#include "include.h"
#include "mainwindow.h"

Drone::Drone(MainWindow * window) {
    this->_window = window;
    Config::getInstance();
}

void Drone::start() {

}
