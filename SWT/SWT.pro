#-------------------------------------------------
#
# Project created by QtCreator 2013-11-21T19:46:58
#
#-------------------------------------------------

QT       += core gui webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SWT
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    TextEditor.cpp \
    WebSitePreview.cpp

HEADERS  += MainWindow.h \
    TextEditor.h \
    WebSitePreview.h

FORMS    += MainWindow.ui \
    TextEditor.ui \
    WebSitePreview.ui
