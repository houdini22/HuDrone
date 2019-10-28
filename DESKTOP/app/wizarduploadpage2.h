#ifndef WIZARDUPLOADPAGE_H
#define WIZARDUPLOADPAGE_H

#include "include.h"

class ThreadBoxConnect;

class WizardUploadPage2 : public QWizardPage
{
    Q_OBJECT
public:
    WizardUploadPage2(QWidget *parent = 0);
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

#endif // WIZARDUPLOADPAGE_H
