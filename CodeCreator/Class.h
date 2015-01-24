#ifndef CLASS_H
#define CLASS_H

#include <QWidget>

#include "IGenerator.h"

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
  void generate(const QString& folder);
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);

private slots:
  void on_checkBoxInherit_toggled(bool checked);

  void on_pushButtonClearHistory_clicked();

private:
  Ui::Class* ui;

  CodeGenerator* m_codeGenerator;
};

#endif // CLASS_H
