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
    CodeGenerator.cpp \
    Generator.cpp \
    Observer.cpp \
    ClassGenerator.cpp \
    Interface.cpp

HEADERS  += CodeCreator.h \
    CodeGenerator.h \
    Generator.h \
    Observer.h \
    IGenerator.h \
    ClassGenerator.h \
    Options.h \
    OptionsTemplate.h \
    Interface.h

FORMS    += CodeCreator.ui \
    ClassGenerator.ui \
    Generator.ui \
    Observer.ui \
    Interface.ui
