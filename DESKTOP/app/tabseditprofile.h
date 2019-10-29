#ifndef TABSEDITPROFILE_H
#define TABSEDITPROFILE_H

#include "include.h"

class TabsEditProfileGeneralTab;

class TabsEditProfile : public QWidget {
    Q_OBJECT
public:
    explicit TabsEditProfile(QWidget * parent = 0);
    QTabWidget * getTabWidget();
    TabsEditProfileGeneralTab * getTab(int);
private:
    QTabWidget * _tab_widget;
};

#endif // TABSEDITPROFILE_H
