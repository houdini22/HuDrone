#ifndef WIZARDUPLOAD_H
#define WIZARDUPLOAD_H

#include "include.h"

class Drone;

class WizardUpload : public QWizard
{
    Q_OBJECT
public:
    WizardUpload(QWidget *parent, Drone * drone);
    void accept() override;
protected:
    Drone * _drone = nullptr;
protected slots:
    void onFinish();
};

#endif // WIZARDCONFIG_H
