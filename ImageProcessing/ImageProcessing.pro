#-------------------------------------------------
#
# Project created by QtCreator 2015-11-09T07:14:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageProcessing
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    ImageDisplay.cpp \
    Point.cpp \
    Rectangle.cpp \
    Circle.cpp \
    FreemanCode.cpp \
    PolyLine.cpp \
    Image.cpp \
    FilterGenerator.cpp \
    StructuringElementGenerator.cpp \
    RunLengthCode.cpp \
    Edge.cpp \
    Line.cpp \
    MathHelper.cpp \
    Converter.cpp \
    GeometryCodeGenerator.cpp \
    TeachableLine.cpp \
    TeachableRectangle.cpp \
    TeachableCirlce.cpp \
    RectangleRotated.cpp \
    TeachableRectangleRotated.cpp \
    TeachablePolyLine.cpp \
    GraphicsPolyLineItem.cpp

HEADERS  += MainWindow.h \
    ImageDisplay.h \
    Point.h \
    Rectangle.h \
    Circle.h \
    FreemanCode.h \
    PolyLine.h \
    Matrix.h \
    Image.h \
    FilterGenerator.h \
    StructuringElementGenerator.h \
    RunLengthCode.h \
    Edge.h \
    Line.h \
    MathHelper.h \
    Statistics.h \
    Converter.h \
    GeometryCodeGenerator.h \
    Teachable.h \
    TeachableLine.h \
    TeachableRectangle.h \
    TeachableCirlce.h \
    RectangleRotated.h \
    TeachableRectangleRotated.h \
    TeachablePolyLine.h \
    GraphicsPolyLineItem.h

FORMS    += MainWindow.ui \
    ImageDisplay.ui

OTHER_FILES += \
    Notes.md
