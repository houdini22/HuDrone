#pragma once
#include "include.h"

class WizardConfigGeneralChannelTab;

class TabsEditProfileGeneralTab : public QWidget {
    Q_OBJECT
public:
    explicit TabsEditProfileGeneralTab(QWidget *parent = nullptr);
    QGridLayout * getLayout();
    QTabWidget * getTabWidget();
    WizardConfigGeneralChannelTab * getTab(int);
private:
    QTabWidget * _tab_widget;
    QGridLayout * _main_layout;
};
