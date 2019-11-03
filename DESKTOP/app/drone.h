#ifndef DRONE_H
#define DRONE_H

#include "include.h"
#include "mainwindow.h"

class MainWindow;
class WizardAddProfile;
class WizardUpload;
class DialogEditProfile;
class DialogFlyWindow;
class SteeringGamepad0;
class SteeringGamepad1;

class Drone : public QObject
{
    Q_OBJECT
public:
    Drone(MainWindow * window);
    MainWindow * _window;
    WizardAddProfile * _wizard_add_profile = nullptr;
    WizardUpload * _wizard_upload = nullptr;
    DialogEditProfile * _dialog_edit_profile = nullptr;
    DialogFlyWindow * _dialog_fly = nullptr;
    void notifyConfigurationChanged();
    void openWizardAddProfile();
    void openWizardUpload();
    void openDialogFly();
    void openDialogEditProfile(QString name);

    Modes * getModes();
    void setModes(Modes * modes);
    SteeringGamepad0 * getGamepad0();
    SteeringGamepad1 * getGamepad1();
private:
    Modes * modes;
    SteeringRegistry * steeringRegistry;
    SendingRegistry * sendingRegistry;
    SteeringGamepad0 * gamepad0;
    SteeringGamepad1 * gamepad1;
private slots:
    void handleMenuActionsSettingsTriggered(bool);
    void handleMenuActionsExitTriggered(bool);
    void handleDialogFlyClosed();
    void handleWizardAddProfileClosed();
    void handleWizardUploadClosed();
    void handleDialogEditProfileClosed();

    void slotSteeringDataChanged(SteeringData *);
    void slotSendingsDataChanged(QHash<QString,SendingData*> *);
signals:
    void configurationChanged();

    void signalModesChanged(Modes * modes);
    void signalSteeringDataChanged(SteeringData *);
    void signalSendingsDataChanged(QHash<QString,SendingData*>*);
};

#endif // DRONE_H
