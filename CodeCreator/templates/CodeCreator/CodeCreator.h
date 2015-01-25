#ifndef CODECREATOR_H
#define CODECREATOR_H

#include <QWidget>

#include "IGenerator.h"

class CodeGenerator;

namespace Ui {
class CodeCreator;
}

class CodeCreator : public QWidget, public IGenerator
{
  Q_OBJECT

public:
  explicit CodeCreator(CodeGenerator* codeGenerator, QWidget *parent = 0);
  ~CodeCreator();

  // IGenerator
  bool generate(const QString& folder);
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);

private:
  Ui::CodeCreator* ui;

  CodeGenerator* mCodeGenerator;
};

#endif // CODECREATOR_H
