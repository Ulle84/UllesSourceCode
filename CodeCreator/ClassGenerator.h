#ifndef CLASSGENERATOR_H
#define CLASSGENERATOR_H

#include <QWidget>
#include <QtCore/QStringList>

class CodeSaver;
class CodeGenerator;

namespace Ui
{
class ClassGenerator;
}

class ClassGenerator : public QWidget
{
  Q_OBJECT

public:
  explicit ClassGenerator(CodeSaver* codeSaver, CodeGenerator* codeGenerator, QWidget* parent = 0);
  ~ClassGenerator();

private slots:
  void on_pushButtonSelectFolder_clicked();
  void on_pushButtonStart_clicked();
  void on_pushButtonClearHistory_clicked();
  void on_checkBoxInherit_toggled(bool checked);

private:
  void updateComboBoxFolders();
  QStringList generateCodeHeader();
  QStringList generateCodeClass();
  QStringList generateCodePimpl();

  Ui::ClassGenerator* ui;
  QStringList m_directories;
  QString m_fileName;
  QString m_className;

  CodeSaver* m_codeSaver;
  CodeGenerator* m_codeGenerator;

  bool fromXml();
  bool toXml();
};

#endif // CLASSGENERATOR_H
