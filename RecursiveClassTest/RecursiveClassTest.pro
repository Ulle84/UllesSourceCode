QT += core
QT -= gui

CONFIG += c++11

TARGET = RecursiveClassTest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    A.cpp

HEADERS += \
    A.h
