#ifndef DRONE_H
#define DRONE_H

#include "include.h"
#include "mainwindow.h"

class MainWindow;
class WizardConfig;

class Drone : public QObject
{
    Q_OBJECT
public:
    Drone(MainWindow * window);
    void start();
    MainWindow * _window;
    WizardConfig * _wizard_config;
    void notifyConfigurationChanged();
protected:
    void openWizardConfig();
private slots:
    void handleMenuActionsSettingsTriggered(bool);
    void handleMenuActionsExitTriggered(bool);
signals:
    void configurationChanged();
};

#endif // DRONE_H
