#pragma once
#include "include.h"
#include "mainwindow.h"

class MainWindow;
class WizardAddProfile;
class WizardUpload;
class DialogEditProfile;
class DialogFly;
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
    void openDialogFly(QString);
    void openDialogEditProfile(QString);

    Modes * getModes();
    void setModes(Modes *);
    bool hasArduino();
    void deleteArduino();
    void start(Profile *);
    void stop();
    //void setArduino(QSerialPort *);
    //void startSendingTimers(Profile *);
    //void stopSendingTimers();
private:
    Modes * _modes;
    SteeringRegistry * _steering_registry = nullptr;
    SendingRegistry * _sending_registry = nullptr;
    bool _has_arduino = false;
    //QSerialPort * _arduino = nullptr;
    SendingArduino * _sending_arduino = nullptr;
    //TimersArduino * _timers;
private slots:
    void handleMenuActionsSettingsTriggered(bool);
    void handleMenuActionsExitTriggered(bool);
    void handleWizardAddProfileClosed();
    void handleWizardUploadClosed();
    void handleDialogEditProfileClosed();
    void slotSteeringDataChanged(SteeringData);
    void slotSteeringsDataChanged(QVector<SteeringData>);
    void slotSendingsDataChanged(QHash<QString, SendingData>);
    //void slotArduinoConnected(QSerialPort *);
signals:
    void configurationChanged();
    void signalModesChanged(Modes *);
    void signalSteeringDataChanged(SteeringData);
    void signalSendingsDataChanged(QHash<QString, SendingData>);
    void signalSteeringsDataChanged(QVector<SteeringData>);
};
