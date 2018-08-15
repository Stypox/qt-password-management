#-------------------------------------------------
#
# Project created by QtCreator 2018-07-18T11:44:21
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = password-management
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    src/main.cpp \
    src/win/passwordswindow.cpp \
    src/win/logindialog.cpp \
    src/win/addeditdialog.cpp \
    src/win/settingsdialog.cpp \
    src/res/passwordwidget.cpp \
    src/res/resources.cpp \
    src/res/settings.cpp \
    src/res/password.cpp \
    src/simplecrypt/simplecrypt.cpp \
    src/res/cryptography.cpp \
    src/win/infodialog.cpp \
    src/res/resources_init.cpp

HEADERS += \
    src/win/passwordswindow.h \
    src/win/logindialog.h \
    src/win/addeditdialog.h \
    src/win/settingsdialog.h \
    src/res/passwordwidget.h \
    src/res/resources.h \
    src/res/settings.h \
    src/res/password.h \
    src/simplecrypt/simplecrypt.h \
    src/res/cryptography.h \
    src/win/infodialog.h

FORMS += \
    src/win/passwordswindow.ui \
    src/win/logindialog.ui \
    src/win/addeditdialog.ui \
    src/win/settingsdialog.ui \
    src/win/infodialog.ui

RESOURCES += resources/qdarkstyle/style.qrc

CONFIG += mobility
MOBILITY = 

