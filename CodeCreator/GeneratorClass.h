#ifndef GENERATORCLASS_H
#define GENERATORCLASS_H

#include <QWidget>

#include "GeneratorI.h"

class QCompleter;
class CodeGenerator;

namespace Ui {
class GeneratorClass;
}

class GeneratorClass : public QWidget, public GeneratorI
{
  Q_OBJECT

public:
  explicit GeneratorClass(CodeGenerator* codeGenerator, QWidget *parent = 0);
  ~GeneratorClass();

  // GeneratorI
  bool generate(const QString& folder);
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);

private slots:
  void on_checkBoxInherit_toggled(bool checked);
  void on_lineEditBaseClass_textEdited(const QString &text);

private:
  Ui::GeneratorClass* ui;

  CodeGenerator* mCodeGenerator;
  QCompleter* mCompleter;
};

#endif // GENERATORCLASS_H
