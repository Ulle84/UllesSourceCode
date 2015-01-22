#ifndef OBSERVER_H
#define OBSERVER_H

#include <QWidget>

#include "GeneratorIterface.h"

class CodeGenerator;

namespace Ui {
class Observer;
}

class Observer : public QWidget, public GeneratorInterface
{
  Q_OBJECT

public:
  explicit Observer(CodeGenerator* codeGenerator, QWidget *parent = 0);
  ~Observer();

  // GeneratorIterface
  void generate(const QString& folder);
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);

private:
  Ui::Observer *ui;

  CodeGenerator* m_codeGenerator;
};

#endif // OBSERVER_H