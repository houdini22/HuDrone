#pragma once
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
    void openDialogFly(QString name);
    void openDialogEditProfile(QString name);

    Modes * getModes();
    void setModes(Modes *);
    bool hasArduino();
    void deleteArduino();
    void start(Profile *);
    void stop();
    void setArduino(QSerialPort *);
    void startSendingTimers(Profile *);
    void stopSendingTimers();
private:
    Modes * _modes;
    SteeringRegistry * _steering_registry = nullptr;
    SendingRegistry * _sending_registry = nullptr;
    bool _has_arduino = false;
    QSerialPort * _arduino = nullptr;
    SendingArduino * _sending_arduino = nullptr;
    TimersArduino * _timers;
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
    void signalModesChanged(Modes * _modes);
    void signalSteeringDataChanged(SteeringData *);
    void signalSendingsDataChanged(QHash<QString,SendingData*>*);
    void signalSteeringsDataChanged(QHash<QString, SteeringData *> *);
};
