#include "include.h"

WizardConfigChannelTabs::WizardConfigChannelTabs(QWidget * parent) : QWidget(parent) {
    _tab_widget = new QTabWidget;
    _tab_widget->addTab(new WizardConfigGeneralChannelTab, "CH 1");
    _tab_widget->addTab(new WizardConfigGeneralChannelTab, "CH 2");
    _tab_widget->addTab(new WizardConfigGeneralChannelTab, "CH 3");
    _tab_widget->addTab(new WizardConfigGeneralChannelTab, "CH 4");
    _tab_widget->addTab(new WizardConfigGeneralChannelTab, "CH 5");
    _tab_widget->addTab(new WizardConfigGeneralChannelTab, "CH 6");
    _tab_widget->addTab(new WizardConfigGeneralChannelTab, "CH 7");
    _tab_widget->addTab(new WizardConfigGeneralChannelTab, "CH 8");

    QSizePolicy sizePolicy;
    sizePolicy.setVerticalStretch(1);
    sizePolicy.setHorizontalStretch(1);
    sizePolicy.setHorizontalPolicy(QSizePolicy::Policy::Expanding);
    sizePolicy.setVerticalPolicy(QSizePolicy::Policy::Expanding);

    _tab_widget->setSizePolicy(sizePolicy);
}

QTabWidget * WizardConfigChannelTabs::getTabWidget() {
    return this->_tab_widget;
}

QWidget * WizardConfigChannelTabs::getTab(int index) {
    return this->_tab_widget->widget(index);
}
