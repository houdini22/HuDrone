#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "include.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setFixedSize(width(), height());

    this->_drone = new Drone(this);
    connect(this->_drone, SIGNAL(configurationChanged()), this, SLOT(configurationChanged()));

    this->renderMenu();
}

void MainWindow::configurationChanged() {
    this->renderMenu();
}

void MainWindow::slotAddProfileTriggered(bool) {
    this->_drone->openWizardAddProfile();
}

void MainWindow::renderMenu() {
    disconnect(this, SLOT(profileItemTriggered(MyMenuAction*, bool)));
    disconnect(this, SLOT(slotAddProfileTriggered(bool)));

    // profiles main menu
    QMenu * menuProfiles = this->menuWidget()->findChild<QMenu *>("menuProfiles");
    menuProfiles->clear();

    // new profile
    MyMenuAction * menuProfiles_newProfileAction = MyMenuAction::factory(menuProfiles)
            ->setText("New profile...")
            ->setParameter("action", "newProfile");
    connect(menuProfiles_newProfileAction, SIGNAL(myTriggered(MyMenuAction *, bool)), this, SLOT(profileItemTriggered(MyMenuAction *, bool)));
    menuProfiles->addAction(menuProfiles_newProfileAction);

    menuProfiles->addSeparator();

    QMenu * menuProfiles__profilesAll = new QMenu(menuProfiles);
    menuProfiles__profilesAll->setTitle("Profiles");
    menuProfiles->addMenu(menuProfiles__profilesAll);

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

        menuProfiles__profilesAll->addMenu(profileMenu);
    }
}

void MainWindow::profileItemTriggered(MyMenuAction * action, bool) {
    if (action->getParameter("action").compare("delete") == 0) {
        if (QMessageBox::question(this, "Confirm", "Are you sure to delete profile \"" + action->getParameter("name") + "\"?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
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
        this->_drone->openWizardUpload();
    } else if (action->getParameter("action").compare("edit") == 0) {
        this->_drone->openDialogEditProfile(action->getParameter("name"));
    } else if (action->getParameter("action").compare("newProfile") == 0) {
        this->_drone->openWizardAddProfile();
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
