#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>

#include "IGenerator.h"

class CodeGenerator;

namespace Ui {
class Interface;
}

class Interface : public QWidget, public IGenerator
{
  Q_OBJECT

public:
  explicit Interface(CodeGenerator* codeGenerator, QWidget *parent = 0);
  ~Interface();

  // IGenerator
  bool generate(const QString& folder);
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);

private:
  Ui::Interface *ui;

  CodeGenerator* m_codeGenerator;
};

#endif // INTERFACE_H
