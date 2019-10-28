#ifndef WIZARDCONFIGINTROPAGE6_H
#define WIZARDCONFIGINTROPAGE6_H

#include "include.h"

class WizardConfigChannelTabs;
class MyLineEdit;

class WizardConfigPage6 : public QWizardPage
{
    Q_OBJECT
public:
    WizardConfigPage6(Config * configuration, Receivers * receivers);
private:
    int getValueFromChannel(int channelNumber, T_String value);
    void showEvent(QShowEvent *event);
    QHBoxLayout * _layout;
    Config * _configuration;
    Receivers * _receivers;
    WizardConfigChannelTabs * _tabs;
    std::map<int, std::map<T_String, MyLineEdit *>> _inputs;
public slots:
    void textEdited(QString, QString);
};

#endif // WIZARDCONFIGINTROPAGE6_H
