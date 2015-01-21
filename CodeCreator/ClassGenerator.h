#ifndef CLASSGENERATOR_H
#define CLASSGENERATOR_H

#include <QWidget>
#include <QtCore/QStringList>

class CodeGenerator;

namespace Ui
{
class ClassGenerator;
}

class ClassGenerator : public QWidget
{
  Q_OBJECT

public:
  explicit ClassGenerator(CodeGenerator* codeGenerator, QWidget* parent = 0);
  ~ClassGenerator();

private slots:
  void on_pushButtonSelectFolder_clicked();
  void on_pushButtonStart_clicked();
  void on_pushButtonClearHistory_clicked();
  void on_checkBoxInherit_toggled(bool checked);

private:
  void updateComboBoxFolders();

  Ui::ClassGenerator* ui;
  QStringList m_directories;
  QString m_fileName;

  CodeGenerator* m_codeGenerator;

  bool fromXml();
  bool toXml();
};

#endif // CLASSGENERATOR_H
