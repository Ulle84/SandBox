#-------------------------------------------------
#
# Project created by QtCreator 2016-05-11T08:22:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BackgroundImage
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    MdiAreaBackground.cpp

HEADERS  += MainWindow.h \
    MdiAreaBackground.h

FORMS    += MainWindow.ui

RESOURCES += \
    Resources.qrc
