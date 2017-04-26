#-------------------------------------------------
#
# Project created by QtCreator 2015-01-23T20:28:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Decorator
TEMPLATE = app


SOURCES += main.cpp\
        DecoratorExample.cpp \
    Decorator.cpp \
    Component.cpp \
    DecoratorA.cpp \
    DecoratorB.cpp

HEADERS  += DecoratorExample.h \
    Decorator.h \
    IComponent.h \
    Component.h \
    DecoratorA.h \
    DecoratorB.h

FORMS    += DecoratorExample.ui
