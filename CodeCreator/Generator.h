#ifndef GENERATOR_H
#define GENERATOR_H

#include <QWidget>

#include "IGenerator.h"

class CodeGenerator;

namespace Ui {
class Generator;
}

class Generator : public QWidget, public IGenerator
{
  Q_OBJECT

public:
  explicit Generator(CodeGenerator* codeGenerator, QWidget *parent = 0);
  ~Generator();

  // IGenerator
  void generate(const QString& folder);
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);

private:
  Ui::Generator *ui;

  CodeGenerator* mCodeGenerator;
};

#endif // GENERATOR_H
