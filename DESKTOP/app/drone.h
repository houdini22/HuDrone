#ifndef DRONE_H
#define DRONE_H

#include "include.h"
#include "mainwindow.h"

class MainWindow;
class WizardAddProfile;
class WizardUpload;
class DialogEditProfile;
class DialogFlyWindow;

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
protected:
private slots:
    void handleMenuActionsSettingsTriggered(bool);
    void handleMenuActionsExitTriggered(bool);
    void handleDialogFlyClosed();
    void handleWizardAddProfileClosed();
    void handleWizardUploadClosed();
    void handleDialogEditProfileClosed();
signals:
    void configurationChanged();
};

#endif // DRONE_H
