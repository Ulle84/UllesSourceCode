#ifndef CLASSADVANCED_H
#define CLASSADVANCED_H

#include <QWidget>

#include "IGenerator.h"

class CodeGenerator;

namespace Ui {
class ClassAdvanced;
}

class ClassAdvanced : public QWidget, public IGenerator
{
  Q_OBJECT

public:
  explicit ClassAdvanced(CodeGenerator* codeGenerator, QWidget *parent = 0);
  ~ClassAdvanced();

  // IGenerator
  bool generate(const QString& folder);
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);

private:
  Ui::ClassAdvanced* ui;

  CodeGenerator* mCodeGenerator;
};

#endif // CLASSADVANCED_H