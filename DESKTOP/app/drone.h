#ifndef DRONE_H
#define DRONE_H

#include "include.h"
#include "mainwindow.h"

class MainWindow;
class WizardAddProfile;

class Drone : public QObject
{
    Q_OBJECT
public:
    Drone(MainWindow * window);
    void start();
    MainWindow * _window;
    WizardAddProfile * _wizard_add_profile;
    void notifyConfigurationChanged();
    void openWizardAddProfile();
protected:
private slots:
    void handleMenuActionsSettingsTriggered(bool);
    void handleMenuActionsExitTriggered(bool);
signals:
    void configurationChanged();
};

#endif // DRONE_H
