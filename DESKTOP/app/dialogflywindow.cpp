#include "include.h"

DialogFlyWindow::DialogFlyWindow(QWidget *parent, Drone * drone) : QDialog(parent) {
    this->_drone = drone;

    setWindowTitle(QString("Fly"));
    setFixedSize(500, 309);

    this->setWindowFlag(Qt::WindowSystemMenuHint, false);
    this->setWindowFlag(Qt::WindowContextHelpButtonHint, false);

    _layout = new QGridLayout;

    setLayout(_layout);
}
