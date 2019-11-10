/********************************************************************************
** Form generated from reading UI file 'dialogfly.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGFLY_H
#define UI_DIALOGFLY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_DialogFly
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *labelDeviceHudroneBox;

    void setupUi(QDialog *DialogFly)
    {
        if (DialogFly->objectName().isEmpty())
            DialogFly->setObjectName(QString::fromUtf8("DialogFly"));
        DialogFly->resize(800, 688);
        groupBox = new QGroupBox(DialogFly);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 291, 231));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 30, 141, 16));
        labelDeviceHudroneBox = new QLabel(groupBox);
        labelDeviceHudroneBox->setObjectName(QString::fromUtf8("labelDeviceHudroneBox"));
        labelDeviceHudroneBox->setGeometry(QRect(150, 30, 131, 16));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        labelDeviceHudroneBox->setFont(font);
        labelDeviceHudroneBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        retranslateUi(DialogFly);

        QMetaObject::connectSlotsByName(DialogFly);
    } // setupUi

    void retranslateUi(QDialog *DialogFly)
    {
        DialogFly->setWindowTitle(QApplication::translate("DialogFly", "Dialog", nullptr));
        groupBox->setTitle(QApplication::translate("DialogFly", "Devices", nullptr));
        label->setText(QApplication::translate("DialogFly", "HuDrone\342\204\242 Box", nullptr));
        labelDeviceHudroneBox->setText(QApplication::translate("DialogFly", "connect", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogFly: public Ui_DialogFly {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGFLY_H
