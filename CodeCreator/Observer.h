#ifndef OBSERVER_H
#define OBSERVER_H

#include <QWidget>

#include "GeneratorI.h"

class CodeGenerator;

namespace Ui {
class Observer;
}

class Observer : public QWidget, public GeneratorI
{
  Q_OBJECT

public:
  explicit Observer(CodeGenerator* codeGenerator, QWidget *parent = 0);
  ~Observer();

  // GeneratorI
  bool generate(const QString& folder);
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);

private:
  Ui::Observer *ui;

  CodeGenerator* mCodeGenerator;
};

#endif // OBSERVER_H
