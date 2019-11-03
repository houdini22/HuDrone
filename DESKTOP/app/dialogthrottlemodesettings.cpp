#include "dialogthrottlemodesettings.h"
#include "ui_dialogthrottlemodesettings.h"
#include "include.h"

DialogThrottleModeSettings::DialogThrottleModeSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogThrottleModeSettings)
{
    ui->setupUi(this);

    QDialogButtonBox * buttonBox = this->findChild<QDialogButtonBox *>(QString("buttonBox"));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(signalAccepted()));

    QLineEdit * inputStep = this->findChild<QLineEdit *>(QString("inputStep"));

    inputStep->setText(QString::number((int) 25));
    inputStep->setValidator( new QIntValidator(0, 2000, this));
  }

void DialogThrottleModeSettings::signalAccepted() {
    QLineEdit * inputStep = this->findChild<QLineEdit *>(QString("inputStep"));
}

DialogThrottleModeSettings::~DialogThrottleModeSettings() {
    delete ui;
}
