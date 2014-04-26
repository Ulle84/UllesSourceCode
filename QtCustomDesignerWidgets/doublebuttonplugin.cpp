#include "doublebutton.h"
#include "doublebuttonplugin.h"

#include <QtPlugin>

DoubleButtonPlugin::DoubleButtonPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void DoubleButtonPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;
    
    // Add extension registrations, etc. here
    
    m_initialized = true;
}

bool DoubleButtonPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *DoubleButtonPlugin::createWidget(QWidget *parent)
{
    return new DoubleButton(parent);
}

QString DoubleButtonPlugin::name() const
{
    return QLatin1String("DoubleButton");
}

QString DoubleButtonPlugin::group() const
{
    return QLatin1String("");
}

QIcon DoubleButtonPlugin::icon() const
{
    return QIcon();
}

QString DoubleButtonPlugin::toolTip() const
{
    return QLatin1String("");
}

QString DoubleButtonPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool DoubleButtonPlugin::isContainer() const
{
    return false;
}

QString DoubleButtonPlugin::domXml() const
{
    return QLatin1String("<widget class=\"DoubleButton\" name=\"doubleButton\">\n</widget>\n");
}

QString DoubleButtonPlugin::includeFile() const
{
    return QLatin1String("doublebutton.h");
}

