#-------------------------------------------------
#
# Project created by QtCreator 2016-07-11T11:39:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ClassAnalyzer
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    ClassAnalyzer.cpp \
    Class.cpp \
    Namespace.cpp

HEADERS  += MainWindow.h \
    ClassAnalyzer.h \
    Class.h \
    Namespace.h

FORMS    += MainWindow.ui

DISTFILES += \
    Notes.md
