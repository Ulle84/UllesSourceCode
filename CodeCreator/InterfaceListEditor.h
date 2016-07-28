#ifndef INTERFACELISTEDITOR_H
#define INTERFACELISTEDITOR_H

#include <QList>
#include <QWidget>

#include "Interface.h"

class WidgetListEditor;

namespace Ui
{
  class InterfaceListEditor;
}

class InterfaceListEditor : public QWidget
{
  Q_OBJECT

public:
  explicit InterfaceListEditor(QWidget *parent = 0);
  ~InterfaceListEditor();

  QList<Interface> interfaceList() const;
  void setInterfaceList(const QList<Interface>& interfaceList);

  void setText(const QString& text);

  void setToImplementAvailable(bool available);

signals:
  void interfaceListChanged();

private slots:
  void on_pushButtonInterfaceList_clicked();
  void addInterface();

private:
  void fillInterfaceList();

  Ui::InterfaceListEditor *ui;

  WidgetListEditor* m_widgetListEditor;
  QList<Interface> m_interfaceList;
  bool m_toImplementAvailable;
};

#endif // INTERFACELISTEDITOR_H
