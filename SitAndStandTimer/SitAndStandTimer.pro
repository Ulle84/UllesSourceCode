#-------------------------------------------------
#
# Project created by QtCreator 2016-10-28T19:53:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SitAndStandTimer
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    TimerDoneDialog.cpp

HEADERS  += MainWindow.h \
    TimerDoneDialog.h

FORMS    += MainWindow.ui \
    TimerDoneDialog.ui
