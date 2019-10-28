#ifndef WIZARDCONFIG_H
#define WIZARDCONFIG_H

#include "include.h"

class Drone;

class WizardConfig : public QWizard
{
    Q_OBJECT
public:
    WizardConfig(QWidget *parent, Drone * drone);
    void accept() override;
    Config * getConfiguration();
    Receivers * getReceivers();
protected:
    Config * _configuration;
    Receivers * _receivers;
    void saveConfiguration();
    Drone * _drone;
protected slots:
    void onFinish();
};

#endif // WIZARDCONFIG_H
