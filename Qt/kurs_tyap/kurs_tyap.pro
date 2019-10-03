#-------------------------------------------------
#
# Project created by QtCreator 2016-12-13T11:35:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
TARGET = kurs_tyap
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    grammarconverter.cpp \
    stringsgenerator.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    grammarconverter.h \
    stringsgenerator.h \
    dialog.h

FORMS    += mainwindow.ui \
    dialog.ui
