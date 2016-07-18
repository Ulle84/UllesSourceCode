#ifndef INTERFACEEDITOR_H
#define INTERFACEEDITOR_H

#include <QWidget>

#include "Interface.h"

class WidgetListEditor;

namespace Ui
{
  class InterfaceEditor;
}

class InterfaceEditor : public QWidget
{
  Q_OBJECT

public:
  explicit InterfaceEditor(QWidget *parent = 0);
  ~InterfaceEditor();

  Interface interface() const;
  void setInterface(const Interface& interface);

  void setText(const QString& text);

signals:
  void interfaceChanged();

private slots:
  void on_pushButtonInterface_clicked();
  void addMethod();

private:
  void fillMethodList();

  Ui::InterfaceEditor *ui;

  WidgetListEditor* m_widgetListEditor;
  Interface m_interface;
};

#endif // INTERFACEEDITOR_H
