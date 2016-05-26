#ifndef GENERATORINTERFACE_H
#define GENERATORINTERFACE_H

#include <QWidget>

#include "IGenerator.h"

class CodeGenerator;

namespace Ui {
class GeneratorInterface;
}

class GeneratorInterface : public QWidget, public IGenerator
{
  Q_OBJECT

public:
  explicit GeneratorInterface(CodeGenerator* codeGenerator, QWidget *parent = 0);
  ~GeneratorInterface();

  // IGenerator
  bool generate(const QString& folder);
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);

private:
  Ui::GeneratorInterface* ui;

  CodeGenerator* m_codeGenerator;
};

#endif // GENERATORINTERFACE_H
