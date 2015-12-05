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
    FilterCreator.cpp

HEADERS  += MainWindow.h \
    ImageDisplay.h \
    Point.h \
    Rectangle.h \
    Circle.h \
    FreemanCode.h \
    PolyLine.h \
    Matrix.h \
    Image.h \
    FilterCreator.h

FORMS    += MainWindow.ui \
    ImageDisplay.ui

OTHER_FILES += \
    Notes.md
