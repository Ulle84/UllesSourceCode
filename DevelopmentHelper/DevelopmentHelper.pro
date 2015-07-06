#-------------------------------------------------
#
# Project created by QtCreator 2015-07-02T17:00:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DevelopmentHelper
TEMPLATE = app


SOURCES += main.cpp\
        DevelopmentHelper.cpp \
    StashHelper.cpp \
    LogFileViewer.cpp

HEADERS  += DevelopmentHelper.h \
    StashHelper.h \
    LogFileViewer.h

FORMS    += DevelopmentHelper.ui \
    StashHelper.ui \
    LogFileViewer.ui
