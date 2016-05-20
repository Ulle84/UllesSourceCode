#-------------------------------------------------
#
# Project created by QtCreator 2016-05-20T07:22:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CodeCleanerGui
TEMPLATE = app


SOURCES += mainGui.cpp\
        CodeCleanerGui.cpp \
    CodeCleaner.cpp

HEADERS  += CodeCleanerGui.h \
    CodeCleaner.h

FORMS    += CodeCleanerGui.ui

DISTFILES += \
    Notes.md
