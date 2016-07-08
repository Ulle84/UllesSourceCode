#ifndef DATA_H
#define DATA_H

#include <QWidget>

#include "GeneratorIOld.h"

class CodeGenerator;

namespace Ui {
class Data;
}

class Data : public QWidget, public GeneratorIOld
{
  Q_OBJECT

public:
  explicit Data(CodeGenerator* codeGenerator, QWidget *parent = 0);
  ~Data();

  // GeneratorIOld
  bool generate(const QString& folder);
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);

private:
  Ui::Data* ui;

  CodeGenerator* mCodeGenerator;
};

#endif // DATA_H
