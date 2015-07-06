#ifndef LOGFILEVIEWER_H
#define LOGFILEVIEWER_H

#include <QDir>
#include <QStringList>
#include <QWidget>

class QSettings;
class QRegExp;

namespace Ui {
class LogFileViewer;
}

class LogFileViewer : public QWidget
{
  Q_OBJECT

public:
  explicit LogFileViewer(QWidget* parent = 0);
  ~LogFileViewer();

private slots:
  void on_pushButtonOpenFiles_clicked();
  void on_pushButtonCombineFiles_clicked();

private:
  bool readFilesAndMerge();
  void updateDir(const QString& fileName);
  bool readFile(const QString& fileName);

  Ui::LogFileViewer* ui;
  QStringList m_mergedFileContent;
  QSettings* m_settings;
  QDir m_dir;
  QRegExp* m_regExp;
};

#endif // LOGFILEVIEWER_H
