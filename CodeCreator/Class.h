#ifndef CLASS_H
#define CLASS_H

#include <QWidget>

#include "IGenerator.h"

class QCompleter;
class CodeGenerator;

namespace Ui {
class Class;
}

class Class : public QWidget, public IGenerator
{
  Q_OBJECT

public:
  explicit Class(CodeGenerator* codeGenerator, QWidget *parent = 0);
  ~Class();

  // IGenerator
  bool generate(const QString& folder);
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);

private slots:
  void on_checkBoxInherit_toggled(bool checked);
  void on_lineEditBaseClass_textEdited(const QString &text);

private:
  Ui::Class* ui;

  CodeGenerator* mCodeGenerator;
  QCompleter* mCompleter;
};

#endif // CLASS_H
