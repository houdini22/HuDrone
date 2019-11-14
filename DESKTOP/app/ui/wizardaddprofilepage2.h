#ifndef WIZARDADDPROFILEPAGE2_H
#define WIZARDADDPROFILEPAGE2_H

#include "include.h"

class WizardAddProfilePage2 : public QWizardPage
{
    Q_OBJECT
public:
    WizardAddProfilePage2(Config * configuration);
private:
    QPushButton * _button_glove = nullptr;
    QPushButton * _button_gamepad = nullptr;
    QGroupBox * _group_box = nullptr;
    QHBoxLayout * _layout = nullptr;
    Config * _configuration = nullptr;
private slots:
    void handleButtonGlove();
    void handleButtonGamepad();
    void showEvent(QShowEvent *);
};

#endif // WIZARDCONFIGINTROPAGE2_H
