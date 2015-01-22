#ifndef INTERFACEGENERATOR_H
#define INTERFACEGENERATOR_H

#include <QWidget>

#include "GeneratorIterface.h"

class CodeGenerator;

namespace Ui {
class InterfaceGenerator;
}

class InterfaceGenerator : public QWidget, public GeneratorInterface
{
  Q_OBJECT

public:
  explicit InterfaceGenerator(CodeGenerator* codeGenerator, QWidget *parent = 0);
  ~InterfaceGenerator();

  // GeneratorInterface
  void generate(const QString& folder);
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);

private slots:
  void on_checkBoxPrefix_toggled(bool checked);

  void on_checkBoxPostfix_toggled(bool checked);

private:
  Ui::InterfaceGenerator *ui;

  CodeGenerator* m_codeGenerator;
};

#endif // INTERFACEGENERATOR_H
