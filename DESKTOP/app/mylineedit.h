#pragma once
#include "include.h"

class MyLineEdit : public QLineEdit
{
   Q_OBJECT
private:
    QString id;
public:
    QString getID() { return id; }
    void setID(QString _id) { id = _id; }
signals:
    void myTextEdited(QString, QString);
private slots:
    void emitMyTextEdited(QString text) { emit myTextEdited(text, id); }
public:
    MyLineEdit(QWidget *parent = 0) : QLineEdit(parent) {
        connect(this, SIGNAL(textEdited(QString)), this, SLOT(emitMyTextEdited(QString)));
    }
};
