#pragma once
#include "include.h"

class Drone;

class WizardUpload : public QWizard
{
    Q_OBJECT
public:
    WizardUpload(QWidget *parent, Drone * drone);
    void accept() override;
private:
    Drone * _drone = nullptr;
protected slots:
    void onFinish();
};
