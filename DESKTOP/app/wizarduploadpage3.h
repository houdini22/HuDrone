#ifndef WIZARDUPLOAPAGE3_H
#define WIZARDUPLOAPAGE3_H

#include "include.h"

class WizardUploadPage3 : public QWizardPage
{
    Q_OBJECT
public:
    WizardUploadPage3(QWidget * parent = 0);
private:
    QLabel * _label;
    QVBoxLayout * _layout;
};

#endif // WIZARDUPLOAPAGE3_H