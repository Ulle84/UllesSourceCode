QT += core
QT -= gui

CONFIG += c++11

TARGET = CodeCleaner
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += mainConsole.cpp \
    CodeCleaner.cpp \
    Options.cpp

HEADERS += \
    CodeCleaner.h \
    Options.h

DISTFILES += \
    Notes.md

RESOURCES +=
