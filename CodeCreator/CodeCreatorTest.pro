QT += core
QT -= gui

CONFIG += c++11

TARGET = CodeCreatorTest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += mainTest.cpp\
        Test.cpp

HEADERS  += Test.h