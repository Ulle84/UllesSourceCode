#ifndef OBSERVER_H
#define OBSERVER_H

#include <QWidget>

#include "GeneratorIOld.h"

class CodeGenerator;

namespace Ui {
class Observer;
}

class Observer : public QWidget, public GeneratorIOld
{
  Q_OBJECT

public:
  explicit Observer(CodeGenerator* codeGenerator, QWidget *parent = 0);
  ~Observer();

  // GeneratorIOld
  bool generate(const QString& folder);
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);

private:
  Ui::Observer *ui;

  CodeGenerator* mCodeGenerator;
};

#endif // OBSERVER_H
