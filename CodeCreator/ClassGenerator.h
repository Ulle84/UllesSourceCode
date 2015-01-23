#ifndef CLASSGENERATOR_H
#define CLASSGENERATOR_H

#include <QWidget>
#include <QtCore/QStringList>

#include "IGenerator.h"

class CodeGenerator;

namespace Ui
{
class ClassGenerator;
}

class ClassGenerator : public QWidget, public IGenerator
{
  Q_OBJECT

public:
  explicit ClassGenerator(CodeGenerator* codeGenerator, QWidget* parent = 0);
  ~ClassGenerator();

  // IGenerator
  void generate(const QString& folder);
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);

private slots:
  void on_checkBoxInherit_toggled(bool checked);
  void on_checkBoxSingleton_toggled(bool checked);

private:
  Ui::ClassGenerator* ui;
  QStringList mDirectories;
  QString mFileName;

  CodeGenerator* mCodeGenerator;
};

#endif // CLASSGENERATOR_H
