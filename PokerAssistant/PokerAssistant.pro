#-------------------------------------------------
#
# Project created by QtCreator 2016-10-07T20:42:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PokerAssistant
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    HandHistory.cpp \
    Hand.cpp \
    Card.cpp \
    Action.cpp

HEADERS  += MainWindow.h \
    HandHistory.h \
    Hand.h \
    Card.h \
    Action.h \
    Phase.h

FORMS    += MainWindow.ui

DISTFILES += \
    Notes.md
