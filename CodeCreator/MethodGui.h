#ifndef METHODGUI_H
#define METHODGUI_H

#include <QWidget>

class Method;

namespace Ui {
class MethodGui;
}

class MethodGui : public QWidget
{
  Q_OBJECT

public:
  explicit MethodGui(Method* method, QWidget *parent = 0);
  ~MethodGui();

private slots:
  void on_comboBoxDeclarationType_currentIndexChanged(const QString &arg1);
  void on_comboBoxType_currentIndexChanged(const QString &arg1);
  void on_lineEditReturnType_textEdited(const QString &returnType);
  void on_lineEditName_textEdited(const QString &name);
  void on_pushButtonParameters_clicked();

private:
  Ui::MethodGui *ui;
  Method* m_method;
};

#endif // METHODGUI_H
