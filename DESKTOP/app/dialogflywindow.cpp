#include "include.h"

DialogFlyWindow::DialogFlyWindow(QWidget *parent, Drone * drone) : QDialog(parent) {
    this->_drone = drone;

    this->setWindowTitle(QString("Fly"));
    this->setFixedSize(800, 688);

    this->setWindowFlag(Qt::WindowSystemMenuHint, false);
    this->setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    this->setWindowFlag(Qt::WindowStaysOnTopHint, true);

    _layout = new QGridLayout;

    setLayout(_layout);
}
