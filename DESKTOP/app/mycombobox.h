#pragma once
#include "include.h"

class MyComboBox : public QComboBox
{
   Q_OBJECT
private:
    int _channel_number = 0;
public:
    void setChannelNumber(int nb) { _channel_number = nb; }
    static MyComboBox * factory(QStringList items, int channelNumber) {
        MyComboBox * instance = new MyComboBox;
        instance->addItems(items);
        instance->setChannelNumber(channelNumber);
        return instance;
    }
    MyComboBox(QWidget *parent = 0) : QComboBox(parent) {
        connect(this, SIGNAL(currentTextChanged(QString)), this, SLOT(emitMyTextChanged(QString)));
    }
signals:
    void myTextChanged(QString, int);
private slots:
    void emitMyTextChanged(QString text) { emit myTextChanged(text, _channel_number); }
};
