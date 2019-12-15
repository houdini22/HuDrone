#pragma once
#include "include.h"

class MyLineEdit : public QLineEdit {
   Q_OBJECT
private:
    QString id;
    std::map<QString, QString> _parameters;
public:
    QString getID() { return id; }
    void setID(QString _id) { id = _id; }
public:
    MyLineEdit * setParameter(QString name, QString value) {
        this->_parameters[name] = value;
        return this;
    }
    QString getParameter(QString name) {
        return this->_parameters[name];
    }
signals:
    void myTextEdited(QString, QString);
    void myTextEdited(MyLineEdit *);
private slots:
    void emitMyTextEdited(QString text) { emit myTextEdited(text, id); emit myTextEdited(this); }
public:
    MyLineEdit(QWidget *parent = 0) : QLineEdit(parent) {
        connect(this, SIGNAL(textEdited(QString)), this, SLOT(emitMyTextEdited(QString)));
    }
};
