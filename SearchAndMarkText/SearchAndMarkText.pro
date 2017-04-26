#-------------------------------------------------
#
# Project created by QtCreator 2017-01-28T06:57:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SearchAndMarkText
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    SearchableTextEdit.cpp

HEADERS  += MainWindow.h \
    SearchableTextEdit.h

FORMS    += MainWindow.ui \
    SearchableTextEdit.ui
