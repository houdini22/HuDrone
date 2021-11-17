/********************************************************************************
** Form generated from reading UI file 'dialogfly.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGFLY_H
#define UI_DIALOGFLY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogFly
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_2;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *labelDeviceGamepad1;
    QLabel *labelDeviceGamepad0;
    QLabel *labelDeviceHudroneBox;
    QGroupBox *groupBox;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *labelLeftX;
    QLabel *labelLeftY;
    QLabel *labelRightX;
    QLabel *labelRightY;
    QLabel *label_10;
    QLabel *labelOther3;
    QLabel *labelOther2;
    QLabel *labelOther4;
    QLabel *labelOther1;
    QLabel *labelLeftY_3;
    QLabel *labelLeftY_4;
    QLabel *labelLeftY_5;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox_3;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *labelThrottleLevel_2;
    QLabel *labelRadioSending;
    QLabel *label_11;
    QLabel *labelMotorsArmed;
    QLabel *labelThrottleModeActive;
    QLabel *labelThrottleLevel;
    QLabel *label_15;
    QLabel *labelButtonsLevel;

    void setupUi(QDialog *DialogFly)
    {
        if (DialogFly->objectName().isEmpty())
            DialogFly->setObjectName(QString::fromUtf8("DialogFly"));
        DialogFly->resize(800, 688);
        horizontalLayoutWidget = new QWidget(DialogFly);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 781, 101));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(horizontalLayoutWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 141, 16));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 60, 141, 16));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 40, 141, 16));
        labelDeviceGamepad1 = new QLabel(groupBox_2);
        labelDeviceGamepad1->setObjectName(QString::fromUtf8("labelDeviceGamepad1"));
        labelDeviceGamepad1->setEnabled(false);
        labelDeviceGamepad1->setGeometry(QRect(250, 60, 131, 16));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        labelDeviceGamepad1->setFont(font);
        labelDeviceGamepad1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelDeviceGamepad0 = new QLabel(groupBox_2);
        labelDeviceGamepad0->setObjectName(QString::fromUtf8("labelDeviceGamepad0"));
        labelDeviceGamepad0->setEnabled(false);
        labelDeviceGamepad0->setGeometry(QRect(250, 40, 131, 16));
        labelDeviceGamepad0->setFont(font);
        labelDeviceGamepad0->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelDeviceHudroneBox = new QLabel(groupBox_2);
        labelDeviceHudroneBox->setObjectName(QString::fromUtf8("labelDeviceHudroneBox"));
        labelDeviceHudroneBox->setEnabled(false);
        labelDeviceHudroneBox->setGeometry(QRect(250, 20, 131, 16));
        labelDeviceHudroneBox->setFont(font);
        labelDeviceHudroneBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(groupBox_2);

        groupBox = new QGroupBox(horizontalLayoutWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 20, 47, 14));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 40, 47, 14));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(330, 20, 47, 14));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(330, 40, 47, 14));
        labelLeftX = new QLabel(groupBox);
        labelLeftX->setObjectName(QString::fromUtf8("labelLeftX"));
        labelLeftX->setGeometry(QRect(140, 20, 47, 14));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        labelLeftX->setFont(font1);
        labelLeftX->setAlignment(Qt::AlignCenter);
        labelLeftY = new QLabel(groupBox);
        labelLeftY->setObjectName(QString::fromUtf8("labelLeftY"));
        labelLeftY->setGeometry(QRect(140, 40, 47, 14));
        labelLeftY->setFont(font1);
        labelLeftY->setAlignment(Qt::AlignCenter);
        labelRightX = new QLabel(groupBox);
        labelRightX->setObjectName(QString::fromUtf8("labelRightX"));
        labelRightX->setGeometry(QRect(200, 20, 47, 14));
        labelRightX->setFont(font1);
        labelRightX->setAlignment(Qt::AlignCenter);
        labelRightY = new QLabel(groupBox);
        labelRightY->setObjectName(QString::fromUtf8("labelRightY"));
        labelRightY->setGeometry(QRect(200, 40, 47, 14));
        labelRightY->setFont(font1);
        labelRightY->setAlignment(Qt::AlignCenter);
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 60, 47, 14));
        labelOther3 = new QLabel(groupBox);
        labelOther3->setObjectName(QString::fromUtf8("labelOther3"));
        labelOther3->setGeometry(QRect(10, 80, 47, 14));
        labelOther2 = new QLabel(groupBox);
        labelOther2->setObjectName(QString::fromUtf8("labelOther2"));
        labelOther2->setGeometry(QRect(330, 60, 47, 14));
        labelOther4 = new QLabel(groupBox);
        labelOther4->setObjectName(QString::fromUtf8("labelOther4"));
        labelOther4->setGeometry(QRect(330, 80, 47, 14));
        labelOther1 = new QLabel(groupBox);
        labelOther1->setObjectName(QString::fromUtf8("labelOther1"));
        labelOther1->setGeometry(QRect(140, 60, 47, 14));
        labelOther1->setAlignment(Qt::AlignCenter);
        labelLeftY_3 = new QLabel(groupBox);
        labelLeftY_3->setObjectName(QString::fromUtf8("labelLeftY_3"));
        labelLeftY_3->setGeometry(QRect(140, 80, 47, 14));
        labelLeftY_3->setAlignment(Qt::AlignCenter);
        labelLeftY_4 = new QLabel(groupBox);
        labelLeftY_4->setObjectName(QString::fromUtf8("labelLeftY_4"));
        labelLeftY_4->setGeometry(QRect(200, 60, 47, 14));
        labelLeftY_4->setAlignment(Qt::AlignCenter);
        labelLeftY_5 = new QLabel(groupBox);
        labelLeftY_5->setObjectName(QString::fromUtf8("labelLeftY_5"));
        labelLeftY_5->setGeometry(QRect(200, 80, 47, 14));
        labelLeftY_5->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(groupBox);

        horizontalLayoutWidget_2 = new QWidget(DialogFly);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(10, 120, 391, 131));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        groupBox_3 = new QGroupBox(horizontalLayoutWidget_2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 40, 141, 16));
        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 60, 141, 16));
        labelThrottleLevel_2 = new QLabel(groupBox_3);
        labelThrottleLevel_2->setObjectName(QString::fromUtf8("labelThrottleLevel_2"));
        labelThrottleLevel_2->setGeometry(QRect(10, 80, 141, 16));
        labelRadioSending = new QLabel(groupBox_3);
        labelRadioSending->setObjectName(QString::fromUtf8("labelRadioSending"));
        labelRadioSending->setEnabled(true);
        labelRadioSending->setGeometry(QRect(250, 20, 131, 16));
        labelRadioSending->setFont(font);
        labelRadioSending->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 20, 141, 16));
        labelMotorsArmed = new QLabel(groupBox_3);
        labelMotorsArmed->setObjectName(QString::fromUtf8("labelMotorsArmed"));
        labelMotorsArmed->setEnabled(true);
        labelMotorsArmed->setGeometry(QRect(250, 40, 131, 16));
        labelMotorsArmed->setFont(font);
        labelMotorsArmed->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelThrottleModeActive = new QLabel(groupBox_3);
        labelThrottleModeActive->setObjectName(QString::fromUtf8("labelThrottleModeActive"));
        labelThrottleModeActive->setEnabled(true);
        labelThrottleModeActive->setGeometry(QRect(250, 60, 131, 16));
        labelThrottleModeActive->setFont(font);
        labelThrottleModeActive->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelThrottleLevel = new QLabel(groupBox_3);
        labelThrottleLevel->setObjectName(QString::fromUtf8("labelThrottleLevel"));
        labelThrottleLevel->setEnabled(true);
        labelThrottleLevel->setGeometry(QRect(250, 80, 131, 16));
        labelThrottleLevel->setFont(font);
        labelThrottleLevel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_15 = new QLabel(groupBox_3);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(10, 100, 141, 16));
        labelButtonsLevel = new QLabel(groupBox_3);
        labelButtonsLevel->setObjectName(QString::fromUtf8("labelButtonsLevel"));
        labelButtonsLevel->setEnabled(true);
        labelButtonsLevel->setGeometry(QRect(250, 100, 131, 16));
        labelButtonsLevel->setFont(font);
        labelButtonsLevel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(groupBox_3);


        retranslateUi(DialogFly);

        QMetaObject::connectSlotsByName(DialogFly);
    } // setupUi

    void retranslateUi(QDialog *DialogFly)
    {
        DialogFly->setWindowTitle(QCoreApplication::translate("DialogFly", "Dialog", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("DialogFly", "Devices", nullptr));
        label->setText(QCoreApplication::translate("DialogFly", "HuDrone\342\204\242 Box", nullptr));
        label_3->setText(QCoreApplication::translate("DialogFly", "Gamepad 2", nullptr));
        label_2->setText(QCoreApplication::translate("DialogFly", "Gamepad 1", nullptr));
        labelDeviceGamepad1->setText(QCoreApplication::translate("DialogFly", "connect...", nullptr));
        labelDeviceGamepad0->setText(QCoreApplication::translate("DialogFly", "connect...", nullptr));
        labelDeviceHudroneBox->setText(QCoreApplication::translate("DialogFly", "connect...", nullptr));
        groupBox->setTitle(QCoreApplication::translate("DialogFly", "Radio", nullptr));
        label_4->setText(QCoreApplication::translate("DialogFly", "Left X", nullptr));
        label_5->setText(QCoreApplication::translate("DialogFly", "Left Y", nullptr));
        label_6->setText(QCoreApplication::translate("DialogFly", "Right X", nullptr));
        label_7->setText(QCoreApplication::translate("DialogFly", "Right Y", nullptr));
        labelLeftX->setText(QCoreApplication::translate("DialogFly", "0", nullptr));
        labelLeftY->setText(QCoreApplication::translate("DialogFly", "0", nullptr));
        labelRightX->setText(QCoreApplication::translate("DialogFly", "0", nullptr));
        labelRightY->setText(QCoreApplication::translate("DialogFly", "0", nullptr));
        label_10->setText(QCoreApplication::translate("DialogFly", "Other 1", nullptr));
        labelOther3->setText(QCoreApplication::translate("DialogFly", "Other 3", nullptr));
        labelOther2->setText(QCoreApplication::translate("DialogFly", "Other 2", nullptr));
        labelOther4->setText(QCoreApplication::translate("DialogFly", "Other 4", nullptr));
        labelOther1->setText(QCoreApplication::translate("DialogFly", "0", nullptr));
        labelLeftY_3->setText(QCoreApplication::translate("DialogFly", "0", nullptr));
        labelLeftY_4->setText(QCoreApplication::translate("DialogFly", "0", nullptr));
        labelLeftY_5->setText(QCoreApplication::translate("DialogFly", "0", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("DialogFly", "Drone", nullptr));
        label_8->setText(QCoreApplication::translate("DialogFly", "Motors armed", nullptr));
        label_9->setText(QCoreApplication::translate("DialogFly", "Throttle mode", nullptr));
        labelThrottleLevel_2->setText(QCoreApplication::translate("DialogFly", "Throttle level", nullptr));
        labelRadioSending->setText(QCoreApplication::translate("DialogFly", "no", nullptr));
        label_11->setText(QCoreApplication::translate("DialogFly", "Radio sending", nullptr));
        labelMotorsArmed->setText(QCoreApplication::translate("DialogFly", "disarmed", nullptr));
        labelThrottleModeActive->setText(QCoreApplication::translate("DialogFly", "no", nullptr));
        labelThrottleLevel->setText(QCoreApplication::translate("DialogFly", "0%", nullptr));
        label_15->setText(QCoreApplication::translate("DialogFly", "Buttons level", nullptr));
        labelButtonsLevel->setText(QCoreApplication::translate("DialogFly", "0%", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogFly: public Ui_DialogFly {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGFLY_H
