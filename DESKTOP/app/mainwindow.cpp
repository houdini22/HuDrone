#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "include.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->_drone = new Drone(this);
    this->setup();
}

void MainWindow::showEvent(QShowEvent *event) {}

void MainWindow::resizeEvent(QResizeEvent *event) {}

void MainWindow::setup() {
    QMenu * profilesMenu = this->menuWidget()->findChild<QMenu *>("menuSavedProfiles");
    T_JSON savedProfiles = Config::getInstance().getObject({"profiles"});

    for (T_JSON::iterator it = savedProfiles.begin(); it != savedProfiles.end(); ++it) {
        T_JSON profile = it.value();
        QString name = QString(profile["name"].get<T_String>().c_str());
        QMenu * profileMenu = new QMenu();

        profileMenu->setTitle(name);
        profilesMenu->addMenu(profileMenu);
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
