#include "include.h"

DialogEditProfile::DialogEditProfile(QWidget *parent, QString name) : QDialog(parent) {
    setWindowTitle(QString("Edit profile: '" + name + "'"));

    this->setWindowFlag(Qt::WindowSystemMenuHint, false);
    this->setWindowFlag(Qt::WindowContextHelpButtonHint, false);
}
