#include "include.h"

TabsEditProfileOtherTab::TabsEditProfileOtherTab(QWidget *parent) : QWidget(parent) {
    _main_layout = new QVBoxLayout();
    setLayout(_main_layout);
}

QVBoxLayout * TabsEditProfileOtherTab::getLayout() {
    return _main_layout;
}
