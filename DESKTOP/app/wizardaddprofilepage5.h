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
    QHBoxLayout * _layout = nullptr;
    Config * _configuration = nullptr;
    Receivers * _receivers = nullptr;
    WizardConfigChannelTabs * _tabs = nullptr;
};

#endif // WIZARDADDPROFILEPAGE5_H
