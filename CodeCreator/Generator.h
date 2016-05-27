#ifndef GENERATOR_H
#define GENERATOR_H

#include <QWidget>

#include "GeneratorI.h"

class CodeGenerator;

namespace Ui {
class Generator;
}

class Generator : public QWidget, public GeneratorI
{
  Q_OBJECT

public:
  explicit Generator(CodeGenerator* codeGenerator, QWidget *parent = 0);
  ~Generator();

  // GeneratorI
  bool generate(const QString& folder);
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);

private:
  Ui::Generator *ui;

  CodeGenerator* mCodeGenerator;
};

#endif // GENERATOR_H
