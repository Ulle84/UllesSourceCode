#ifndef CODECREATOR_H
#define CODECREATOR_H

#include <QWidget>

#include "GeneratorIterface.h"

class CodeGenerator;

namespace Ui {
class CodeCreator;
}

class CodeCreator : public QWidget, public GeneratorInterface
{
  Q_OBJECT

public:
  explicit CodeCreator(CodeGenerator* codeGenerator, QWidget *parent = 0);
  ~CodeCreator();

  // GeneratorIterface
  void generate(const QString& folder);
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);

private:
  Ui::CodeCreator *ui;

  CodeGenerator* m_codeGenerator;
};

#endif // CODECREATOR_H
