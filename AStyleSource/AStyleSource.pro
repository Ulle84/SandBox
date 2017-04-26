QT += core
QT -= gui

CONFIG += c++11

TARGET = AStyleSource
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    ASBeautifier.cpp \
    ASEnhancer.cpp \
    ASFormatter.cpp \
    ASLocalizer.cpp \
    ASResource.cpp \
    astyle_main.cpp

HEADERS += \
    ASLocalizer.h \
    astyle.h \
    astyle_main.h
