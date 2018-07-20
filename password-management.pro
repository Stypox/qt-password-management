#-------------------------------------------------
#
# Project created by QtCreator 2018-07-18T11:44:21
#
#-------------------------------------------------

QT       += core gui

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
        main.cpp \
        passwordswindow.cpp \
    simplecrypt/simplecrypt.cpp \
    passwordwidget.cpp \
    logindialog.cpp \
    addeditdialog.cpp \
    helpdialog.cpp \
    settingsdialog.cpp \
    pwneddialog.cpp \
    settings.cpp \
    password.cpp

HEADERS += \
        passwordswindow.h \
    simplecrypt/simplecrypt.h \
    passwordwidget.h \
    logindialog.h \
    addeditdialog.h \
    helpdialog.h \
    settingsdialog.h \
    pwneddialog.h \
    resources.h \
    settings.h \
    password.h

FORMS += \
        passwordswindow.ui \
    logindialog.ui \
    addeditdialog.ui \
    helpdialog.ui \
    settingsdialog.ui \
    pwneddialog.ui

CONFIG += mobility
MOBILITY = 

