#-------------------------------------------------
#
# Project created by QtCreator 2016-11-10T14:57:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = poker2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    player.cpp

HEADERS  += mainwindow.h \
    player.h \
    lab1.h

FORMS    += mainwindow.ui

RESOURCES += \
    img/kards.qrc
