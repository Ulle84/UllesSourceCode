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
    XmlHelper.cpp \
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
    Member.cpp \
    MemberGui.cpp \
    Members.cpp \
    GeneratorTemplate.cpp \
    GeneratorDecorator.cpp \
    StringHelper.cpp \
    GeneratorObserver.cpp \
    GeneratorState.cpp \
    Declaration.cpp \
    Declarations.cpp \
    InterfaceEditor.cpp

HEADERS  += CodeCreator.h \
    XmlHelper.h \
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
    Member.h \
    MemberGui.h \
    Members.h \
    GeneratorTemplate.h \
    GeneratorDecorator.h \
    StringHelper.h \
    GeneratorObserver.h \
    GeneratorState.h \
    Declaration.h \
    Declarations.h \
    InterfaceEditor.h

FORMS    += CodeCreator.ui \
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
    MemberGui.ui \
    GeneratorTemplate.ui \
    GeneratorDecorator.ui \
    GeneratorObserver.ui \
    GeneratorState.ui \
    InterfaceEditor.ui

OTHER_FILES += \
    ToDo.txt \
    Bugs.txt \
    Ideas.txt \
    Notes.md

DISTFILES += \
    Notes.md

RESOURCES += \
    Resources.qrc
