#ifndef WIZARDUPLOADPAGE1_H
#define WIZARDUPLOADPAGE1_H

#include "include.h"

class WizardUploadPage1 : public QWizardPage
{
    Q_OBJECT
public:
    WizardUploadPage1(QWidget *parent = 0);
private:
    QLabel * _label = nullptr;
    QVBoxLayout * _layout = nullptr;
};

#endif // WIZARDUPLOADPAGE1_H
