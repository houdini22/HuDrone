#pragma once
#include "include.h"

class MyPushButton : public QPushButton {
   Q_OBJECT
private:
    std::map<QString, QString> _parameters;
public:
    MyPushButton * setParameter(QString name, QString value) {
        this->_parameters[name] = value;
        return this;
    }
    MyPushButton * setText(QString text) {
        QPushButton::setText(text);
        return this;
    }
    QString getParameter(QString name) {
        return this->_parameters[name];
    }
    static MyPushButton * factory(QWidget *parent) {
        MyPushButton * instance = new MyPushButton(parent);
        return instance;
    }
signals:
    void myReleased(MyPushButton *);
private slots:
    void emitMyReleased() {
        emit myReleased(this);
    }
public:
    MyPushButton(QWidget *parent = nullptr) : QPushButton(parent) {
        connect(this, SIGNAL(released()), this, SLOT(emitMyReleased()));
    }
};
