#ifndef DRONE_H
#define DRONE_H

#include "include.h"
#include "mainwindow.h"

class MainWindow;
class WizardAddProfile;
class WizardUpload;
class DialogEditProfile;

class Drone : public QObject
{
    Q_OBJECT
public:
    Drone(MainWindow * window);
    void start();
    MainWindow * _window;
    WizardAddProfile * _wizard_add_profile = nullptr;
    WizardUpload * _wizard_upload = nullptr;
    DialogEditProfile * _dialog_edit_profile = nullptr;
    void notifyConfigurationChanged();
    void openWizardAddProfile();
    void openWizardUpload();
    void openDialogEditProfile(QString name);
protected:
private slots:
    void handleMenuActionsSettingsTriggered(bool);
    void handleMenuActionsExitTriggered(bool);
signals:
    void configurationChanged();
};

#endif // DRONE_H
