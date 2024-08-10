QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

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
    ../../../Controlers/ControlerAbstractBase.cpp \
    ../../../Controlers/Controler_QT/controler_qt.cpp \
    ../../../Models/Administrator.cpp \
    ../../../Models/CipherText.cpp \
    ../../../Models/Date.cpp \
    ../../../Models/DateTime.cpp \
    ../../../Models/MD5.cpp \
    ../../../Models/Message.cpp \
    ../../../Models/Time.cpp \
    ../../../Models/User.cpp \
    adminwindow.cpp \
    main.cpp \
    loginwindow.cpp \
    userwindow.cpp

HEADERS += \
    ../../../Controlers/ControlerAbstractBase.hpp \
    ../../../Controlers/Controler_QT/controler_qt.h \
    ../../../Models/Administrator.hpp \
    ../../../Models/CipherText.hpp \
    ../../../Models/Date.hpp \
    ../../../Models/DateTime.hpp \
    ../../../Models/MD5.hpp \
    ../../../Models/Message.hpp \
    ../../../Models/Time.hpp \
    ../../../Models/User.hpp \
    adminwindow.h \
    loginwindow.h \
    userwindow.h

FORMS += \
    adminwindow.ui \
    loginwindow.ui \
    userwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
