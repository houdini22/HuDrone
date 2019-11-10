#ifndef DIALOGFLY_H
#define DIALOGFLY_H

#include "include.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DialogFly; }
QT_END_NAMESPACE

class Drone;

class DialogFly : public QDialog {
    Q_OBJECT
public:
    DialogFly(QWidget * parent, Drone * drone);
private:
    Drone * _drone;
    QGridLayout * _layout;
    Ui::DialogFly * ui;
    void closeEvent(QCloseEvent *);
private slots:
    void slotSendingsDataChanged(QHash<QString,SendingData*>*);
};

#endif // DIALOGFLY_H
