CONFIG      += designer plugin debug_and_release
TARGET      = $$qtLibraryTarget(customwidgetsplugin)
TEMPLATE    = lib

HEADERS     = doublebuttonplugin.h smalltestplugin.h customwidgets.h
SOURCES     = doublebuttonplugin.cpp smalltestplugin.cpp customwidgets.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(smalltest.pri)
include(doublebutton.pri)
