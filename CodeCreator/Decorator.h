#ifndef DECORATOR_H
#define DECORATOR_H

#include <QWidget>

#include "IGenerator.h"

class CodeGenerator;

namespace Ui {
class Decorator;
}

class Decorator : public QWidget, public IGenerator
{
  Q_OBJECT

public:
  explicit Decorator(CodeGenerator* codeGenerator, QWidget *parent = 0);
  ~Decorator();

  // IGenerator
  bool generate(const QString& folder);
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);

private slots:
  void on_checkBoxDecorator_toggled(bool checked);

  void on_checkBoxComponent_toggled(bool checked);

  void on_checkBoxInterface_toggled(bool checked);

private:
  Ui::Decorator* ui;

  CodeGenerator* mCodeGenerator;
};

#endif // DECORATOR_H
