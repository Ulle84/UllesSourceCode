#ifndef STATE_H
#define STATE_H

#include <QWidget>

#include "IGenerator.h"

class CodeGenerator;

namespace Ui {
class State;
}

class State : public QWidget, public IGenerator
{
  Q_OBJECT

public:
  explicit State(CodeGenerator* codeGenerator, QWidget *parent = 0);
  ~State();

  // IGenerator
  bool generate(const QString& folder);
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);

private slots:
  void on_checkBoxContext_toggled(bool checked);

  void on_checkBoxState_toggled(bool checked);

  void on_checkBoxStateInterface_toggled(bool checked);

private:
  Ui::State* ui;

  CodeGenerator* mCodeGenerator;
};

#endif // STATE_H
