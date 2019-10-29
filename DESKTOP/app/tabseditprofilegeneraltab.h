#ifndef TABSEDITPROFILEGENERALTAB_H
#define TABSEDITPROFILEGENERALTAB_H

#include "include.h"

class WizardConfigGeneralChannelTab;

class TabsEditProfileGeneralTab : public QWidget {
    Q_OBJECT
public:
    explicit TabsEditProfileGeneralTab(QWidget *parent = 0);
    QGridLayout * getLayout();
    QTabWidget * getTabWidget();
    WizardConfigGeneralChannelTab * getTab(int);
private:
    QTabWidget * _tab_widget;
    QGridLayout * _main_layout;
};

#endif // TABSEDITPROFILEGENERALTAB_H
