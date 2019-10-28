#ifndef WIZARDADDPROFILEPAGE6_H
#define WIZARDADDPROFILEPAGE6_H

#include "include.h"

class WizardAddProfilePage6 : public QWizardPage
{
    Q_OBJECT
public:
    WizardAddProfilePage6(Config * configuration, Receivers * receivers);
    void showEvent(QShowEvent *);
private:
    QHBoxLayout * _layout;
    Config * _configuration;
    Receivers * _receivers;
    WizardConfigChannelTabs * _tabs;
};

#endif // WIZARDADDPROFILEPAGE6_H
