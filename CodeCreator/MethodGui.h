#ifndef METHODGUI_H
#define METHODGUI_H

#include <QWidget>

#include "Method.h"

class WidgetListEditor;

namespace Ui {
class MethodGui;
}

class MethodGui : public QWidget
{
  Q_OBJECT

public:
  explicit MethodGui(QWidget *parent = 0);
  ~MethodGui();

  void setMethod(const Method& method);
  Method method();

private slots:
  void on_comboBoxDeclarationType_currentIndexChanged(const QString &arg1);
  void on_comboBoxType_currentIndexChanged(const QString &arg1);
  void on_lineEditReturnType_textEdited(const QString &returnType);
  void on_lineEditName_textEdited(const QString &name);
  void on_pushButtonParameters_clicked();
  void addParameter();

private:
  Ui::MethodGui *ui;
  Method m_method;
  WidgetListEditor* m_widgetListEditor;
};

#endif // METHODGUI_H
