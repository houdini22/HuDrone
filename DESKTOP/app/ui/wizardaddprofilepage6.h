#pragma once
#include "include.h"

class WizardAddProfilePage6 : public QWizardPage
{
    Q_OBJECT
public:
    WizardAddProfilePage6(Config * configuration, Receivers * receivers);
    void showEvent(QShowEvent *) override;
private:
    QHBoxLayout * _layout = nullptr;
    Config * _configuration = nullptr;
    Receivers * _receivers = nullptr;
    WizardConfigChannelTabs * _tabs = nullptr;
};
