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
    Image.cpp \
    ImageDisplay.cpp \
    Point.cpp \
    Rectangle.cpp \
    Circle.cpp \
    FilterMask.cpp \
    ImageT.cpp \
    FreemanCode.cpp \
    PolyLine.cpp \
    Histogram.cpp \
    LookUpTable.cpp

HEADERS  += MainWindow.h \
    Image.h \
    ImageDisplay.h \
    Point.h \
    Rectangle.h \
    Circle.h \
    FilterMask.h \
    ImageT.h \
    FreemanCode.h \
    PolyLine.h \
    Histogram.h \
    LookUpTable.h

FORMS    += MainWindow.ui \
    ImageDisplay.ui

OTHER_FILES += \
    ToDo.txt

DISTFILES += \
    Notes.md
