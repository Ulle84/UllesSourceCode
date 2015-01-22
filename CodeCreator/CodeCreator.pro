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
    InterfaceGenerator.cpp \
    CodeGenerator.cpp \
    Options.cpp \
    Generator.cpp \
    Observer.cpp \
    ClassGenerator.cpp

HEADERS  += CodeCreator.h \
    InterfaceGenerator.h \
    CodeGenerator.h \
    Options.h \
    GeneratorIterface.h \
    Generator.h \
    Observer.h \
    ClassGenerator.h

FORMS    += CodeCreator.ui \
    ClassGenerator.ui \
    InterfaceGenerator.ui \
    Generator.ui \
    Observer.ui
