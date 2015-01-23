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
    Interface.cpp \
    Singleton.cpp \
    Class.cpp

HEADERS  += CodeCreator.h \
    CodeGenerator.h \
    Generator.h \
    Observer.h \
    IGenerator.h \
    Interface.h \
    Singleton.h \
    Class.h \
    Options.h

FORMS    += CodeCreator.ui \
    Generator.ui \
    Observer.ui \
    Interface.ui \
    Singleton.ui \
    Class.ui
