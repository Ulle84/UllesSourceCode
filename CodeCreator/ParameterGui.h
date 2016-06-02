#ifndef PARAMETERGUI_H
#define PARAMETERGUI_H

#include "Parameter.h"

#include <QWidget>

namespace Ui {
class ParameterGui;
}

class ParameterGui : public QWidget
{
  Q_OBJECT

public:
  explicit ParameterGui(QWidget *parent = 0);
  ~ParameterGui();

  void setParameter(const Parameter& parameter);
  Parameter parameter();

private slots:
  void on_lineEditType_textEdited(const QString &type);
  void on_lineEditName_textEdited(const QString &name);
  void on_lineEditDefaultValue_textEdited(const QString &defaultValue);

private:
  Ui::ParameterGui *ui;

  Parameter m_parameter;
};

#endif // PARAMETERGUI_H
