#ifndef CODECREATOR_H
#define CODECREATOR_H

#include <map>

#include <QWidget>
#include <QString>

class CodeGenerator;

namespace Ui {
class CodeCreator;
}

class CodeCreator : public QWidget
{
  Q_OBJECT

public:
  explicit CodeCreator(QWidget *parent = 0);
  ~CodeCreator();

private slots:
  void on_comboBoxType_currentIndexChanged(const QString &type);

private:
  void initGenerators();

  Ui::CodeCreator *ui;
  std::map<QString, QWidget*> m_generators;
  QWidget* m_currentGenerator;

  CodeGenerator* m_codeGenerator;
};

#endif // CODECREATOR_H
