#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "include.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Drone;
class MyMenuAction;
class WizardUpload;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    Drone * _drone;
    void renderMenu();
    WizardUpload * _wizard_upload = nullptr;
private slots:
    void configurationChanged();
    void profileItemTriggered(MyMenuAction *, bool);
    void wizardUploadFinished(int);
};
#endif // MAINWINDOW_H
