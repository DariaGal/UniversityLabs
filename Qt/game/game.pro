#-------------------------------------------------
#
# Project created by QtCreator 2016-05-13T16:46:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = game
TEMPLATE = app


SOURCES += main.cpp\
        game.cpp \
    peg.cpp \
    hole.cpp

HEADERS  += game.h \
    peg.h \
    hole.h

FORMS    += game.ui
