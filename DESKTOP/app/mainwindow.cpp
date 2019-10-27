#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "include.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->_drone = new Drone(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

