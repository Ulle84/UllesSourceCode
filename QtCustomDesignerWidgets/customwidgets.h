#ifndef CUSTOMWIDGETS_H
#define CUSTOMWIDGETS_H

#include <QtDesigner>
#include <qplugin.h>

class CustomWidgets : public QObject, public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
    
public:
    explicit CustomWidgets(QObject *parent = 0);
    
    virtual QList<QDesignerCustomWidgetInterface*> customWidgets() const;
    
private:
    QList<QDesignerCustomWidgetInterface*> m_widgets;
};

#endif
