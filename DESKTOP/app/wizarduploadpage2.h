#ifndef WIZARDUPLOADPAGE2_H
#define WIZARDUPLOADPAGE2_H

#include "include.h"

class ThreadBoxConnect;

class WizardUploadPage2 : public QWizardPage
{
    Q_OBJECT
public:
    WizardUploadPage2(Drone *);
private:
    QLabel * _label = nullptr;
    QLabel * _label_status = nullptr;
    QVBoxLayout * _layout = nullptr;
    ThreadBoxConnect * _thread_box_connect = nullptr;
    Drone * _drone = nullptr;
private slots:
    void showEvent(QShowEvent *);
    void onWizardClose();
    void handleArduinoConnected(QSerialPort *);
};

#endif // WIZARDUPLOADPAGE2_H
