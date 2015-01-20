#-------------------------------------------------
#
# Project created by QtCreator 2015-01-20T14:05:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CodeCreator
TEMPLATE = app


SOURCES += main.cpp\
        CodeCreator.cpp \
    ClassGenerator.cpp \
    InterfaceGenerator.cpp \
    SingletonGenerator.cpp \
    CodeSaver.cpp \
    CodeGenerator.cpp \
    HeaderOptions.cpp

HEADERS  += CodeCreator.h \
    ClassGenerator.h \
    InterfaceGenerator.h \
    SingletonGenerator.h \
    CodeSaver.h \
    CodeGenerator.h \
    HeaderOptions.h

FORMS    += CodeCreator.ui \
    ClassGenerator.ui \
    InterfaceGenerator.ui \
    SingletonGenerator.ui
