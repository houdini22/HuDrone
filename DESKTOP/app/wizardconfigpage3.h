#ifndef WIZARDCONFIGINTROPAGE3_H
#define WIZARDCONFIGINTROPAGE3_H

#include "include.h"

class ThreadBoxConnect;

class WizardConfigPage3 : public QWizardPage
{
    Q_OBJECT
public:
    WizardConfigPage3(QWidget *parent = 0);
private:
    QLabel * _label;
    QLabel * _label_status;
    QVBoxLayout * _layout;
    ThreadBoxConnect * _thread_box_connect = nullptr;
private slots:
    void showEvent(QShowEvent *);
    void onWizardClose();
    void handleArduinoConnected(SerialPort *);
signals:
    void arduinoConnected(SerialPort *);
};

#endif // WIZARDCONFIGINTROPAGE3_H
