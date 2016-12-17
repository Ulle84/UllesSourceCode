#-------------------------------------------------
#
# Project created by QtCreator 2016-12-17T10:55:26
#
#-------------------------------------------------

QT       += core gui uitools

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GuiStyleTester
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    PathSelector.cpp

HEADERS  += MainWindow.h \
    PathSelector.h

FORMS    += MainWindow.ui \
    PathSelector.ui

DISTFILES += \
    Style.css
