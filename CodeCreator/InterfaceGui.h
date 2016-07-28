#ifndef INTERFACEGUI_H
#define INTERFACEGUI_H

#include <QDialog>

#include "Interface.h"

class WidgetListEditor;

namespace Ui {
class InterfaceGui;
}

class InterfaceGui : public QDialog
{
  Q_OBJECT

public:
  explicit InterfaceGui(QWidget *parent = 0);
  ~InterfaceGui();

  void setInterface(const Interface& interface);
  Interface interface();

  void setToImplementAvailable(bool available);

private slots:
  void on_pushButtonMethods_clicked();
  void addMethod();
  void on_lineEditName_textEdited(const QString &name);
  void on_checkBox_clicked(bool checked);

private:
  void fillMethodList();

  Ui::InterfaceGui *ui;
  Interface m_interface;
  WidgetListEditor* m_widgetListEditor;
};

#endif // INTERFACEGUI_H
