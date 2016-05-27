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
    Singleton.cpp \
    Data.cpp \
    Decorator.cpp \
    XmlHelper.cpp \
    InterfaceHelper.cpp \
    State.cpp \
    Options.cpp \
    ClassAdvanced.cpp \
    Parameter.cpp \
    Function.cpp \
    GeneratorInterface.cpp \
    Interface.cpp \
    GeneratorClass.cpp \
    Class.cpp \
    Method.cpp

HEADERS  += CodeCreator.h \
    CodeGenerator.h \
    Generator.h \
    Observer.h \
    Singleton.h \
    Options.h \
    Data.h \
    Decorator.h \
    XmlHelper.h \
    InterfaceHelper.h \
    State.h \
    ClassAdvanced.h \
    Parameter.h \
    Function.h \
    GeneratorInterface.h \
    Interface.h \
    GeneratorClass.h \
    Class.h \
    Method.h \
    GeneratorI.h

FORMS    += CodeCreator.ui \
    Generator.ui \
    Observer.ui \
    Singleton.ui \
    Data.ui \
    Decorator.ui \
    State.ui \
    ClassAdvanced.ui \
    GeneratorInterface.ui \
    GeneratorClass.ui

OTHER_FILES += \
    ToDo.txt \
    Bugs.txt \
    Ideas.txt \
    Notes.md

DISTFILES += \
    Notes.md
