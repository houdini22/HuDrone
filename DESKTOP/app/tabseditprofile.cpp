#include "include.h"

TabsEditProfile::TabsEditProfile(QWidget * parent) : QWidget(parent) {
    _tab_widget = new QTabWidget;
    _tab_widget->addTab(new TabsEditProfileGeneralTab, "Radio");
    _tab_widget->addTab(new TabsEditProfileGeneralTab, "Arming");
    _tab_widget->addTab(new TabsEditProfileGeneralTab, "Disarming");

    QSizePolicy sizePolicy;
    sizePolicy.setVerticalStretch(1);
    sizePolicy.setHorizontalStretch(1);
    sizePolicy.setHorizontalPolicy(QSizePolicy::Policy::Expanding);
    sizePolicy.setVerticalPolicy(QSizePolicy::Policy::Expanding);

    _tab_widget->setSizePolicy(sizePolicy);
}

QTabWidget * TabsEditProfile::getTabWidget() {
    return this->_tab_widget;
}

TabsEditProfileGeneralTab * TabsEditProfile::getTab(int index) {
    return (TabsEditProfileGeneralTab *) this->_tab_widget->widget(index);
}
