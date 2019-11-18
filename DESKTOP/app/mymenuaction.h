#pragma once
#include "include.h"

class MyMenuAction : public QAction {
   Q_OBJECT
private:
    std::map<QString, QString> _parameters;
public:
    MyMenuAction * setParameter(QString name, QString value) {
        this->_parameters[name] = value;
        return this;
    }
    MyMenuAction * setText(QString text) {
        QAction::setText(text);
        return this;
    }
    QString getParameter(QString name) {
        return this->_parameters[name];
    }
    static MyMenuAction * factory(QWidget *parent) {
        MyMenuAction * instance = new MyMenuAction(parent);
        return instance;
    }
signals:
    void myTriggered(MyMenuAction *, bool triggered);
private slots:
    void emitMyTriggered(bool triggered) {
        emit myTriggered(this, triggered);
    }
public:
    MyMenuAction(QWidget *parent = 0) : QAction(parent) {
        connect(this, SIGNAL(triggered(bool)), this, SLOT(emitMyTriggered(bool)));
    }
};
