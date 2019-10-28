#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "include.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->_drone = new Drone(this);
}

void MainWindow::showEvent(QShowEvent *event) {
    this->setup();
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    this->setup();
}

void MainWindow::setup() {

}

MainWindow::~MainWindow() {
    delete ui;
}
