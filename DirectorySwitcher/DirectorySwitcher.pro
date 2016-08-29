#-------------------------------------------------
#
# Project created by QtCreator 2016-08-24T10:34:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DirectorySwitcher
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    InfoFile.cpp

HEADERS  += MainWindow.h \
    InfoFile.h

FORMS    += MainWindow.ui

DISTFILES += \
    Notes.md
