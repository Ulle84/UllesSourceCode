#include "doublebuttonplugin.h"
#include "smalltestplugin.h"
#include "customwidgets.h"

CustomWidgets::CustomWidgets(QObject *parent)
    : QObject(parent)
{
    m_widgets.append(new DoubleButtonPlugin(this));
    m_widgets.append(new SmallTestPlugin(this));
    
}

QList<QDesignerCustomWidgetInterface*> CustomWidgets::customWidgets() const
{
    return m_widgets;
}

Q_EXPORT_PLUGIN2(customwidgetsplugin, CustomWidgets)
