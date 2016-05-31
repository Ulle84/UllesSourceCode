#ifndef INTERFACEGUI_H
#define INTERFACEGUI_H

#include <QDialog>

class Interface;
class WidgetListEditor;

namespace Ui {
class InterfaceGui;
}

class InterfaceGui : public QDialog
{
  Q_OBJECT

public:
  explicit InterfaceGui(Interface* interface, QWidget *parent = 0);
  ~InterfaceGui();

private slots:
  void on_pushButtonMethods_clicked();
  void addMethod();

  void on_lineEditName_textEdited(const QString &name);

private:
  Ui::InterfaceGui *ui;
  Interface* m_interface;
  WidgetListEditor* m_widgetListEditor;
};

#endif // INTERFACEGUI_H
