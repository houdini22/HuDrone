#ifndef WIZARDCONFIGINTROPAGE8_H
#define WIZARDCONFIGINTROPAGE8_H

#include "include.h"

class WizardConfigPage8 : public QWizardPage
{
    Q_OBJECT
public:
    WizardConfigPage8(Config * configuration, Receivers * receivers);
    T_JSON getValueFromChannel(int channelNumber, T_String value);
    void showEvent(QShowEvent *);
private:
    QHBoxLayout * _layout;
    Config * _configuration;
    Receivers * _receivers;
    WizardConfigChannelTabs * _tabs;
};

#endif // WIZARDCONFIGINTROPAGE8_H
