#ifndef GENERATOR_H
#define GENERATOR_H

#include <QWidget>

#include "GeneratorIterface.h"

class CodeGenerator;

namespace Ui {
class Generator;
}

class Generator : public QWidget, public GeneratorInterface
{
  Q_OBJECT

public:
  explicit Generator(CodeGenerator* codeGenerator, QWidget *parent = 0);
  ~Generator();

  // GeneratorIterface
  void generate(const QString& folder);
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);

private:
  Ui::Generator *ui;

  CodeGenerator* m_codeGenerator;
};

#endif // GENERATOR_H
