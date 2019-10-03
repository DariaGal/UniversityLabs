#-------------------------------------------------
#
# Project created by QtCreator 2016-06-03T17:20:12
#
#-------------------------------------------------

QT       += core gui
QT       += xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = writexml
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    saxparser.cpp \
    writexml.cpp

HEADERS  += mainwindow.h \
    saxparser.h \
    writexml.h

FORMS    += mainwindow.ui
