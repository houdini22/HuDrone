#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "include.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->_drone = new Drone(this);

    connect(this->_drone, SIGNAL(configurationChanged()), this, SLOT(configurationChanged()));

    this->renderMenu();
}

void MainWindow::configurationChanged() {
    this->renderMenu();
}

void MainWindow::renderMenu() {
    QMenu * profilesMenu = this->menuWidget()->findChild<QMenu *>("menuSavedProfiles");
    profilesMenu->clear();

    T_JSON savedProfiles = Config::getInstance().getObject({"profiles"});

    for (T_JSON::iterator it = savedProfiles.begin(); it != savedProfiles.end(); ++it) {
        T_JSON profile = it.value();
        QString name = QString(profile["name"].get<T_String>().c_str());

        QMenu * profileMenu = new QMenu();
        profileMenu->addAction("Upload...");
        profileMenu->addSeparator();
        profileMenu->addAction("Edit...");
        profileMenu->addAction("Delete...");

        profileMenu->setTitle(name);
        profilesMenu->addMenu(profileMenu);
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
