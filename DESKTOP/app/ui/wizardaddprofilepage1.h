#pragma once
#include "include.h"

class WizardAddProfilePage1 : public QWizardPage
{
    Q_OBJECT
public:
    WizardAddProfilePage1(QWidget *parent = 0);
private:
    QLabel * _label = nullptr;
    QVBoxLayout * _layout = nullptr;
};
