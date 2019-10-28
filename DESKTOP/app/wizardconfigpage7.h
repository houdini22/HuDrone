#ifndef WIZARDCONFIGINTROPAGE7_H
#define WIZARDCONFIGINTROPAGE7_H

#include "include.h"

class WizardConfigPage7 : public QWizardPage
{
    Q_OBJECT
public:
    WizardConfigPage7(Config * configuration, Receivers * receivers);
    void showEvent(QShowEvent *);
private:
    QHBoxLayout * _layout;
    Config * _configuration;
    Receivers * _receivers;
    WizardConfigChannelTabs * _tabs;
};

#endif // WIZARDCONFIGINTROPAGE7_H
