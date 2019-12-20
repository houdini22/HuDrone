#pragma once
#include "include.h"

class WizardAddProfilePage5: public QWizardPage {
    Q_OBJECT
public:
    WizardAddProfilePage5(Config * configuration, Receivers * receivers);
    void showEvent(QShowEvent *) override;
private:
    QHBoxLayout * _layout = nullptr;
    Config * _configuration = nullptr;
    Receivers * _receivers = nullptr;
    WizardConfigChannelTabs * _tabs = nullptr;
    std::map<int, std::map<int, int>> _add_buttons;
private slots:
    void slotMyPushButton(MyPushButton *);
};
