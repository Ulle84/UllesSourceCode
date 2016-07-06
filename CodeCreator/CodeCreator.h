#ifndef CODECREATOR_H
#define CODECREATOR_H

#include <QMap>
#include <QWidget>
#include <QString>
#include <QSettings>

class CodeGenerator;
class Options;

namespace Ui
{
  class CodeCreator;
}

class CodeCreator : public QWidget
{
  Q_OBJECT

public:
  explicit CodeCreator(QWidget* parent = 0);
  ~CodeCreator();

private slots:
  void on_comboBoxType_currentIndexChanged(const QString& type);
  void on_pushButtonSelectFolder_clicked();
  void on_pushButtonStart_clicked();
  void on_pushButtonClearHistory_clicked();
  void on_pushButtonSelectTemplateFolder_clicked();

  void updatePreview();

private:
  bool readXml();
  bool writeXml();

  void updateComboBoxFolders();
  void initGenerators();

  Ui::CodeCreator* ui;
  QMap<QString, QWidget*> m_generators;
  QWidget* m_currentGenerator;
  QStringList m_directories;
  QString m_fileName;
  QSettings* m_settings;

  CodeGenerator* m_codeGenerator;
};

#endif // CODECREATOR_H
