#pragma once
#include "include.h"

class WizardConfigGeneralChannelTab;

class TabsEditProfileOtherTab : public QWidget {
    Q_OBJECT
public:
    explicit TabsEditProfileOtherTab(QWidget *parent = nullptr);
    QVBoxLayout * getLayout();
private:
    QVBoxLayout * _main_layout = nullptr;
};
