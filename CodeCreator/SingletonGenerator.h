#ifndef SINGLETONGENERATOR_H
#define SINGLETONGENERATOR_H

#include <QWidget>

#include "GeneratorIterface.h"

class CodeGenerator;

namespace Ui {
class SingletonGenerator;
}

class SingletonGenerator : public QWidget, public GeneratorInterface
{
  Q_OBJECT

public:
  explicit SingletonGenerator(CodeGenerator* codeGenerator, QWidget *parent = 0);
  ~SingletonGenerator();

  // GeneratorInterface
  void generate(const QString& folder);
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);

private:
  Ui::SingletonGenerator *ui;

  CodeGenerator* m_codeGenerator;
};

#endif // SINGLETONGENERATOR_H
