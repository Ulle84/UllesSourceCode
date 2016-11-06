#-------------------------------------------------
#
# Project created by QtCreator 2016-11-05T19:39:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PhoneBook
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp\
        ProxyModel.cpp\
    PhoneBook.cpp \
    PhoneBookEntry.cpp

HEADERS  += MainWindow.h\
         ProxyModel.h\
    PhoneBook.h \
    PhoneBookEntry.h

FORMS    += MainWindow.ui
