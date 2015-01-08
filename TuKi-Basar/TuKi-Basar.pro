#-------------------------------------------------
#
# Project created by QtCreator 2014-12-06T14:07:10
#
#-------------------------------------------------

QT       += core gui webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TuKi-Basar
TEMPLATE = app


SOURCES += main.cpp\
        TuKiBasar.cpp \
    Evaluation.cpp \
    Settings.cpp \
    Article.cpp \
    ArticleManager.cpp \
    PrizeCorrection.cpp

HEADERS  += TuKiBasar.h \
    Evaluation.h \
    Settings.h \
    Article.h \
    ArticleManager.h \
    PrizeCorrection.h

FORMS    += TuKiBasar.ui \
    Evaluation.ui \
    Settings.ui \
    PrizeCorrection.ui
