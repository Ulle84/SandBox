QT += core
QT -= gui

CONFIG += c++11

TARGET = AbstractFactory
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ConcreteFactory1.cpp \
    ConcreteFactory2.cpp \
    ProductA1.cpp \
    ProductA2.cpp \
    ProductB1.cpp \
    ProductB2.cpp

HEADERS += \
    AbstractFactoryI.h \
    AbstractProductAI.h \
    AbstractProductBI.h \
    ConcreteFactory1.h \
    ConcreteFactory2.h \
    ProductA1.h \
    ProductA2.h \
    ProductB1.h \
    ProductB2.h
