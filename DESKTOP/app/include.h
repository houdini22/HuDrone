#ifndef INCLUDE_H
#define INCLUDE_H

#include <QThread>
#include <QString>
#include <QLabel>
#include <QDebug>
#include <QObject>
#include <QTimer>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QMap>
#include <QHash>
#include <QLineEdit>
#include <QEvent>
#include <QAbstractButton>
#include <QDesktopWidget>
#include <QRect>
#include <QGroupBox>
#include <QMouseEvent>
#include <QRadioButton>
#include <QWizard>
#include <QWizardPage>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include <QtQml>
#include <QtQuick/QQuickView>
#include <QtSerialPort/QSerialPortInfo>
#include <QList>
#include <QApplication>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QSerialPort>
#include <QComboBox>
#include <QGamepadManager>
#include <QGamepad>

#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <chrono>
#include <future>
#include <math.h>
#include <string>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <map>
#include <sstream>
#include <iostream>
#include <dirent.h>
#include <fstream>
#include <stdio.h>
#include <set>

#ifdef WIN32
#include <windows.h>
#include <fileapi.h>
#include <winbase.h>
#endif

#ifndef WIN32
#include "gamepad.h"
#include <sys/stat.h>
#include "experimental/filesystem"
#endif

#include "json.hpp"

#include "mymenuaction.h"
#include "mylineedit.h"
#include "mycombobox.h"

typedef bool T_Bool;
typedef std::string T_String;
typedef nlohmann::json T_JSON;

#include "threadgamepad.h"
#include "buttons.h"
#include "dronemodes.h"
#include "steeringregistry.h"
#include "steering.h"
#include "sendingregistry.h"
#include "sendinginterface.h"
#include "sendingarduino.h"
//#include "threadarduinoping.h"
#include "threadarduinosend.h"
#include "threadgamepadupdate.h"
#include "steering.h"
#include "dialogeditprofile.h"
#include "serialportutilities.h"
#include "threadboxconnect.h"
#include "filesystem.h"
#include "config.h"
#include "receivers.h"
#include "dialogfly.h"
#include "drone.h"
#include "tabseditprofilegeneraltab.h"
#include "tabseditprofile.h"
#include "wizardconfiggeneralchanneltab.h"
#include "wizardconfigchanneltabs.h"
#include "wizardaddprofilepage1.h"
#include "wizardaddprofilepage2.h"
#include "wizardaddprofilepage3.h"
#include "wizardaddprofilepage4.h"
#include "wizardaddprofilepage5.h"
#include "wizardaddprofilepage6.h"
#include "wizardaddprofilepage7.h"
#include "wizardaddprofilepage8.h"
#include "wizardaddprofile.h"
#include "wizarduploadpage1.h"
#include "wizarduploadpage2.h"
#include "wizarduploadpage3.h"
#include "wizarduploadpage4.h"
#include "wizardupload.h"

#endif // INCLUDE_H
