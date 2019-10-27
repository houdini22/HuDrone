#ifndef WIZARDCONFIG_H
#define WIZARDCONFIG_H

#include "include.h"

class WizardConfig : public QWizard
{
    Q_OBJECT
public:
    WizardConfig(QWidget *parent = 0);
    void accept() override;
    Config * getConfiguration();
protected:
    Config * _configuration;
    void saveConfiguration();
protected slots:
    void onFinish();
};

#endif // WIZARDCONFIG_H
