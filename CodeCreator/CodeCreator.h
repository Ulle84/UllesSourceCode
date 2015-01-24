#ifndef CODECREATOR_H
#define CODECREATOR_H

#include <QMap>
#include <QWidget>
#include <QString>

class CodeGenerator;
class Options;

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
  void on_pushButtonSelectFolder_clicked();
  void on_pushButtonStart_clicked();
  void on_pushButtonClearHistory_clicked();

private:
  bool readXml();
  bool writeXml();

  void updateComboBoxFolders();
  void initGenerators();

  Ui::CodeCreator *ui;
  QMap<QString, QWidget*> mGenerators;
  QWidget* mCurrentGenerator;
  QStringList mDirectories;
  QString mFileName;

  CodeGenerator* mCodeGenerator;
};

#endif // CODECREATOR_H
