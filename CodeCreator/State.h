#ifndef STATE_H
#define STATE_H

#include <QWidget>

#include "GeneratorI.h"

class CodeGenerator;

namespace Ui {
class State;
}

class State : public QWidget, public GeneratorI
{
  Q_OBJECT

public:
  explicit State(CodeGenerator* codeGenerator, QWidget *parent = 0);
  ~State();

  // GeneratorI
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
