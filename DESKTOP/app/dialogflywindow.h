#ifndef DIALOGFLYWINDOW_H
#define DIALOGFLYWINDOW_H

#include "include.h"

class Drone;

class DialogFlyWindow : public QDialog {
    Q_OBJECT
public:
    DialogFlyWindow(QWidget * parent, Drone * drone);
private:
    Drone * _drone;
    QGridLayout * _layout;
};

#endif // DIALOGFLYWINDOW_H
