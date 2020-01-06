#pragma once
#include "include.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DialogFly; }
QT_END_NAMESPACE

class Drone;

class DialogFly : public QDialog {
    Q_OBJECT
public:
    DialogFly(QWidget * parent, Drone * drone, QString profileName);
private:
    Drone * _drone;
    QGridLayout * _layout;
    Ui::DialogFly * ui;
    void closeEvent(QCloseEvent *) override;
    void showEvent(QShowEvent *) override;
    Profile * _profile;
    Modes * _modes;
private slots:
    void slotSendingsDataChanged(QHash<QString,SendingData>);
    void slotSteeringsDataChanged(QVector<SteeringData>);
    void slotModesChanged(Modes *);
signals:
    void signalModesChanged(Modes *);
};
