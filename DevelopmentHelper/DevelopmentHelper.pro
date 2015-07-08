#-------------------------------------------------
#
# Project created by QtCreator 2015-07-02T17:00:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DevelopmentHelper
TEMPLATE = app


SOURCES += main.cpp\
        DevelopmentHelper.cpp \
    StashHelper.cpp \
    LogFileViewer.cpp \
    CodeAssistant.cpp \
    ConverterBase64.cpp \
    DateTimeHelper.cpp \
    HtmlTableGenerator.cpp \
    CryptoHelper.cpp \
    ClipboardManager.cpp

HEADERS  += DevelopmentHelper.h \
    StashHelper.h \
    LogFileViewer.h \
    CodeAssistant.h \
    ConverterBase64.h \
    DateTimeHelper.h \
    HtmlTableGenerator.h \
    CryptoHelper.h \
    ClipboardManager.h

FORMS    += DevelopmentHelper.ui \
    StashHelper.ui \
    LogFileViewer.ui \
    CodeAssistant.ui \
    ConverterBase64.ui \
    DateTimeHelper.ui \
    HtmlTableGenerator.ui \
    CryptoHelper.ui \
    ClipboardManager.ui
