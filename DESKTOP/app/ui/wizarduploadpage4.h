#ifndef WIZARDUPLOAPAGE4_H
#define WIZARDUPLOAPAGE4_H

#include "include.h"

class WizardUploadPage4 : public QWizardPage
{
    Q_OBJECT
public:
    WizardUploadPage4(QWidget * parent = nullptr);
private:
    QVBoxLayout * _layout = nullptr;
};

#endif // WIZARDUPLOAPAGE4_H
