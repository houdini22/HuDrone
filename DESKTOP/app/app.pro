QT       += core gui serialport qml gamepad

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

#LIBS += -ludev
LIBS += -lstdc++fs

SOURCES += \
    ui/dialogeditprofile.cpp \
    ui/dialogfly.cpp \
    drone.cpp \
    main.cpp \
    mainwindow.cpp \
    profile.cpp \
    receivers.cpp \
    sendingarduino.cpp \
    sendinginterface.cpp \
    sendingregistry.cpp \
    steering.cpp \
    steeringregistry.cpp \
    tabseditprofile.cpp \
    tabseditprofilegeneraltab.cpp \
    threadarduinosend.cpp \
    threadboxconnect.cpp \
    ui/wizardaddprofile.cpp \
    ui/wizardaddprofilepage1.cpp \
    ui/wizardaddprofilepage2.cpp \
    ui/wizardaddprofilepage3.cpp \
    ui/wizardaddprofilepage4.cpp \
    ui/wizardaddprofilepage5.cpp \
    ui/wizardaddprofilepage6.cpp \
    ui/wizardaddprofilepage7.cpp \
    ui/wizardaddprofilepage8.cpp \
    ui/wizardconfigchanneltabs.cpp \
    ui/wizardconfiggeneralchanneltab.cpp \
    ui/wizardupload.cpp \
    ui/wizarduploadpage1.cpp \
    ui/wizarduploadpage2.cpp \
    ui/wizarduploadpage3.cpp \
    ui/wizarduploadpage4.cpp

HEADERS += \
    buttons.h \
    config.h \
    drone.h \
    dronemodes.h \
    filesystem.h \
    include.h \
    json.hpp \
    mainwindow.h \
    mycombobox.h \
    mylineedit.h \
    mymenuaction.h \
    profile.h \
    receivers.h \
    sendingarduino.h \
    sendinginterface.h \
    sendingregistry.h \
    serialportutilities.h \
    steering.h \
    steeringregistry.h \
    tabseditprofile.h \
    tabseditprofilegeneraltab.h \
    threadarduinosend.h \
    threadboxconnect.h \
    ui/dialogeditprofile.h \
    ui/dialogfly.h \
    ui/wizardaddprofile.h \
    ui/wizardaddprofilepage1.h \
    ui/wizardaddprofilepage2.h \
    ui/wizardaddprofilepage3.h \
    ui/wizardaddprofilepage4.h \
    ui/wizardaddprofilepage5.h \
    ui/wizardaddprofilepage6.h \
    ui/wizardaddprofilepage7.h \
    ui/wizardaddprofilepage8.h \
    ui/wizardconfigchanneltabs.h \
    ui/wizardconfiggeneralchanneltab.h \
    ui/wizardupload.h \
    ui/wizarduploadpage1.h \
    ui/wizarduploadpage2.h \
    ui/wizarduploadpage3.h \
    ui/wizarduploadpage4.h

FORMS += \
    dialogfly.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
