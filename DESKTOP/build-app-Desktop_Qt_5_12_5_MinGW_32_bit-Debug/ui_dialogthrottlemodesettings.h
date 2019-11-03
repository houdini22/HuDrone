/********************************************************************************
** Form generated from reading UI file 'dialogthrottlemodesettings.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGTHROTTLEMODESETTINGS_H
#define UI_DIALOGTHROTTLEMODESETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_DialogThrottleModeSettings
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QLineEdit *inputStep;

    void setupUi(QDialog *DialogThrottleModeSettings)
    {
        if (DialogThrottleModeSettings->objectName().isEmpty())
            DialogThrottleModeSettings->setObjectName(QString::fromUtf8("DialogThrottleModeSettings"));
        DialogThrottleModeSettings->resize(460, 151);
        buttonBox = new QDialogButtonBox(DialogThrottleModeSettings);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(110, 110, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox = new QGroupBox(DialogThrottleModeSettings);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 441, 91));
        inputStep = new QLineEdit(groupBox);
        inputStep->setObjectName(QString::fromUtf8("inputStep"));
        inputStep->setGeometry(QRect(170, 40, 101, 32));

        retranslateUi(DialogThrottleModeSettings);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogThrottleModeSettings, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogThrottleModeSettings, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogThrottleModeSettings);
    } // setupUi

    void retranslateUi(QDialog *DialogThrottleModeSettings)
    {
        DialogThrottleModeSettings->setWindowTitle(QApplication::translate("DialogThrottleModeSettings", "Dialog", nullptr));
        groupBox->setTitle(QApplication::translate("DialogThrottleModeSettings", "Step", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogThrottleModeSettings: public Ui_DialogThrottleModeSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGTHROTTLEMODESETTINGS_H
