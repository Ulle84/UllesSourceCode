#-------------------------------------------------
#
# Project created by QtCreator 2016-11-12T20:43:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CircularBuffer
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    CircularBuffer.cpp \
    CircularBufferElement.cpp \
    RingBuffer.cpp

HEADERS  += MainWindow.h \
    CircularBuffer.h \
    CircularBufferElement.h \
    RingBuffer.h

FORMS    += MainWindow.ui
