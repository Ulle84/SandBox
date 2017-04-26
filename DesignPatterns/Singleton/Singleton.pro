#-------------------------------------------------
#
# Project created by QtCreator 2015-01-23T19:20:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Singleton
TEMPLATE = app


SOURCES += main.cpp\
        Singleton.cpp \
    SingletonEager.cpp

HEADERS  += Singleton.h \
    SingletonEager.h

FORMS    += Singleton.ui
