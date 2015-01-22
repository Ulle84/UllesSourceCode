#ifndef CLASSGENERATOR_H
#define CLASSGENERATOR_H

#include <QWidget>
#include <QtCore/QStringList>

#include "GeneratorIterface.h"

class CodeGenerator;

namespace Ui
{
class ClassGenerator;
}

class ClassGenerator : public QWidget, public GeneratorInterface
{
  Q_OBJECT

public:
  explicit ClassGenerator(CodeGenerator* codeGenerator, QWidget* parent = 0);
  ~ClassGenerator();

  // GeneratorInterface
  void generate(const QString& folder);
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);

private slots:
  void on_checkBoxInherit_toggled(bool checked);
  void on_checkBoxSingleton_toggled(bool checked);

private:
  Ui::ClassGenerator* ui;
  QStringList m_directories;
  QString m_fileName;

  CodeGenerator* m_codeGenerator;
};

#endif // CLASSGENERATOR_H
