#include "smalltest.h"
#include "smalltestplugin.h"

#include <QtPlugin>

SmallTestPlugin::SmallTestPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void SmallTestPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;
    
    // Add extension registrations, etc. here
    
    m_initialized = true;
}

bool SmallTestPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *SmallTestPlugin::createWidget(QWidget *parent)
{
    return new SmallTest(parent);
}

QString SmallTestPlugin::name() const
{
    return QLatin1String("SmallTest");
}

QString SmallTestPlugin::group() const
{
    return QLatin1String("");
}

QIcon SmallTestPlugin::icon() const
{
    return QIcon();
}

QString SmallTestPlugin::toolTip() const
{
    return QLatin1String("");
}

QString SmallTestPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool SmallTestPlugin::isContainer() const
{
    return false;
}

QString SmallTestPlugin::domXml() const
{
    return QLatin1String("<widget class=\"SmallTest\" name=\"smallTest\">\n</widget>\n");
}

QString SmallTestPlugin::includeFile() const
{
    return QLatin1String("smalltest.h");
}

