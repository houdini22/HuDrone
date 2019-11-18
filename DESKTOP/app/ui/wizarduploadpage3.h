#pragma once
#include "include.h"

class WizardUploadPage3 : public QWizardPage
{
    Q_OBJECT
public:
    WizardUploadPage3(QWidget * parent = nullptr);
private:
    QLabel * _label = nullptr;
    QVBoxLayout * _layout = nullptr;
};
