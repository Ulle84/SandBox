#-------------------------------------------------
#
# Project created by QtCreator 2017-01-29T10:16:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XmlEditor
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    XmlEditor.cpp \
    XmlHighlighter.cpp \
    QColorEx.cpp \
    XmlParser.cpp

HEADERS  += MainWindow.h \
    XmlEditor.h \
    XmlHighlighter.h \
    QColorEx.h \
    XmlParser.h

FORMS    += MainWindow.ui
