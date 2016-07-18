#-------------------------------------------------
#
# Project created by QtCreator 2016-07-18T20:43:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CodeCreatorTest
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Observer.cpp \
    Subject.cpp

HEADERS  += MainWindow.h \
    Observer.h \
    ObserverI.h \
    Subject.h \
    SubjectI.h

FORMS    += MainWindow.ui
