#ifndef WIZARDADDPROFILEPAGE5_H
#define WIZARDADDPROFILEPAGE5_H

#include "include.h"

class WizardAddProfilePage5: public QWizardPage
{
    Q_OBJECT
public:
    WizardAddProfilePage5(Config * configuration, Receivers * receivers);
    void showEvent(QShowEvent *);
private:
    QHBoxLayout * _layout;
    Config * _configuration;
    Receivers * _receivers;
    WizardConfigChannelTabs * _tabs;
};

#endif // WIZARDADDPROFILEPAGE5_H
