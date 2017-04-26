QT += core
QT -= gui

CONFIG += c++11

TARGET = AbstractFactoryExample
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    BurgerKing.cpp \
    BurgerKingCheeseburger.cpp \
    BurgerKingFries.cpp \
    MacDonald.cpp \
    MacDonaldCheeseburger.cpp \
    MacDonaldFries.cpp

HEADERS += \
    BurgerKing.h \
    BurgerKingCheeseburger.h \
    BurgerKingFries.h \
    BurgerShopI.h \
    CheeseburgerI.h \
    FriesI.h \
    MacDonald.h \
    MacDonaldCheeseburger.h \
    MacDonaldFries.h
