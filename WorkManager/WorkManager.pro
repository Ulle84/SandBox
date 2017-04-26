#-------------------------------------------------
#
# Project created by QtCreator 2016-11-06T19:51:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WorkManager
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    ToDoItem.cpp \
    TreeItem.cpp \
    TreeModel.cpp \
    ProxyModel.cpp

HEADERS  += MainWindow.h \
    ToDoItem.h \
    TreeItem.h \
    TreeModel.h \
    ProxyModel.h

FORMS    += MainWindow.ui

DISTFILES += \
    Notes.md
