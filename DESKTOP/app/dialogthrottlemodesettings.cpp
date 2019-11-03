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

    nlohmann::json data = Storage::getInstance().getData();

    QLineEdit * inputStep = this->findChild<QLineEdit *>(QString("inputStep"));

    inputStep->setText(QString::number((int) data["throttleMode"]["step"].get<int>()));
    inputStep->setValidator( new QIntValidator(0, 2000, this));
  }

void DialogThrottleModeSettings::signalAccepted() {
    QLineEdit * inputStep = this->findChild<QLineEdit *>(QString("inputStep"));
    nlohmann::json data = Storage::getInstance().getData();

    int step = std::atoi(inputStep->text().toStdString().c_str());
    data["throttleMode"]["step"] = step;

    Storage::getInstance().setData(data)->save();
}

DialogThrottleModeSettings::~DialogThrottleModeSettings() {
    delete ui;
}
