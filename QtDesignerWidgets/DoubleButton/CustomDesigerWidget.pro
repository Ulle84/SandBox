CONFIG      += designer plugin debug_and_release
TARGET      = $$qtLibraryTarget(doublebuttonplugin)
TEMPLATE    = lib

HEADERS     = DoubleButtonPlugin.h \
    DoubleButtonTaskMenu.h
SOURCES     = DoubleButtonPlugin.cpp \
    DoubleButtonTaskMenu.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(doublebutton.pri)
