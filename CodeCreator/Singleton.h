#ifndef SINGLETON_H
#define SINGLETON_H

#include <QWidget>

#include "IGenerator.h"

class CodeGenerator;

namespace Ui {
class Singleton;
}

class Singleton : public QWidget, public IGenerator
{
  Q_OBJECT

public:
  explicit Singleton(CodeGenerator* codeGenerator, QWidget *parent = 0);
  ~Singleton();

  // IGenerator
  bool generate(const QString& folder);
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);

private:
  Ui::Singleton* ui;

  CodeGenerator* m_codeGenerator;
};

#endif // SINGLETON_H
