#-------------------------------------------------
#
# Project created by QtCreator 2016-01-24T20:20:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DPointer
TEMPLATE = app


SOURCES += main.cpp \
    Base.cpp \
    Derived.cpp

HEADERS  += \
    Base.h \
    Derived.h \
    BasePrivate.h
