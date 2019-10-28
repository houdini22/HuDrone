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
    disconnect(this, SLOT(profileItemTriggered(MyMenuAction*, bool)));

    QMenu * profilesMenu = this->menuWidget()->findChild<QMenu *>("menuSavedProfiles");
    profilesMenu->clear();

    T_JSON savedProfiles = Config::getInstance().getObject({"profiles"});

    for (T_JSON::iterator it = savedProfiles.begin(); it != savedProfiles.end(); ++it) {
        T_JSON profile = it.value();
        QString name = QString(profile["name"].get<T_String>().c_str());

        QMenu * profileMenu = new QMenu();

        auto uploadAction = MyMenuAction::factory(profileMenu)
                ->setText("Upload...")
                ->setParameter("action", "upload")
                ->setParameter("name", name);
        auto editAction = MyMenuAction::factory(profileMenu)
                ->setText("Edit...")
                ->setParameter("action", "edit")
                ->setParameter("name", name);
        auto deleteAction = MyMenuAction::factory(profileMenu)
                ->setText("Delete...")
                ->setParameter("action", "delete")
                ->setParameter("name", name);

        connect(uploadAction, SIGNAL(myTriggered(MyMenuAction *, bool)), this, SLOT(profileItemTriggered(MyMenuAction *, bool)));
        connect(editAction, SIGNAL(myTriggered(MyMenuAction *, bool)), this, SLOT(profileItemTriggered(MyMenuAction *, bool)));
        connect(deleteAction, SIGNAL(myTriggered(MyMenuAction *, bool)), this, SLOT(profileItemTriggered(MyMenuAction *, bool)));

        profileMenu->addAction(uploadAction);
        profileMenu->addSeparator();
        profileMenu->addAction(editAction);
        profileMenu->addAction(deleteAction);
        profileMenu->setTitle(name);
        profilesMenu->addMenu(profileMenu);
    }
}

void MainWindow::profileItemTriggered(MyMenuAction * action, bool triggered) {
    if (action->getParameter("action").compare("delete") == 0) {
        if (QMessageBox::question(this, "Confirm", "Are you sure to delete?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
            T_JSON config = Config::getInstance().getData();
            T_JSON configProfiles = config["profiles"];
            T_JSON newProfiles = T_JSON::array();

            for (T_JSON::iterator it = configProfiles.begin(); it != configProfiles.end(); ++it) {
                T_JSON val = it.value();
                if (val["name"].get<T_String>().compare(action->getParameter("name").toStdString()) != 0) {
                    newProfiles.push_back(val);
                }
            }

            config["profiles"] = newProfiles;
            Config::getInstance().setData(config)->save();
            this->renderMenu();
        }
    } else if (action->getParameter("action").compare("upload") == 0) {
        if (this->_wizard_upload == nullptr) {
            this->_wizard_upload = new WizardUpload(this->window(), this->_drone);
            this->_wizard_upload->show();
            this->_wizard_upload->stackUnder(this->window());

            connect(this->_wizard_upload, SIGNAL(finished(int)), this, SLOT(wizardUploadFinished(int)));
        }
    }
}

void MainWindow::wizardUploadFinished(int) {
    delete this->_wizard_upload;
    this->_wizard_upload = nullptr;
}

MainWindow::~MainWindow() {
    delete ui;
}
