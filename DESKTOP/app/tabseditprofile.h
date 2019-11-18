#pragma once
#include "include.h"

class TabsEditProfileGeneralTab;

class TabsEditProfile : public QWidget {
    Q_OBJECT
public:
    explicit TabsEditProfile(QWidget * parent = nullptr);
    QTabWidget * getTabWidget();
    TabsEditProfileGeneralTab * getTab(int);
private:
    QTabWidget * _tab_widget;
};
