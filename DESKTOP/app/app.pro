QT       += core gui serialport qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialogeditprofile.cpp \
    dialogflywindow.cpp \
    drone.cpp \
    main.cpp \
    mainwindow.cpp \
    tabseditprofile.cpp \
    tabseditprofilegeneraltab.cpp \
    threadboxconnect.cpp \
    SerialPort.cpp \
    wizardaddprofile.cpp \
    wizardaddprofilepage1.cpp \
    wizardaddprofilepage2.cpp \
    wizardaddprofilepage3.cpp \
    wizardaddprofilepage4.cpp \
    wizardaddprofilepage5.cpp \
    wizardaddprofilepage6.cpp \
    wizardaddprofilepage7.cpp \
    wizardconfigchanneltabs.cpp \
    wizardconfiggeneralchanneltab.cpp \
    wizardupload.cpp \
    wizarduploadpage1.cpp \
    wizarduploadpage2.cpp \
    wizarduploadpage3.cpp \
    wizarduploadpage4.cpp

HEADERS += \
    config.h \
    dialogeditprofile.h \
    dialogflywindow.h \
    drone.h \
    filesystem.h \
    include.h \
    mainwindow.h \
    mylineedit.h \
    mymenuaction.h \
    receivers.h \
    serialportutilities.h \
    tabseditprofile.h \
    tabseditprofilegeneraltab.h \
    threadboxconnect.h \
    SerialPort.h \
    wizardaddprofile.h \
    wizardaddprofilepage1.h \
    wizardaddprofilepage2.h \
    wizardaddprofilepage3.h \
    wizardaddprofilepage4.h \
    wizardaddprofilepage5.h \
    wizardaddprofilepage6.h \
    wizardaddprofilepage7.h \
    wizardconfigchanneltabs.h \
    wizardconfiggeneralchanneltab.h \
    wizardupload.h \
    wizarduploadpage1.h \
    wizarduploadpage2.h \
    wizarduploadpage3.h \
    wizarduploadpage4.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
