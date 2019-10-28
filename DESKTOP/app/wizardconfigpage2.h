#ifndef WIZARDCONFIGINTROPAGE2_H
#define WIZARDCONFIGINTROPAGE2_H

#include "include.h"

class WizardConfigPage2 : public QWizardPage
{
    Q_OBJECT
public:
    WizardConfigPage2(Config * configuration);
private:
    QPushButton * _button_glove;
    QPushButton * _button_gamepad;
    QGroupBox * _group_box;
    QHBoxLayout * _layout;
    Config * _configuration;
private slots:
    void handleButtonGlove();
    void handleButtonGamepad();
    void showEvent(QShowEvent *);
};

#endif // WIZARDCONFIGINTROPAGE2_H
