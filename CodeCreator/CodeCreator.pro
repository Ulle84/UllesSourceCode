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
    Data.cpp \
    Decorator.cpp \
    XmlHelper.cpp \
    InterfaceHelper.cpp \
    State.cpp \
    Options.cpp \
    Parameter.cpp \
    GeneratorInterface.cpp \
    Interface.cpp \
    GeneratorClass.cpp \
    Class.cpp \
    SelectorDeclarationType.cpp \
    SelectorDPointerType.cpp \
    SelectorSingletonType.cpp \
    ParameterGui.cpp \
    Method.cpp \
    MethodGui.cpp \
    WidgetListEditor.cpp \
    WidgetListItem.cpp \
    InterfaceGui.cpp \
    GeneratorData.cpp \
    Member.cpp \
    MemberGui.cpp

HEADERS  += CodeCreator.h \
    CodeGenerator.h \
    Generator.h \
    Observer.h \
    Options.h \
    Data.h \
    Decorator.h \
    XmlHelper.h \
    InterfaceHelper.h \
    State.h \
    Parameter.h \
    GeneratorInterface.h \
    Interface.h \
    GeneratorClass.h \
    Class.h \
    GeneratorI.h \
    SelectorDeclarationType.h \
    SelectorDPointerType.h \
    SelectorSingletonType.h \
    ParameterGui.h \
    Method.h \
    MethodGui.h \
    WidgetListEditor.h \
    WidgetListItem.h \
    InterfaceGui.h \
    GeneratorIOld.h \
    GeneratorData.h \
    Member.h \
    MemberGui.h

FORMS    += CodeCreator.ui \
    Generator.ui \
    Observer.ui \
    Data.ui \
    Decorator.ui \
    State.ui \
    GeneratorInterface.ui \
    GeneratorClass.ui \
    SelectorDeclarationType.ui \
    SelectorDPointerType.ui \
    SelectorSingletonType.ui \
    ParameterGui.ui \
    MethodGui.ui \
    WidgetListEditor.ui \
    WidgetListItem.ui \
    InterfaceGui.ui \
    GeneratorData.ui \
    MemberGui.ui

OTHER_FILES += \
    ToDo.txt \
    Bugs.txt \
    Ideas.txt \
    Notes.md

DISTFILES += \
    Notes.md
