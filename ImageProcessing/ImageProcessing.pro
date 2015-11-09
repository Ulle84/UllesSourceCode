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
    ImageDisplay.cpp

HEADERS  += MainWindow.h \
    Image.h \
    ImageDisplay.h

FORMS    += MainWindow.ui \
    ImageDisplay.ui
