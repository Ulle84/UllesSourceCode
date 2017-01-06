#-------------------------------------------------
#
# Project created by QtCreator 2017-01-04T20:38:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleHtml
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Converter.cpp \
    Viewer.cpp \
    Editor.cpp \
    Attribute.cpp \
    Highlighter.cpp

HEADERS  += MainWindow.h \
    Converter.h \
    Viewer.h \
    Editor.h \
    Attribute.h \
    Highlighter.h

FORMS    += MainWindow.ui

DISTFILES += \
    Notes.md
