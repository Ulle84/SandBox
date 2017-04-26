#-------------------------------------------------
#
# Project created by QtCreator 2015-01-23T19:41:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Observer
TEMPLATE = app


SOURCES += main.cpp\
        ObserverExample.cpp \
    Subject.cpp \
    ObserverA.cpp \
    ObserverB.cpp

HEADERS  += ObserverExample.h \
    IObserver.h \
    ISubject.h \
    Subject.h \
    ObserverA.h \
    ObserverB.h

FORMS    += ObserverExample.ui
