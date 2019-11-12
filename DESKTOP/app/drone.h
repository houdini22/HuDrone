#ifndef DRONE_H
#define DRONE_H

#include "include.h"
#include "mainwindow.h"

class MainWindow;
class WizardAddProfile;
class WizardUpload;
class DialogEditProfile;
class DialogFly;
class SteeringGamepad0;
class SteeringGamepad1;
class SendingArduino;

class Drone : public QObject
{
    Q_OBJECT
public:
    Drone(MainWindow * window);
    MainWindow * _window;
    WizardAddProfile * _wizard_add_profile = nullptr;
    WizardUpload * _wizard_upload = nullptr;
    DialogEditProfile * _dialog_edit_profile = nullptr;
    DialogFly * _dialog_fly = nullptr;
    void notifyConfigurationChanged();
    void openWizardAddProfile();
    void openWizardUpload();
    void openDialogFly();
    void openDialogEditProfile(QString name);

    Modes * getModes();
    void setModes(Modes * modes);
    SteeringGamepad0 * getGamepad0();
    SteeringGamepad1 * getGamepad1();
    bool hasArduino();
    void deleteArduino();
    void start();
    void stop();
    void setArduino(QSerialPort *);
private:
    Modes * modes;
    SteeringRegistry * steeringRegistry;
    SendingRegistry * sendingRegistry;
    SteeringGamepad0 * gamepad0;
    SteeringGamepad1 * gamepad1;
    bool _has_arduino = false;
    QSerialPort * _arduino = nullptr;
    SendingArduino * _sending_arduino;
private slots:
    void handleMenuActionsSettingsTriggered(bool);
    void handleMenuActionsExitTriggered(bool);
    void handleWizardAddProfileClosed();
    void handleWizardUploadClosed();
    void handleDialogEditProfileClosed();
    void slotSteeringDataChanged(SteeringData *);
    void slotSteeringsDataChanged(QHash<QString, SteeringData *> *);
    void slotSendingsDataChanged(QHash<QString,SendingData*> *);
    void slotArduinoConnected(QSerialPort *);
signals:
    void configurationChanged();
    void signalModesChanged(Modes * modes);
    void signalSteeringDataChanged(SteeringData *);
    void signalSendingsDataChanged(QHash<QString,SendingData*>*);
    void signalSteeringsDataChanged(QHash<QString, SteeringData *> *);
};

#endif // DRONE_H
