#pragma once
#include "include.h"

class WizardConfigGeneralChannelTab;

class WizardConfigChannelTabs : public QWidget {
    Q_OBJECT
public:
    explicit WizardConfigChannelTabs(QWidget * parent = nullptr);
    QTabWidget * getTabWidget();
    QWidget * getTab(int);
private:
    QTabWidget * _tab_widget = nullptr;
};
