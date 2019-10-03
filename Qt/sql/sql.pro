#-------------------------------------------------
#
# Project created by QtCreator 2016-03-31T19:12:34
#
#-------------------------------------------------

QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sql
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    changepswd.cpp \
    addnewuser.cpp \
    forgotpassword.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    crypter.h \
    changepswd.h \
    addnewuser.h \
    forgotpassword.h

FORMS    += mainwindow.ui \
    dialog.ui \
    changepswd.ui \
    addnewuser.ui \
    forgotpassword.ui

RESOURCES += \
    res.qrc
