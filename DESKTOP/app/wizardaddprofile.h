#ifndef WIZARDADDPROFILE_H
#define WIZARDADDPROFILE_H

#include "include.h"

class Drone;

class WizardAddProfile : public QWizard
{
    Q_OBJECT
public:
    WizardAddProfile(QWidget *parent, Drone * drone);
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

#endif // WIZARDADDPROFILE_H
